#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //使用widget作为基类，在单个窗口内通过鼠标按键操作实现界面切换
    Widget w;
    w.show();

    return a.exec();
}
