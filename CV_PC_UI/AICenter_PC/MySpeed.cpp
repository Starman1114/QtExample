#include "MySpeed.h"


MySpeed::MySpeed(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);

	ui.imageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.imageList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//设置QListWidget的显示模式
	ui.imageList->setViewMode(QListView::IconMode);
	//设置QListWidget中单元项的图片大小
	ui.imageList->setIconSize(QSize(270, 360));
	//设置QListWidget中单元项的间距
	ui.imageList->setSpacing(10);
	//设置自动适应布局调整（Adjust适应，Fixed不适应），默认不适应
	ui.imageList->setResizeMode(QListWidget::Adjust);

	ui.imageList->setMovement(QListView::Static);//禁止元素拖拽

	//int length = GameList_Image.length();
	//for (int i = 0; i < length; i++)
	//{
	//	//定义QListWidgetItem对象
	//	QListWidgetItem *imageItem = new QListWidgetItem;
	//
	//	ui.imageList->addItem(imageItem);
	//	//重新设置单元项图片的宽度和高度
	//	imageItem->setSizeHint(QSize(198, 258));
	//	//将单元项添加到QListWidget中
	//	Image_Big *img = new Image_Big(i, GameList_Name[i], ":/AICenter_PC/Resources/images/" + GameList_Image[i] + "_Big.jpg");
	////	connect(img, SIGNAL(beclicked(int)), this, SLOT(sendIndex(int)));
	//	ui.imageList->setItemWidget(imageItem, img);
	//
	//}
	//ui.imageList->setCurrentRow(0);
}

bool MySpeed::addItem(int ind) {	
	//定义QListWidgetItem对象
	QListWidgetItem *imageItem = new QListWidgetItem;

	ui.imageList->addItem(imageItem);
	//重新设置单元项图片的宽度和高度
	imageItem->setSizeHint(QSize(270, 360));
	//将单元项添加到QListWidget中
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

