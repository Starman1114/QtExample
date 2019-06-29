#include "qtserial.h"
#include "ui_qtserial.h"

QtSerial::QtSerial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtSerial)
{
    ui->setupUi(this);
    my_serialport= new QSerialPort();
    my_serialport->setPortName("/dev/ttyACM0");
    my_serialport->open(QIODevice::ReadWrite);
    my_serialport->setBaudRate(9600);

   // my_serialport->setParity(QSerialPort::NoParity);

    receiver = new QUdpSocket(this);
    receiver->bind(40001,QUdpSocket::ShareAddress);
    connect(receiver,SIGNAL(readyRead()),
    this,SLOT(processPendingDatagram()));


}

QtSerial::~QtSerial()
{
    delete ui;
}


void QtSerial::processPendingDatagram() //处理等待的数据报
{
    while(receiver->hasPendingDatagrams())  //拥有等待的数据报
    {
       QByteArray datagram; //拥于存放接收的数据报
//让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
       datagram.resize(receiver->pendingDatagramSize());
       //接收数据报，将其存放到datagram中
       receiver->readDatagram(datagram.data(),datagram.size());
       //将数据报内容显示出来
       ui->Link_Push->setText(datagram);
       receivedata(datagram);
    }
}

void QtSerial::receivedata(QByteArray datagram)
{
    QString data=datagram;
    if(data=="1"){
        my_serialport->write("1");
        //1-forward
        //2-back
        //3-left
        //4-right
        //5-stop
        my_serialport->write("/n");
    }else if(data=="2"){
        my_serialport->write("2");
        my_serialport->write("/n");
    }else if(data=="3"){
        my_serialport->write("3");
        my_serialport->write("/n");
    }else if(data=="4"){
        my_serialport->write("4");
        my_serialport->write("/n");
    }else if(data=="5"){
        my_serialport->write("5");
        my_serialport->write("/n");
    }
}






void QtSerial::on_pushButton_pressed()
{
  //  my_serialport->write(ui->lineEdit->text().toLatin1());
    my_serialport->write("1");
    //1-forward
    //2-back
    //3-left
    //4-right
    //5-stop
    my_serialport->write("/n");
}

void QtSerial::on_pushButton_2_pressed()
{
    my_serialport->write("2");
    my_serialport->write("/n");
}

void QtSerial::on_pushButton_3_pressed()
{
    my_serialport->write("3");
    my_serialport->write("/n");
}

void QtSerial::on_pushButton_4_pressed()
{
    my_serialport->write("4");
    my_serialport->write("/n");
}


void QtSerial::on_pushButton_released()
{
    my_serialport->write("5");
    my_serialport->write("/n");
}

void QtSerial::on_pushButton_2_released()
{
    my_serialport->write("5");
    my_serialport->write("/n");
}

void QtSerial::on_pushButton_3_released()
{
    my_serialport->write("5");
    my_serialport->write("/n");
}

void QtSerial::on_pushButton_4_released()
{
    my_serialport->write("5");
    my_serialport->write("/n");
}


