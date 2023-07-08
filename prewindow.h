#ifndef PREWINDOW_H
#define PREWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include "mylabel.h"

#include "setwindow.h"
class PreWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PreWindow(QWidget *parent = nullptr);
    void ALLHIDE();
    void ALLSHOW();

signals:
    void signal_BacktoMain();
    void signal_ToGame();

public slots:
    void init();
    void ToMain();
    void ToGame();

private:
    QPushButton* backButton;
    QLabel *Showlabel;//界面说明
    myLabel* PreWindow_backgroud;

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

    SetWindow *m_setwindow;
};

#endif // PREWINDOW_H
