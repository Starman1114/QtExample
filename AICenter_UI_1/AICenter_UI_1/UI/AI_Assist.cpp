#include "AI_Assist.h"


AI_Assist::AI_Assist(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);

	ui.imageList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.imageList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//设置QListWidget的显示模式
	ui.imageList->setViewMode(QListView::IconMode);
	//设置QListWidget中单元项的大小
	ui.imageList->setIconSize(QSize(160, 120));
	//设置QListWidget中单元项的间距
	ui.imageList->setSpacing(10);
	//设置自动适应布局调整（Adjust适应，Fixed不适应），默认不适应
	ui.imageList->setResizeMode(QListWidget::Adjust);

	ui.imageList->setMovement(QListView::Static);//禁止元素拖拽

	ui.stackedWidget->removeWidget(ui.page_3);
	ui.stackedWidget->removeWidget(ui.page_4);
	ReadXMLFile(XML_Game_CONF);

	ui.imageList->setCurrentRow(0);


	

}


AI_Assist::~AI_Assist()
{
	while (ui.imageList->count() > 0)
	{
		ui.imageList->removeItemWidget(ui.imageList->item(0));
		ui.imageList->takeItem(0);
	}
}

void AI_Assist::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		break;
	default:
		QDialog::keyPressEvent(event);
	}
}

int AI_Assist::ReadXMLFile(QString FilePath) {
	tinyxml2::XMLDocument docXml;
	if (docXml.LoadFile(FilePath.toStdString().c_str()) != 0)
	{
		return -1;
	}
	XMLElement* elmtRoot = docXml.RootElement();

	//Get Setting
	XMLElement *game = elmtRoot->FirstChildElement("Game");
	int ind = 0;
	while (game != NULL) {
		gameList.push_back(AI_GAME_CONF(game));

		//定义QListWidgetItem对象
		QListWidgetItem *imageItem = new QListWidgetItem;

		ui.imageList->addItem(imageItem);
		//重新设置单元项的宽度和高度
		imageItem->setSizeHint(QSize(160, 120));
		Image_Small *img = new Image_Small(ind, gameList.back().Name, ":/AICenter_UI_1/Resources/images/" + gameList.back().Name + ".jpg");
		connect(img, SIGNAL(beclicked(int)), this, SLOT(gain_Game_Ind(int)));

		ui.imageList->setItemWidget(imageItem, img);

		ui.stackedWidget->addWidget(new Device_Conf(&gameList.back()));

		ind++;
		game = game->NextSiblingElement();//下一个兄弟节点
	}
	return 0;
}

void AI_Assist::gain_Game_Ind(int ind) {
	ui.stackedWidget->setCurrentIndex(ind);
	//for (int i = 0; i < gameList[ind].DeviceList.size(); i++) {
	//	for (int j = 0; j < gameList[ind].DeviceList[i].modeList.size(); j++) {
	//		qDebug() << gameList[ind].DeviceList[i].modeList[j].Name << gameList[ind].DeviceList[i].modeList[j].choose << endl;
	//	}
	//}
}