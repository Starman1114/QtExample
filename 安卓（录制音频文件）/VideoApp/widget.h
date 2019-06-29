#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "datalist.h"
#include "workerthread.h"

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
    void on_recordButton_clicked();
    void onTimeOut();

    void on_timeBox_valueChanged(int arg1);

    void on_clearButton_clicked();

private:
    void Init_Monitor();
    qint64 addWavHeader(QString catheFileName , QString wavFileName);
    void File_Gain();
    void File_Start();

private:
    Ui::Widget *ui;
    int count=1; //音频文件序号

    QLCDNumber *m_pLCD; //LCD时间显示
    QTimer *pTimer; //定时器
    QDateTime countTime;  //计时
    int count_Number=0;  //计时处理
    QStatusBar *message; //状态栏

    QStringListModel *model;
};

#endif // WIDGET_H
