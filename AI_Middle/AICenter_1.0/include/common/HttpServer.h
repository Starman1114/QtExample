#pragma once

#include "httpserver_global.h"

class HTTPSERVER_EXPORT HttpServer : public QTcpServer
{
	Q_OBJECT
public:
	HttpServer();
	~HttpServer();
	HTTP_RESULT CheckEnv(HTTP_GAME game);

private:
	//void incomingConnection(int sockDesc);
	void incomingConnection(qintptr handle);


signals:
	void getCSGOResult(Game_Message type);
	
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
