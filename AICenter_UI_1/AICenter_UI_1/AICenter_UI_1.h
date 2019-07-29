#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AICenter_UI_1.h"
#include "util.h"
#include "Device_Support.h"
#include "AI_Assist.h"

class AICenter_UI_1 : public QMainWindow
{
	Q_OBJECT

public:
	AICenter_UI_1(QWidget *parent = Q_NULLPTR);
	~AICenter_UI_1();

private slots:
	void buttonJudge(int id);

private:
	void Initialization();
	void paintEvent(QPaintEvent *event);

protected:
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);

signals:
	void deviceChange();
private:
	Ui::AICenter_UI_1Class ui;
	QButtonGroup *buttonGroup;
	
};
