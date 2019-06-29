#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "datalist.h"
#include "setdata.h"
#include "workwidget.h"
#include <QtWidgets>
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
    void on_rightButton_clicked();

    void on_leftButton_clicked();

private:
    void SetStyle(const QString &styleName);
    void InitStyle();
    void SetIcon(QPushButton* btn, QString c, QString family,int size, int weight);
    void SetIcon(QLabel* lab, QString c, QString family,int size, int weight);

private:
    Ui::Widget *ui;
    QStackedWidget *m_pStackedWidget;
    WorkWidget *workW;
    SetData *setD;

    int height;
    int weight;
};

#endif // WIDGET_H
