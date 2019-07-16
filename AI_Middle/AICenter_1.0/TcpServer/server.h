#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

#include <QSettings>
#include <QDir>
#include <QFile>

#include "serverthread.h"
#include "configure.h"

//#define RUN_KEY "HKEY_CURRENT_USER\\SOFTWARE\\Qt\\Qt Apps"
#define RUN_KEY "HKEY_CURRENT_USER\\SOFTWARE\\Valve\\Steam"
#define RESOURCES ":/CSGO_Server/Resources"
#define DIR_CSGO_CFG "/steamapps/common/Counter-Strike Global Offensive/csgo/cfg"
#define FILE_LOCAL_CFG "gamestate_integration_consolesample.cfg"

class Dialog;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = Q_NULLPTR);
    ~Server();
	void CheckEnv();

private:
    //void incomingConnection(int sockDesc);
	void incomingConnection(qintptr handle);
	

signals:
	void getData(QString data);
	void getCSGOResult(int type);

private slots:
	void recvData(bool isplay, bool isMaster, int weapon, int Killhs, int Kills, int Deaths);

private:
	int kills = 0;
	int deaths = 0;
	int killhs = 0;
	QString act = "";
	bool isDeath = false;
	int isK = 0;
    
};

#endif // SERVER_H
