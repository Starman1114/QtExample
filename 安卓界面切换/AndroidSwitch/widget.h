#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "onewidget.h"
#include "twowidget.h"
#include "setdata.h"
#include <QtWidgets>
#include <QTableWidget>

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
    void on_oneButton_clicked();

    void on_twoButton_clicked();

    void on_rightButton_clicked();

private:
    void SetStyle(const QString &styleName);
    void InitStyle();
    void SetIcon(QPushButton* btn, QString c, int size);
    void SetIcon(QLabel* lab, QString c, int size);

private:
    Ui::Widget *ui;
    QStackedWidget *m_pStackedWidget;
    OneWidget *one;
    TwoWidget *two;
    SetData *setD;
    QFont iconFont;

};

#endif // WIDGET_H
