#ifndef COUNTSHOW_H
#define COUNTSHOW_H

#include <QDialog>
#include "datalist.h"
namespace Ui {
class CountShow;
}

class CountShow : public QDialog
{
    Q_OBJECT

public:
    explicit CountShow(QWidget *parent = 0);
    ~CountShow();

private slots:
    void onTimeOut();

private:
    Ui::CountShow *ui;
    QTimer *pTimer; //定时器
    int count_Number;  //计时处理

};

#endif // COUNTSHOW_H
