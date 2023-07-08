#include "setwindow.h"
#include "ui_setwindow.h"
#include <QButtonGroup>
#include <QPushButton>
#include "util.h"
extern playerInfo player1_Info;
extern playerInfo player2_Info;
extern playgroundInfo playground_Info;

SetWindow::SetWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetWindow)
{
    ui->setupUi(this);

    QPixmap pix(":/image/img_icon/back_icon.png");
    ui->pushButtonBack->setFixedSize(pix.size());
    ui->pushButtonBack->setStyleSheet("QPushButton{border:0px;}");
    ui->pushButtonBack->setIcon(pix);
    ui->pushButtonBack->setIconSize(pix.size());

    QPixmap pix2(":/image/img_icon/start_icon.png");
    ui->pushButtonBegin->setFixedSize(pix2.size());
    ui->pushButtonBegin->setStyleSheet("QPushButton{border:0px;}");
    ui->pushButtonBegin->setIcon(pix2);
    ui->pushButtonBegin->setIconSize(pix2.size());

    //新建状态虚拟分组，添加玩家1角色选择情况
    m_player1 =new QButtonGroup(this);
    m_player1->addButton(ui->radioButton11,1);
    m_player1->addButton(ui->radioButton12,2);
    m_player1->addButton(ui->radioButton13,3);
    m_player1->addButton(ui->radioButton14,4);

    //新建状态虚拟分组，添加玩家2角色选择情况
    m_player2 =new QButtonGroup(this);
    m_player2->addButton(ui->radioButton21,1);
    m_player2->addButton(ui->radioButton22,2);
    m_player2->addButton(ui->radioButton23,3);
    m_player2->addButton(ui->radioButton24,4);

    //新建状态虚拟分组，添加场地角色选择情况
    m_playground =new QButtonGroup(this);
    m_playground->addButton(ui->radioButton31,1);
    m_playground->addButton(ui->radioButton32,2);
    m_playground->addButton(ui->radioButton33,3);


    //关联角色选择和调试输出
    connect(m_player1,QOverload<int>::of(&QButtonGroup::buttonClicked),this,&SetWindow::RecvPlayer1);
    connect(m_player2,QOverload<int>::of(&QButtonGroup::buttonClicked),this,&SetWindow::RecvPlayer2);
    connect(m_playground,QOverload<int>::of(&QButtonGroup::buttonClicked),this,&SetWindow::RecvPlayground);

    connect(ui->pushButtonBack,&QPushButton::clicked,this,&SetWindow::ToMain);
    connect(ui->pushButtonBegin,&QPushButton::clicked,this,&SetWindow::ToGame);

    //初始默认:ikun(第一个)、羽毛球馆
    ui->radioButton11->setChecked(true);
    ui->radioButton21->setChecked(true);
    ui->radioButton31->setChecked(true);
}

SetWindow::~SetWindow()
{
    delete ui;
}

void SetWindow::init(){
    ui->BackGround->show();
    ui->pushButtonBack->show();
    ui->pushButtonBegin->show();
    ui->groupBox->show();
    ui->groupBox_2->show();
    ui->groupBox_3->show();
    ui->label_intro1->show();
    ui->label_intro2->show();
    ui->label_role1->show();
    ui->label_role2->show();
    ui->label_playground_pic->show();
    ui->label_playground_text->show();

}
void SetWindow::ToMain(){
    this->hide();
    emit signal_BacktoMain();
}
void SetWindow::ToGame(){
    this->hide();
    emit signal_ToGame();
}

//接收角色选择情况的信号，传递角色属性给游戏界面
void SetWindow::RecvPlayer1(int id){
    QString formattedText,new_styleSheet;
    switch(id){
    case 1:
        player1_Info.type=1;
        player1_Info.speed=2;
        player1_Info.bounce=5;
        player1_Info.strength=2;

        formattedText="<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">IKUN 只因你太美</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">敏捷(2) 弹跳(5) 力量(2)</span></p></body></html>";
        new_styleSheet="background-image: url(:/image/img_role/ikunW.png)";
        break;
    case 2:
        player1_Info.type=2;
        player1_Info.speed=2;
        player1_Info.bounce=2;
        player1_Info.strength=5;
        formattedText="<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">郭神 启动!</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">敏捷(2) 弹跳(2) 力量(5)</span></p></body></html>";
        new_styleSheet="background-image: url(:/image/img_role/guoshenW.png)";
        break;
    case 3:
        player1_Info.type=3;
        player1_Info.speed=3;
        player1_Info.bounce=3;
        player1_Info.strength=3;
        formattedText="<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">路人甲 打酱油</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">敏捷(3) 弹跳(3) 力量(3)</span></p></body></html>";
        new_styleSheet="background-image: url(:/image/img_role/nobodyW.png)";
        break;
    case 4:
        player1_Info.type=4;
        player1_Info.speed=5;
        player1_Info.bounce=2;
        player1_Info.strength=2;
        formattedText="<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">绿头鸭 嘎嘎</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">敏捷(5) 弹跳(2) 力量(2)</span></p></body></html>";
        new_styleSheet="background-image: url(:/image/img_role/duckW.png)";
        break;
    default:
        break;
    }
    ui->label_intro1->setText(formattedText);
    ui->label_role1->setStyleSheet(new_styleSheet);
}
void SetWindow::RecvPlayer2(int id){
    QString formattedText,new_styleSheet;
    switch(id){
    case 1:
        player2_Info.type=1;
        player2_Info.speed=2;
        player2_Info.bounce=5;
        player2_Info.strength=2;
        formattedText="<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">IKUN 只因你太美</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">敏捷(2) 弹跳(5) 力量(2)</span></p></body></html>";
        new_styleSheet="background-image: url(:/image/img_role/ikunW.png)";
        break;
    case 2:
        player2_Info.type=2;
        player2_Info.speed=2;
        player2_Info.bounce=2;
        player2_Info.strength=5;
        formattedText="<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">郭神 启动!</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">敏捷(2) 弹跳(2) 力量(5)</span></p></body></html>";
        new_styleSheet="background-image: url(:/image/img_role/guoshenW.png)";
        break;
    case 3:
        player2_Info.type=3;
        player2_Info.speed=3;
        player2_Info.bounce=3;
        player2_Info.strength=3;
        formattedText="<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">路人甲 打酱油</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">敏捷(3) 弹跳(3) 力量(3)</span></p></body></html>";
        new_styleSheet="background-image: url(:/image/img_role/nobodyW.png)";
        break;
    case 4:
        player2_Info.type=4;
        player2_Info.speed=5;
        player2_Info.bounce=2;
        player2_Info.strength=2;
        formattedText="<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">绿头鸭 嘎嘎</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">敏捷(5) 弹跳(2) 力量(2)</span></p></body></html>";
        new_styleSheet="background-image: url(:/image/img_role/duckW.png)";
        break;
    default:
        break;
    }
    ui->label_intro2->setText(formattedText);
    ui->label_role2->setStyleSheet(new_styleSheet);
}


void SetWindow::RecvPlayground(int id){
    QString formattedText,new_styleSheet;
    switch(id){
    case 1:
        playground_Info.type=1;
        playground_Info.g_coeff=3;
        playground_Info.f_coeff=3;
        formattedText="<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">一个普通的羽毛球馆</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">重力(3) 空气阻力(3)</span></p></body></html>";
        new_styleSheet="background-image: url(:/image/img_BG/gymBG_260.png)";
        break;
    case 2:
        playground_Info.type=2;
        playground_Info.g_coeff=1;
        playground_Info.f_coeff=3;
        formattedText="<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">我要上天!</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">重力(1) 空气阻力(3)</span></p></body></html>";
        new_styleSheet="background-image: url(:/image/img_BG/spaceBG_260.png)";
        break;
    case 3:
        playground_Info.type=3;
        playground_Info.g_coeff=3;
        playground_Info.f_coeff=5;
        formattedText="<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">道可道，非常道</span></p><p align=\"center\"><span style=\" font-size:12pt; font-weight:600;\">重力(3) 空气阻力(5)</span></p></body></html>";
        new_styleSheet="background-image: url(:/image/img_BG/daoBG_260.png)";
        break;

    default:
        break;
    }
    ui->label_playground_text->setText(formattedText);
    ui->label_playground_pic->setStyleSheet(new_styleSheet);
}







//处理主界面的esc enter space
void SetWindow::keyPressEvent(QKeyEvent *event){
    qDebug()<<"SetWindow into keyPressEvent--------"<<endl;
    auto key = event->key();
    switch (key) {
        case Qt::Key_Escape:ToMain();break;
        case Qt::Key_Space:ToGame();break;
        default:break;
    }
    return ;
}
