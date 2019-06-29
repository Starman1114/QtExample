#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDateTime time = QDateTime::currentDateTime();
    datalist = time.toString("yyyy-MM-dd-hh-mm-ss").split("-");
    data.push_back(2018);
    data.push_back(8);
    data.push_back(23);
    data.push_back(17);
    data.push_back(18);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(closeWidget()));
    timer->start(3000);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeWidget()
{
    for(int i=0;i<5;i++){
        if(datalist[i].toInt()>data[i]){
            qDebug()<<datalist[i].toInt()<<data[i];
            qApp->exit();
            return;
        }
    }
}
