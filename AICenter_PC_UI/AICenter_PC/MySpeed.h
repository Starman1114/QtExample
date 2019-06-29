#ifndef MySPEED_H
#define MySPEED_H

#include <QtWidgets/QDialog>
#include "ui_MySpeed.h"
#include "Image_Big.h"
#include "FormSet.h"

class MySpeed : public QDialog
{
    Q_OBJECT

public:
    explicit MySpeed(QWidget *parent = Q_NULLPTR);
    ~MySpeed();
	bool addItem(int ind);

private slots:
	void deleteGame(int ind);

signals:
	void deleteG(int ind);

private:
    Ui::MySpeed_Class ui;
};

#endif // MySPEED_H
