#ifndef ONEWIDGET_H
#define ONEWIDGET_H

#include <QWidget>

namespace Ui {
class OneWidget;
}

class OneWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OneWidget(QWidget *parent = 0);
    ~OneWidget();

private:
    Ui::OneWidget *ui;
};

#endif // ONEWIDGET_H
