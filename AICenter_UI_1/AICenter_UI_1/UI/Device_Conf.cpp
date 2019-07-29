#include "Device_Conf.h"


Device_Conf::Device_Conf(AI_GAME_CONF *game, QWidget *parent) :
	game(game),QDialog(parent)
{
    ui.setupUi(this);

	
	ui.tabWidget->setTabText(0, QString::fromLocal8Bit("»¶Ó­½çÃæ"));
	ui.label->setText(game->Describe);
	ui.tabWidget->setTabText(1, "VPN");
	ui.tabWidget->widget(1)->setStyleSheet(QString("border-image:url(:/AICenter_UI_1/Resources/images/%1_VPN.jpg);padding:0px;margin:0px;").arg(game->Name));
	
	for (int i = 0; i < game->DeviceList.size(); i++) {
		ui.tabWidget->addTab(new Device_Mode(&(game->DeviceList[i])), game->DeviceList[i].Name);
	}
	ui.tabWidget->setCurrentIndex(0);
}


Device_Conf::~Device_Conf()
{

}


void Device_Conf::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		break;
	default:
		QDialog::keyPressEvent(event);
	}
}