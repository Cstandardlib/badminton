#ifndef GAME_H
#define GAME_H

#include "engine.h"
#include"util.h"
extern playerInfo player1_Info;
extern playerInfo player2_Info;
extern playgroundInfo playground_Info;

class CGame{
public:
    CGame(){

        player1.init(CGame::PLAYER_SPEEDX,CGame::PLAYER_SPEEDY,CGame::ballVtotal);
        player2.init(CGame::PLAYER_SPEEDX,CGame::PLAYER_SPEEDY,CGame::ballVtotal);
        racket1.reset(static_cast<CPlayer *>(&player1),CRacket::RACKET_LEFT_SIDE);
        racket2.reset(static_cast<CPlayer *>(&player2),CRacket::RACKET_RIGHT_SIDE);
    }
    CPlayer player1, player2;
    CRacket racket1, racket2;
    CBall ball;

    // 计算用时间参数
    constexpr static const qreal dt_update = 0.005;          // update间隔10ms
    constexpr static const qreal dt_single_swing = 0.200;    // 挥拍来回500ms，单趟250ms
    constexpr static const int TOTALCNT_single_swing =int(dt_single_swing / dt_update);   // x循环一挥拍

    // 玩家
    constexpr static const qreal PLAYER_SPEEDX = 8.0;      // 人水平移速，1s过半场
    constexpr static const qreal PLAYER_SPEEDY = 8.0;      // 人竖直初速，0.4s到达最高

    
    // 球
    constexpr static const qreal ballVx = 12.0;      // 发球初速度-水平
    constexpr static const qreal ballVy = 12.0;      // 发球初速度-竖直
    constexpr static const qreal ballVtotal = 35.0;  // 总初速度



    void collideCheck();    //碰撞检测
    void update();          //更新游戏状态 a v s

};

#endif
