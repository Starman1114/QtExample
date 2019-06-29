#include "countstep.h"
#include "ui_countstep.h"

CountStep::CountStep(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CountStep)
{
    ui->setupUi(this);
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置窗体关闭时自动释放内存
    this->setAttribute(Qt::WA_DeleteOnClose);
}

CountStep::~CountStep()
{
    delete ui;
}
