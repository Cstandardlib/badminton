#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include "mylabel.h"
#include "mybutton.h"
#include "setwindow.h"
#include "pausewindow.h"
#include "gamewindow.h"
#include "util.h"
#include "description.h"


class Widget : public QWidget
{
    Q_OBJECT
public slots:
    void keyPressEvent(QKeyEvent *event) override;

public:
    Widget(QWidget *parent = NULL);
    ~Widget();

public:
    void ALLHIDE();
    void ALLSHOW();
    void QuitMsg();

    void ToSet();
    void ToHelp();
    void ToGame();

    void Back();
    QMediaPlayer mainBGM_player;
private:
    myLabel *mainbg;
    myButton* quitbutton;
    myButton* nextbutton;
    myButton* helpbutton;
    QLabel *Showlabel;//界面说明

    SetWindow* m_setwindow;//设置界面
    PauseWindow* m_pausewindow;//暂停界面
    Description* m_helpwindow;//描述界面
    gamewindow* m_gamewindow;//游戏界面



};

#endif // WIDGET_H
