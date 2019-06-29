#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //camera set
    f = new Form();
    form_Set=false;



    //设置初始放大倍数为1，即不放大
    scale =1;

    // 画布大小为200*200，背景为白色
    // Path->setBaseSize(350,120);
    p = new Path();
    path1=false;

    q= new QtSerial();
    car=false;
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pic_clicked()
{
    f->pic("temp");
    temp=QImage("../build-product/temp.jpg");
    width = temp.width(); //获得以前图片的宽和高
    height = temp.height();
    aa = temp.scaled(width*scale, height*scale, Qt::KeepAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(aa));

}


void MainWindow::on_add_clicked()
{
    scale *=2;
    aa = temp.scaled(width*scale, height*scale, Qt::KeepAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(aa));
}

void MainWindow::on_subtract_clicked()
{
    scale /=2;
    aa = temp.scaled(width*scale, height*scale, Qt::KeepAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(aa));
}

void MainWindow::on_pushButton_3_clicked()//save
{
    QString s=ui->lineEdit->text();
    f->pic(s);
}

void MainWindow::on_set_Push_clicked()
{
  if(form_Set==false){
    form_Set=true;
    f->show();
}else{
      f->hide();
      form_Set=false;
  }
}

void MainWindow::on_path_Push_clicked()
{
    if(path1==false){
      path1=true;
      p->show();
  }else{
        p->hide();
        path1=false;
    }
}

void MainWindow::on_car_Push_clicked()
{
    if(car==false){
      car=true;
      q->show();
  }else{
        q->hide();
        car=false;
    }
}
