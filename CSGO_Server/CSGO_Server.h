#pragma once

#include <QtWidgets/QMainWindow>
#include <QDateTime>
#include "ui_CSGO_Server.h"
#include <QDebug>
#include "server.h"

#include "LedDLL.h"
#pragma comment(lib,"InterDLL")

class CSGO_Server : public QMainWindow
{
	Q_OBJECT

public:
	CSGO_Server(QWidget *parent = Q_NULLPTR);
	~CSGO_Server();

private:
	

private slots:
	void getData(QString data);
	void getCSGOResult(int type);
	void on_checkButton_clicked();

private:
	Ui::CSGO_ServerClass ui;
	Server *m_server;

};