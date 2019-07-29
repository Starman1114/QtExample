#include "Mode_Drop.h"


Mode_Drop::Mode_Drop(AI_MODE_CONF *mode, QWidget *parent) :
	mode(mode),QDialog(parent)
{
    ui.setupUi(this);

	ui.label->setText(mode->Name);
	ui.comboBox->addItems(mode->DropList);
	
}


Mode_Drop::~Mode_Drop()
{

}

void Mode_Drop::on_checkBox_stateChanged(int arg1)
{
	if (arg1 == 2) {
		mode->choose = true;
	}
	else {
		mode->choose = false;
	}
}

void Mode_Drop::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		break;
	default:
		QDialog::keyPressEvent(event);
	}
}