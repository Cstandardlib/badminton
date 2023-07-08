#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>

class myButton : public QPushButton
{
    Q_OBJECT
public:
    myButton (QString Img,QWidget *parent);
    myButton (QWidget *parent);
    void SetImg(QString Img);

    void EmitClick();
    void mousePress(QMouseEvent *ev);
    void mouseRelease(QMouseEvent *ev);
signals:
    void ButtonClicked();
public slots:
};

#endif // MYBUTTON_H
