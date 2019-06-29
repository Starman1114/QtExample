#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QThread>
#include <QtCore>
#include <QList>
#include <QLabel>

#include <QtBluetooth/qbluetoothglobal.h>
#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothsocket.h>
#include <QBluetoothDeviceDiscoveryAgent>

#define dataLength_One 44
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void initStyle();

    void on_openButton_clicked();

    void on_closeButton_clicked();

    void on_scanButton_clicked();

    void addBlueToothDevicesToList( const QBluetoothDeviceInfo &info );

    void itemActivated(QListWidgetItem *item);

    void readBluetoothDataEvent();

    void on_breakButton_clicked();

    void on_clearButton_clicked();

    void dataChartSetUp();

    void on_recordButton_clicked();

private:
    Ui::MainWindow *ui;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;
    QBluetoothSocket *socket;
    unsigned char comBuffer[15];
    unsigned int  comCount;
    QByteArray buffer;//缓存区
    QList<QStringList> Name;
    QStringList Unit={"g","°/s","°","mG"};
    QList<QLabel*> dataListShow; //数据
    int Lable_count=0;

    char packBuffer[11];
    float fData[32];
};

#endif // MAINWINDOW_H
