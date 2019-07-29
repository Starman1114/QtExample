#pragma once
#include <QPushButton>
#include <QFont>
#include <QFontDatabase>
#include <QFile>
#include <qDebug>
#include <qmath.h>
#include <QPainter>
#include <QListWidget>
#include <QPixmap>
#include <QLabel>
#include <QCheckBox>
#include <QList>
#include "SetDialog.h"

#include "LedDLL.h"
#include "SDKDLL.h"

//#pragma comment(lib, "face_lib.lib")

#pragma comment(lib,"InterDLL")

#ifdef _WIN64
#pragma comment(lib,"SDKDLL64.lib") 
#else
#pragma comment(lib,"SDKDLL.lib") 
#endif


extern QStringList GameList_Name;
extern QStringList GameList_Image;
extern QStringList Device_Name;

struct Device
{
	QString name;
	bool isChoose = false;
};


class FormSet
{
public:
	FormSet();
	~FormSet();
	static void SetIcon(QPushButton* btn, QChar c, int size);
	static void SetIcon(QPushButton* btn, QString c, int size);
	
};

