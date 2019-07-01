#include "ScreenShot.h"
#include <QWindow>
ScreenShot::ScreenShot(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect screenRect = desktopWidget->screenGeometry();
	ui.sizeLabel->setText(QString("%1 * %2").arg(screenRect.width()).arg(screenRect.height()));

	//注册全局热键
	//注册快捷键  
	MyGlobalShortCut *shortcutP = new MyGlobalShortCut("Ctrl+F1", this);  //正
	//绑定响应热键的slot
	QObject::connect(shortcutP, SIGNAL(activated()), this, SLOT(addPBoard()));

	//MyGlobalShortCut *shortcutN = new MyGlobalShortCut("Ctrl+F2", this);  //负
	////绑定响应热键的slot
	//QObject::connect(shortcutN, SIGNAL(activated()), this, SLOT(addNBoard()));

	MyGlobalShortCut *changeT = new MyGlobalShortCut("Ctrl+F2", this);  //切换
	//绑定响应热键的slot
	QObject::connect(changeT, SIGNAL(activated()), this, SLOT(ChangeFirstType()));

	MyGlobalShortCut *Run = new MyGlobalShortCut("Ctrl+F3", this);  //负
	//绑定响应热键的slot
	QObject::connect(Run, SIGNAL(activated()), this, SLOT(running()));


	// 检查目录是否存在，若不存在则新建 
	QDir dir;
	
	if (!dir.exists(QString("%1/%2").arg(ui.DirNameEdit->text()).arg(dirList[0])))
	{
		if (dir.mkpath(QString("%1/%2").arg(ui.DirNameEdit->text()).arg(dirList[0]))){
			qDebug()<<"dir_P Create!"<<endl;
		}
	}
	if (!dir.exists(QString("%1/%2").arg(ui.DirNameEdit->text()).arg(dirList[1])))
	{
		if (dir.mkpath(QString("%1/%2").arg(ui.DirNameEdit->text()).arg(dirList[1]))) {
			qDebug() << "dir_N Create!" << endl;
		}
	}


	ui.textLabel->setText(QString("%1 : Add Board \n%2 : Change Board Type\n%3 : Run/Stop!\n").arg("Ctrl F1").arg("Ctrl F2").arg("Ctrl F3"));

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerUpDate()));

}

ScreenShot::~ScreenShot() {
	for (int i = 0; i < FrameList.length(); i++) {
		delete FrameList[i];
	}
	FrameList.clear();
	delete timer;
}

void ScreenShot::timerUpDate() {
	QScreen *screen = QGuiApplication::primaryScreen();
	for (int i = 0; i < FrameList.length(); i++) {

		pixmap = screen->grabWindow(0, FrameList[i]->getRect().topLeft().rx() + 4, FrameList[i]->getRect().topLeft().ry() + 4,
			FrameList[i]->getRect().bottomRight().rx() - FrameList[i]->getRect().topLeft().rx() - 8, FrameList[i]->getRect().bottomRight().ry() - FrameList[i]->getRect().topLeft().ry() - 8);

		QString fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss-zzz") + ".jpg";
		if (!pixmap.save(QString("%1/%2/%3").arg(ui.DirNameEdit->text()).arg(dirList[FrameList[i]->returnType()]).arg(fileName), "jpg"))
		{
			qDebug() << "Fail " << i << endl;
		}
	}
}
void ScreenShot::closeEvent(QCloseEvent * e)
{
	emit beclose();
}

void ScreenShot::deleteBoard(int ind) {
	delete FrameList[ind];
	FrameList.removeAt(ind);
	for (int i = 0; i < FrameList.length(); i++) {
		FrameList[i]->ChangeInd(i);
	}
}
void ScreenShot::ChangeFirstType() {
	FrameList[0]->ChangeType();
}

void ScreenShot::addPBoard() {
	if (FrameList.length() == 0) {
		Frame *a = new Frame(FrameList.length(), 0);  //为了不跟随主窗口最小化 ， 不能（this）
		connect(a, SIGNAL(returnInd(int)), this, SLOT(deleteBoard(int)));
		connect(this, SIGNAL(beclose()), a, SLOT(beClose()));
		FrameList.append(a);
		a->show();
	}
}
void ScreenShot::addNBoard() {
	Frame *a = new Frame(FrameList.length(), 1);  //为了不跟随主窗口最小化 ， 不能（this）
	connect(this, SIGNAL(beclose()), a, SLOT(beClose()));
	connect(a, SIGNAL(returnInd(int)), this, SLOT(deleteBoard(int)));
	FrameList.append(a);
	a->show();
}


void ScreenShot::running(){
	
	//pixmap = screen->grabWindow(QApplication::activeWindow()->winId(), 30, 30, 90, 90);
//	pixmap = screen->grabWindow(0);
//	QPixmap aa = pixmap.scaled(ui.imgLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//	ui.imgLabel->setScaledContents(true);
//	ui.imgLabel->setPixmap(aa);
	//qDebug() << ui.timeBox->value() << endl;
	if (timer->isActive()) {
		timer->stop();
		FrameList[0]->changeIsRun(false);
		ui.timeBox->setEnabled(true);
		ui.DirNameEdit->setEnabled(true);
	}
	else {
		QDir dir;

		if (!dir.exists(QString("%1/%2").arg(ui.DirNameEdit->text()).arg(dirList[0])))
		{
			if (dir.mkpath(QString("%1/%2").arg(ui.DirNameEdit->text()).arg(dirList[0]))) {
				qDebug() << "dir_P Create!" << endl;
			}
		}
		if (!dir.exists(QString("%1/%2").arg(ui.DirNameEdit->text()).arg(dirList[1])))
		{
			if (dir.mkpath(QString("%1/%2").arg(ui.DirNameEdit->text()).arg(dirList[1]))) {
				qDebug() << "dir_N Create!" << endl;
			}
		}

		ui.DirNameEdit->setDisabled(true);
		FrameList[0]->changeIsRun(true);
		timer->start(ui.timeBox->value());
		ui.timeBox->setDisabled(true);
			
	}
}
