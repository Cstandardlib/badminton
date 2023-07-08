#ifndef PAUSEWINDOW_H
#define PAUSEWINDOW_H

#include <QWidget>
#include "mylabel.h"
#include <QPushButton>
class PauseWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PauseWindow(QWidget *parent = nullptr);

signals:
    void BacktoMain();
public slots:
    void init();
    void ToMain();

private:
    QPushButton* backButton;
    QLabel *Showlabel;//界面说明
    myLabel* PauseWindow_backgroud;
};

#endif // PAUSEWINDOW_H
