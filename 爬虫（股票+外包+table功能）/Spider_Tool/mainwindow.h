#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QLineEdit>
#include <QtNetwork>
#include <QTableWidget>
#include <QCheckBox>
#include <QFileDialog>
#include <QHeaderView>
#include <QTimer>
#include <QFontDatabase>
#include "pagedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum DataType //初始数据类型
    {
        URL,
        HEAD,
        Rex,
        DECODE,
        USER,
        TEST
    };

    enum SpiderStaus //初始数据类型
    {
        TOSTART,
        TOSTOP
    };
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_SpiderButton_clicked();//爬虫

    void slot_requestFinished();//处理接受的数据

    void upLoadError(QNetworkReply::NetworkError code);//报错信息

    void uploadProcess(qint64 bytesReceived, qint64 bytesTotal);//接受信息

    void on_tabWidget_currentChanged(int index);//url切换


    void on_FileOnlyButton_clicked();

    void on_FileWholeButton_clicked();

    void on_SearchEdit_textEdited(const QString &arg1);

    void on_pageButton_clicked();

    void changePageNum(QStringList pn);

private:
    void InitStyle();//界面初始化
    void ReadData(QString FireName);//读取设置信息
    void ChangeSet(QTextStream *in);//初始数据设置
    void AddItemWidget(QStringList data,int num);//添加图标项
    void getDataFromWeb();
    void SetStyle();
    void Delay_MSec(unsigned int msec);



private:
    Ui::MainWindow *ui;
    QList<QTableWidget*> tableList;
    QStringList urlName;
    QStringList url;
    QStringList pageNumber;
    QString Current_url;
    QList<QStringList> Data_Head;
    QList<QStringList> Data_Rex;
    QStringList Decode;
    QStringList UserAgeny;
    int userN=0;

    int Run_num;//当前表格下标
    int All_page;//本次爬虫全部的页数
    int Current_page;//当前读取的页数
    int Current_Data_Number;//当前读取的数据数
    SpiderStaus staus = TOSTART;

    QNetworkReply *reply;
    QTimer *m_pTimer;
    int timeCount=0;
};

#endif // MAINWINDOW_H
