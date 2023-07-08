#ifndef ENGINE_H
#define ENGINE_H

#include <QPointF>
#include <QDebug>


// 物理参数更新用的场地信息
struct CCourt{
    constexpr static const double COURT_WIDTH = 16;              // 场地大小
    constexpr static const double COURT_HEIGHT = 9;
    constexpr static const double NET_HEIGHT = 0.2*COURT_HEIGHT; // 球网高度

    // 场地重力加速度 向下
    constexpr const static double default_ACCELERATION_OF_GRAVITY=-20.0;
    static double ACCELERATION_OF_GRAVITY;

    // 空气阻力系数，每次刷新时速度变为原来的coef倍
    static double RESISTANCE_COEFFICIENT;
    constexpr const static double default_RESISTANCE_COEFFICIENT=0.99211;

    constexpr static const double COLLIDE_COEFFICIENT = 0.863; // 碰撞系数，碰到墙体时的法向速度耗散

    constexpr static const double LAND_VY_COEFFICIENT = 0.2;   // 落地弹起时的竖直方向阻尼
    constexpr static const double LAND_VX_COEFFICIENT = 0.6;   // 落地的水平方向阻尼

    void reset(double g, double f); // 设置场地参数，重力加速度和空气阻力

};

// 角色，球 基类
class CMovingObject{
protected:
    QPointF position;     // 物理坐标
    QPointF speed;        // 速度
    QPointF acceleration; // 加速度

public:
    qreal X()  const {return position.x();}
    qreal Y()  const {return position.y();}
    qreal vX() const {return speed.x();}
    qreal vY() const {return speed.y();}
    qreal aX() const {return acceleration.x();}
    qreal aY() const {return acceleration.y();}
    QPointF get_position() const {return position;} // 获得物理坐标
    QPointF get_speed() const {return speed;}
    QPointF get_acceleration() const {return acceleration;}
    // 设定位置
    void set_position(qreal x, qreal y){position.setX(x); position.setY(y);}
    void set_x(qreal x){position.setX(x);}
    void set_y(qreal y){position.setY(y);}
    void set_position(const QPointF &pos){position=pos;}
    // 设置速度
    void set_speed(qreal vx, qreal vy){speed.setX(vx); speed.setY(vy);}
    void set_vx(qreal vx){speed.setX(vx);}
    void set_vy(qreal vy){speed.setY(vy);}
    // 设置加速度
    void set_acceleration(qreal ax, qreal ay){acceleration.setX(ax); acceleration.setY(ay);}
};

class CPlayer: public CMovingObject{
private:
    int speedx_direction;    // 地速方向
    bool on_ground=true;          // 在地面， jump()和落地时改变
    // 初始化时设置的移动和跳跃速度
    qreal speedx;
    qreal speedy;
    // 击球力量
    qreal strength_HitBallSpeed;
public:
    constexpr static const double PLAYER_HEIGHT = 130.0/1280*16;

    CPlayer():on_ground(true),speedx(0),speedy(0)
        ,strength_HitBallSpeed(42.0) // CGame::ballVtotal
    {}
    CPlayer(qreal vx, qreal vy):on_ground(true),speedx(vx),speedy(vy)
        ,strength_HitBallSpeed(42.0) // CGame::ballVtotal
    {}
    void init(qreal vx, qreal vy, qreal strength);

    qreal get_player_strength() const {return strength_HitBallSpeed;}

    enum eDirectionType {PLAYER_MOVING_LEFT, PLAYER_MOVING_RIGHT };

    // 按键交互后根据设定值改变速度向量
    void start_moving(enum eDirectionType direction);
    void stop_moving(); // 水平置0

    // 判断离地
    bool is_on_ground() const {return on_ground;}
    
    bool jump();
    void land();
};

class CRacket{
/*球拍
绘图调用接口：握拍点位置，角度
计算用： 长度，角速度
*/
private:
    double angle_to_horizontal=INIT_ANGLE_LOW;
    
    bool swinging=false; // 正在挥拍
    bool hitted = false; // 每一轮击球是否打中？若已经击球则不再发生hit
    int racket_pos=RACKET_LOW_POS;     // 迎球位，上手和下手，在update中更新
    int gocnt_swing=0;    // 出手循环计数
    int backcnt_swing=0;  // 复位循环计数

    CPlayer *owner;
    int racket_side=RACKET_LEFT_SIDE;
    
public:
    friend class CBall;

    constexpr static const double INIT_ANGLE_HIGH = 150; // 上迎球位
    constexpr static const double INIT_ANGLE_LOW  = 210; // 下迎球位

    constexpr static const int TOTALCNT_single_swing = 40;
    constexpr static const double SWING_SPEED = INIT_ANGLE_HIGH / TOTALCNT_single_swing; // 角速度，每个循环划过半圆的1/TOTALCNT_single_swing

    constexpr static const double RACKET_LENGTH =(70.0-10) * 16 / 1280; // 握拍点到拍面底部的距离，杆长
    constexpr static const double RACKET_AREA_RANGE =(60.0+20) * 16 / 1280; // 拍面大小


    enum eRacketPosition { RACKET_HIGH_POS=-1, RACKET_LOW_POS=1};  // 上手击球和下手击球位置
    enum eRacketSide { RACKET_LEFT_SIDE = 1, RACKET_RIGHT_SIDE = -1}; // 左右半场，右半场-1

    CRacket():angle_to_horizontal(INIT_ANGLE_LOW),swinging(false)
        ,racket_pos(RACKET_LOW_POS), gocnt_swing(0), backcnt_swing(0) {}

    CRacket(CPlayer *_owner, enum eRacketSide side):angle_to_horizontal(INIT_ANGLE_LOW),swinging(false)
        ,racket_pos(RACKET_LOW_POS), gocnt_swing(0), backcnt_swing(0)
        ,owner(_owner),racket_side(side){}
    void reset(CPlayer *_owner,enum eRacketSide side){
        owner = _owner;
        swinging=false;
        hitted = false;
        racket_side = side;
        angle_to_horizontal=get_init_angle_low();
        racket_pos=RACKET_LOW_POS;     // 迎球位，上手和下手，在update中更新
        gocnt_swing=0;    // 出手循环计数
        backcnt_swing=0;  // 复位循环计数
    }



    // racket x y 返回球员坐标
    qreal X()  const {return owner->X();}
    qreal Y()  const {return owner->Y();}
    QPointF get_owner_pos() const {return owner->get_position();}

    QPointF get_start_point() const;
    QPointF get_end_point() const;


    void set_racket_pos(enum eRacketPosition _racket_Position);
    int get_racket_pos() const {return racket_pos;}

    int get_racket_side() const {return racket_side;}
    double get_init_angle_high() const {return 90+racket_side*90-racket_side*30;}
    double get_init_angle_low() const  {return 90+racket_side*90+racket_side*30;}

    double get_angle() const {return angle_to_horizontal;}
    int get_go_cnt() const {return gocnt_swing; }
    int get_back_cnt() const {return backcnt_swing;}

    bool is_swinging() const {return swinging;}

    bool start_swing();
    void swing();       // 挥拍的坐标改变
};

class CBall: public CMovingObject{
private:
    bool serving=true;   // 发球状态：在人手上
    bool landed=false;    // 球已经落地
    QPointF serving_direction;
public:
    // 球受重力加速度，serve发球后才考虑
    CBall():serving(true),landed(false){
        set_acceleration(0,0.0);
    }
    // 球重置在发球员手中，设置发球方向
    void reset(CPlayer *pPlayer, const QPointF &serving_dir);
    // 获得球尾朝向，serving（在手上准备发球）返回给定方向，否则返回飞行速度反向
    QPointF get_direction() const{
        if(serving) return serving_direction;
        return -get_speed();
    }
    // 发球
    bool is_serving() const {return serving;}
    bool is_flying() const {return !serving;} // 球已经发出
    void serve();
    // 撞墙
    void bounce();
    // 落地
        // 球落地弹起，只弹起一次，第二次竖直方向速度设为0并设置水平加速度？
    // 正常落地弹起，当竖直方向位移足够小时会被窗口坐标取整截断
    void land();
    bool is_landed() const {return landed;}
    // 击球
    void hit(CRacket *racket);
};

#endif
