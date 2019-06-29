#include "SetDialog.h"


SetDialog::SetDialog(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);

	this->setWindowOpacity(0.9);

	ui.imageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.imageList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


	//����QListWidget����ʾģʽ
	ui.imageList->setViewMode(QListView::IconMode);
	//����QListWidget�е�Ԫ��Ĵ�С
	ui.imageList->setIconSize(QSize(178, 32));
	//����QListWidget�е�Ԫ��ļ��
	ui.imageList->setSpacing(10);
	//�����Զ���Ӧ���ֵ�����Adjust��Ӧ��Fixed����Ӧ����Ĭ�ϲ���Ӧ
	ui.imageList->setResizeMode(QListWidget::Adjust);

	
	on_flashButton_clicked();

}

void SetDialog::on_flashButton_clicked() {

	while (ui.imageList->count() > 0)
	{
		ui.imageList->removeItemWidget(ui.imageList->item(0));
		ui.imageList->takeItem(0);
	}

	if (Get_Device_Link()) {
		//����QListWidgetItem����
		QListWidgetItem *deviceItem = new QListWidgetItem;

		ui.imageList->addItem(deviceItem);
		//�������õ�Ԫ��Ŀ�Ⱥ͸߶�
		deviceItem->setSizeHint(QSize(178, 32));
		//����Ԫ����ӵ�QListWidget��
		Device_Choose *device1 = new Device_Choose(0, Device_Name[0]);
		connect(device1, SIGNAL(beChoosen(int, bool)), this, SLOT(checkChoose(int,bool)));
		ui.imageList->setItemWidget(deviceItem, device1);

	}


	if (IsDevicePlug((DEVICE_INDEX)20)) {
		//����QListWidgetItem����
		QListWidgetItem *deviceItem = new QListWidgetItem;

		ui.imageList->addItem(deviceItem);
		//�������õ�Ԫ��Ŀ�Ⱥ͸߶�
		deviceItem->setSizeHint(QSize(178, 32));
		//����Ԫ����ӵ�QListWidget��
		Device_Choose *device2 = new Device_Choose(1, Device_Name[1]);
		connect(device2, SIGNAL(beChoosen(int, bool)), this, SLOT(checkChoose(int, bool)));
		ui.imageList->setItemWidget(deviceItem, device2);
	}
}

void SetDialog::checkChoose(int ind, bool isChoosen) {
	
}

void SetDialog::on_saveButton_clicked() {
	accept();
}

SetDialog::~SetDialog()
{
	while (ui.imageList->count() > 0)
	{
		ui.imageList->removeItemWidget(ui.imageList->item(0));
		ui.imageList->takeItem(0);
	}
}
