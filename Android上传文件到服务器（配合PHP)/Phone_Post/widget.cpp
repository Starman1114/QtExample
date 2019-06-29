#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::FindFile3()
{
   QAndroidJniObject pp =QAndroidJniObject::callStaticObjectMethod<jstring>(
           "org/qtproject/example/MainActivity", "path");
   QString route = pp.toString()+"/test1";
  // QString path = route.append("/video2.wav");

    QString path = QFileDialog::getOpenFileName(NULL,"打开录制文件",route,"*.wav");
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("audio/wav"));  //image/png
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QString("form-data; name=\"%1\"; filename=\"%2\"").arg("file").arg(path));
    QFile *file = new QFile(path);
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(imagePart);

    QUrl url("http://192.168.1.44/bigData/upload_file.php");
    QNetworkRequest *request=new QNetworkRequest(url);
    QNetworkAccessManager *manager =new QNetworkAccessManager();
    reply = manager->post(*request, multiPart);
    multiPart->setParent(reply); // delete the multiPart with the reply
                                 // here connect signals etc.


   connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(upLoadError(QNetworkReply::NetworkError)));
   connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(uploadProcess(qint64, qint64)));
   connect(reply, SIGNAL(finished()), this, SLOT(slot_requestFinished()));
}


void Widget::upLoadError(QNetworkReply::NetworkError code)
{
    qDebug() << "错误： "<<code;
}

void Widget::uploadProcess(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << bytesReceived << bytesTotal;
}

void Widget::slot_requestFinished()
{
    QByteArray resultContent = reply->readAll();
    QTextCodec* pCodec = QTextCodec::codecForName("UTF-8");
    QString strResult = pCodec->toUnicode(resultContent);
    int nHttpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码

    ui->textBrowser->setPlainText(strResult);
    ui->textBrowser_2->setText(QString("%1").arg(nHttpCode));
}

void Widget::on_pushButton_clicked()
{
    FindFile3();
}
