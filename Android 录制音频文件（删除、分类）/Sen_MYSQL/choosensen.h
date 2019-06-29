#ifndef CHOOSENSEN_H
#define CHOOSENSEN_H

#include <QDialog>
#include "datalist.h"

namespace Ui {
class ChoosenSen;
}

class ChoosenSen : public QDialog
{
    Q_OBJECT

public:
    explicit ChoosenSen(QWidget *parent = 0);
    ~ChoosenSen();

private slots:
    void on_commonButton_clicked();

    void on_nervousButton_clicked();

    void on_confButton_clicked();

    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    Ui::ChoosenSen *ui;
    QString SenData;
};

#endif // CHOOSENSEN_H
