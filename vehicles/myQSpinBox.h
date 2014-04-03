
#ifndef MYQSPINBOX_H_
#define MYQSPINBOX_H_

#include <QWidget>
#include <QString>
#include <QColor>
#include <QGridLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QSpinBox>

#include <iostream>
#include <stdio.h>

class myQSpinBox : public QSpinBox
{
	Q_OBJECT
public:
    myQSpinBox(QWidget *parent = 0);
	 ~myQSpinBox();
	void keyPressEvent(QKeyEvent* event);
};

#endif