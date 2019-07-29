#include "AICenter_PC.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AICenter_PC w;
	w.show();
	return a.exec();
}
