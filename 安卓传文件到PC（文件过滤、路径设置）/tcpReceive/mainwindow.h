#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QtNetWork>
#include "setpath.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    QString getIP();
    void initStyle();

    void start();   //开始监听
    void acceptConnection();  //建立连接
    void updateServerProgress();  //更新进度条，接收数据
    void displayError(QAbstractSocket::SocketError socketError);
    void on_btn_opendir_clicked();

    void on_setButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer tcpServer;
    QTcpSocket *tcpServerConnection;
    qint64 totalBytes=0;  //存放总大小信息
    qint64 bytesReceived=0;  //已收到数据的大小
    qint64 fileNameSize=0;  //文件名的大小信息
    QString fileName;   //存放文件名
    QFile *localFile;   //本地文件
    QByteArray inBlock;   //数据缓冲区

    bool isLink=false;

    SetPath *setP;


};

#endif // MAINWINDOW_H
