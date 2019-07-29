#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QtWidgets/QDialog>
#include "ui_SetDialog.h"
#include "FormSet.h"
#include "Device_Choose.h"

class SetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetDialog(QWidget *parent = Q_NULLPTR);
    ~SetDialog();

private slots:
	void on_saveButton_clicked();
	void on_flashButton_clicked();
	void checkChoose(int ind, bool isChoosen);

private :
	

private:
    Ui::SetDialog_Class ui;

};

#endif // SETDIALOG_H
