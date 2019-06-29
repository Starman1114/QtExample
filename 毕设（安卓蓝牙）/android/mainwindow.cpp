#include "mainwindow.h"
#include "ui_mainwindow.h"

static const QLatin1String serviceUuid("00001101-0000-1000-8000-00805F9B34FB");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent();
    localDevice = new QBluetoothLocalDevice();
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    connect(discoveryAgent,
            SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this,
            SLOT(addBlueToothDevicesToList(QBluetoothDeviceInfo))
            );
    connect(ui->list,
            SIGNAL(itemActivated(QListWidgetItem*)),
            this,
            SLOT(itemActivated(QListWidgetItem*))
            );

    connect(socket,
            SIGNAL(readyRead()),
            this,
            SLOT(readBluetoothDataEvent())
            );
    connect(socket,
            SIGNAL(connected()),
            this,
            SLOT(bluetoothConnectedEvent())
            );

    if( localDevice->hostMode() == QBluetoothLocalDevice::HostPoweredOff ) {
        ui->openButton->setEnabled(true);
        ui->closeButton->setEnabled(false);
    }else {
        ui->openButton->setEnabled(false);
        ui->closeButton->setEnabled(true);
    }


    QStringList NACC={"accX","accY","accZ","ACC"};
    QStringList NGYRO={"gyroX","gyroY","gyroZ","GYRO"};
    QStringList NMAG={"magX","magY","magZ","MAG"};
    QStringList NANGLE={"angleX","angleY","angleZ","ANGLE"};
    Name.append(NACC);
    Name.append(NGYRO);
    Name.append(NANGLE);
    Name.append(NMAG);

    ui->tabWidget->setTabText(0,"数据");
    ui->tabWidget->setTabText(1,"原始数据");
    ui->tabWidget->setCurrentIndex(0);


    ui->headButton->setFlat(true);//去边框
  //
    dataChartSetUp();
    initStyle();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addBlueToothDevicesToList( const QBluetoothDeviceInfo &info )
{
    QString label = QString("%1 %2").arg(info.address().toString()).arg(info.name());

    QList<QListWidgetItem *> items = ui->list->findItems(label, Qt::MatchExactly);

    if (items.empty()) {
        QListWidgetItem *item = new QListWidgetItem(label);
        QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(info.address());
        if (pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired )
            item->setTextColor(QColor(Qt::green));
        else
            item->setTextColor(QColor(Qt::white));
        ui->list->addItem(item);
    }

}

void MainWindow::itemActivated(QListWidgetItem *item)
{
    socket->disconnectFromService();
    QString text = item->text();

    int index = text.indexOf(' ');

    if (index == -1)
        return;

    QBluetoothAddress address(text.left(index));
    QString name(text.mid(index + 1));
    qDebug() << "You has choice the bluetooth address is " << address;
    qDebug() << "The device is connneting.... ";
    QMessageBox::information(this,tr("Info"),name+" is connecting...");
    socket->connectToService(address, QBluetoothUuid(serviceUuid) ,QIODevice::ReadWrite);
}

void MainWindow::readBluetoothDataEvent()
{
   buffer.append(socket->readAll());
   while(buffer.size()>11){
       if(buffer.data()[0]!=0x55){
           buffer.remove(0,1);
           continue;
       }

       QString strData = buffer.left(11).toHex();
       ui->textBrowser->append(strData + "\n");

       buffer.remove(0,1);//去掉0x55
       char head =buffer.data()[0];
       buffer.remove(0,1);
       for (int j = 0; j < 9; j++){
           packBuffer[j] = buffer.data()[0];
           buffer.remove(0,1);
       }

       switch(head){
        case 0x51: //加速度
            fData[0] = ((((short) packBuffer[1]) << 8) | ((short) packBuffer[0] & 0xff)) / 32768.0f * 16;
            fData[1] = ((((short) packBuffer[3]) << 8) | ((short) packBuffer[2] & 0xff)) / 32768.0f * 16;
            fData[2] = ((((short) packBuffer[5]) << 8) | ((short) packBuffer[4] & 0xff)) / 32768.0f * 16;
            for(int k=0;k<3;k++){
                if(fData[k]>10)
                    fData[k]=fData[k]-32;

            }
        //    fData[16] = ((((short) packBuffer[7]) << 8) | ((short) packBuffer[6] & 0xff)) / 100.0f;
            break;
        case 0x52: //角速度
            fData[3] = ((((short) packBuffer[1]) << 8) | ((short) packBuffer[0] & 0xff)) / 32768.0f * 2000;
            fData[4] = ((((short) packBuffer[3]) << 8) | ((short) packBuffer[2] & 0xff)) / 32768.0f * 2000;
            fData[5] = ((((short) packBuffer[5]) << 8) | ((short) packBuffer[4] & 0xff)) / 32768.0f * 2000;
            for(int k=3;k<6;k++){
                if(fData[k]>500)
                    fData[k]=fData[k]-4000;

            }
         //   fData[16] = ((((short) packBuffer[7]) << 8) | ((short) packBuffer[6] & 0xff)) / 100.0f;
         //   RecordData(sHead,String.format("% 10.2f", fData[3])+String.format("% 10.2f", fData[4])+String.format("% 10.2f", fData[5])+" ");
            break;
        case 0x53: //角度
            fData[6] = ((((short) packBuffer[1]) << 8) | ((short) packBuffer[0] & 0xff)) / 32768.0f * 180;
            fData[7] = ((((short) packBuffer[3]) << 8) | ((short) packBuffer[2] & 0xff)) / 32768.0f * 180;
            fData[8] = ((((short) packBuffer[5]) << 8) | ((short) packBuffer[4] & 0xff)) / 32768.0f * 180;
            for(int k=6;k<9;k++){
                if(fData[k]>300)
                    fData[k]=fData[k]-360;
            }
         //   fData[16] = ((((short) packBuffer[7]) << 8) | ((short) packBuffer[6] & 0xff)) / 100.0f;
         //   RecordData(sHead,String.format("% 10.2f", fData[6])+String.format("% 10.2f", fData[7])+String.format("% 10.2f", fData[8]));
            break;
        case 0x54://磁场
            fData[9] = ((((short) packBuffer[1]) << 8) | ((short) packBuffer[0] & 0xff));
            fData[10] = ((((short) packBuffer[3]) << 8) | ((short) packBuffer[2] & 0xff));
            fData[11] = ((((short) packBuffer[5]) << 8) | ((short) packBuffer[4] & 0xff));
           for(int k=9;k<12;k++){
               if(fData[k]>60000)
                   fData[k]=fData[k]-65535;
           }
         //   fData[16] = ((((short) packBuffer[7]) << 8) | ((short) packBuffer[6] & 0xff)) / 100.0f;
         //   RecordData(sHead,String.format("% 10.2f", fData[9])+String.format("% 10.2f", fData[10])+String.format("% 10.2f", fData[11]));
            break;
       }

       for(int k=0;k<dataListShow.length();k++){

       }

       int count=0;
       for(int i=0;i<4;i++){
           for(int j=0;j<3;j++){
               dataListShow[count]->setText(Name[i].at(j)+": "+QString("%1").arg(fData[count])+Unit[i]);
               count++;
           }
       }
   }
}

void MainWindow::initStyle()
{
    //加载样式表
    QFile file(":/qss/psblack.css");
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void MainWindow::on_openButton_clicked()
{
    localDevice->powerOn();
    ui->closeButton->setEnabled(true);
    ui->openButton->setEnabled(false);
    ui->scanButton->setEnabled(true);
}

void MainWindow::on_closeButton_clicked()
{
    localDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
    ui->closeButton->setEnabled(false);
    ui->openButton->setEnabled(true);
    ui->scanButton->setEnabled(false);
}

void MainWindow::on_scanButton_clicked()
{
    ui->list->clear();
    discoveryAgent->start();
  //  ui->scanButton->setEnabled(false);
}

void MainWindow::on_breakButton_clicked()
{
    socket->disconnectFromService();
}

void MainWindow::on_clearButton_clicked()
{
    ui->textBrowser->clear();
    int count=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<3;j++){
            dataListShow[count]->setText(Name[i].at(j));
            count++;
        }
    }
}


void MainWindow::dataChartSetUp()
{
    QVBoxLayout *vbox = new QVBoxLayout;
    for(int i=0;i<4;i++){
        QHBoxLayout *vbox1 = new QHBoxLayout;
        for(int j=0;j<3;j++){
            QLabel *l=new QLabel(Name[i].at(j)+":");
            dataListShow.append(l);
            vbox1->addWidget(dataListShow[Lable_count]);
            Lable_count++;
        }
        vbox->addLayout(vbox1);
    }
    ui->tabWidget->widget(0)->setLayout(vbox);
}

void MainWindow::on_recordButton_clicked()
{

}
