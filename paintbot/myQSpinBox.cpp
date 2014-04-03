
#include "myQSpinBox.h"

myQSpinBox::myQSpinBox(QWidget *parent)
: QSpinBox(parent)
{}

myQSpinBox::~myQSpinBox()
{}

void myQSpinBox::keyPressEvent(QKeyEvent* event)
{
	std::cout << "Key Pressed in mySpinBox (" << event->key() << ")\n";
	if (event->key() == Qt::Key_Right
	 || event->key() == Qt::Key_Left
	 || event->key() == Qt::Key_Up
	 || event->key() == Qt::Key_Down )
	{
		std::cout << "Arrow Key pressed - sending to spinBox (" << event->key() << ")\n";
		QSpinBox::keyPressEvent(event);
	}
	else
	{
		event->ignore();
	}
}




