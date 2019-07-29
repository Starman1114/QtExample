#ifndef DEVICE_SUPPORT_H
#define DEVICE_SUPPORT_H

#include <QtWidgets/QDialog>
#include <QTreeWidgetItem>
#include "ui_Device_Support.h"
#include "util.h"

#include <Windows.h>
#include <setupapi.h>
#include <QRegExp>
#include <QStringList>
#include <Cfgmgr32.h>

#include <QWidget>
#include <windows.h>
#include <QString>
#include <dbt.h>
#pragma comment(lib, "Setupapi.lib")
#define INTERFACE_DETAIL_SIZE   (1024)

typedef struct _pci_info {
	bool enable;		// �豸���ñ�־
	ulong busNum;		// ���ߺ�
	ulong devNum;		// �豸��
	ulong funcNum;		// ���ܺ�
	ulong vid;			// ��ƷID
	ulong pid;			// ����ID
	QString desc;		// �豸������Ϣ

}PCI_INFO;

typedef struct _usb_info {
	bool enable;		// �豸���ñ�־	
	ulong vid;			// ��ƷID
	ulong pid;			// ����ID

	QString type;   //�豸����   camera�� Image   keyboard �� HIDClass
	QString desc;           // �豸������Ϣ
	QString manufacturer;   // ��������Ϣ

}USB_INFO;





class Device_Support : public QDialog
{
    Q_OBJECT

public:
    explicit Device_Support(QWidget *parent = Q_NULLPTR);
    ~Device_Support();

	static int GetPCIDeviceInfos(QList<PCI_INFO> &infos);
	static int GetUSBDeviceInfos(QList<USB_INFO> &infos);

private slots:
	void on_reflechButton_clicked();
	void on_SetButton_clicked();
	void checkself(QTreeWidgetItem* item, int column);

signals:
private:
	int ReadXMLFile(QString FilePath);
	void keyPressEvent(QKeyEvent *event);


private:
    Ui::Device_Support_Class ui;
	QList<PCI_INFO> infos_PCI;
	QList<USB_INFO> infos_USB;
	QList<DEVICE> infos_Device;

	QTreeWidgetItem *Item_keyboard;
	QTreeWidgetItem *Item_Camera;
};

#endif // DEVICE_SUPPORT_H
