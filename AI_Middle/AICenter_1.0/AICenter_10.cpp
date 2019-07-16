#include "AICenter_10.h"

AICenter_10::AICenter_10(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	AICENTER& AICenter = AICENTER::Instance();
	ui.textBrowser->append(QString("%1").arg(AICenter.Initial("Intel AI")));
	ui.textBrowser->append(QString::fromStdString(AICenter.MODsListReport(GAME_TYPE::CSGO)));
	ui.textBrowser->append(QString::fromStdString(AICenter.ALL_MODsListReport()));
	ui.textBrowser->append(QString("%1").arg(AICenter.CfgMOD(AI_MOD::PBUG_DEAD, AI_Equipment::CPU)));
	AI_MOD HANDS[] = { AI_MOD::PBUG_DEAD,AI_MOD::HEAD_LEFT };
	AI_Equipment EQUITM[] = { AI_Equipment::CPU,AI_Equipment::GPU };
	ui.textBrowser->append(QString("%1").arg(AICenter.CfgMOD(HANDS, EQUITM)));
	ui.textBrowser->append(QString::fromStdString(AICenter.CFG_MODsListReport()));


//	list<string> printDescribe = AIcenter.MODsListReport();
//	for (list<string>::iterator i = printDescribe.begin(); i != printDescribe.end(); ++i)
//	{
//		ui.textBrowser->append(QString::fromStdString(*i));
//	}
	//Server *m_server = new Server(this);
}
