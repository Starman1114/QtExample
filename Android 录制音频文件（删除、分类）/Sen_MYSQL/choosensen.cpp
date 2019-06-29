#include "choosensen.h"
#include "ui_choosensen.h"

ChoosenSen::ChoosenSen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoosenSen)
{
    ui->setupUi(this);
    QFont font1("Microsoft YaHei", 20, 50); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是weight）
    ui->commonButton->setFont(font1);
    ui->nervousButton->setFont(font1);
    ui->confButton->setFont(font1);
    ui->okButton->setFont(font1);
    ui->cancelButton->setFont(font1);

}

ChoosenSen::~ChoosenSen()
{
    delete ui;
}

void ChoosenSen::on_commonButton_clicked()
{
    ui->commonButton->setChecked(true);
    if(ui->nervousButton->isChecked())
        ui->nervousButton->setChecked(false);
    if(ui->confButton->isChecked())
        ui->confButton->setChecked(false);
    SenData = "一般";
}

void ChoosenSen::on_nervousButton_clicked()
{
    ui->nervousButton->setChecked(true);
    if(ui->commonButton->isChecked())
        ui->commonButton->setChecked(false);
    if(ui->confButton->isChecked())
        ui->confButton->setChecked(false);
    SenData = "紧张";
}

void ChoosenSen::on_confButton_clicked()
{
    ui->confButton->setChecked(true);
    if(ui->commonButton->isChecked())
        ui->commonButton->setChecked(false);
    if(ui->nervousButton->isChecked())
        ui->nervousButton->setChecked(false);
    SenData = "自信";
}

void ChoosenSen::on_cancelButton_clicked()
{
    reject();
}

void ChoosenSen::on_okButton_clicked()
{
    PreEmotion = SenData;
    accept();
}
