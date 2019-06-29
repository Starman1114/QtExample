#ifndef STOCKWIDGET_H
#define STOCKWIDGET_H

#include <QWidget>
#include <QDateTime>
#include "workerthread.h"


namespace Ui {
class StockWidget;
}

class StockWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StockWidget(QWidget *parent = 0,QStringList number={},QStringList name={},QStringList head={},QString urlpre="");
    ~StockWidget();

private:
    void Initialization();
    void getDataFromWeb();
    void Delay_MSec(unsigned int msec);

private slots:
    void GainData(QStringList data);
    void Search_Show(const QString &arg1);
    void sortData(int column);

signals:
    void GainProcess(int RIndex);

private:
    Ui::StockWidget *ui;
    QNetworkReply *reply;

    QStringList Number;
    QStringList Name;
    QStringList Head;
    QString urlPre;
    QString urltext;
    int VisitTime=0;
    int CurrentTime=1;

    QStringList LastData;



    WorkerThread *thread;
};

#endif // STOCKWIDGET_H
