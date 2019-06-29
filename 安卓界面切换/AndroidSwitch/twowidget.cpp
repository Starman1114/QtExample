#include "twowidget.h"
#include "ui_twowidget.h"

TwoWidget::TwoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TwoWidget)
{
    ui->setupUi(this);
    ui->setupUi(this);

}

TwoWidget::~TwoWidget()
{
    delete ui;
}
