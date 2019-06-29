#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/main.ico"));
    MainWindow w;
    //要对你的窗口设置WA_DeleteOnClose属性，默认的情况下关闭窗口仅仅意味着隐藏它
    w.setAttribute( Qt::WA_DeleteOnClose, true );
  //  w.setWindowTitle("彭堉斌毕设作品");

    w.show();
    return a.exec();

}
