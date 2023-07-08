#ifndef SETWINDOW_H
#define SETWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QKeyEvent>
#include <QtDebug>

namespace Ui {
class SetWindow;
}

class SetWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SetWindow(QWidget *parent = nullptr);
    ~SetWindow();
    void init();
signals:
    void signal_BacktoMain();
    void signal_ToGame();

public slots:

    void ToMain();
    void ToGame();
    void RecvPlayer1(int id);
    void RecvPlayer2(int id);
    void RecvPlayground(int id);
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::SetWindow *ui;
    QButtonGroup *m_player1;
    QButtonGroup *m_player2;
    QButtonGroup *m_playground;

};

#endif // SETWINDOW_H
