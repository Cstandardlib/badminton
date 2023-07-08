#include "pausewindow.h"
#include <QMessageBox>
PauseWindow::PauseWindow(QWidget *parent) : QWidget(parent)
{
    PauseWindow_backgroud=new myLabel(":/image/6.png",this);
    PauseWindow_backgroud->move(0,0);


    backButton = new QPushButton("暂停",this);
    backButton->move(80,60);

    Showlabel=new QLabel("暂停界面",this);
    Showlabel->move(640,100);

    connect(backButton,&QPushButton::clicked,this,&PauseWindow::ToMain);
}

void PauseWindow::init(){
    PauseWindow_backgroud->show();
    backButton->show();
    Showlabel->show();
}
void PauseWindow::ToMain(){
    int res = QMessageBox::question(nullptr,"WARNING","Are you sure to exit？", QMessageBox::Yes|QMessageBox::No, QMessageBox::NoButton);
    if(res == QMessageBox::Yes){
        PauseWindow_backgroud->hide();
        backButton->hide();
        Showlabel->hide();
        emit BacktoMain();
    }
}
