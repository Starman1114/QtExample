#include "GameList.h"


GameList::GameList(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);

	ui.imageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.imageList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//����QListWidget����ʾģʽ
	ui.imageList->setViewMode(QListView::IconMode);
	//����QListWidget�е�Ԫ��Ĵ�С
	ui.imageList->setIconSize(QSize(118, 138));
	//����QListWidget�е�Ԫ��ļ��
	ui.imageList->setSpacing(10);
	//�����Զ���Ӧ���ֵ�����Adjust��Ӧ��Fixed����Ӧ����Ĭ�ϲ���Ӧ
	ui.imageList->setResizeMode(QListWidget::Adjust);

	ui.imageList->setMovement(QListView::Static);//��ֹԪ����ק

	int length = GameList_Image.length();
	for (int i = 0;i<length; i++)
	{
		//����QListWidgetItem����
		QListWidgetItem *imageItem = new QListWidgetItem;
		
		ui.imageList->addItem(imageItem);
		//�������õ�Ԫ��Ŀ�Ⱥ͸߶�
		imageItem->setSizeHint(QSize(118, 138));
		//����Ԫ����ӵ�QListWidget��
		Image_Small *img = new Image_Small(i,GameList_Name[i], ":/AICenter_PC/Resources/images/" + GameList_Image[i]+".jpg");
		connect(img, SIGNAL(beclicked(int)), this, SLOT(sendIndex(int)));
		ui.imageList->setItemWidget(imageItem, img);
		
	}
	ui.imageList->setCurrentRow(0);
}

bool GameList::reset(int ind) {
	ui.imageList->removeItemWidget(ui.imageList->item(ind));
	Image_Small *img = new Image_Small(ind, GameList_Name[ind], ":/AICenter_PC/Resources/images/" + GameList_Image[ind] + ".jpg");
	connect(img, SIGNAL(beclicked(int)), this, SLOT(sendIndex(int)));
	ui.imageList->setItemWidget(ui.imageList->item(ind), img);
	return true;
}
bool GameList::setAdd(int ind) {

	ui.imageList->removeItemWidget(ui.imageList->item(ind));
	Image_Small *img = new Image_Small(ind, GameList_Name[ind], ":/AICenter_PC/Resources/images/" + GameList_Image[ind] + "_add.jpg");
	ui.imageList->setItemWidget(ui.imageList->item(ind), img);
	return true;
}

void GameList::sendIndex(int ind) {
	emit add(ind);
	
}

GameList::~GameList()
{
	while (ui.imageList->count() > 0)
	{
		ui.imageList->removeItemWidget(ui.imageList->item(0));
		ui.imageList->takeItem(0);
	}
}
