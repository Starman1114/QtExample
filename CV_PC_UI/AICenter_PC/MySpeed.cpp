#include "MySpeed.h"


MySpeed::MySpeed(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);

	ui.imageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.imageList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//����QListWidget����ʾģʽ
	ui.imageList->setViewMode(QListView::IconMode);
	//����QListWidget�е�Ԫ���ͼƬ��С
	ui.imageList->setIconSize(QSize(270, 360));
	//����QListWidget�е�Ԫ��ļ��
	ui.imageList->setSpacing(10);
	//�����Զ���Ӧ���ֵ�����Adjust��Ӧ��Fixed����Ӧ����Ĭ�ϲ���Ӧ
	ui.imageList->setResizeMode(QListWidget::Adjust);

	ui.imageList->setMovement(QListView::Static);//��ֹԪ����ק

	//int length = GameList_Image.length();
	//for (int i = 0; i < length; i++)
	//{
	//	//����QListWidgetItem����
	//	QListWidgetItem *imageItem = new QListWidgetItem;
	//
	//	ui.imageList->addItem(imageItem);
	//	//�������õ�Ԫ��ͼƬ�Ŀ�Ⱥ͸߶�
	//	imageItem->setSizeHint(QSize(198, 258));
	//	//����Ԫ����ӵ�QListWidget��
	//	Image_Big *img = new Image_Big(i, GameList_Name[i], ":/AICenter_PC/Resources/images/" + GameList_Image[i] + "_Big.jpg");
	////	connect(img, SIGNAL(beclicked(int)), this, SLOT(sendIndex(int)));
	//	ui.imageList->setItemWidget(imageItem, img);
	//
	//}
	//ui.imageList->setCurrentRow(0);
}

bool MySpeed::addItem(int ind) {	
	//����QListWidgetItem����
	QListWidgetItem *imageItem = new QListWidgetItem;

	ui.imageList->addItem(imageItem);
	//�������õ�Ԫ��ͼƬ�Ŀ�Ⱥ͸߶�
	imageItem->setSizeHint(QSize(270, 360));
	//����Ԫ����ӵ�QListWidget��
	Image_Big *img = new Image_Big(ind, GameList_Name[ind], ":/AICenter_PC/Resources/images/" + GameList_Image[ind] + "_Big.jpg");
	connect(img, SIGNAL(deleteDialog(int)), this, SLOT(deleteGame(int)));
	ui.imageList->setItemWidget(imageItem, img);
	return true;
}

void MySpeed::deleteGame(int ind){
	ui.imageList->removeItemWidget(ui.imageList->itemAt(ui.imageList->mapFromGlobal(QCursor::pos())));
	ui.imageList->takeItem(ui.imageList->row(ui.imageList->itemAt(ui.imageList->mapFromGlobal(QCursor::pos()))));
	emit deleteG(ind);
}

MySpeed::~MySpeed()
{
	while (ui.imageList->count() > 0)
	{
		ui.imageList->removeItemWidget(ui.imageList->item(0));
		ui.imageList->takeItem(0);
	}
}

