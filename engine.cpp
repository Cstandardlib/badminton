#include "engine.h"
#include "game.h"

#include <QtMath>

// 设置场地参数，重力加速度和空气阻力
void CCourt::reset(double g, double f){
    ACCELERATION_OF_GRAVITY=g;
    RESISTANCE_COEFFICIENT=f;
}

double CCourt::ACCELERATION_OF_GRAVITY=-20.0;
double CCourt::RESISTANCE_COEFFICIENT=0.99211;


//------------------------
// class CPlayer

void CPlayer::init(qreal vx, qreal vy, qreal strength)
{
    speedx = vx; speedy = vy;
    strength_HitBallSpeed = strength;
    on_ground = true;
    set_y(PLAYER_HEIGHT);
    set_vx(0.0);
    set_vy(0.0);
    set_acceleration(0.0,0.0);
}

void CPlayer::start_moving(enum eDirectionType direction)
{
    if(CPlayer::PLAYER_MOVING_LEFT == direction) speed.setX(-speedx);
    else if(CPlayer::PLAYER_MOVING_RIGHT== direction) speed.setX(speedx);
}

// 水平置0
void CPlayer::stop_moving(){
    speed.setX(0.0);
}

// 如果在地面，起跳
bool CPlayer::jump(){
    if(!on_ground) return false;
    on_ground = false;
    speed.setY(speedy);
    acceleration.setY(CCourt::ACCELERATION_OF_GRAVITY);
    return true;
}
// 落地
void CPlayer::land()
{
    if(on_ground) return;
    on_ground = true;
    set_y(PLAYER_HEIGHT);
    speed.setY(0.0);
    acceleration.setY(0.0);
}

//------------------------
// class CRacket

// 按键触发：开始挥拍，如果正在挥拍则什么也不干
// 停止挥拍：由swing函数判断和修改
void CRacket::set_racket_pos(enum eRacketPosition _racket_Position)
{
    if(is_swinging()) return;
    racket_pos = _racket_Position;
    if(RACKET_HIGH_POS == racket_pos) angle_to_horizontal = get_init_angle_high();
    if(RACKET_LOW_POS == racket_pos) angle_to_horizontal = get_init_angle_low();
}

bool CRacket::start_swing()
{
    if(swinging) return false;
    swinging = true;
    hitted = false;
    gocnt_swing = CGame::TOTALCNT_single_swing;
    backcnt_swing = CGame::TOTALCNT_single_swing;
    return true;
}
// 
void CRacket::swing()
{
    if(false == this->is_swinging()) return; // 不在挥拍
    if(this->gocnt_swing > 0){
        // 正在挥拍
        gocnt_swing--;
        // racket_pos = -1 HIGH   1 LOW
        // racket_side = 1 LEFT  -1 RIGHT
        this->angle_to_horizontal += this->racket_side * this->racket_pos * SWING_SPEED;
    }
    else if (this->backcnt_swing > 0){
        // 正在复位
        backcnt_swing--;
        this->angle_to_horizontal -= this->racket_side * this->racket_pos * SWING_SPEED;
    }
    else {
        // 两个都为0，停止挥拍
        swinging = false;
    }
}


QPointF CRacket::get_start_point() const
{
    return QPointF(
        owner->X() +  CRacket::RACKET_LENGTH *qCos(angle_to_horizontal *M_PI/180)
        , owner->Y() + CRacket::RACKET_LENGTH *qSin(angle_to_horizontal *M_PI/180));
}

QPointF CRacket::get_end_point() const
{
    return QPointF(
        owner->X() +  (CRacket::RACKET_LENGTH + CRacket::RACKET_AREA_RANGE)*qCos(angle_to_horizontal *M_PI/180)
        , owner->Y() + (CRacket::RACKET_LENGTH + CRacket::RACKET_AREA_RANGE)*qSin(angle_to_horizontal *M_PI/180));
}


//------------------------
// class CBall

void CBall::reset(CPlayer *pPlayer, const QPointF &serving_dir)
{
    // 球放到球员位置上，准备发球
    serving = true;
    landed = false;
    this->set_x(pPlayer->X());
    this->set_y(pPlayer->Y());
    this->set_vx(0.0);
    this->set_vy(0.0);
    set_acceleration(0.0,0.0);
    // 设置球尾方向
    this->serving_direction = serving_dir;
}


// 发球
void CBall::serve(){
    if(!serving) return;
    serving = false;
    set_acceleration(0.0,CCourt::ACCELERATION_OF_GRAVITY);
}

// 球撞墙
// 撞墙后水平方向耗散，竖直方向速度不变
void CBall::bounce()
{
    // 只影响水平速度
    this->set_vx(-CCourt::COLLIDE_COEFFICIENT * this->vX());
}

// 球落地
// 落地时竖直方向水平方向耗散
void CBall::land()
{
    // 竖直方向耗散更大
    landed=true;
    set_y(0.0);
    this->set_vx( CCourt::LAND_VX_COEFFICIENT * this->vX());
    this->set_vy(-CCourt::LAND_VY_COEFFICIENT * this->vY());
}

// 击球
// 根据球拍参数获得球的初速度
void CBall::hit(CRacket *racket)
{
    if(racket->hitted) return;
    racket->hitted = true;
    // 球拍不挥动时，不会击打球
    if(racket->is_swinging() == false) return;
    // 当前球拍的起点和拍面角度决定了球获得的初速度方向
    // 挥拍时间决定了初速度大小
    // 无牵连速度 球速度只和球拍角度和时间有关

    // 上半区 左边 150(high) ~ 0  右边 30(high) ~ 180
    double angleV = racket->get_init_angle_high() - 90;
    if(racket->get_racket_pos() == CRacket::RACKET_HIGH_POS){
        angleV = racket->get_angle() - racket->get_racket_side()* 90; // 上半区 球初速度角度为球拍角度 (45 ~  0-90)
    }
    // 下半区 左边 210(low) ~ 360  右边  330(low) ~ 180
    if(racket->get_racket_pos() == CRacket::RACKET_LOW_POS){
        angleV = racket->get_angle() + racket->get_racket_side()* 90; // 下半区 球初速度角度为球拍角度 (315 ~ 360+90)
    }
    qreal vtotal = racket->owner->get_player_strength() * (2*CGame::TOTALCNT_single_swing - racket->get_go_cnt())/2/CGame::TOTALCNT_single_swing;
    this->set_vx( vtotal * qCos(angleV *M_PI/180) );
    this->set_vy( vtotal * qSin(angleV *M_PI/180) );
}
