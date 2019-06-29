#ifndef COUNTSTEP_H
#define COUNTSTEP_H

#include <QDialog>
#include "count.h"


namespace Ui {
class CountStep;
}

class CountStep : public QDialog
{
    Q_OBJECT

public:
    explicit CountStep(QWidget *parent = 0);
    ~CountStep();
/**************************************************************************
    * 界面窗口操作
    */
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void InitStyle();

    void ChartShow();
    void StartShow();
    

    
private slots:
/**************************************************************************
    * 界面窗口操作
    */
    void on_btnMenu_Close_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Min_clicked();

    void on_runButton_clicked();

    void changeData();

    void on_zeroButton_clicked();

signals:
    void beClose();

private:
    Ui::CountStep *ui;
    QPoint mousePoint;
    bool mousePressed;
    bool max;
    QRect location;

    Chart *C;
    QChart *chart;
    QChartView *chartView;
    //图示
    FunctionData *F;
    
    Count *CT;


};

#endif // COUNTSTEP_H
