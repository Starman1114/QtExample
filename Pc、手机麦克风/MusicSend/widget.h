#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "datalist.h"
#include "workerthread.h"
#include "monitor.h"
#include "Downchirp/Downchirp.h"
#include "Upchirp/Upchirp.h"



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_monitorButton_clicked();

    void on_sendBtn_clicked();

    void on_receiveButton_clicked();


    void on_horizontalSlider_valueChanged(int value);

private:
    void Init_Monitor();
    QString hexTobinary(QString tem);
    QString binaryToString(QString binary);


private:
    Ui::Widget *ui;

    WorkerThread *wt;
    Monitor *mon;

    QString txt;
    QString binary;

    double Down_chirp[882];
    double Up_chirp[882];
    double t[882];

    double* send_Data;
    QByteArray array;
};

#endif // WIDGET_H
