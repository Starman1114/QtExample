#include "FormSet.h"



FormSet::FormSet()
{
	
}


FormSet::~FormSet()
{
}

void FormSet::SetIcon(QPushButton* btn, QChar c, int size) {
	QFont iconFont;
	iconFont.setPointSize(size);
	btn->setFont(iconFont);  
	btn->setText(c); 
}

void FormSet::SetIcon(QPushButton* btn, QString c, int size) {
	QFont iconFont;
	iconFont.setPointSize(size);
	btn->setFont(iconFont);
	btn->setText(c);
}

QStringList GameList_Name = { "PUBG","CsGo"};

QStringList GameList_Image = { "pbug","csgo"};


QStringList Device_Name = { "DELUX ","Coolermaster MK730"};