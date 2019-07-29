#include "Device_Support.h"


Device_Support::Device_Support(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
	ReadXMLFile(XML_DEVICE);


	ui.treeWidget_Device->setColumnCount(1); //��������
	ui.treeWidget_Device->setHeaderLabel(QString::fromLocal8Bit("�豸ѡ��")); //����ͷ�ı���
	
	Item_keyboard = new QTreeWidgetItem(ui.treeWidget_Device, QStringList() << QString::fromLocal8Bit("����") << QString::number(0));
	//imageItem1->setIcon(0, QIcon("xxx.png"));
	//QTreeWidgetItem *imageItem1_1 = new QTreeWidgetItem(imageItem1, QStringList(QString("Band1"))); //�ӽڵ�1
	//imageItem1->addChild(imageItem1_1); //����ӽڵ�
	
	Item_Camera = new QTreeWidgetItem(ui.treeWidget_Device, QStringList() << QString::fromLocal8Bit("����ͷ") << QString::number(1));
	//QTreeWidgetItem *imageItem2_1 = new QTreeWidgetItem(imageItem2, QStringList(QString("Band1"))); //�ӽڵ�1
	//QTreeWidgetItem *imageItem2_2 = new QTreeWidgetItem(imageItem2, QStringList(QString("Band2"))); //�ӽڵ�2
	//imageItem2->addChild(imageItem2_1);  //����ӽڵ�
	//imageItem2->addChild(imageItem2_2);

	ui.treeWidget_Device->expandAll(); //���ȫ��չ��

	on_reflechButton_clicked();

	connect(ui.treeWidget_Device, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(checkself(QTreeWidgetItem*, int)));


	
}


Device_Support::~Device_Support()
{
	
}

void Device_Support::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		break;
	default:
		QDialog::keyPressEvent(event);
	}
}

void Device_Support::checkself(QTreeWidgetItem* item, int column) {
	if (item->checkState(0) == Qt::Checked) {
		QTreeWidgetItem *parent = item->parent();
		if (parent->text(1).toInt() == 1) { //����ͷֻ����ͬʱѡ��һ��
			for (int i = 0; i < parent->childCount(); i++) {
				parent->child(i)->setCheckState(0, Qt::Unchecked);
			}
			item->setCheckState(0, Qt::Checked);
		}
	}
	
}

int Device_Support::ReadXMLFile(QString FilePath) {
	tinyxml2::XMLDocument docXml;
	if (docXml.LoadFile(FilePath.toStdString().c_str()) != 0)
	{
		return -1;
	}
	XMLElement* elmtRoot = docXml.RootElement();

	//Get Setting
	XMLElement *elmtSet = elmtRoot->FirstChildElement("DEVICE");
	
	int ind = 0;
	while (elmtSet != NULL)
	{
		DEVICE device = DEVICE(elmtSet);
		QString a = QString("%1 %2").arg(elmtSet->Attribute("PID")).arg(elmtSet->Attribute("VID"));
		infos_Device.append(device);

		infos_Device_Hash[a] = ind;
		ind++;
		elmtSet = elmtSet->NextSiblingElement();//��һ���ֵܽڵ�
	}
	return 0;
}

void Device_Support::on_SetButton_clicked() {
	for (int i = 0; i < infos_Device.size(); i++) {
		infos_Device[i].choose = false;
	}
	for (int i = 0; i < Item_keyboard->childCount() ; i++) {
		if(Item_keyboard->child(i)->checkState(0)==Qt::Checked)
			infos_Device[Item_keyboard->child(i)->text(1).toInt()].choose = true;
		
	}
	for (int i = 0; i< Item_Camera->childCount() ; i++) {
		if (Item_keyboard->child(i)->checkState(0) == Qt::Checked)
			infos_Device[Item_keyboard->child(i)->text(1).toInt()].choose = true;
	}

	for (int i = 0; i < infos_Device.size(); i++) {
		qDebug() << infos_Device[i].Name <<  infos_Device[i].choose << endl;
	}
}
void Device_Support::on_reflechButton_clicked() {
	//GetPCIDeviceInfos(infos_PCI);
	//ui.textBrowser->append("PCI\n");
	//for (int i = 0; i < infos_PCI.size(); i++) {
	//	ui.textBrowser->append(QString("%1 %2 %3").arg(infos_PCI[i].desc).arg(infos_PCI[i].vid).arg(infos_PCI[i].pid));
	//}

	/*��ȡϵͳUSB�豸��Ϣ*/
	GetUSBDeviceInfos(infos_USB);
	//for (int i = 0; i < infos_USB.size(); i++) {
	//	qDebug()<<QString("%1 %2 %3 %4").arg(infos_USB[i].desc).arg(infos_USB[i].vid).arg(infos_USB[i].pid).arg(infos_USB[i].type)<<endl;
	//}

	for (int i = 0; i < infos_Device.size(); i++) {
		infos_Device[i].linked = false;
	}

	for (int i = Item_keyboard->childCount() - 1; i >= 0; i--) {
		delete Item_keyboard->takeChild(i);
	}
	for (int i = Item_Camera->childCount() - 1; i >= 0; i--) {
		delete Item_Camera->takeChild(i);
	}


	/*��ȡĿ���豸��Ϣ*/
	for (int i = 0; i < infos_USB.size(); i++) {
		QString a = QString("%1 %2").arg(infos_USB[i].pid).arg(infos_USB[i].vid);
		if (infos_Device_Hash.contains(a)) {
			qDebug() << a << endl;
			int ind = infos_Device_Hash[a];
			if (!infos_Device[ind].linked) {
				infos_Device[ind].linked = true;
				QTreeWidgetItem *imageItem;
				qDebug() << int(infos_Device[ind].type) << endl;
				switch (infos_Device[ind].type) {
				case DEVICE_HID::KEYBoard:
					imageItem = new QTreeWidgetItem(Item_keyboard, QStringList()<<infos_Device[ind].Name<<QString::number(ind)); //�ӽڵ�1
					imageItem->setCheckState(0, Qt::Unchecked);
					
					//Item_keyboard->addChild(imageItem); //����ӽڵ�
					
					break;
				case DEVICE_HID::Camera:
					qDebug() << a << endl;
					imageItem = new QTreeWidgetItem(Item_Camera, QStringList() << infos_Device[ind].Name << QString::number(ind)); //�ӽڵ�1
					imageItem->setCheckState(0, Qt::Unchecked);
					//Item_keyboard->addChild(imageItem); //����ӽڵ�
					break;
				}
			}
			
		}
		
	}
//
//
//	/*������ڵ�*/
//	for (int i = Item_keyboard->childCount()-1; i >=0; i--) {
//		delete Item_keyboard->takeChild(i);
//	}
//	for (int i = Item_Camera->childCount() - 1; i >= 0; i--) {
//		delete Item_Camera->takeChild(i);
//	}
//	for (int i = 0; i < infos_Device_Cur.size(); i++) {
//		QTreeWidgetItem *imageItem;
//
//		switch (infos_Device_Cur[i].type) {
//		case DEVICE_HID::KEYBoard:
//			imageItem = new QTreeWidgetItem(Item_keyboard, QStringList(infos_Device_Cur[i].Name)); //�ӽڵ�1
//			imageItem->setCheckState(0, Qt::Unchecked);
//			Item_keyboard->addChild(imageItem); //����ӽڵ�
//			break;
//		case DEVICE_HID::Camera:
//			imageItem = new QTreeWidgetItem(Item_Camera, QStringList(infos_Device_Cur[i].Name)); //�ӽڵ�1
//			imageItem->setCheckState(0, Qt::Checked);
//			Item_Camera->addChild(imageItem); //����ӽڵ�
//			break;
//		default:
//			break;
//		}
//	}
}

int Device_Support::GetPCIDeviceInfos(QList<PCI_INFO> &infos)
{
	infos.clear();

	bool ok;
	QString str;
	PCI_INFO info;
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData;
	WCHAR buffer[INTERFACE_DETAIL_SIZE] = { 0 };

	SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
	DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

	if ((hDevInfo = SetupDiGetClassDevs(NULL, L"PCI", 0, DIGCF_PRESENT | DIGCF_ALLCLASSES)) == INVALID_HANDLE_VALUE) {
		// Insert error handling here.
		return 0;
	}

	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	// �豸���=0,1,2... ��һ�����豸�ӿڣ���ʧ��Ϊֹ
	for (int i = 0; SetupDiEnumDeviceInfo(hDevInfo, i,
		&DeviceInfoData); i++)
	{
		DWORD DataT;
		DWORD buffersize = 0;


		if (!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&DeviceInfoData,
			SPDRP_HARDWAREID,
			&DataT,
			(PBYTE)buffer,
			INTERFACE_DETAIL_SIZE,
			&buffersize))
		{
			continue;
		}

		str = QString::fromWCharArray(buffer, wcslen(buffer));
		info.vid = str.mid(str.indexOf("VEN") + 4, 4).toULong(&ok, 16);
		info.pid = str.mid(str.indexOf("DEV") + 4, 4).toULong(&ok, 16);


		memset(buffer, 0, INTERFACE_DETAIL_SIZE);
		if (!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&DeviceInfoData,
			SPDRP_LOCATION_INFORMATION,
			&DataT,
			(PBYTE)buffer,
			INTERFACE_DETAIL_SIZE,
			&buffersize))
		{
			continue;
		}
		QStringList list;
		str = QString::fromWCharArray(buffer);
		QRegExp rx("(\\d+)");
		int pos = 0;

		while ((pos = rx.indexIn(str, pos)) != -1) {
			list << rx.cap(1);
			pos += rx.matchedLength();
		}
		info.busNum = list.at(0).toULong(&ok, 10);
		info.devNum = list.at(1).toULong(&ok, 10);
		info.funcNum = list.at(2).toULong(&ok, 10);

		memset(buffer, 0, INTERFACE_DETAIL_SIZE);
		if (!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&DeviceInfoData,
			SPDRP_DEVICEDESC,
			&DataT,
			(PBYTE)buffer,
			INTERFACE_DETAIL_SIZE,
			&buffersize))
		{
			continue;
		}
		info.desc = QString::fromWCharArray(buffer);

		ULONG pulStatus;
		ULONG pulProblemNumber;
		CM_Get_DevNode_Status(&pulStatus, &pulProblemNumber, DeviceInfoData.DevInst, 0);

		if ((pulStatus & DN_HAS_PROBLEM) && !(pulStatus & DN_DRIVER_LOADED))
		{
			info.enable = false;
		}
		else
		{
			info.enable = true;
		}

		infos.append(info);
	}

	//  Cleanup
	SetupDiDestroyDeviceInfoList(hDevInfo);

	return 0;
}

int Device_Support::GetUSBDeviceInfos(QList<USB_INFO> &infos)
{
	infos.clear();

	bool ok;
	QString str;
	USB_INFO info;
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData;
	WCHAR buffer[INTERFACE_DETAIL_SIZE] = { 0 };

	if ((hDevInfo = SetupDiGetClassDevs(NULL, L"USB", 0, DIGCF_PRESENT | DIGCF_ALLCLASSES)) == INVALID_HANDLE_VALUE) {
		// Insert error handling here.
		return 0;
	}

	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	// �豸���=0,1,2... ��һ�����豸�ӿڣ���ʧ��Ϊֹ
	for (int i = 0; SetupDiEnumDeviceInfo(hDevInfo, i,
		&DeviceInfoData); i++)
	{
		DWORD DataT;
		DWORD buffersize = 0;
		if (!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&DeviceInfoData,
			SPDRP_HARDWAREID,
			&DataT,
			(PBYTE)buffer,
			INTERFACE_DETAIL_SIZE,
			&buffersize))
		{
			continue;
		}

		str = QString::fromWCharArray(buffer, wcslen(buffer));
		info.vid = str.mid(str.indexOf("VID") + 4, 4).toULong(&ok, 16);
		info.pid = str.mid(str.indexOf("PID") + 4, 4).toULong(&ok, 16);

		memset(buffer, 0, INTERFACE_DETAIL_SIZE);
		if (!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&DeviceInfoData,
			SPDRP_DEVICEDESC,           // �豸������Ϣ
			&DataT,
			(PBYTE)buffer,
			INTERFACE_DETAIL_SIZE,
			&buffersize))
		{
			continue;
		}
		info.desc = QString::fromWCharArray(buffer);

		//�豸����
		memset(buffer, 0, INTERFACE_DETAIL_SIZE);
		if (!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&DeviceInfoData,
			SPDRP_CLASS,           // �豸 SPDRP_CLASS SPDRP_SERVICE
			&DataT,
			(PBYTE)buffer,
			INTERFACE_DETAIL_SIZE,
			&buffersize))
		{
			continue;
		}
		info.type = QString::fromWCharArray(buffer);


		memset(buffer, 0, INTERFACE_DETAIL_SIZE);
		if (!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&DeviceInfoData,
			SPDRP_MFG,          // ������
			&DataT,
			(PBYTE)buffer,
			INTERFACE_DETAIL_SIZE,
			&buffersize))
		{
			continue;
		}
		info.manufacturer = QString::fromWCharArray(buffer);

		ULONG pulStatus;
		ULONG pulProblemNumber;
		CM_Get_DevNode_Status(&pulStatus, &pulProblemNumber, DeviceInfoData.DevInst, 0);

		if ((pulStatus & DN_HAS_PROBLEM) && !(pulStatus & DN_DRIVER_LOADED))
		{
			info.enable = false;
		}
		else
		{
			info.enable = true;
		}

		infos.append(info);
	}

	//  Cleanup
	SetupDiDestroyDeviceInfoList(hDevInfo);

	return 0;
}