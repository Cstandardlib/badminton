#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include"game.h"
#include"util.h"
#include <QWidget>
#include<QGraphicsPixmapItem>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QKeyEvent>
#include<QTimer>
#include<QDebug>
#include<QPointF>
#include<QMovie>
#include<QMediaPlayer>
#include<QtMath>
#include<QImage>
#include<QGraphicsProxyWidget>
#include<QLabel>

namespace Ui {
class gamewindow;
}

class gamewindow : public QWidget
{
    Q_OBJECT

public:
    explicit gamewindow(QWidget *parent = nullptr);
    ~gamewindow();


private:
    Ui::gamewindow *ui;

signals:
    void signal_BacktoMain();

public slots:
    //界面跳转
    void init();
    void ToMain();
    void QuitMsg();
    //按键处理
    void keyChangeCallback();
    void gameLoopCallback();
    void afterPointCallback();
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;


public:
    //游戏界面元素
    QTimer* keyEventTimer;
    QTimer* gameLoopTimer;
    QTimer* afterPointTimer;
    CGame *game;

    bool keyBook[20];
    QPointF ballOffset;//把球放在人手上

    int window_width;
    int window_height;
    QGraphicsView vGameView;
    QGraphicsScene vGameScene;

    QGraphicsPixmapItem vBackground;
    QGraphicsPixmapItem vBall;

    QGraphicsPixmapItem vRacket_1;
    QGraphicsPixmapItem vRacket_2;
    QGraphicsPixmapItem vPlayer_1;
    QGraphicsPixmapItem vPlayer_2;
    QGraphicsPixmapItem vLeg_1;
    QGraphicsPixmapItem vLeg_2;
    QGraphicsPixmapItem vArm_1;
    QGraphicsPixmapItem vArm_2;
//    QGraphicsProxyWidget vMovingLegs_1;
//    QGraphicsProxyWidget vMovingLegs_2;
//    QMovie* run_anime_1;
//    QMovie* run_anime_2;
//    QLabel run_label_1;
//    QLabel run_label_2;


    stateInfo states;
    int lastWinner;

    void judge();
    void reset_match();
    void reset_point();
    void run();
    void render();


    QPointF physics2Window(QPointF input);//物理引擎空间至显示窗口的映射


private slots:
    void on_restart_button_clicked();
};

#endif // GAMEWINDOW_H
