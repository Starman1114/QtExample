#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>

#include "stockwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void ReadCsvFile(QString FireName,QStringList *NumberList,QStringList *NameList,QString Pre);
    void SetStyle();

private slots:
    void ShowGainProcess(int Rindix);
    void CreatWidget();


    void on_SpiderButton_clicked();


private:
    Ui::MainWindow *ui;

    QStringList UserAgeny;
    int userN=0;

    QStringList SHNumber;//沪市股票代码
    QStringList SZNumber;//深市股票代码
    QStringList Number;
    QStringList SHName;//沪市股票名字
    QStringList SZName;//深市股票名字
    QStringList Name;
    QStringList OriginHead= {"股票","代码","涨跌幅%"};
    QString urlPre = "http://qt.gtimg.cn/r=0.8409869808238q=s_";

    QHBoxLayout *vbox1;
    QTimer *timer;
    bool SpiderRun=false;
    \
    int WidgetIndex=0;

    StockWidget *dialog1;
    QList<StockWidget *> WidgetList;
};

#endif // MAINWINDOW_H
