#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QTcpSocket>
#include <QHostAddress>
#include "httpserver_global.h"
class MySocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MySocket(int sockDesc, QObject *parent = Q_NULLPTR);
    ~MySocket();

signals:
    void dataReady(bool isplay, bool isMaster, int weapon, int Kills, int Killhs, int Deaths);

public slots:
    void recvData(void);
	void sendData();

private:
    int m_sockDesc;
	int pos;
};

#endif // MYSOCKET_H
