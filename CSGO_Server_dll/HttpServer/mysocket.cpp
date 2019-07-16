#include "mysocket.h"

MySocket::MySocket(int sockDesc, QObject *parent) :
    QTcpSocket(parent),
    m_sockDesc(sockDesc)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(recvData()));

}

MySocket::~MySocket()
{

}

void MySocket::recvData(void)
{
	QByteArray buffer = readAll();
	QString data = QString::fromLocal8Bit(buffer);
	pos = data.indexOf(rx_Player);
	QString user_ID = rx_Player.cap(1);
	QString state = rx_Player.cap(2);
	QString Player_ID = rx_Player.cap(3);
	QString Killhs = rx_Player.cap(4);
	QString Weapon = rx_Player.cap(5);
	QString Kills = rx_Player.cap(6);
	QString Deaths = rx_Player.cap(7);
	pos = Weapon.indexOf(rx_Weapon);
	QString KnifeState = rx_Weapon.cap(1);
	int isKnife = -1;
	if (KnifeState == "active") {
		isKnife = 1;
	}
	else {
		isKnife = 0;
	}
	sendData();
	emit dataReady(state.length()>50,user_ID == Player_ID, isKnife, Killhs.toInt(), Kills.toInt(), Deaths.toInt());
	
}

void MySocket::sendData()
{
	QByteArray buffer;
	buffer.append("HTTP/1.1 200 OK\r\nServer : WAS / 6.0\r\nContent - length : 0\r\n\r\n\r\n");

	this->write(buffer);
}