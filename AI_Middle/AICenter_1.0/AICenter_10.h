#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AICenter_10.h"
#include "AICenter_LIB.h"
#include <qDebug>


class AICenter_10 : public QMainWindow
{
	Q_OBJECT

public:
	AICenter_10(QWidget *parent = Q_NULLPTR);

private:
	Ui::AICenter_10Class ui;
};
