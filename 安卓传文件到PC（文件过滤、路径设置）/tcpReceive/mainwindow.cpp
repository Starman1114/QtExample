#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDesktopServices>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(close()),qApp,SLOT(quit()));
    initStyle();
    start();
    connect(&tcpServer,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    ui->IPlabel->setText("服务器IP："+getIP()+" 端口号：");

    setP = new SetPath();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start() //开始监听
{
    bytesReceived =0;
    if(!tcpServer.listen(QHostAddress(getIP()),ui->portEdit->text().toInt()))
    {
        qDebug() << tcpServer.errorString();
        close();
        return;
    }
    ui->statusLabel->setText(tr("监听"));
}

void MainWindow::acceptConnection()  //接受连接
{
    tcpServerConnection = tcpServer.nextPendingConnection();
    connect(tcpServerConnection,SIGNAL(readyRead()),this,SLOT(updateServerProgress()));
    connect(tcpServerConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
    ui->statusLabel->setText(tr("接受连接"));
    tcpServer.close();
}

void MainWindow::updateServerProgress()  //更新进度条，接收数据
{
    QDataStream in(tcpServerConnection);
    in.setVersion(QDataStream::Qt_5_10);

    if(bytesReceived <= sizeof(qint64)*2)
    { //如果接收到的数据小于16个字节，那么是刚开始接收数据，我们保存到//来的头文件信息

        if((tcpServerConnection->bytesAvailable() >= sizeof(qint64)*2)&& (fileNameSize == 0))
        { //接收数据总大小信息和文件名大小信息
            in >> totalBytes >> fileNameSize;
            bytesReceived += sizeof(qint64) * 2;
        }

        if((tcpServerConnection->bytesAvailable() >= fileNameSize)
                && (fileNameSize != 0))
        {  //接收文件名，并建立文件
            in >> fileName;
            ui->statusLabel->setText(tr("接收文件 %1 …").arg(fileName));
            bytesReceived += fileNameSize;
            qDebug()<<2333<<endl;
            localFile = new QFile(Path+fileName);
            if(!localFile->open(QFile::WriteOnly))
            {
                qDebug() << "open file error!";
                return;
            }
        }

        else return;
    }


    if(bytesReceived < totalBytes)
    {  //如果接收的数据小于总数据，那么写入文件
        bytesReceived += tcpServerConnection->bytesAvailable();
        inBlock = tcpServerConnection->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }

    ui->serverProgressBar->setMaximum(totalBytes);
    ui->serverProgressBar->setValue(bytesReceived);
    //更新进度条
    if(bytesReceived == totalBytes)

    { //接收数据完成时
        tcpServerConnection->close();
        localFile->close();
        ui->statusLabel->setText(tr("接收文件 %1 成功！").arg(fileName));
        start();
    }
}


void MainWindow::displayError(QAbstractSocket::SocketError) //错误处理
{
    qDebug() << tcpServerConnection->errorString();
    tcpServerConnection->close();
    ui->serverProgressBar->reset();
    ui->statusLabel->setText(tr("服务端就绪"));
}

// 获取ip地址，获取本机ip地址(其协议为ipv4的ip地址)
QString MainWindow::getIP()
{
    //QList是Qt中一个容器模板类，是一个数组指针？
    QList<QHostAddress> list = QNetworkInterface::allAddresses();//此处的所有地址是指ipv4和ipv6的地址
    //foreach (variable, container),此处为按照容器list中条目的顺序进行迭代
    foreach (QHostAddress address, list) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();
    }
    return 0;
}

void MainWindow::initStyle()
{
    //加载样式表
    QFile file(":/qss/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void MainWindow::on_btn_opendir_clicked() //打开文件夹
{
    QDesktopServices::openUrl(QUrl(Path));
}

void MainWindow::on_setButton_clicked()
{
    setP->show();
}

