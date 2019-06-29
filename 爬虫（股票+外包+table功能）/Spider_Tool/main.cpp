#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("微软雅黑");
    //将此字体设为QApplication的默认字体
    QApplication::setFont(font);
    a.setWindowIcon(QIcon(":/main.ico"));
    MainWindow w;
    w.show();

    return a.exec();
}
