#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //初始路径
    QAndroidJniObject path1 =QAndroidJniObject::callStaticObjectMethod<jstring>(
            "org/qtproject/example/MainActivity", "path");

    QDir dir(path1.toString());
    showFiles(dir);
    ui->currDir->setText(path1.toString());
    connect(ui->currDir, SIGNAL(returnPressed()),this, SLOT(showFiles()));

    connect(ui->fileListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
        this, SLOT(showDir(QListWidgetItem *)));


    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
             this,SLOT(displayError(QAbstractSocket::SocketError)));

 //   QString localHostName = QHostInfo::localHostName();//返回主机名，QHostInfo包含了一些关于主机的静态函数
    ui->hostLineEdit->setText("192.168.1.162");
    initStyle();

    connect(tcpSocket,SIGNAL(connected()),this,SLOT(startTransfer()));
    connect(tcpSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));


}

Widget::~Widget()
{
    delete ui;
}

// 获取ip地址，获取本机ip地址(其协议为ipv4的ip地址)
QString Widget::getIP()
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


void Widget::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug() << tcpSocket->errorString();
    tcpSocket->close();
    ui->file_Bar->reset();
    ui->messageLabel->setText(tr("客户端就绪"));
}

void Widget::newConnect()
{
    bytesWritten  = 0; //初始化其为0
    tcpSocket->abort(); //取消已有的连接
    ui->messageLabel->setText("连接中…");
    //连接到主机，这里从界面获取主机地址和端口号
    tcpSocket->connectToHost(ui->hostLineEdit->text(),
                             ui->portLineEdit->text().toInt());
}



    //算字符串长度
  //  QAndroidJniObject action = QAndroidJniObject::fromString("android.settings.SETTINGS");
  //  int a= action.callMethod<jint>("length");
  //  ui->messageLabel->setText(QString::number(a));
    //求最大值
   // jint a = 2;
   // jint b = 4;
   // jint max = QAndroidJniObject::callStaticMethod<jint>(
   //                    "java/lang/Math", "max", "(II)I", a, b);

    //调用 java.lang.Thread 的 currentThread方法获取当前的线程对象，currentThread 方法没有参数，返回值是 Thread 对象。
   // QAndroidJniObject thread = QAndroidJniObject::callStaticObjectMethod("java/lang/Thread", "currentThread",
   //                  "()Ljava/lang/Thread;");

    //调用 java.lang.String 的 valueOf 方法把一个数字转换为字符串
   // QAndroidJniObject string =QAndroidJniObject::callStaticObjectMethod(
   //         "java/lang/String", "valueOf", "(I)Ljava/lang/String;", 10);
   //
    // jint a = 2;
    // QAndroidJniObject::callStaticMethod<void>("org/qtproject/example/MainActivity","setVolume","(I)V",a);

    //运用java文件函数实例
  //   jint max = QAndroidJniObject::callStaticMethod<jint>(
  //                          "org/qtproject/example/MainActivity", "getmax");



void Widget::showFiles()
{
    QDir dir(ui->currDir->text());
    showFiles(dir);
}


void Widget::showFiles(QDir dir)  //除初始化后的路径及文件显示
{
    QStringList strings;
    strings << "*";
    //strings << "*.hts"<<"*.mp3" ;
    QFileInfoList list = dir.entryInfoList(strings,   //文件名称过滤器，"*", "*.tar.gz"
                         QDir::AllEntries,  //文件属性过滤器，目录，文件，读写
                         QDir::DirsLast  //排序方式，名称，修改时间，大小，目录最后
                         //QDir::DirsFirst  //排序方式，名称，修改时间，大小，目录优先
                         );
    showFileInfoList(list); //列表信息显示
}

//显示文件信息列表
void Widget::showFileInfoList(QFileInfoList list)
{
    ui->fileListWidget->clear();//清空前面留下的数据
      for(int i=0; i<list.count(); i++)
      {
           QFileInfo tmpFileInfo = list.at(i);  //文件列的第i个
           if((tmpFileInfo.isDir()))  //判断是否是路径    路径的名称就是一个路径
           {
               QIcon icon(":/image/dir.png");
               QString fileName = tmpFileInfo.fileName();  //返回文件名称
               if(fileName==".")
                   continue;
               QListWidgetItem *tmp = new QListWidgetItem(icon, fileName); //在列表上显示图标和名称
               ui->fileListWidget->addItem(tmp);
           }else if(tmpFileInfo.isFile()) //判断是否是文件
           {
               //文件后缀
               QString file_suffix = tmpFileInfo.suffix();
               if(file_suffix=="pcm"){
                   QIcon icon(":/image/fire.png");
                   QString fileName = tmpFileInfo.fileName();
                   QListWidgetItem *tmp = new QListWidgetItem (icon, fileName);
                   ui->fileListWidget->addItem(tmp);
               }
           }
      }
}


void Widget::showDir(QListWidgetItem * item) //双击文件或路径
{
    QString str = item->text(); //得到所双击的名称
    file_name =str;
    QDir dir;
    dir.setPath(ui->currDir->text()); //设置路径,文件所在文件夹
    QString Path=dir.absolutePath();

    QStringList ff =  Path.split(QRegExp("[/]"));
    if(ff[ff.length()-1]=="0"&&str=="..")  //防止一退到底
        return;

    QStringList filedata =  str.split(QRegExp("[.]"));
    filedata.append("aa");
    if(filedata[1]=="pcm"){
        file_Path = Path +"/"+str;
        SendData();
    }
    dir.cd(str); //切换到原路径下双击的文件夹
    ui->currDir->setText(dir.absolutePath()); //现在的决定路径
    showFiles(dir);
}

void Widget::SendData()
{
    if(QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("发送确认"),
                                                  tr("确认发送该文件?"),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::Yes)) {
        newConnect(); //请求连接
    }
}

void Widget::startTransfer()  //实现文件大小等信息的发送
{
    /*********打开文件*********/
    f = new QFile(file_Path);
    if(!f->open(QFile::ReadOnly))
    {
      qDebug() << "open file error!";
      return;
    }
    //文件总大小
    totalBytes = f->size();
    QDataStream sendOut(&block,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_10);
    //依次写入总大小信息空间，文件名大小信息空间，文件名
    sendOut << qint64(0) << qint64(0) << file_name;
    //这里的总大小是文件名大小等信息和实际文件大小的总和
    totalBytes += block.size();
    sendOut.device()->seek(0);
    //返回outBolock的开始，用实际的大小信息代替两个qint64(0)空间
    sendOut<<totalBytes<<qint64((block.size() - sizeof(qint64)*2));
    //发送完头数据后剩余数据的大小
    bytesToWrite = totalBytes - tcpSocket->write(block);
    ui->messageLabel->setText("发送文件："+file_name);
    block.resize(0);
}

void Widget::updateClientProgress(qint64 numBytes)
{
    //已经发送数据的大小
    bytesWritten += (int)numBytes;

    if(bytesToWrite > 0) //如果已经发送了数据
    {
   //每次发送loadSize大小的数据，这里设置为4KB，如果剩余的数据不足4KB，
   //就发送剩余数据的大小
       block = f->read(qMin(bytesToWrite,loadSize));
       //发送完一次数据后还剩余数据的大小
       bytesToWrite -= (int)tcpSocket->write(block);
       //清空发送缓冲区
       block.resize(0);
    } else {
       f->close(); //如果没有发送任何数据，则关闭文件
    }
    //更新进度条
    ui->file_Bar->setMaximum(totalBytes);
    ui->file_Bar->setValue(bytesWritten);
    if(bytesWritten == totalBytes) //发送完毕
    {
     ui->messageLabel->setText(QStringLiteral("文件已传送完成！"));
       f->close();
       tcpSocket->close();
    }
}


void Widget::initStyle()
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

void Widget::handleData(QString a)
{
    ui->messageLabel->setText(a);
}
