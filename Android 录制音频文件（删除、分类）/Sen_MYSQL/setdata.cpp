#include "setdata.h"
#include "ui_setdata.h"

SetData::SetData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetData)
{
    ui->setupUi(this);
    InitStyle();
    originData();

}

SetData::~SetData()
{
    delete ui;
}

void SetData::InitStyle(){
    serverIP = "10.30.30.176";
    ui->IPEdit->setText(serverIP);
 //   QUrl url(QString("http://%1/bigData/getLinkData.php").arg(serverIP));
 //   QNetworkRequest *request=new QNetworkRequest(url);
 //   QNetworkAccessManager *manager =new QNetworkAccessManager();
 //   reply = manager->get(*request);
 //   connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(upLoadError(QNetworkReply::NetworkError)));
 //   connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(uploadProcess(qint64, qint64)));
 //   connect(reply, SIGNAL(finished()), this, SLOT(slot_requestFinished()));
}

void SetData::originData()
{
    QString urlphp="bigData/upload_file.php";
    urltext = QString("http://%1/%2").arg(serverIP).arg(urlphp);
    ui->urlEdit->setText(urltext);

    QString http ="bigData/form.html";
    ui->httpEdit->setText(QString("http://%1/%2").arg(serverIP).arg(http));

    QAndroidJniObject pp =QAndroidJniObject::callStaticObjectMethod<jstring>(
            "org/qtproject/example/MainActivity", "path");
    QString r = "SenData";
    route = pp.toString()+QString("/%1").arg(r);
    ui->routeEdit->setText(route);

    QDir *temp = new QDir;
    bool exist = temp->exists(route);
    if(!exist){
       temp->mkdir(route);
    }else{
        temp->rmdir(route);
        temp->mkdir(route);
    }

    fileType = "audio/wav";
    ui->typeEdit->setText(fileType);
}


void SetData::upLoadError(QNetworkReply::NetworkError code)
{
    qDebug() << "错误： "<<code;
    originData();
}

void SetData::uploadProcess(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << bytesReceived << bytesTotal;

}

void SetData::slot_requestFinished()
{
    QByteArray resultContent = reply->readAll();
    QTextCodec* pCodec = QTextCodec::codecForName("UTF-8");
    QString strResult = pCodec->toUnicode(resultContent);
    int nHttpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码

    ui->textBrowser->setPlainText(strResult);
    qDebug()<<QString("%1").arg(nHttpCode)<<endl;

    QStringList data =  strResult.split(QRegExp("[;]"));

    urltext = QString("http://%1/%2").arg(serverIP).arg(data[0]);
            //"http://192.168.1.44/bigData/upload_file.php";
    ui->urlEdit->setText(urltext);
    ui->httpEdit->setText(QString("http://%1/%2").arg(serverIP).arg(data[1]));

    QAndroidJniObject pp =QAndroidJniObject::callStaticObjectMethod<jstring>(
            "org/qtproject/example/MainActivity", "path");
    route = pp.toString()+QString("/%1").arg(data[2]);
    ui->routeEdit->setText(route);

    QDir *temp = new QDir;
    bool exist = temp->exists(route);
    if(!exist){
       temp->mkdir(route);
    }else{
        temp->rmdir(route);
        temp->mkdir(route);
    }

    fileType = data[3];
    ui->typeEdit->setText(fileType);
}


