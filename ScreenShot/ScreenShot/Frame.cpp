#include "Frame.h"


Frame::Frame(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);

	
}

Frame::Frame(int ind,int type) 
{
	ui.setupUi(this);
	this->type = type;
	this->ind = ind;
	this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Dialog);
	//this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CoverWindow | Qt::WindowStaysOnTopHint);
	//������Ӱ
	this->setAttribute(Qt::WA_TranslucentBackground, true);      //����Ϊ͸������
	if (!isRun) {
		this->setStyleSheet(QString("#widget{border:4px dashed %1;background:none;}").arg(boardColor[this->type]));
	}
	else {
		this->setStyleSheet(QString("#widget{border:4px solid  %1;background:none;}").arg(boardColor[this->type]));
	}
	

	//����겻���µ�����²�׽mouseMoveEvent
	this->setMouseTracking(true);
	ui.widget->setMouseTracking(true);

	m_ChangeAction = new QAction("Change Type", this);
	m_deleteAction = new QAction("Delete", this);
	connect(m_ChangeAction, SIGNAL(triggered()), this, SLOT(ChangeType()));
	connect(m_deleteAction, SIGNAL(triggered()), this, SLOT(Delete()));

}

void Frame::ChangeInd(int nind) {
	this->ind = nind;
}

int Frame::returnType() {
	return this->type;
}

void Frame::Delete() {
	emit returnInd(ind);
}

void Frame::changeIsRun(bool isr) {
	isRun = isr;
	if (!isRun) {
		this->setStyleSheet(QString("#widget{border:4px dashed %1;background:none;}").arg(boardColor[this->type]));
		m_deleteAction->setEnabled(true);
	}
	else {
		this->setStyleSheet(QString("#widget{border:4px solid  %1;background:none;}").arg(boardColor[this->type]));
		m_deleteAction->setDisabled(true);
	}
}
void Frame::ChangeType() {
	if (this->type == 0) {
		this->type = 1;
	}
	else {
		this->type = 0;
	}
	if (!isRun) {
		this->setStyleSheet(QString("#widget{border:4px dashed %1;background:none;}").arg(boardColor[this->type]));
	}
	else {
		this->setStyleSheet(QString("#widget{border:4px solid  %1;background:none;}").arg(boardColor[this->type]));
	}
}

void Frame::contextMenuEvent(QContextMenuEvent* e)
{
	//����һ���˵������治�ڽ���.

	QMenu *m_contextMenu = new QMenu;
	
	m_contextMenu->addAction(m_ChangeAction);
	m_contextMenu->addAction(m_deleteAction);

	m_contextMenu->exec(e->globalPos());
	delete m_contextMenu;
}


Frame::~Frame()
{
	delete m_ChangeAction;
	delete m_deleteAction;
}		   
void Frame::beClose() {
	this->close();
}

QRect Frame::getRect() {
	return this->geometry();
}

// �ڴ��ڵ�һ��show��֮����Ҫ������������Rectλ��;
void Frame::showEvent(QShowEvent *event)
{
	calculateCurrentStrechRect();

	return __super::showEvent(event);
}


// ������������Rectλ��;
// ����8��Rect��Ӧ��ͼ��8������;
void Frame::calculateCurrentStrechRect()
{
	// �ĸ���Rect;
	m_leftTopRect = QRect(0, 0, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
	m_leftBottomRect = QRect(0, this->height() - STRETCH_RECT_HEIGHT, STRETCH_RECT_WIDTH, STRETCH_RECT_WIDTH);
	m_rightTopRect = QRect(this->width() - STRETCH_RECT_WIDTH, 0, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);
	m_rightBottomRect = QRect(this->width() - STRETCH_RECT_WIDTH, this->height() - STRETCH_RECT_HEIGHT, STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT);

	// ������Rect;
	m_topBorderRect = QRect(STRETCH_RECT_WIDTH, 0, this->width() - STRETCH_RECT_WIDTH * 2, STRETCH_RECT_HEIGHT);
	m_rightBorderRect = QRect(this->width() - STRETCH_RECT_WIDTH, STRETCH_RECT_HEIGHT, STRETCH_RECT_WIDTH, this->height() - STRETCH_RECT_HEIGHT * 2);
	m_bottomBorderRect = QRect(STRETCH_RECT_WIDTH, this->height() - STRETCH_RECT_HEIGHT, this->width() - STRETCH_RECT_WIDTH * 2, STRETCH_RECT_HEIGHT);
	m_leftBorderRect = QRect(0, STRETCH_RECT_HEIGHT, STRETCH_RECT_WIDTH, this->height() - STRETCH_RECT_HEIGHT * 2);
}

// ���ݵ�ǰ���λ�ã���λ����ھ�����һ����������;
WindowStretchRectState Frame::getCurrentStretchState(QPoint cursorPos)
{
	WindowStretchRectState stretchState;
	if (m_leftTopRect.contains(cursorPos))
	{
		stretchState = LEFT_TOP_RECT;
	}
	else if (m_rightTopRect.contains(cursorPos))
	{
		stretchState = RIGHT_TOP_RECT;
	}
	else if (m_rightBottomRect.contains(cursorPos))
	{
		stretchState = RIGHT_BOTTOM_RECT;
	}
	else if (m_leftBottomRect.contains(cursorPos))
	{
		stretchState = LEFT_BOTTOM_RECT;
	}
	else if (m_topBorderRect.contains(cursorPos))
	{
		stretchState = TOP_BORDER;
	}
	else if (m_rightBorderRect.contains(cursorPos))
	{
		stretchState = RIGHT_BORDER;
	}
	else if (m_bottomBorderRect.contains(cursorPos))
	{
		stretchState = BOTTOM_BORDER;
	}
	else if (m_leftBorderRect.contains(cursorPos))
	{
		stretchState = LEFT_BORDER;
	}
	else
	{
		stretchState = NO_SELECT;
	}

	return stretchState;
}

// ����getCurrentStretchState����״̬���и��������ʽ;
void Frame::updateMouseStyle(WindowStretchRectState stretchState)
{
	switch (stretchState)
	{
	case NO_SELECT:
		setCursor(Qt::ArrowCursor);
		atAngle = false;
		break;
	case LEFT_TOP_RECT:
	case RIGHT_BOTTOM_RECT:
		atAngle = true;
		setCursor(Qt::SizeFDiagCursor);
		break;
//	case TOP_BORDER:
//	case BOTTOM_BORDER:
//		setCursor(Qt::SizeVerCursor);
//		break;
	case RIGHT_TOP_RECT:
	case LEFT_BOTTOM_RECT:
		atAngle = true;
		setCursor(Qt::SizeBDiagCursor);
		break;
//	case LEFT_BORDER:
//	case RIGHT_BORDER:
//		setCursor(Qt::SizeHorCursor);
//		break;
	default:
		setCursor(Qt::ArrowCursor);
		atAngle = false;
		break;
	}

}


/**************************************************************************
* ���洰�ڲ���
*/
void Frame::mouseMoveEvent(QMouseEvent *e)
{
	// �����ǰ���δ���£�����ݵ�ǰ����λ�ø�������״̬����ʽ;
	if (!mousePressed)
	{
		QPoint cursorPos = e->pos();
		// ���ݵ�ǰ����λ����ʾ��ͬ����ʽ;
		m_stretchRectState = getCurrentStretchState(cursorPos);
		updateMouseStyle(m_stretchRectState);
	}


	if (mousePressed && (e->buttons() && Qt::LeftButton)) {
	
		if (atAngle) {
			m_endPoint = this->mapToGlobal(e->pos());
			updateWindowSize();
		}
		else {
			this->move(e->globalPos() - mousePoint);
			e->accept();
		}
		
		QRect rt = this->geometry();
		emit returnRectValue(rt.topLeft().rx()+4, rt.topLeft().ry() + 4, rt.bottomRight().rx() - rt.topLeft().rx() - 8, rt.bottomRight().ry() - rt.topLeft().ry() - 8);

	}
}

void Frame::setLocation(int x, int y, int w, int h) {
	this->setGeometry(x - 4, y - 4, w+9, h+9);
}

void Frame::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton) {
		mousePressed = true;
		if(atAngle){
			// ��¼�µ�ǰ���λ�ã�Ϊ�����������λ��;
			m_startPoint = this->mapToGlobal(e->pos());
			// ����������ǰ�Ĵ���λ�ü���С;
			m_windowRectBeforeStretch = this->geometry();

		}
		else {
			mousePoint = e->globalPos() - this->pos();
			e->accept();
		}
		
	}
	
}

// ���촰�ڹ����У����ݼ�¼��������´��ڴ�С;
void Frame::updateWindowSize()
{
	// ����ʱҪע�����ô�����Сֵ;
	QRect windowRect = m_windowRectBeforeStretch;
	int delValue_X = m_startPoint.x() - m_endPoint.x();
	int delValue_Y = m_startPoint.y() - m_endPoint.y();
	
	if (m_stretchRectState == LEFT_TOP_RECT)
	{
		QPoint topLeftPoint = windowRect.topLeft();
		topLeftPoint.setX(topLeftPoint.x() - delValue_X);
		topLeftPoint.setY(topLeftPoint.y() - delValue_Y);
		windowRect.setTopLeft(topLeftPoint);
	}
	else if (m_stretchRectState == RIGHT_TOP_RECT)
	{
		QPoint topRightPoint = windowRect.topRight();
		topRightPoint.setX(topRightPoint.x() - delValue_X);
		topRightPoint.setY(topRightPoint.y() - delValue_Y);
		windowRect.setTopRight(topRightPoint);
	}
	else if (m_stretchRectState == RIGHT_BOTTOM_RECT)
	{
		QPoint bottomRightPoint = windowRect.bottomRight();
		bottomRightPoint.setX(bottomRightPoint.x() - delValue_X);
		bottomRightPoint.setY(bottomRightPoint.y() - delValue_Y);
		windowRect.setBottomRight(bottomRightPoint);
	}
	else if (m_stretchRectState == LEFT_BOTTOM_RECT)
	{
		QPoint bottomLeftPoint = windowRect.bottomLeft();
		bottomLeftPoint.setX(bottomLeftPoint.x() - delValue_X);
		bottomLeftPoint.setY(bottomLeftPoint.y() - delValue_Y);
		windowRect.setBottomLeft(bottomLeftPoint);
	}


	this->setGeometry(windowRect);
}


void Frame::mouseReleaseEvent(QMouseEvent *)
{
	mousePressed = false;
	calculateCurrentStrechRect();
}