#include "mybutton.h"
#include <QMouseEvent>

myButton::myButton(QString Img,QWidget *parent)
{
    SetImg(Img);
    setParent(parent);
    connect(this,&myButton::clicked,this,&myButton::EmitClick);
}
void myButton::SetImg(QString Img){
    QPixmap pix(Img);
    setFixedSize(pix.size());
    setStyleSheet("QPushButton{border:0px;}");
    setIcon(pix);
    setIconSize(pix.size());
}

void myButton::EmitClick(){
    emit ButtonClicked();
}

void myButton::mousePress(QMouseEvent *ev){
    return QPushButton::mousePressEvent(ev);
}

void myButton::mouseRelease(QMouseEvent *ev){
    return QPushButton::mouseReleaseEvent(ev);
}

