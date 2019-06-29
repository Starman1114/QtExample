#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/main.ico"));
    Dialog w;
    w.setWindowTitle("彭堉斌毕设");
    w.setAttribute( Qt::WA_DeleteOnClose, true );
    w.show();

    return a.exec();
}
