#include "MyTcpServer.h"



MyTcpServer::MyTcpServer(QString IP_Addresses,int Port)
{
	tcpServer = new QTcpServer();
	if (IP_Addresses == "")
		this->IP_Addresses = QNetworkInterface().allAddresses().at(1).toString();
	else
		this->IP_Addresses = IP_Addresses;
	this->Port = Port;	

	tcpServer->setMaxPendingConnections(1); //�����������������

	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(NewConnectionSlot()));

	// \"player\": \{[0-9a-z\n\t"\s\S]+\},\n\t\"auth
	rx_Player.setPattern("\\\"player\\\": \\{([0-9a-z\\n\\t\"\\s\\S]+)\\},\\n\\t\\\"auth");
	// \"name\": \"��˹��\"    "\\\"name\\\": \\\"��˹��\\\"" 
//	rx_Player_Name.setPattern("\\\"name\\\": \\\"([\u4e00-\u9fa5a-zA-Z0-9]+)\\\"");  //ƥ������[\u4e00-\u9fa5] ������ſ��Խ������ڵ�ͨ��cap��������ȡ
	// \"name\": \"unconnected\",\n\t\t\"activity\": \"playing\"
	rx_Player_Activity.setPattern("\\\"name\\\": \\\"([\u4e00-\u9fa5a-zA-Z0-9]+)\\\",\\n\\t\\t\\\"activity\\\": \\\"([a-z]+)\\\"");
	// "\\\"kills\\\": [0-9]+," 
	//rx_Player_Kills.setPattern("\\\"kills\\\": ([0-9]+),");
	// "\\\"deaths\\\": [0-9]+," 
	//rx_Player_Deaths.setPattern("\\\"deaths\\\": ([0-9]+),");

	rx_Player_States.setPattern("\\\"kills\\\": ([0-9]+),\\n\\t\\t\\t\\\"assists\\\": ([0-9]+),\\n\\t\\t\\t\\\"deaths\\\": ([0-9]+),");
	// "\"kills\\\": 0,\\n\\t\\t\\t\\\"assists\\\": 0,\\n\\t\\t\\t\\\"deaths\\\": 1" 
}


MyTcpServer::~MyTcpServer()
{
	delete tcpServer;
	delete currentClient;
}

void MyTcpServer::CheckEnv() {

	// ���Steam�Ƿ�װ
	QSettings *pReg = new QSettings(RUN_KEY, QSettings::NativeFormat);
	QString SteamPath = pReg->value("SteamPath").toString();
	if (SteamPath.length() == 0) {
		emit getData("Not install Steam!\n"); //��ȡע���ֵ
		return;
	}
	else {
		emit getData("SteamPath: " + SteamPath + "\n"); //��ȡע���ֵ
	}
	delete pReg;

	// ���CSGO�Ƿ�װ
	QDir dir;
	QString cfgDir = QString("%1%2").arg(SteamPath).arg(DIR_CSGO_CFG);
	if (!dir.exists(cfgDir))
	{
		emit getData("Not install CSGO!\n"); //��ȡע���ֵ
		return;
	}
	else {
		emit getData("CSGO: " + cfgDir + "\n"); //��ȡע���ֵ
	}

	//���Ŀ��cfg�ļ�
	QString goalCfg = QString("%1/%2").arg(RESOURCES).arg(FILE_LOCAL_CFG);
	if (!QFile::exists(goalCfg)) {
		emit getData("Not Goal Cfg File!\n");
		return;
	}
	else {
		emit getData("Have Goal Cfg File!\n");
	}

	//��黷������cfg�ļ�
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

// newConnection -> newConnectionSlot �����ӽ����Ĳۺ���
void MyTcpServer::NewConnectionSlot()
{
	currentClient = tcpServer->nextPendingConnection();
//	tcpClient.append(currentClient);
	
	//QMessageBox::information(NULL, "Messag", "A Client is linked", QMessageBox::Yes , QMessageBox::Yes);
	//emit getData(QString("%1 %2 is linked\n").arg(currentClient->peerAddress().toString().split("::ffff:")[1]).arg(currentClient->peerPort()));
	connect(currentClient, SIGNAL(readyRead()), this, SLOT(ReadData()));
//	connect(currentClient, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));
}


// �ͻ������ݿɶ��źţ���Ӧ�Ķ����ݲۺ���
void MyTcpServer::ReadData()
{
	// ����readyRead�źŲ�δ�ṩSocketDecriptor��������Ҫ�������пͻ���
//	for (int i = 0; i < tcpClient.length(); i++)
//	{
	//	QByteArray buffer = tcpClient[i]->readAll();
	//	if (buffer.isEmpty())    
	//		continue;	


	    QByteArray buffer = currentClient->readAll();
		QString data = QString::fromLocal8Bit(buffer);
		//QStringList dataList;
		//while ((pos = rx.indexIn(data, pos)) != -1)
		//{
		//	dataList.push_back(rx.capturedTexts().at(0));
		//	pos += rx.matchedLength();
		//}
		pos = data.indexOf(rx_Player);
		QString Player = rx_Player.cap(1);
		pos = Player.indexOf(rx_Player_Activity);
		QString tName = rx_Player_Activity.cap(1);
		QString Activity = rx_Player_Activity.cap(2);

		if (Activity != act) {
			act = Activity;
			if (act == "menu") {
				user_Name = "";
			}
			else {
				user_Name = tName;
			}
			kills = 0;
			deaths = 0;
		}
		emit getData("Player: "+Player + "\n");
		emit getData(Activity + " " + tName + " " + user_Name + "\n");

		if (tName == user_Name) {
			
			if (Activity == "playing") {
				pos = Player.indexOf(rx_Player_States);
				QString Kills = rx_Player_States.cap(1);
				QString Deaths = rx_Player_States.cap(3);
				if (Kills.length() > 0) {
					int t_kill = Kills.toInt();
					if (t_kill > kills) {
						kills = t_kill;
						emit getResult(Actions::Kills);
						return;
					}
				}
				if (Deaths.length() > 0) {
					int t_death = Deaths.toInt();
					if (t_death > deaths) {
						deaths = t_death;
						emit getResult(Actions::Death);
					}
				}

		
				//pos = data.indexOf(rx_Player_Deaths);
				//QString Deaths = rx_Player_Deaths.cap(1);
				//if (Deaths.length() > 0) {
				//
				//	int t_death = Deaths.toInt();
				//	if (t_death > deaths) {
				//		deaths = t_death;
				//		emit getResult(Actions::Death);
				//	}
				//}
			
			}
		}

		
//	}
	
}
// disconnected -> disconnectedSlot �ͻ��˶Ͽ����ӵĲۺ���
void MyTcpServer::disconnectedSlot()
{
	//QMessageBox::information(NULL, "Messag", "A Client break linking", QMessageBox::Yes, QMessageBox::Yes);
	
	//����disconnected�źŲ�δ�ṩSocketDescriptor��������Ҫ����Ѱ��
//if (!isClientClear) {
//	for (int i = tcpClient.length() - 1; i >= 0; i--)
//	{
//		if (tcpClient[i]->state() == QAbstractSocket::UnconnectedState)
//		{
//		//	emit getData(QString("%1 %2 break linking\n").arg(tcpClient[i]->peerAddress().toString().split("::ffff:")[1]).arg(tcpClient[i]->peerPort()));
//			// ɾ���洢��tcpClient�б��еĿͻ�����Ϣ
//			tcpClient[i]->destroyed();
//			tcpClient.removeAt(i);
//		}
//	}
//}
	
}

// ����--�Ͽ�
bool MyTcpServer::listen(bool l)
{
	if (l)
	{
		return tcpServer->listen(QHostAddress::Any, Port);	
	}
	else
	{
	//	isClientClear = true;
	//	for (int i = tcpClient.length() - 1; i >= 0; i--)//�Ͽ���������
	//	{
	//		tcpClient[i]->disconnectFromHost();
	//		bool ok = tcpClient[i]->waitForDisconnected(1000);
	//		if (!ok)
	//		{
	//			// �����쳣
	//		}
	//		tcpClient.removeAt(i);  //�ӱ���Ŀͻ����б���ȡȥ��
	//	}

		currentClient->disconnectFromHost();
		bool ok = currentClient->waitForDisconnected(1000);

		tcpServer->close();     //���ټ����˿�
	//	isClientClear = false;
		return true;
	}
}