#include "setdata.h"
#include "ui_setdata.h"

SetData::SetData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetData)
{
    ui->setupUi(this);
    QAndroidJniObject pp =QAndroidJniObject::callStaticObjectMethod<jstring>(
            "org/qtproject/example/MainActivity", "path");
    route = pp.toString()+"/test1";
    ui->routeEdit->setText(route);
    urltext = "http://192.168.1.44/bigData/upload_file.php";
    ui->urlEdit->setText(urltext);
    ui->httpEdit->setText("http://192.168.1.44/bigData/form.html");
    fileType = "audio/wav";
    ui->typeEdit->setText(fileType);
}

SetData::~SetData()
{
    delete ui;
}
