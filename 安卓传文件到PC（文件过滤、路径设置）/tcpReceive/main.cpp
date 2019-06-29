#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/main.ico"));
    MainWindow w;
    w.setWindowTitle("服务器");
    w.show();

    return a.exec();
}
