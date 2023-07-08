#include "description.h"
#include "ui_description.h"

Description::Description(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Description)
{
    ui->setupUi(this);
    QPixmap pix(":/image/img_icon/back_icon.png");
    ui->pushButton->setFixedSize(pix.size());
    ui->pushButton->setStyleSheet("QPushButton{border:0px;}");
    ui->pushButton->setIcon(pix);
    ui->pushButton->setIconSize(pix.size());

    connect(ui->pushButton,&QPushButton::clicked,this,&Description::ToMain);
}

Description::~Description()
{
    delete ui;
}

void Description::init(){
    setFocus();
    ui->pushButton->show();
    ui->graphicsView->show();
}

void Description::ToMain(){
    ui->pushButton->hide();
    ui->graphicsView->hide();
    this->hide();
    emit signal_BacktoMain();
}
