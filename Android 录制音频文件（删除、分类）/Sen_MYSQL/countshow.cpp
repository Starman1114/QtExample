#include "countshow.h"
#include "ui_countshow.h"

CountShow::CountShow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CountShow)
{
    ui->setupUi(this);
    count_Number = count_Number_Origin;

    this->setWindowOpacity(0.7);
    //定时器设置
    pTimer = new QTimer(this);
    // 设置定时间隔
    pTimer->setInterval(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    QFont font1("Microsoft YaHei", 150, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是weight）
    ui->countButton->setFont(font1);
    ui->countButton->setText(QString::number(count_Number));
    ui->countButton->setFocusPolicy(Qt::NoFocus);



    // 启动定时器
    if(pTimer->isActive()){
        pTimer->stop();
    }
    pTimer->start();
}

CountShow::~CountShow()
{
    delete ui;
}

void CountShow::onTimeOut()
{
    ui->countButton->setText(QString::number(--count_Number));
    if(count_Number==-1){
         pTimer->stop();
         accept();
    }
}
