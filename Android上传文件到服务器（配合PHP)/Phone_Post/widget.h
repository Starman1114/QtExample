#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QHttpPart>
#include <QTextCodec>
#include <QFile>
#include <QFileDialog>

#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QAndroidActivityResultReceiver>
#include <QtAndroid>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void FindFile3();


private slots:
    void on_pushButton_clicked();

    void slot_requestFinished();
    void upLoadError(QNetworkReply::NetworkError code);
    void uploadProcess(qint64 bytesReceived, qint64 bytesTotal);

signals:

private:
    Ui::Widget *ui;
    QNetworkReply *reply;
};

#endif // WIDGET_H
