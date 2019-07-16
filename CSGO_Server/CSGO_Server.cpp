#include "CSGO_Server.h"

CSGO_Server::CSGO_Server(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//CheckEnv();
	//server = new MyTcpServer("",3000);
	//connect(server, SIGNAL(getData(QString)), this, SLOT(getData(QString)));
	//connect(server, SIGNAL(getResult(int)), this, SLOT(getResult(int)));
	//server->listen(true);

	m_server = new Server(this);
	connect(m_server, SIGNAL(getData(QString)), this, SLOT(getData(QString)));
	connect(m_server, SIGNAL(getCSGOResult(int)), this, SLOT(getCSGOResult(int)));
	//m_server->setMaxPendingConnections(1);
	m_server->listen(QHostAddress::Any, 3000);

	if (Get_Device_Link()) {
		ui.textBrowser->append("Keyboard Linked\n");
		Set_hw_light_mode(0x07);
	}

}

CSGO_Server::~CSGO_Server() {

}

void CSGO_Server::getData(QString data) {
	QDateTime time = QDateTime::currentDateTime();
	ui.textBrowser->append(data + "\n");
}

void CSGO_Server::getCSGOResult(int type) {
	if (type == 1 || type == 3) {
		Set_hw_light_mode(0x15);
	}
	else if (type == 2) {
		Set_hw_light_mode(0x16);
	}
	else if(type == 4)
		Set_hw_light_mode(0x04);
	else if(type == 5)
		Set_hw_light_mode(0x07);

}

void CSGO_Server::on_checkButton_clicked() {
	m_server->CheckEnv();
}