#include "widget.h"
#include <QApplication>
#include <QIcon>
#include <qscreen.h>
#include "QTextCodec"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    Widget w;
    w.show();

    return a.exec();
}