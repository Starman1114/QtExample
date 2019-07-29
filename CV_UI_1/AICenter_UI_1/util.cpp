#include "util.h"


QHash<QString, int>infos_Device_Hash;
QList<DEVICE> infos_Device;

util::util()
{
}


util::~util()
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

//ÉèÖÃÆ¤·ôÑùÊ½
void FormSet::SetStyle(QWidget *This, const QString &styleName)
{
	QFile file(QString(":/%1/Resources/%2.css").arg(This->metaObject()->className()).arg(styleName));
	if (file.open(QFile::ReadOnly)) {

		QString qss = QLatin1String(file.readAll());
		//qDebug() << qss << endl;
		QString paletteColor = "#00AFF0";
		This->setPalette(QPalette(QColor(paletteColor)));
		qApp->setStyleSheet(qss); 
		file.close();
	}
}