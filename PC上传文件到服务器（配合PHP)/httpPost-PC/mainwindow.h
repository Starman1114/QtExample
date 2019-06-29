#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QFile>
#include <QFileDialog>

#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QAndroidActivityResultReceiver>
#include <QtAndroid>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void FindFile3();

private slots:
    void on_pushButton_clicked();

    void slot_requestFinished();
    void upLoadError(QNetworkReply::NetworkError code);
    void uploadProcess(qint64 bytesReceived, qint64 bytesTotal);

signals:

private:
    Ui::MainWindow *ui;
    QNetworkReply *reply;  //3
};

#endif // MAINWINDOW_H
