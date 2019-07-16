#include "server.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
  
}

Server::~Server()
{

}

void Server::CheckEnv() {

	// 检查Steam是否安装
	QSettings *pReg = new QSettings(RUN_KEY, QSettings::NativeFormat);
	QString SteamPath = pReg->value("SteamPath").toString();
	if (SteamPath.length() == 0) {
		emit getData("Not install Steam!\n"); //读取注册表值
		return;
	}
	else {
		emit getData("SteamPath: " + SteamPath + "\n"); //读取注册表值
	}
	delete pReg;

	// 检查CSGO是否安装
	QDir dir;
	QString cfgDir = QString("%1%2").arg(SteamPath).arg(DIR_CSGO_CFG);
	if (!dir.exists(cfgDir))
	{
		emit getData("Not install CSGO!\n"); //读取注册表值
		return;
	}
	else {
		emit getData("CSGO: " + cfgDir + "\n"); //读取注册表值
	}

	//检查目标cfg文件
	QString goalCfg = QString("%1/%2").arg(RESOURCES).arg(FILE_LOCAL_CFG);
	if (!QFile::exists(goalCfg)) {
		emit getData("Not Goal Cfg File!\n");
		return;
	}
	else {
		emit getData("Have Goal Cfg File!\n");
	}

	//检查环境本地cfg文件
	if (!QFile::exists(QString("%1%2/%3").arg(SteamPath).arg(DIR_CSGO_CFG).arg(FILE_LOCAL_CFG))) {
		emit getData("Not Local Cfg File!\n");

		//if (!QFile::copy(goalCfg, QString("%1%2/%3").arg(SteamPath).arg(DIR_CSGO_CFG).arg(FILE_LOCAL_CFG)))
		//if (!QFile::copy(goalCfg, QString("C:/Program Files (x86)/Steam/steamapps/common/Counter-Strike Global Offensive/csgo/cfg/%1").arg(FILE_LOCAL_CFG)))
		if (!QFile::copy(goalCfg, QString("%1%2/%3").arg(SteamPath).arg(DIR_CSGO_CFG).arg(FILE_LOCAL_CFG)))
		{
			emit getData("Fail!\n");
		}
		else {
			emit getData("Cfg has been installed!\n");
		}

	}
	else {
		emit getData("Have Local Cfg File!\n");
	}
}


void Server::incomingConnection(qintptr handle)
{
    serverThread *thread = new serverThread(handle);

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    connect(thread, SIGNAL(dataReady(bool, bool,int,int,int,int)),
            this, SLOT(recvData(bool, bool,int, int,int,int)));

    thread->start();
}

void Server::recvData(bool isplay, bool isMaster, int weapon, int Killhs, int Kills, int Deaths)
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
				emit getData("killhs");
				emit getCSGOResult(3);
			}
			else {
				killhs = Killhs;
			}
			if (Kills > kills) {
				kills = Kills;
				if (!isKh) {
					emit getData("Kill");
					emit getCSGOResult(1);
				}
				else {
					isKh = false;
				}
			}
			
			if (Deaths > deaths) {
				deaths = Deaths;
				emit getCSGOResult(2);
				emit getData("Deaths");
			}

			if (isK != weapon) {
				isK = weapon;
				if(isK==1)
					emit getCSGOResult(4);
				else
					emit getCSGOResult(5);
			}
		}
	}
	
}