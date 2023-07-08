#include "widget.h"
#include <QLabel>
#include "mylabel.h"
#include "mybutton.h"
#include <QPushButton>
#include <QMessageBox>
#include "description.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMediaPlayer>
extern QMediaPlayer mainBGM_player;
extern QMediaPlayer gameBGM_player;
extern QMediaPlayer score_player;
//主窗口函数，控制各界面出现的消失信号与槽函数的实现
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mainbg=new myLabel(":/image/img_BG/welcomeBG_800.png",this);
    //游戏界面是1280*720
    //窗口大小是1280*800
    mainbg->move(0,0);
    mainBGM_player.setMedia(QUrl("qrc:/image/music_BGM/menuBGM.mp3"));
    mainBGM_player.play();
    setFocus();
    setFixedSize(1280,800);//重要++设定窗口大小
    setWindowIcon(QIcon(":/image/img_icon/badminton_icon.png"));
    setWindowTitle("火柴人羽毛球");


    //帮助界面 对象初始化
    m_helpwindow=new Description(this);
    m_helpwindow->move(0,0);
    m_helpwindow->hide();


    //设置界面 对象初始化
//    m_prewindow=new PreWindow(this);
//    m_prewindow->setFixedSize(this->size());
//    //m_prewindow->move(0,0);
//    m_prewindow->hide();

    m_setwindow=new SetWindow(this);
    m_setwindow->setFixedSize(this->size());
    //m_prewindow->move(0,0);
    m_setwindow->hide();
    m_setwindow->setParent(this);

    //游戏界面 对象初始化
    m_gamewindow =new gamewindow(this);
    m_gamewindow->setFixedSize(this->size());
    m_gamewindow->hide();

    //暂停界面 对象初始化
    m_pausewindow=new PauseWindow(this);
    m_pausewindow->setFixedSize(this->size());
    //m_pausewindow->move(0,0);
    m_pausewindow->hide();


    //帮助按钮 后期可改成自定义类 加上动画和音乐特效
    //helpbutton=new QPushButton("帮助",this);
    helpbutton=new myButton(":/image/img_icon/help_icon.png",this);
    helpbutton->move(220,720);
    helpbutton->setCursor(Qt::PointingHandCursor);
    //connect(helpbutton,&QPushButton::clicked,this,&Widget::ToHelp);
    connect(helpbutton,&myButton::ButtonClicked,this,&Widget::ToHelp);
    connect(m_helpwindow,&Description::signal_BacktoMain,this,&Widget::Back);


    //开始按钮 后期可改成自定义类
    //nextbutton=new QPushButton("开始!",this);
    nextbutton=new myButton(":/image/img_icon/start_icon.png",this);
    nextbutton->move(1000,720);
    nextbutton->setCursor(Qt::PointingHandCursor);
//    connect(nextbutton,&QPushButton::clicked,this,&Widget::ToPre);
    connect(nextbutton,&myButton::ButtonClicked,this,&Widget::ToSet);
    //connect(m_prewindow,&PreWindow::signal_BacktoMain,this,&Widget::Back);
    //connect(m_prewindow,&PreWindow::signal_ToGame,this,&Widget::ToGame);
    connect(m_setwindow,&SetWindow::signal_BacktoMain,this,&Widget::Back);
    connect(m_setwindow,&SetWindow::signal_ToGame,this,&Widget::ToGame);


    connect(m_gamewindow,&gamewindow::signal_BacktoMain,this,&Widget::Back);
    //退出选项
    //quitbutton=new QPushButton("退出",this);
    quitbutton=new myButton(":/image/img_icon/quit_icon.png",this);
    quitbutton->move(80,720);
    quitbutton->setCursor(Qt::PointingHandCursor);
    //connect(quitbutton,&QPushButton::clicked,this,&Widget::QuitMsg);
    connect(quitbutton,&myButton::ButtonClicked,this,&Widget::QuitMsg);


}

Widget::~Widget()
{

}


void Widget::QuitMsg(){//退出消息提醒
    int res = QMessageBox::question(nullptr,"提醒","是否确认退出游戏？", QMessageBox::Yes|QMessageBox::No, QMessageBox::NoButton);
    if(res == QMessageBox::Yes){
        this->close();
    }
}
void Widget::ALLHIDE(){//隐藏主界面所有
    quitbutton->hide();
    nextbutton->hide();
    helpbutton->hide();
    //Showlabel->hide();
    mainbg->hide();
//    this->hide();
}
void Widget::ALLSHOW(){//显示主界面所有
    setFocus();
    mainbg->show();
    quitbutton->show();
    nextbutton->show();
    helpbutton->show();
    //Showlabel->show();
//    this->show();
}
void Widget::ToHelp(){//前往帮助界面
    ALLHIDE();
    m_helpwindow->show();
    m_helpwindow->init();
}
void Widget::ToSet(){//前往准备界面
    ALLHIDE();
    qDebug()<<tr("前往准备界面--------");
    m_setwindow->show();
    m_setwindow->init();
}
void Widget::ToGame(){//前往游戏界面
    ALLHIDE();
    qDebug()<<tr("前往游戏界面");
    mainBGM_player.stop();
    m_gamewindow->setFocus();
    m_gamewindow->init();
    m_gamewindow->run();
}
void Widget::Back(){//从其他界面返回
    this->setFocus();
    mainBGM_player.setMedia(QUrl("qrc:/image/music_BGM/menuBGM.mp3"));
    mainBGM_player.play();
    ALLSHOW();
}
//处理主界面的esc enter space
void Widget::keyPressEvent(QKeyEvent *event){
    qDebug()<<"Main into keyPressEvent--------"<<endl;
    auto key = event->key();
    switch (key) {
        case Qt::Key_Escape:QuitMsg();break;
        case Qt::Key_Space:ToSet();break;
        case Qt::Key_Enter:ToSet();break;
        default:break;
    }
    return ;
}
