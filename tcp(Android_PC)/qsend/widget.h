#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>
#include <QFileDialog>
#include <QMessageBox>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QAndroidActivityResultReceiver>
#include <QDebug>
#include <QtAndroid>
#include <QListWidgetItem>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void newConnect(); //连接服务器
    void SendData();
    QString getIP();
    void initStyle();
    void handleData(QString);
    void showFiles();
    void showFiles(QDir dir);  //除初始化后的路径及文件显示
    //显示文件信息列表
    void showFileInfoList(QFileInfoList list);
    void showDir(QListWidgetItem * item); //打开文件夹
    void updateClientProgress(qint64 numBytes);
    void displayError(QAbstractSocket::SocketError); //显示错误
    void startTransfer();
private:
    Ui::Widget *ui;
    QTcpSocket *tcpSocket;
    QString message;  //存放从服务器接收到的字符串
    QString  file_Path;
    QString  file_name;
    int fireN=0;
    QByteArray block;/******二进制数据块******/
    qint64  totalBytes=0;//文件总大小
    qint64  bytesToWrite=0;//发送完头数据后剩余数据的大小
    qint64  bytesWritten=0;//已经发送数据的大小
    qint64  loadSize=4*1024;//每次发送的数据大小
    QFile *f;
};

#endif // WIDGET_H
