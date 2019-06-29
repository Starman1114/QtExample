#ifndef QTSERIAL_H
#define QTSERIAL_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtNetwork>
#include "path.h"
namespace Ui {
class QtSerial;
}

class QtSerial : public QWidget
{
    Q_OBJECT

public:
    explicit QtSerial(QWidget *parent = 0);
    ~QtSerial();

private slots:
    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_4_pressed();


    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void processPendingDatagram();

    void receivedata(QByteArray datagram);

private:
    Ui::QtSerial *ui;
    QSerialPort *my_serialport;
    QUdpSocket *receiver;
    int x;
    int y;

};

#endif // QTSERIAL_H
