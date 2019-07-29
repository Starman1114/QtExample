#include "Mode_HotKey.h"


Mode_HotKey::Mode_HotKey(AI_MODE_CONF *mode, QWidget *parent) :
	mode(mode),QDialog(parent)
{
    ui.setupUi(this);

	ui.label->setText(mode->Name);
	ui.pushButton->setText(mode->HotKey);
	
}


Mode_HotKey::~Mode_HotKey()
{

}

void Mode_HotKey::on_checkBox_stateChanged(int arg1)
{
	if (arg1 == 2) {
		mode->choose = true;
	}
	else {
		mode->choose = false;
	}
}

void Mode_HotKey::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		break;
	default:
		if (change) {
			qDebug() << event->modifiers() << event->key() << event->text() << endl;
			mode->HotKey ="";
			switch (event->modifiers())
			{
			case Qt::NoModifier:
				break;
			case Qt::ShiftModifier:
				mode->HotKey.append("Shift+");
				break;
			case Qt::ControlModifier:
				mode->HotKey.append("Ctrl+");
				break;
			case Qt::AltModifier:
				mode->HotKey.append("Alt+");
				break;
			default:
				break;
			}
			QMetaEnum meta = QMetaEnum::fromType<Qt::Key>();
			mode->HotKey.append( QString(meta.valueToKey(Qt::Key(event->key()))).mid(4)  );
			ui.pushButton->setText(mode->HotKey);
		}
		else {
			QDialog::keyPressEvent(event);
		}	
	}
}

void Mode_HotKey::on_pushButton_clicked() {
	if (!change) 
		change = true;
	else 
		change = false;
}