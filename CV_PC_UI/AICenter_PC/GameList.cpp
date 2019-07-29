#include "GameList.h"


GameList::GameList(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);

	ui.imageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.imageList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//设置QListWidget的显示模式
	ui.imageList->setViewMode(QListView::IconMode);
	//设置QListWidget中单元项的大小
	ui.imageList->setIconSize(QSize(118, 138));
	//设置QListWidget中单元项的间距
	ui.imageList->setSpacing(10);
	//设置自动适应布局调整（Adjust适应，Fixed不适应），默认不适应
	ui.imageList->setResizeMode(QListWidget::Adjust);

	ui.imageList->setMovement(QListView::Static);//禁止元素拖拽

	int length = GameList_Image.length();
	for (int i = 0;i<length; i++)
	{
		//定义QListWidgetItem对象
		QListWidgetItem *imageItem = new QListWidgetItem;
		
		ui.imageList->addItem(imageItem);
		//重新设置单元项的宽度和高度
		imageItem->setSizeHint(QSize(118, 138));
		//将单元项添加到QListWidget中
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
