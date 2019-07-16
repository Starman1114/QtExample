#include "HttpServer.h"

QRegExp rx_Player(REXPLAYER);
QRegExp rx_Weapon(REXWEAPON);

HttpServer::HttpServer()
{
}

HttpServer::~HttpServer()
{

}


HTTP_RESULT HttpServer::CheckEnv(HTTP_GAME game) {

	// 检查Steam是否安装
	QSettings *pReg = new QSettings(RUN_KEY, QSettings::NativeFormat);
	QString SteamPath = pReg->value("SteamPath").toString(); //读取注册表值
	if (SteamPath.length() == 0) {
		qDebug() << "Not install Steam!" << endl;
		return HTTP_ERR_LACK_STREAM;
	}
	else 
		qDebug()<<"SteamPath: " << SteamPath <<endl; 
	delete pReg;

	//文件路径初始化
	QDir dir;
	QString cfgDir;
	QString goalCfg;
	QString localCfg;
	switch (game)
	{
	case HTTP_GAME::CSGO :
		cfgDir = QString("%1%2").arg(SteamPath).arg(DIR_CFG_CSGO);
		goalCfg = QString("%1/%2").arg(RESOURCES).arg(FILE_LOCAL_CFG_CSGO);
		localCfg = QString("%1%2/%3").arg(SteamPath).arg(DIR_CFG_CSGO).arg(FILE_LOCAL_CFG_CSGO);
		break;
	default:
		break;
	}

	// 检查CSGO是否安装
	if (!dir.exists(cfgDir)) {
		qDebug() << "Not install CSGO!" << endl;
		return HTTP_ERR_LACK_GAME;
	}
	else
		qDebug() << "CSGO: " << cfgDir << endl;

	//检查目标cfg文件
	if (!QFile::exists(goalCfg)) {
		qDebug() << "Not Goal Cfg File!" << endl;
		return HTTP_ERR_LACK_CFG;
	}
	else
		qDebug() << "Have Goal Cfg File!" << endl;

	
	//检查环境本地cfg文件
	if (!QFile::exists(localCfg)) {
		qDebug() << "Not Local Cfg File!" << endl;
		if (!QFile::copy(goalCfg, localCfg)) {
			qDebug() << "Fail!" << endl;
			return HTTP_ERR_COPY_CFG;
		}
		else 
			qDebug() << "Cfg has been installed!" << endl;
	}
	else {
		qDebug() << "Have Local Cfg File!" << endl;
	}

	return HTTP_ERR_NONE;
}

void HttpServer::incomingConnection(qintptr handle)
{
	serverThread *thread = new serverThread(handle);

	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

	connect(thread, SIGNAL(dataReady(bool, bool, int, int, int, int)),
		this, SLOT(recvData(bool, bool, int, int, int, int)));

	thread->start();
}

void HttpServer::recvData(bool isplay, bool isMaster, int weapon, int Killhs, int Kills, int Deaths)
{
	bool isKh = false;
	if (isMaster) {
		if (!isplay) {
			kills = 0;
			deaths = 0;
			killhs = 0;
		}
		else {
			if (Killhs > killhs) {
				killhs = Killhs;
				isKh = true;
				emit getCSGOEvent(Game_Message::CSGO_KILLhs);
			}
			else {
				killhs = Killhs;
			}
			if (Kills > kills) {
				kills = Kills;
				if (!isKh) {
					emit getCSGOEvent(Game_Message::CSGO_KILL);
				}
				else {
					isKh = false;
				}
			}

			if (Deaths > deaths) {
				deaths = Deaths;
				emit getCSGOEvent(Game_Message::CSGO_DEATH);
			}

			if (isK != weapon) {
				isK = weapon;
				if (isK == 1)
					emit getCSGOEvent(Game_Message::CSGO_KINFE);
				else
					emit getCSGOEvent(Game_Message::CSGO_GUN);
			}
		}
	}

}

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
	emit dataReady(state.length() > 50, user_ID == Player_ID, isKnife, Killhs.toInt(), Kills.toInt(), Deaths.toInt());

}

void MySocket::sendData()
{
	QByteArray buffer;
	buffer.append("HTTP/1.1 200 OK\r\nServer : WAS / 6.0\r\nContent - length : 0\r\n\r\n\r\n");

	this->write(buffer);
}

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
		return;
	}

	connect(m_socket, &MySocket::disconnected, this, &serverThread::disconnectToHost);
	connect(m_socket, SIGNAL(dataReady(bool, bool, int, int, int, int)),
		this, SLOT(recvDataSlot(bool, bool, int, int, int, int)));

	this->exec();
}


void serverThread::recvDataSlot(bool isplay, bool isMaster, int weapon, int Killhs, int Kills, int Deaths)
{
	emit dataReady(isplay, isMaster, weapon, Killhs, Kills, Deaths);
}

void serverThread::disconnectToHost(void)
{
	m_socket->disconnectFromHost();
	this->quit();
}


