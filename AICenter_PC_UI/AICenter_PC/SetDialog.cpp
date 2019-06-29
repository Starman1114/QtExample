#include "SetDialog.h"


SetDialog::SetDialog(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);

	this->setWindowOpacity(0.9);

	ui.imageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.imageList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


	//设置QListWidget的显示模式
	ui.imageList->setViewMode(QListView::IconMode);
	//设置QListWidget中单元项的大小
	ui.imageList->setIconSize(QSize(178, 32));
	//设置QListWidget中单元项的间距
	ui.imageList->setSpacing(10);
	//设置自动适应布局调整（Adjust适应，Fixed不适应），默认不适应
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
		//定义QListWidgetItem对象
		QListWidgetItem *deviceItem = new QListWidgetItem;

		ui.imageList->addItem(deviceItem);
		//重新设置单元项的宽度和高度
		deviceItem->setSizeHint(QSize(178, 32));
		//将单元项添加到QListWidget中
		Device_Choose *device1 = new Device_Choose(0, Device_Name[0]);
		connect(device1, SIGNAL(beChoosen(int, bool)), this, SLOT(checkChoose(int,bool)));
		ui.imageList->setItemWidget(deviceItem, device1);

	}


	if (IsDevicePlug((DEVICE_INDEX)20)) {
		//定义QListWidgetItem对象
		QListWidgetItem *deviceItem = new QListWidgetItem;

		ui.imageList->addItem(deviceItem);
		//重新设置单元项的宽度和高度
		deviceItem->setSizeHint(QSize(178, 32));
		//将单元项添加到QListWidget中
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
