#pragma once

#include <QPushButton>
#include <QFont>
#include <QFontDatabase>
#include <QFile>
#include <qDebug>
#include <QHash>
#include <QPair>
#include <string>
#include <QKeyEvent>
#include <QMetaEnum>
using namespace std;
/*窗口*/
#include <qmath.h>
#include <QPainter>
#include <QDesktopWidget>
#include "qapplication.h"
#include <QButtonGroup>

/*XML读取*/
#include "tinyxml2.h" 
#ifndef __MSXML_LIBRARY_DEFINED__
#define __MSXML_LIBRARY_DEFINED__
#endif
#include <Windows.h>
using namespace tinyxml2;
#define XML_DEVICE "./include/DEVICELIST.xml"
#define XML_Game_CONF "./include/GameList_Conf.xml"
#define AI_GAME_LEN	 2 
typedef enum
{
	PBUG = 0,
	CSGO
}GAME;


enum class DEVICE_HID {
	KEYBoard = 0,
	Mouse,
	Mouse_Dian,
	Jixiang,
	Yinxiang,
	Camera
};

enum class MODE_TYPE {
	Drop = 0,
	HotKey
};


typedef struct _device {
	bool linked = false;
	bool choose = false;
	DEVICE_HID type;
	int vid;			// 产品ID
	int pid;			// 厂商ID
	QString Name;
	_device(XMLElement *Mod) {
		Name = Mod->Attribute("Name");
		type = DEVICE_HID(atoi(Mod->Attribute("TYPE")));
		vid = atoi(Mod->Attribute("VID"));
		pid = atoi(Mod->Attribute("PID"));
	}
}DEVICE;
extern QHash<QString, int>infos_Device_Hash;  //QString : pid vid
extern QList<DEVICE> infos_Device;


typedef struct  _MODE_CONF {
	QString Name;
	MODE_TYPE type;
	bool choose = false;
	QString HotKey;
	QStringList DropList;
	_MODE_CONF(XMLElement *Mod) {
		Name = QString(Mod->Attribute("Name"));
		type = MODE_TYPE(QString(Mod->Attribute("Type")).toInt());
		XMLElement* Drop_HotKey;
		switch (type) {
		case MODE_TYPE::Drop:
			Drop_HotKey = Mod->FirstChildElement("Drop");
			while (Drop_HotKey != NULL) {
				DropList.append(QString(Drop_HotKey->GetText()));
				Drop_HotKey = Drop_HotKey->NextSiblingElement();//下一个兄弟节点
			}
			break;
		case MODE_TYPE::HotKey:
			Drop_HotKey = Mod->FirstChildElement("HotKey");
			HotKey = QString(Drop_HotKey->GetText());
			break;
		}
		
	}

}AI_MODE_CONF;

typedef struct  _DEVICE_CONF {
	QString Name;
	DEVICE_HID type;
	vector<AI_MODE_CONF> modeList;
	_DEVICE_CONF(XMLElement *Mod) {
		Name = QString(Mod->Attribute("Name"));
		type = DEVICE_HID(QString(Mod->Attribute("Type")).toInt());
		XMLElement* mode = Mod->FirstChildElement("Mode");

		while (mode != NULL) {
			modeList.push_back(AI_MODE_CONF(mode));
			mode = mode->NextSiblingElement();//下一个兄弟节点
		}


	}
}AI_DEVICE_CONF;

typedef vector<AI_DEVICE_CONF> AI_DEVICE_LIST;
typedef struct  _GAME_CONF {
	QString Name;
	GAME gtype;
	QString Describe;
	AI_DEVICE_LIST DeviceList;
	_GAME_CONF(XMLElement *Mod) {
		Name = QString(Mod->Attribute("Name"));
		gtype = GAME(QString(Mod->Attribute("Type")).toInt());
		XMLElement* Desc = Mod->FirstChildElement("Describe");
		XMLElement* text = Desc->FirstChildElement("text");
		while (text != NULL) {
			Describe.append(QString("%1\n").arg(text->GetText()));
			text = text->NextSiblingElement();//下一个兄弟节点
		}

		XMLElement* Device = Mod->FirstChildElement("Device");
		while (Device != NULL) {
			DeviceList.push_back(AI_DEVICE_CONF(Device));
			Device = Device->NextSiblingElement();//下一个兄弟节点
		}


		//	modInd = AI_MOD(*ModeInd);
		//	Describe = Mod->FirstChildElement("Describe")->GetText();
		//	XML = Mod->FirstChildElement("Path_XML")->GetText();
		//	BIN = Mod->FirstChildElement("Path_BIN")->GetText();
		//	XMLElement* elmtRect = Mod->FirstChildElement("Rect");
		//	Rect[0] = atoi(elmtRect->FirstChildElement("X")->GetText());
		//	Rect[1] = atoi(elmtRect->FirstChildElement("Y")->GetText());
		//	Rect[2] = atoi(elmtRect->FirstChildElement("W")->GetText());
		//	Rect[3] = atoi(elmtRect->FirstChildElement("H")->GetText());
		//	(*ModeInd)++;
		//
	}
}AI_GAME_CONF;



class util
{
public:
	util();
	~util();
};

class FormSet
{
public:
	static void SetIcon(QPushButton* btn, QChar c, int size);
	static void SetIcon(QPushButton* btn, QString c, int size);
	static void SetStyle(QWidget *This, const QString &styleName);

};