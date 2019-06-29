#ifndef SETDATA_H
#define SETDATA_H

#include <QWidget>
#include "datalist.h"

#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QAndroidActivityResultReceiver>
#include <QtAndroid>

namespace Ui {
class SetData;
}

class SetData : public QWidget
{
    Q_OBJECT

public:
    explicit SetData(QWidget *parent = 0);
    ~SetData();

private:
    void InitStyle();
    void originData();

private slots:
    void slot_requestFinished();
    void upLoadError(QNetworkReply::NetworkError code);
    void uploadProcess(qint64 bytesReceived, qint64 bytesTotal);

private:
    Ui::SetData *ui;
    QNetworkReply *reply;
};

#endif // SETDATA_H
