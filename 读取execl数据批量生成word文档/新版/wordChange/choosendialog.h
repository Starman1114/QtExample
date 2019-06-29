#ifndef CHOOSENDIALOG_H
#define CHOOSENDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include <QStandardItemModel>
namespace Ui {
class ChoosenDialog;
}

class ChoosenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChoosenDialog(QWidget *parent = 0);
    ~ChoosenDialog();
    QStringList Cells;
    QStringList Bookmarks;
    void getData(QStringList Cells_Origin,QStringList Bookmarks_Origin);

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_cancelButton_clicked();

    void on_okButton_clicked();

    void on_upButton_clicked();

    void on_downButton_clicked();

private:
    void InitSetup();


private:
    Ui::ChoosenDialog *ui;
    QStandardItemModel *studentModel;

};

#endif // CHOOSENDIALOG_H
