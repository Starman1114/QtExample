#include "CSGO_Server.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CSGO_Server w;
	w.show();

	

	return a.exec();
}
