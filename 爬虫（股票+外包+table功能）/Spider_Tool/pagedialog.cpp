#include "pagedialog.h"
#include "ui_pagedialog.h"

PageDialog::PageDialog(QWidget *parent,QStringList pageN) :
    QDialog(parent),
    pagen(pageN),
    ui(new Ui::PageDialog)
{
    ui->setupUi(this);
    setWindowTitle("页数设置");
    ui->haBox->setValue(pagen[0].toInt());
    ui->saBox->setValue(pagen[1].toInt());
    ui->hbBox->setValue(pagen[2].toInt());
    ui->sbBox->setValue(pagen[3].toInt());
}

PageDialog::~PageDialog()
{
    delete ui;
}

void PageDialog::on_okButton_clicked()
{
    pagen[0]=QString::number(ui->haBox->value());
    pagen[1]=QString::number(ui->saBox->value());
    pagen[2]=QString::number(ui->hbBox->value());
    pagen[3]=QString::number(ui->sbBox->value());
    emit changePageNumber(pagen);
    accept();
}

void PageDialog::on_cancelButton_clicked()
{
    reject();
}
