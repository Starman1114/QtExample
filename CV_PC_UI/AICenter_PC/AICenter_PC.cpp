#include "AICenter_PC.h"

AICenter_PC::AICenter_PC(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Initialization();

	connect(ui.TitleWidget, SIGNAL(beMin()), this, SLOT(on_btnMenu_Min_clicked()));
	connect(ui.TitleWidget, SIGNAL(beExit()), this, SLOT(on_btnMenu_Close_clicked()));

	this->setFixedSize(850, 500);
	
}

AICenter_PC::~AICenter_PC()
{
	
}

void AICenter_PC::on_btnMenu_Min_clicked()
{
	this->showMinimized();
}

void AICenter_PC::on_btnMenu_Close_clicked()
{
	qApp->exit();
}


//设置皮肤样式
void AICenter_PC::SetStyle(const QString &styleName)
{
	QFile file(QString(":/AICenter_PC/Resources/%1.css").arg(styleName));
	if (file.open(QFile::ReadOnly)) {

		QString qss = QLatin1String(file.readAll());
		//qDebug() << qss << endl;
		QString paletteColor = "#00AFF0";
		this->setPalette(QPalette(QColor(paletteColor)));
		qApp->setStyleSheet(qss);
		file.close();
	}
	else {
		qDebug() << 2333 << endl;
	}
	
}

void AICenter_PC::Initialization() {
	//字体设置
	int fontId = QFontDatabase::addApplicationFont(":/AICenter_PC/Resources/fontawesome-webfont.ttf");
	QString msyh = QFontDatabase::applicationFontFamilies(fontId).at(0);
	QFont font(msyh);
	QApplication::setFont(font);

	//样式表
	SetStyle("pybqss");

	//设置窗体标题栏隐藏
	// 第一个参数是设置无边框。第二个参数是允许任务栏按钮右键菜单，第三个参数是允许最小化与还原。
	//this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

	this->setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::FramelessWindowHint);

	this->setAttribute(Qt::WA_TranslucentBackground, true);

	//myspeed = new MySpeed(this);
	//ui.stackedWidget->addWidget(myspeed);
	//gameList = new GameList(this);
	connect(ui.page_4, SIGNAL(add(int)), this, SLOT(addGame(int)));
	connect(ui.page_3, SIGNAL(deleteG(int)), this, SLOT(deleteGame(int)));
	//ui.stackedWidget->addWidget(gameList);

	//ui.stackedWidget->setCurrentWidget(myspeed);
	ui.stackedWidget->setCurrentIndex(0);
	
	ui.ChooseSpeed->setFocus();


	
	ui.stackedWidget->setStyleSheet("background-color: rgba(255, 255, 255, 0);}");
}

bool AICenter_PC::deleteGame(int ind) {
	return ui.page_4->reset(ind);
}

bool AICenter_PC::addGame(int ind) {
	if (ui.page_3->addItem(ind)) {
		if (ui.page_4->setAdd(ind)) {

		}
	}
	return true;
}

void AICenter_PC::on_ChooseSpeed_clicked() {
	ui.stackedWidget->setCurrentIndex(0);
}

void AICenter_PC::on_ChooseGame_clicked() {
	ui.stackedWidget->setCurrentIndex(1);
}

void AICenter_PC::paintEvent(QPaintEvent *event)
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
