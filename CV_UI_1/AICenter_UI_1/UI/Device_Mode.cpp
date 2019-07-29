#include "Device_Mode.h"


Device_Mode::Device_Mode(AI_DEVICE_CONF *device, QWidget *parent) :
	device(device),QDialog(parent)
{
    ui.setupUi(this);

	ui.label->setText(QString::fromLocal8Bit("ģʽѡ��"));

	QString image;
	switch (device->type)
	{
	case DEVICE_HID::KEYBoard:
		image = ":/AICenter_UI_1/Resources/images/Keyboard.png";
		break;
	case DEVICE_HID::Camera:
		image = ":/AICenter_UI_1/Resources/images/Camera.jpg";
		break;
	case DEVICE_HID::Mouse:
		image = ":/AICenter_UI_1/Resources/images/Mouse.jpg";
		break;
	case DEVICE_HID::Mouse_Dian:
		image = ":/AICenter_UI_1/Resources/images/mouse_dian.jpg";
		break;
	case DEVICE_HID::Jixiang:
		image = ":/AICenter_UI_1/Resources/images/jixiang.jpg";
		break;
	case DEVICE_HID::Yinxiang:
		image = ":/AICenter_UI_1/Resources/images/yinxiang.jpg";
		break;
	default:
		break;
	}
	pixmap = new QPixmap(image);
	pixmap->scaled(ui.imageLabel->size(), Qt::KeepAspectRatio);
	ui.imageLabel->setScaledContents(true);
	ui.imageLabel->setPixmap(*pixmap);
	ui.imageLabel->setFixedSize(200, 200);



	ui.imageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.imageList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//����QListWidget����ʾģʽ
	ui.imageList->setViewMode(QListView::IconMode);
	//����QListWidget�е�Ԫ��Ĵ�С
	ui.imageList->setIconSize(QSize(400, 40));
	//����QListWidget�е�Ԫ��ļ��
	ui.imageList->setSpacing(10);
	//�����Զ���Ӧ���ֵ�����Adjust��Ӧ��Fixed����Ӧ����Ĭ�ϲ���Ӧ
	ui.imageList->setResizeMode(QListWidget::Adjust);

	ui.imageList->setMovement(QListView::Static);//��ֹԪ����ק
	
	
	for (int i = 0; i < device->modeList.size(); i++) {

		//����QListWidgetItem����
		QListWidgetItem *imageItem = new QListWidgetItem;
		ui.imageList->addItem(imageItem);
		//�������õ�Ԫ��Ŀ�Ⱥ͸߶�
		imageItem->setSizeHint(QSize(400, 40));
		
		switch (device->modeList[i].type) {
		case MODE_TYPE::Drop:
			ui.imageList->setItemWidget(imageItem, new Mode_Drop(&(device->modeList[i])));
			break;
		case MODE_TYPE::HotKey:
			ui.imageList->setItemWidget(imageItem, new Mode_HotKey(&(device->modeList[i])));
			break;
		}
		
	}
	
	
}


Device_Mode::~Device_Mode()
{

}

void Device_Mode::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		break;
	default:
		QDialog::keyPressEvent(event);
	}
}