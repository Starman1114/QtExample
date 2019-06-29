#ifndef COUNTSTEP_H
#define COUNTSTEP_H

#include <QDialog>

namespace Ui {
class CountStep;
}

class CountStep : public QDialog
{
    Q_OBJECT

public:
    explicit CountStep(QWidget *parent = 0);
    ~CountStep();

private:
    Ui::CountStep *ui;
};

#endif // COUNTSTEP_H
