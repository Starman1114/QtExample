#ifndef TWOWIDGET_H
#define TWOWIDGET_H

#include <QWidget>

namespace Ui {
class TwoWidget;
}

class TwoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TwoWidget(QWidget *parent = 0);
    ~TwoWidget();

private:
    Ui::TwoWidget *ui;
};

#endif // TWOWIDGET_H
