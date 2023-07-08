#include "prewindow.h"
#include "setwindow.h"
#include <QDebug>
//Prelabel

PreWindow::PreWindow(QWidget *parent) : QWidget(parent)
{
    //方案一:手动构建准备界面的玩家选择等参数设置，较为复杂但自由度高
//    PreWindow_backgroud =new myLabel(":/image/5.png",this);
//    PreWindow_backgroud->move(0,0);

//    Showlabel=new QLabel("选择界面",this);
//    Showlabel->move(640,100);

//    backButton=new QPushButton("返回",this);
//    backButton->move(80,60);
//    connect(backButton,&QPushButton::clicked,this,&PreWindow::ToMain);

    /*
    QRadioButton *A_Button1;
    QRadioButton *A_Button2;
    QRadioButton *A_Button3;
    QRadioButton *A_Button4;

    QRadioButton *B_Button1;
    QRadioButton *B_Button2;
    QRadioButton *B_Button3;
    QRadioButton *B_Button4;

    QButtonGroup *m_A_playerGroup;
    QButtonGroup *m_B_playerGroup;
     */
//    A_Button1=new QRadioButton("IKUN",this);
    //A_Button1->move()

    //方案二:选用便于制作的UI文件作为准备界面，便于实现但是不易修改
    m_setwindow=new SetWindow(this);
    m_setwindow->move(0,0);
    m_setwindow->hide();
    connect(m_setwindow,&SetWindow::signal_BacktoMain,this,&PreWindow::ToMain);
    connect(m_setwindow,&SetWindow::signal_ToGame,this,&PreWindow::ToGame);
}
void PreWindow::ALLHIDE(){
    PreWindow_backgroud->hide();
    backButton->hide();
    Showlabel->hide();
}
void PreWindow::ALLSHOW(){
    PreWindow_backgroud->show();
    backButton->show();
    Showlabel->show();
}


void PreWindow::init(){
    //ALLSHOW();
    qDebug()<<tr("前往设置界面--------");
    m_setwindow->setFocus();
    m_setwindow->show();
//    m_setwindow->init();
}

void PreWindow::ToMain(){
    //ALLHIDE();
    m_setwindow->hide();
    this->hide();
    emit signal_BacktoMain();
}

void PreWindow::ToGame(){
    m_setwindow->hide();
    emit signal_ToGame();
}
