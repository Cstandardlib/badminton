#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include <QWidget>

namespace Ui {
class Description;
}

class Description : public QWidget
{
    Q_OBJECT

public:
    explicit Description(QWidget *parent = nullptr);
    ~Description();

signals:
    void signal_BacktoMain();
public slots:
    void init();
    void ToMain();
private:
    Ui::Description *ui;
};

#endif // DESCRIPTION_H
