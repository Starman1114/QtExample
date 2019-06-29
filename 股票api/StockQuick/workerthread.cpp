#include "workerthread.h"



void WorkerThread::run()
{
     getDataFromWeb();
}

void WorkerThread::getDataFromWeb()
{
     QNetworkAccessManager *manager = new QNetworkAccessManager();
     QNetworkRequest *request=new QNetworkRequest(QUrl(Url));

     reply = manager->get(*request);
     connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(upLoadError(QNetworkReply::NetworkError)));
     connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(uploadProcess(qint64, qint64)));
     connect(reply, SIGNAL(finished()), this, SLOT(slot_requestFinished()));

     QEventLoop loop;
     QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
     loop.exec();
}

void WorkerThread::slot_requestFinished()
{
    QByteArray resultContent = reply->readAll();
    QTextCodec* pCodec = QTextCodec::codecForName("gbk");
    QString strResult = pCodec->toUnicode(resultContent);
    int nHttpCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();//http返回码
    qDebug()<<"状态码： "<<nHttpCode;
    qDebug()<<reply->error();

    if(reply->error()==QNetworkReply::NetworkError::NoError){
        QStringList datalist = strResult.split(";");
        qDebug()<<datalist.length();
        int index=0;
        for(int i=0;i<VisitNumber;i++){
            QString num;
            if(index!=0)
                num = datalist[index].mid(5,6);
            else
                num = datalist[index].mid(6,6);
            if(!onlyNumber[ReadIndex].compare(num)){
                QStringList data = datalist[index].split("~");
                if(data.length()>=33){
                    RiseFall.append(data[32]);
                }else{
                    RiseFall.append("0.00");
                }
                index++;
            }else{
                RiseFall.append("0.00");
            }
            ReadIndex++;
        }

        emit resultReady(RiseFall);
    }else{
        disconnect(reply);
        qDebug()<<"重新爬取"<<ReadIndex;
        getDataFromWeb();
    }

}

void WorkerThread::upLoadError(QNetworkReply::NetworkError code)
{
    qDebug() << "错误： "<<code;
}

void WorkerThread::uploadProcess(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << "信息" << bytesReceived << bytesTotal;
}
