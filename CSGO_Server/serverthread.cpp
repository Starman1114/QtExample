#include "serverthread.h"

serverThread::serverThread(qintptr sockDesc, QObject *parent) :
    QThread(parent),
    m_sockDesc(sockDesc)
{

}

serverThread::~serverThread()
{
    m_socket->close();
}

void serverThread::run(void)
{
    m_socket = new MySocket(m_sockDesc);

    if (!m_socket->setSocketDescriptor(m_sockDesc)) {
        return ;
    }

    connect(m_socket, &MySocket::disconnected, this, &serverThread::disconnectToHost);
    connect(m_socket, SIGNAL(dataReady(bool, bool, int,int,int,int)),
            this, SLOT(recvDataSlot(bool, bool, int,int,int,int)));
	
    this->exec();
}


void serverThread::recvDataSlot(bool isplay, bool isMaster, int weapon, int Killhs, int Kills, int Deaths)
{
    emit dataReady(isplay, isMaster, weapon,Killhs,Kills, Deaths);
}

void serverThread::disconnectToHost(void)
{
    m_socket->disconnectFromHost();
    this->quit();
}
