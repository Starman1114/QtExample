#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QMessageBox>
#include <QDebug>
#include <QRegExp>

#include <QSettings>
#include <QDir>
#include <QFile>

//#define RUN_KEY "HKEY_CURRENT_USER\\SOFTWARE\\Qt\\Qt Apps"
#define RUN_KEY "HKEY_CURRENT_USER\\SOFTWARE\\Valve\\Steam"
#define RESOURCES ":/CSGO_Server/Resources"
#define DIR_CSGO_CFG "/steamapps/common/Counter-Strike Global Offensive/csgo/cfg"
#define FILE_LOCAL_CFG "gamestate_integration_consolesample.cfg"

enum Actions { Kills = 0, Death };

class MyTcpServer :public QObject
{
	Q_OBJECT
public:
	MyTcpServer(QString IP_Addresses, int Port);
	~MyTcpServer();
	bool listen(bool l);
	void CheckEnv();

signals:
	void getData(QString data);
	void getResult(int type);

private slots:
	void NewConnectionSlot();
	void disconnectedSlot();
	void ReadData();

private:
	QTcpServer *tcpServer;
	//QList<QTcpSocket*> tcpClient;
	QTcpSocket *currentClient;
	QString IP_Addresses;
	int Port;
	bool isClientClear = false;
	QRegExp rx_Player;
	QRegExp rx_Player_Activity;
	//QRegExp rx_Player_Name;
	QRegExp rx_Player_States;

	int pos;
	QString user_Name = "";
	int kills = 0;
	int deaths = 0;
	QString act = "";
};

