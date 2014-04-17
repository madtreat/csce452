
#include "window.h"
#include "consts.h"
#include "canvas.h"
#include "canvaswidget.h"
#include "manager.h"

#include <QLabel>
#include <QDebug>
#include <QGridLayout>
#include <QSpinBox>
#include <QTimer>
#include <QPushButton>
#include <QFile>

#include <unistd.h>

Window::Window(Manager* _manager)
: QWidget(),
manager(_manager)
{
   initStyles();
   initCanvas();
   initLayout();

   setObjectName("main-window");

   // Start animating
   QTimer* timer = new QTimer(this);
	timer->setInterval(30);	//miliseconds
   connect(timer, SIGNAL(timeout()), this, SLOT(windowAnimate()));
   timer->start();

   setWindowTitle("Braitenberg Simulator");
}

Window::~Window()
{
   delete canvas;
}

void Window::windowAnimate()
{
   // move each car based on positions of light sources
	manager->timeStep();
   // update the combo boxes
   //updateComboBoxes();
   // draw the new positions
	canvasWidget->animate();
}

void Window::initStyles()
{
   QFile file(":/style");
   file.open(QFile::ReadOnly);
   
   controlPanelStyle = QLatin1String(file.readAll());
}

//--------------------------------------------------------//
// Create the canvas and its container widget
//--------------------------------------------------------//
void Window::initCanvas()
{
   if (!manager)
      manager   = new Manager();
   canvas       = new Canvas(manager);
   canvasWidget = new CanvasWidget(canvas, this);
}

void Window::initLayout()
{
   // Create the main/top-level grid layout
   layout = new QGridLayout(this);
   layout->setContentsMargins(0, 0, 0, 0);

   // Add to main grid layout
   if (!canvasWidget)
      initCanvas();
   layout->addWidget(canvasWidget, 0, 0);
}

void Window::keyPressEvent(QKeyEvent* event)
{
   qDebug() << "Key Pressed" << event->key();
   if (event->key() == Qt::Key_Space)
   {
   }
	if (event->key() == Qt::Key_D)
   {
   }
	if (event->key() == Qt::Key_A)
   {
   }
	if (event->key() == Qt::Key_W)
   {
   }
	if (event->key() == Qt::Key_S)
   {
   }
}

void Window::keyReleaseEvent(QKeyEvent* event)
{
   qDebug() << "Key Released" << event->key();
   if (event->key() == Qt::Key_Space)
   {
   }
   if (event->key() == Qt::Key_1)
   {
   }
   if (event->key() == Qt::Key_2)
   {
   }
   if (event->key() == Qt::Key_3)
   {
   }
   if (event->key() == Qt::Key_4)
   {
   }
}

