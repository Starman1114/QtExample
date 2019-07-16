#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QObject>
#include <QtNetwork>
#include <QDebug>

#include "mysocket.h"

class Socket;

class serverThread : public QThread
{
    Q_OBJECT
public:
    serverThread(qintptr sockDesc, QObject *parent = Q_NULLPTR);
    ~serverThread();

private:
    void run(void);

signals:
    void dataReady(bool isplay, bool isMaster, int weapon, int Killhs, int Killss, int Deaths);

private slots:   
    void recvDataSlot(bool isplay, bool isMaster, int weapon, int Killhs, int Kills, int Deaths);
    void disconnectToHost(void);

private:
    MySocket *m_socket;

	qintptr m_sockDesc;
};

#endif // SERVERTHREAD_H
