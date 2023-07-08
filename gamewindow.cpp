#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QMessageBox>
extern playerInfo player1_Info;
extern playerInfo player2_Info;
extern playgroundInfo playground_Info;
extern QMediaPlayer mainBGM_player;
extern QMediaPlayer gameBGM_player;
extern QMediaPlayer score_player;
gamewindow::gamewindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewindow)
{


    ui->setupUi(this);
    window_width=1280;
    window_height=720;

    game = new CGame();



    //set timers
    keyEventTimer=new QTimer();
    QObject::connect(keyEventTimer,SIGNAL(timeout()),this,SLOT(keyChangeCallback()));
    gameLoopTimer=new QTimer();
    QObject::connect(gameLoopTimer,SIGNAL(timeout()),this,SLOT(gameLoopCallback()));
    afterPointTimer=new QTimer();
    QObject::connect(afterPointTimer,SIGNAL(timeout()),this,SLOT(afterPointCallback()));

    //set QGraphicItems
    vBackground.setPixmap(QPixmap(":/image/img_BG/gymBG.png"));

    //ball setup:
    ballOffset.setX(60.0/1280*16);
    ballOffset.setY(10.0/1280*16);
    vBall.setPixmap(QPixmap(":/image/badmintonBall.png"));
    vBall.setTransformOriginPoint(vBall.boundingRect().center());

    QPixmap tmp;

    //player setup:
    vPlayer_1.setPixmap(QPixmap(":/image/img_role/ikun.png"));
    vPlayer_1.setTransformOriginPoint(vPlayer_1.boundingRect().center());
    tmp=QPixmap::fromImage(QImage(":/image/img_role/ikun.png").mirrored(true,false));//水平翻转
    vPlayer_2.setPixmap(tmp);
    vPlayer_2.setTransformOriginPoint(vPlayer_2.boundingRect().center());



    //racket setup
    vRacket_1.setPixmap(QPixmap(":/image/img_role/racket60.png"));
    vRacket_1.setTransformOriginPoint(vRacket_1.boundingRect().center());
    vRacket_1.setParentItem(&vPlayer_1);
    vRacket_2.setPixmap(QPixmap(":/image/img_role/racket60.png"));
    vRacket_2.setTransformOriginPoint(vRacket_2.boundingRect().center());
    vRacket_2.setParentItem(&vPlayer_2);


    //leg setup
    vLeg_1.setPixmap(QPixmap(":/image/img_role/leg.png"));
    vLeg_1.setTransformOriginPoint(vLeg_1.boundingRect().center());
    vLeg_1.setParentItem(&vPlayer_1);
    tmp=QPixmap::fromImage(QImage(":/image/img_role/leg.png").mirrored(true,false));//水平翻转
    vLeg_2.setPixmap(tmp);
    vLeg_2.setTransformOriginPoint(vLeg_2.boundingRect().center());
    vLeg_2.setParentItem(&vPlayer_2);


    //arm setup
    vArm_1.setPixmap(QPixmap(":/image/img_role/arm_long.png"));
    vArm_1.setTransformOriginPoint(vArm_1.boundingRect().center());
    vArm_1.setParentItem(&vPlayer_1);
    tmp=QPixmap::fromImage(QImage(":/image/img_role/arm_long.png").mirrored(true,false));//水平翻转
    vArm_2.setPixmap(tmp);
    vArm_2.setTransformOriginPoint(vArm_2.boundingRect().center());
    vArm_2.setParentItem(&vPlayer_2);

    //set QGraphicScene
    vGameScene.addItem(&vBackground);
    vGameScene.addItem(&vBall);
    vGameScene.addItem(&vPlayer_1);
    vGameScene.addItem(&vRacket_1);
    vGameScene.addItem(&vLeg_1);
    vGameScene.addItem(&vArm_1);
    vGameScene.addItem(&vPlayer_2);
    vGameScene.addItem(&vRacket_2);
    vGameScene.addItem(&vLeg_2);
    vGameScene.addItem(&vArm_2);
    vGameScene.setSceneRect(QRect(0,80,window_width,window_height+80));

    //set QGraphicView
    vGameView.setSceneRect(QRect(0,0,window_width,window_height));
    vGameView.move(0,80);//向下平移80，腾出上方的比赛信息栏
    vGameView.setFocusPolicy(Qt::NoFocus);//防止GraphicView类对方向键的占用
    vGameView.setScene(&vGameScene);
    vGameView.setParent(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&gamewindow::QuitMsg);
}

gamewindow::~gamewindow()
{
    delete ui;
    delete keyEventTimer;
    delete gameLoopTimer;
    delete afterPointTimer;

}

void gamewindow::init(){
    //set QGraphicItems


    //player1 setup:
    switch (player1_Info.type) {
    case 1:
        vPlayer_1.setPixmap(QPixmap(":/image/img_role/ikun.png"));
        break;
    case 2:
        vPlayer_1.setPixmap(QPixmap(":/image/img_role/guoshen.png"));
        break;
    case 3:
        vPlayer_1.setPixmap(QPixmap(":/image/img_role/nobody.png"));
        break;
    case 4:
        vPlayer_1.setPixmap(QPixmap(":/image/img_role/duck.png"));
        break;
    default:     
        break;
    }


    //player2 setup:
    QPixmap tmp;
    switch (player2_Info.type) {
    case 1:
        tmp=QPixmap::fromImage(QImage(":/image/img_role/ikun.png").mirrored(true,false));//水平翻转
        vPlayer_2.setPixmap(tmp);
        break;
    case 2:
        tmp=QPixmap::fromImage(QImage(":/image/img_role/guoshen.png").mirrored(true,false));//水平翻转
        vPlayer_2.setPixmap(tmp);
        break;
    case 3:
        tmp=QPixmap::fromImage(QImage(":/image/img_role/nobody.png").mirrored(true,false));//水平翻转
        vPlayer_2.setPixmap(tmp);
        break;
    case 4:
        tmp=QPixmap::fromImage(QImage(":/image/img_role/duck.png").mirrored(true,false));//水平翻转
        vPlayer_2.setPixmap(tmp);
        break;
    default:
        break;
    }
    //player ability setup
    double dspeed=2.0,dbounce=1.0,dstrength=5;
    double speed1=CGame::PLAYER_SPEEDX+(player1_Info.speed-3)*dspeed;
    double speed2=CGame::PLAYER_SPEEDX+(player2_Info.speed-3)*dspeed;
    double bounce1=CGame::PLAYER_SPEEDY+(player1_Info.bounce-3)*dbounce;
    double bounce2=CGame::PLAYER_SPEEDY+(player2_Info.bounce-3)*dbounce;
    double strength1=CGame::ballVtotal+(player1_Info.strength-3)*dstrength;
    double strength2=CGame::ballVtotal+(player2_Info.strength-3)*dstrength;

    game->player1.init(speed1,bounce1,strength1);
    game->player2.init(speed2,bounce2,strength2);

    //playground property setup
    double dg=-4,df=-0.002;
    CCourt::ACCELERATION_OF_GRAVITY=CCourt::default_ACCELERATION_OF_GRAVITY+(playground_Info.g_coeff-3)*dg;
    CCourt::RESISTANCE_COEFFICIENT=CCourt::default_RESISTANCE_COEFFICIENT+(playground_Info.f_coeff-3)*df;

    memset(keyBook,false,sizeof(keyBook));
    reset_match();
    this->show();
}
void gamewindow::ToMain(){
    this->hide();
    qDebug()<<"before"<<endl;
    gameBGM_player.pause();
    keyEventTimer->stop();
    gameLoopTimer->stop();
    qDebug()<<"after"<<endl;
    emit signal_BacktoMain();
}
void gamewindow::QuitMsg(){
    gameBGM_player.pause();
    int tmpState=states.game_state;
    states.game_state=5;
    int res=QMessageBox::question(nullptr,"提醒","是否确认退出比赛？", QMessageBox::Yes|QMessageBox::No, QMessageBox::NoButton);
    if(res==QMessageBox::Yes){
        ToMain();
        return;
    }
    memset(keyBook,false,sizeof(keyBook));
    states.game_state=tmpState;
    gameBGM_player.play();
}

void gamewindow::run(){
    keyEventTimer->start(10);
    gameLoopTimer->start(5);
}

QPointF gamewindow::physics2Window(QPointF input){
    double ix=input.x();
    double iy=input.y();
    double H=window_height;
    double W=window_width;
    double X=8;
    double Y=9;
    double ox=W/(2*X)*ix+W/2;
    double oy=-H/Y*iy+H;
    return QPointF(ox,oy);
}


void gamewindow::render(){
    double xb = game->ball.X();
    double yb = game->ball.Y();
    QPointF dir=game->ball.get_direction();
    double ab=0;
    if(dir.x()>0){
        ab= qAtan(dir.y()/dir.x());
    }
    else if(dir.x()<0){
        ab= qAtan(dir.y()/dir.x())+M_PI;
    }
    else{
        if(dir.y()>0){ab=M_PI/2;}
        else if(dir.y()<0){ab=-M_PI/2;}
        else{ab=0;}
    }
    ab=ab/M_PI*180;//radian to degree
    ab=90-ab;// 物理坐标和窗口坐标转换

    double x1=game->player1.X();
    double y1=game->player1.Y();
    double a1 = game->racket1.get_angle();
    a1 *= -1; // 物理坐标和窗口坐标转换

    double x2=game->player2.X();
    double y2=game->player2.Y();
    double a2 = game->racket2.get_angle();
    a2 *= -1; // 物理坐标和窗口坐标转换

    vBall.setPos(physics2Window(QPointF(xb, yb))-QPointF(vBall.boundingRect().width()/2,vBall.boundingRect().height()/2));
    vBall.setRotation(ab);
    vPlayer_1.setPos(physics2Window(QPointF(x1,y1))-QPointF(vPlayer_1.boundingRect().width()/2,vPlayer_1.boundingRect().height()/2));
    vRacket_1.setRotation(a1);
    vPlayer_2.setPos(physics2Window(QPointF(x2,y2))-QPointF(vPlayer_2.boundingRect().width()/2,vPlayer_2.boundingRect().height()/2));
    vRacket_2.setRotation(a2);
}


void gamewindow::reset_match(){
    lastWinner=1;//player 1 serves first by default
    states.game_state=1;
    states.score_1=0;
    states.score_2=0;
    score_player.setMedia((QUrl("qrc:/image/music_effect/getScore.MP3")));
    switch (playground_Info.type) {
    case 1:
        gameBGM_player.setMedia(QUrl("qrc:/image/music_BGM/gymBGM.MP3"));
        vBackground.setPixmap(QPixmap(":/image/img_BG/gymBG.png"));
        break;
    case 2:
        gameBGM_player.setMedia(QUrl("qrc:/image/music_BGM/spaceBGM.MP3"));
        vBackground.setPixmap(QPixmap(":/image/img_BG/spaceBG.png"));
        break;
    case 3:
        gameBGM_player.setMedia(QUrl("qrc:/image/music_BGM/taichiBGM.mp3"));
        vBackground.setPixmap(QPixmap(":/image/img_BG/daoBG.png"));
        break;
    default:
        break;
    }
    gameBGM_player.play();

    // player initial pos
    game->player1.set_x(-4);
    game->player1.set_y(CPlayer::PLAYER_HEIGHT);

    game->player2.set_x(4);
    game->player2.set_y(CPlayer::PLAYER_HEIGHT);

    // ball initial pos
    game->ball.set_x(game->player1.get_position().x()+ballOffset.x());
    game->ball.set_y(game->player1.get_position().y()-ballOffset.y());//把球放在手上
    game->ball.reset(static_cast<CPlayer *>(&game->player1),QPointF(0,1));

    // racket initial pos
    game->racket1.reset(static_cast<CPlayer *>(&game->player1),CRacket::RACKET_LEFT_SIDE);
    game->racket2.reset(static_cast<CPlayer *>(&game->player2),CRacket::RACKET_RIGHT_SIDE);


    ui->label_p1win->hide();
    ui->label_p2win->hide();
    ui->restart_button->hide();
    ui->scoreboard_1->display(states.score_1);
    ui->scoreboard_2->display(states.score_2);
}

void gamewindow::reset_point(){
    //0: in gaming
    //1: player 1 serving
    //2: player 2 serving
    //3: after winning a point
    //4: after winning a match
    //5: pause
    states.game_state=lastWinner;
    if(states.game_state==1){
        game->ball.reset(static_cast<CPlayer *>(&game->player1),QPointF(0,1));
        game->ball.set_x(game->player1.get_position().x()+ballOffset.x());
        game->ball.set_y(game->player1.get_position().y()-ballOffset.y());//把球放在手上
    }
    else{
        game->ball.reset(static_cast<CPlayer *>(&game->player2),QPointF(0,1));
        game->ball.set_x(game->player2.get_position().x()-ballOffset.x());
        game->ball.set_y(game->player2.get_position().y()-ballOffset.y());//把球放在手上
    }

}

void gamewindow::judge(){
    double ballx = game->ball.X();
    double bally = game->ball.Y();
    if(-0.1 < bally && bally < 0.1){
        score_player.setMedia((QUrl("qrc:/image/music_effect/getScore.MP3")));
        score_player.play();
        if(ballx<0){//p2 get a point
            states.score_2++;
            lastWinner=2;
        }
        else{
            states.score_1++;//p1 get a point
            lastWinner=1;
        }
        if(states.score_1==7||states.score_2==7){
            states.game_state=4;

            if(lastWinner==1){
                ui->label_p1win->show();
            }
            else if(lastWinner==2){
                ui->label_p2win->show();
            }
            ui->restart_button->show();

        }
        else{
             states.game_state=3;
             afterPointTimer->start(3000);
        }
        ui->scoreboard_1->display(states.score_1);
        ui->scoreboard_2->display(states.score_2);

    }

}




void gamewindow::keyPressEvent(QKeyEvent* event){
    auto key = event->key();
    switch(key){
    case Qt::Key_W: keyBook[0] = true;break;
    case Qt::Key_S: keyBook[1] = true;break;
    case Qt::Key_A: keyBook[2] = true;break;
    case Qt::Key_D: keyBook[3] = true;break;
    case Qt::Key_Up: keyBook[4] = true;break;
    case Qt::Key_Down: keyBook[5] = true;break;
    case Qt::Key_Left: keyBook[6] = true;break;
    case Qt::Key_Right: keyBook[7] = true;break;
    case Qt::Key_Escape: QuitMsg();break;
    }


}

void gamewindow::keyReleaseEvent(QKeyEvent *event){
    auto key = event->key();
    switch(key){
    case Qt::Key_W:keyBook[0]= false;break;
    case Qt::Key_S:keyBook[1]= false;break;
    case Qt::Key_A:keyBook[2]= false;break;
    case Qt::Key_D:keyBook[3]= false;break;
    case Qt::Key_Up: keyBook[4] = false;break;
    case Qt::Key_Down: keyBook[5] = false;break;
    case Qt::Key_Left: keyBook[6] = false;break;
    case Qt::Key_Right: keyBook[7] =false;break;
    }
}

void gamewindow::keyChangeCallback(){
    if(states.game_state==5){return;}//pause
    // W S
    if(keyBook[0]){
        game->player1.jump();
    }
    if(keyBook[1]){
        game->racket1.start_swing();
        if(game->ball.is_serving()&&1==states.game_state){
            game->ball.serve();
            states.game_state=0;
        }
    }
    // A D
    if(keyBook[2]) {
        game->player1.start_moving(CPlayer::PLAYER_MOVING_LEFT);
    }
    else if(keyBook[3]) {
        game->player1.start_moving(CPlayer::PLAYER_MOVING_RIGHT);
    }
    else game->player1.stop_moving();


    // ARROW -- UP DOWN
    if(keyBook[4]) {
         game->player2.jump();
    }
    if(keyBook[5]) {
         game->racket2.start_swing();
         if(game->ball.is_serving()&&2==states.game_state){
            game->ball.serve();
            states.game_state=0;
         }
    }
    // ARROW -- LEFT RIGHT
    if(keyBook[6]) {
         game->player2.start_moving(CPlayer::PLAYER_MOVING_LEFT);
    }
    else if(keyBook[7]) {
         game->player2.start_moving(CPlayer::PLAYER_MOVING_RIGHT);
    }
    else game->player2.stop_moving();


}
void gamewindow::gameLoopCallback(){
    if(states.game_state==5){return;}//pause

    game->update();
    if(states.game_state==1) {
         game->ball.set_x(game->player1.get_position().x()+ballOffset.x());
         game->ball.set_y(game->player1.get_position().y()-ballOffset.y());//把球放在手上
    }
    if(states.game_state==2) {
         game->ball.set_x(game->player2.get_position().x()-ballOffset.x());
         game->ball.set_y(game->player2.get_position().y()-ballOffset.y());//把球放在手上
    }

    if(states.game_state!=3&&states.game_state!=4) judge();
    render();

}

void gamewindow::afterPointCallback(){
    reset_point();
    afterPointTimer->stop();
}

void gamewindow::on_restart_button_clicked()
{
    reset_match();
}

