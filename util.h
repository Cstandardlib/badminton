
#ifndef UTIL_H
#define UTIL_H

#include<QMediaPlayer>

struct playerInfo{
    int type=1;
    int speed=2;
    int strength=2;
    int bounce=5;
};
//type:1--ikun   --speed:2--bounce:5--strength:2
//type:2--guoshen--speed:2--bounce:2--strength:5
//type:3--nobody --speed:3--bounce:3--strength:3
//type:4--duck   --speed:5--bounce:2--strength:2

struct playgroundInfo{
    int type=1;
    double g_coeff=3;//重力加速度
    double f_coeff=3;//空气阻力系数
};
//type:1--gym--g_coeff:3--f_coeff:3
//type:2--space--g_coeff:1--f_coeff:3
//type:3--taichi--g_coeff:3--f_coeff:5

struct stateInfo{
    int game_state;
    //0: in gaming
    //1: player 1 serving
    //2: player 2 serving
    //3: after winning a point
    //4: after winning a match
    //5: pause
    int score_1;
    int score_2;

};



#endif // UTIL_H
