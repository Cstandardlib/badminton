#include "game.h"
#include <QtMath>

// 进行全局碰撞检测
// 处理改变速度的碰撞：球触网，玩家落地
// 修改速度，flag等变量
// 如果玩家前后两次位置差穿越了
void CGame::collideCheck()
{
    // 玩家落地
    // 玩家碰到墙和网在update时处理，无需改变速度
    if(player1.Y() + player1.vY()*dt_update < CPlayer::PLAYER_HEIGHT) { player1.land(); }
    if(player2.Y() + player2.vY()*dt_update < CPlayer::PLAYER_HEIGHT) { player2.land(); }

    // 球

    // 球撞墙 左右墙体
    if(ball.X() + ball.vX()*dt_update < -CCourt::COURT_WIDTH/2){
        ball.set_x(-CCourt::COURT_WIDTH/2);
        ball.bounce();
    }
    if(ball.X() + ball.vX()*dt_update >  CCourt::COURT_WIDTH/2)
    {
        ball.set_x(CCourt::COURT_WIDTH/2);
        ball.bounce();
    }
    // 球落地
    if(ball.Y() + ball.vY()*dt_update < 0){
        ball.land();
    }
    // 球触网
    // 和触墙一样反弹
    if(ball.Y() < CCourt::NET_HEIGHT){ // 球高度在网下
        // 球越过网：更新前后x坐标符号相反
        if(ball.X() * (ball.X() + ball.vX() * dt_update) <= 0){
            ball.set_x(0.0);
            ball.bounce();
        }
    }
    
    // 球触拍
    // 拍面和球足够进（用半径和角度判断），球hit拍，获得初速度
    QPointF vec_RacketToBall = ball.get_position()-racket1.get_owner_pos();
    qreal len_RacketToBall = qSqrt(QPointF::dotProduct(vec_RacketToBall,vec_RacketToBall));
    QPointF vec_RacketRod = racket1.get_start_point() - racket1.get_owner_pos();
    qreal len_RacketRod = qSqrt(QPointF::dotProduct(vec_RacketRod,vec_RacketRod));
    qreal angle = qAcos(
                (QPointF::dotProduct(vec_RacketRod,vec_RacketToBall)/len_RacketToBall/len_RacketRod));
    if(CRacket::RACKET_LENGTH <= len_RacketToBall
            && len_RacketToBall <= CRacket::RACKET_LENGTH+CRacket::RACKET_AREA_RANGE)
        // 落在拍面圆环内
    {
        if(angle < M_PI / 6.0){
            ball.hit(static_cast<CRacket *>(&racket1));
        }
    }

    vec_RacketToBall = ball.get_position()-racket2.get_owner_pos();
    len_RacketToBall = qSqrt(QPointF::dotProduct(vec_RacketToBall,vec_RacketToBall));
    vec_RacketRod = racket2.get_start_point() - racket2.get_owner_pos();
    len_RacketRod = qSqrt(QPointF::dotProduct(vec_RacketRod,vec_RacketRod));
    angle = qAcos(
                    (QPointF::dotProduct(vec_RacketRod,vec_RacketToBall)/len_RacketToBall/len_RacketRod));
    if(CRacket::RACKET_LENGTH <= len_RacketToBall
            && len_RacketToBall <= CRacket::RACKET_LENGTH+CRacket::RACKET_AREA_RANGE)
        // 落在拍面圆环内
    {
        if(angle < M_PI / 6.0){
            ball.hit(static_cast<CRacket *>(&racket2));
        }
    }

}

// 和dt相关，每次更新dt内移动的距离
// 根据a刷新v，根据v刷新x
// 处理玩家碰到墙和网：不改变速度，但不穿墙即不更新位置
void CGame::update()
{
    collideCheck();
    // Player 1,2
    // 玩家撞墙or网则不改变速度，但不更新位置，速度由按键决定
    // 起跳后竖直方向有加速度
    player1.set_vy(player1.vY() + player1.aY()*dt_update);
    qreal newx = player1.X() + player1.vX()*dt_update;
    if(-CCourt::COURT_WIDTH/2 <= newx && newx <=0) player1.set_x(newx);
    qreal newy = player1.Y() + player1.vY()*dt_update;
    player1.set_y(newy);

    player2.set_vy(player2.vY() + player2.aY()*dt_update);
    newx = player2.X() + player2.vX()*dt_update;
    if(0 <= newx && newx <=CCourt::COURT_WIDTH/2) player2.set_x(newx);
    newy = player2.Y() + player2.vY()*dt_update;
    player2.set_y(newy);

    // Ball
    // 刷新球的速度 空气阻力
    qreal new_ballvx = ball.vX() + ball.aX()*dt_update;
    new_ballvx *= CCourt::RESISTANCE_COEFFICIENT;
    qreal new_ballvy = ball.vY() + ball.aY()*dt_update;
    new_ballvy *= CCourt::RESISTANCE_COEFFICIENT;
    ball.set_vx(new_ballvx);
    ball.set_vy(new_ballvy);
    ball.set_x(ball.X() + ball.vX()*dt_update);
    ball.set_y(ball.Y() + ball.vY()*dt_update);

    // Racket
    // 跟随玩家移动
    // Racket 不另外维护位置 直接调用racket1.X()获得球员位置

    // 实时刷新迎球位置
    // 球在高处，上迎球
    if(racket1.Y() + 0.5*CRacket::RACKET_LENGTH < ball.Y()) racket1.set_racket_pos(CRacket::RACKET_HIGH_POS);
    else racket1.set_racket_pos(CRacket::RACKET_LOW_POS);

    if(racket2.Y() + 0.5*CRacket::RACKET_LENGTH < ball.Y()) racket2.set_racket_pos(CRacket::RACKET_HIGH_POS);
    else racket2.set_racket_pos(CRacket::RACKET_LOW_POS);

    // 挥拍   只有已经start_swing的拍子才会在swing函数中挥动 否则不产生作用
    racket1.swing();
    racket2.swing();
    
}
