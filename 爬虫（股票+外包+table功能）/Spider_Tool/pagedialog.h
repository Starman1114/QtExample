#ifndef PAGEDIALOG_H
#define PAGEDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class PageDialog;
}

class PageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PageDialog(QWidget *parent = 0,QStringList pageN={});
    ~PageDialog();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

signals:
    void changePageNumber(QStringList pn);

private:
    Ui::PageDialog *ui;
    QStringList pagen;
};

#endif // PAGEDIALOG_H
