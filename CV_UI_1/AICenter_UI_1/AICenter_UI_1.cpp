#include "AICenter_UI_1.h"

AICenter_UI_1::AICenter_UI_1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Initialization();
}

AICenter_UI_1::~AICenter_UI_1() {
	delete buttonGroup;
}

bool AICenter_UI_1::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	
	Q_UNUSED(eventType);
	MSG* msg = reinterpret_cast<MSG*>(message);
	int msgType = msg->message;
	if (msgType == WM_DEVICECHANGE)
	{
		emit deviceChange();
	}
	return false;
}



void AICenter_UI_1::Initialization() {

	ui.TitleWidget->setPoint(this);

	//字体设置
	int fontId = QFontDatabase::addApplicationFont(QString(":/%1/Resources/fontawesome-webfont.ttf").arg(this->metaObject()->className()));
	QString msyh = QFontDatabase::applicationFontFamilies(fontId).at(0);
	QFont font(msyh);
	QApplication::setFont(font);

	//样式表
	FormSet::SetStyle(this,"IntelAI");

	//设置窗体标题栏隐藏
	// 第一个参数是设置无边框。第二个参数是允许任务栏按钮右键菜单，第三个参数是允许最小化与还原。
	//this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

	this->setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::FramelessWindowHint);

	this->setAttribute(Qt::WA_TranslucentBackground, true);


//	connect(ui.page_4, SIGNAL(add(int)), this, SLOT(addGame(int)));
//	connect(ui.page_3, SIGNAL(deleteG(int)), this, SLOT(deleteGame(int)));
//
//	ui.stackedWidget->setCurrentIndex(0);
//
//	ui.ChooseSpeed->setFocus();

	buttonGroup = new QButtonGroup;
	//第二个参数id可以自行定义
	buttonGroup->addButton(ui.Device_Support_Button, 0);
	ui.Device_Support_Button->setCheckable(true);
	buttonGroup->addButton(ui.AI_Assist_Button, 1);
	ui.AI_Assist_Button->setCheckable(true);
	buttonGroup->addButton(ui.Scene_Assist_Button, 2);
	ui.Scene_Assist_Button->setCheckable(true);
	connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonJudge(int)));

	//ui.stackedWidget->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
	ui.stackedWidget->setCurrentIndex(0);

	//设备热插拔信号绑定
	connect(this,SIGNAL(deviceChange()),ui.page, SLOT(on_reflechButton_clicked()));


//	QDesktopWidget* desktopWidget = QApplication::desktop();
//	QRect screenRect = desktopWidget->screenGeometry();
//	int g_nActScreenW = screenRect.width();
//	int g_nActScreenH = screenRect.height();
//	this->resize(g_nActScreenW /2, g_nActScreenH /2);
//	delete desktopWidget;
}

void AICenter_UI_1::buttonJudge(int id) {
	ui.stackedWidget->setCurrentIndex(id);
	//	for (int i = 0; i < buttonGroup->buttons().size(); i++) {
}


void AICenter_UI_1::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);


	QColor m_defaultBackgroundColor = qRgb(65, 65, 65);
	QColor m_defaultBorderColor = qRgb(69, 69, 69);
	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRoundedRect(10, 10, this->width() - 20, this->height() - 20, 5, 5);

	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(path, QBrush(QColor(m_defaultBackgroundColor.red(),
		m_defaultBackgroundColor.green(),
		m_defaultBackgroundColor.blue())));

	QColor color(45, 45, 45, 50);
	for (int i = 0; i < 5; i++)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRoundedRect(5 - i, 5 - i, this->width() - (5 - i) * 2, this->height() - (5 - i) * 2, 5, 5);
		color.setAlpha(100 - qSqrt(i) * 50);
		painter.setPen(color);
		painter.drawPath(path);
	}

	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(QBrush("#00AFF0"));
	painter.setPen(Qt::transparent);
	QRect rect = this->rect();
	rect.setX(5);
	rect.setY(5);
	rect.setWidth(rect.width() - 5);
	rect.setHeight(rect.height() - 5);
	// rect: 绘制区域  15：圆角弧度
	painter.drawRoundedRect(rect, 5, 5);

}



