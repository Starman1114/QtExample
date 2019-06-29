#ifndef TRASHDIALOG_H
#define TRASHDIALOG_H

#include <QDialog>
#include "datalist.h"

namespace Ui {
class TrashDialog;
}

class TrashDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrashDialog(QWidget *parent = 0);
    ~TrashDialog();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

    void on_allBox_clicked(bool checked);

private:
    Ui::TrashDialog *ui;
    QList<QCheckBox*> CheckList;
};

#endif // TRASHDIALOG_H
