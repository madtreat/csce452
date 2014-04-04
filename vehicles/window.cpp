
#include "window.h"
#include "canvas.h"
#include "canvaswidget.h"

#include <QLabel>
#include <QDebug>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QTimer>
#include <QPushButton>
#include <QFile>
#include <QApplication>
#include <QGroupBox>
#include <QSpacerItem>
#include <unistd.h>

Window::Window()
: QWidget()
{
   initStyles();
   initCanvas();
   initLayout();
   QWidget* controlLabel = initControlPanel();

   QWidget* jointPanel = initJointControls();
   QWidget* worldPanel = initWorldControls();
   QWidget* brushPanel = initBrushControls();

   controlLayout->addWidget(controlLabel, 0, 0, 1, 2);
   controlLayout->addWidget(brushPanel,   1, 0, 1, 2);
   controlLayout->addWidget(jointPanel,   2, 0, 1, 1);
   controlLayout->addWidget(worldPanel,   2, 1, 1, 1);

   connect( canvasWidget,  SIGNAL(jointsChanged()),
            this,          SLOT  (updateBrushPos()));
   connect( canvasWidget,  SIGNAL(brushPosChanged()),
            this,          SLOT  (updateJointPos()));

   //--------------------------------------------------------//
   // Add control panel to main grid layout
   //--------------------------------------------------------//
   layout->addWidget(controlPanel, 0, 1);


   // Start animating
   QTimer* timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), canvasWidget, SLOT(animate()));
   timer->start();

   setWindowTitle("Braitenberg Simulator");
}

Window::~Window()
{
   delete canvas;
}

int Window::jointToNum(QString name)
{

   // parse the last character of name ( "Joint1" | "Joint2" | etc. )
   QChar digit = name.at(name.size()-1);
   int num = digit.digitValue();

   if (num == -1)
      return 0;
   
   return num;
}

QString Window::numToJoint(int num)
{
   
   QString joint = "Joint";
   joint += QString::number(num);
   return joint;
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
	//TODO: Fill this
   // Create RobotArm here so we can call canvas::drawLinks
   //arm          = new RobotArm();
   //canvas       = new Canvas(arm);
   //canvasWidget = new CanvasWidget(canvas, arm, this);
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

//--------------------------------------------------------//
// Create the control panel layout and widgets
//--------------------------------------------------------//
QWidget* Window::initControlPanel()
{
   QSizePolicy policy(QSizePolicy::Fixed, QSizePolicy::Fixed);

   controlPanel  = new QWidget(this);
   controlPanel->setMinimumWidth(2*CONTROL_WIDTH+24);
   controlPanel->setSizePolicy(policy);
   controlPanel->setStyleSheet(controlPanelStyle);

   controlLayout = new QGridLayout(controlPanel);

   // Control Panel Label
   QLabel* controlLabel = new QLabel(tr("Controls"));
   controlLabel->setAlignment(Qt::AlignHCenter);
   return controlLabel;
}

QWidget* Window::initJointControls()
{
	//TODO: Fill
   return NULL;
}

QWidget* Window::initWorldControls()
{
	//TODO: Fill
   return NULL;
}

QWidget* Window::initBrushControls()
{
   //TODO: Fill
	return NULL;
}

void Window::togglePaintText(bool enabled)
{
   if (enabled)
      paintButton->setText("Stop Painting");
   else
      paintButton->setText("Paint");
}

void Window::toggleJointControlsVisible(bool enabled)
{
   jointControls->setVisible(enabled);
   /*
   if (enabled)
      jointButton->setText("Joint Mode");
   else
      jointButton->setText("Show Joint Mode");
   // */
}

void Window::toggleWorldControlsVisible(bool enabled)
{
   worldControls->setVisible(enabled);
   /*
   if (enabled)
      worldButton->setText("World Mode");
   else
      worldButton->setText("Show World Mode");
   // */
}

void Window::updateBrushPos()
{
   if (!brushSpinX || !brushSpinY)
      return;

   // block all signals from being emitted from the canvasWidget while all values are updated
   // to avoid infinite signal-update loops
   canvasWidget->blockSignals(true);

   // update the brush spin boxes' values
   //brushSpinX->setValue(arm->getBrush()->joint.X);
   //brushSpinY->setValue(arm->getBrush()->joint.Y);

   // allow canvasWidget's signals to emit again
   canvasWidget->blockSignals(false);
}

void Window::updateJointPos()
{
   if (!joint1Spin || !joint2Spin || !joint3Spin)
      return;

   // block all signals from being emitted from the canvasWidget while all values are updated
   // to avoid infinite signal-update loops
   canvasWidget->blockSignals(true);

   // update brush spin boxes' values
   //joint1Spin->setValue(arm->getLink(1)->joint.rotation);
   //joint2Spin->setValue(arm->getLink(2)->joint.rotation);
   //joint3Spin->setValue(arm->getLink(3)->joint.rotation);

   // allow canvasWidget's signals to emit again
   canvasWidget->blockSignals(false);
}

void Window::keyPressEvent(QKeyEvent* event)
{
   qDebug() << "Key Pressed" << event->key();
   if (event->key() == Qt::Key_Space)
   {
      qDebug() << "Toggling paint in canvas widget...";
      paintButton->toggle();
   }
   // move right
	if (event->key() == Qt::Key_D)
   {
      //int newX = 4 + arm->getBrush()->joint.X;
      //canvasWidget->changeBrushX(newX);
   }
   // move left
	if (event->key() == Qt::Key_A)
   {
      //int newX = -4 + arm->getBrush()->joint.X;
      //canvasWidget->changeBrushX(newX);
   }
   // move up
	if (event->key() == Qt::Key_W)
   {
      //int newY = -4 + arm->getBrush()->joint.Y;
      //canvasWidget->changeBrushY(newY);
   }
   // move down
	if (event->key() == Qt::Key_S)
   {
      //int newY = 4 + arm->getBrush()->joint.Y;
      //canvasWidget->changeBrushY(newY);
   }
}

void Window::keyReleaseEvent(QKeyEvent* event)
{
   qDebug() << "Key Released" << event->key();
   if (event->key() == Qt::Key_Space)
   {
      //qDebug() << "Toggling paint in canvas widget...";
      //paintButton->toggle();
   }
   if (event->key() == Qt::Key_1)
   {
      // focus joint 1 control
      //joint1Spin->setFocus();
   }
   if (event->key() == Qt::Key_2)
   {
      // focus joint 2 control
      //joint2Spin->setFocus();
   }
   if (event->key() == Qt::Key_3)
   {
      // focus joint 3 control
      //joint3Spin->setFocus();
   }
   if (event->key() == Qt::Key_4)
   {
      // focus brush control
      //brushSpinX->setFocus();
   }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
// Joint Controls: widget { gridlayout { label, spinbox } }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
QWidget* Window::createJointControl(int id)
{
   //TODO: Fill
	return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
// World Controls: widget { gridlayout { label, spinbox, spinbox } }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
QWidget* Window::createWorldControl(int id)
{
   //TODO: Fill
	return NULL;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
// Add the brush activator button to the control panel
// - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
QWidget* Window::createBrushControl()
{
   QString name = "brush";

   QWidget*     paintWidget = new QWidget(this);
   QGridLayout* paintLayout = new QGridLayout(paintWidget);

   paintWidget->setObjectName(name);
   paintWidget->setMinimumHeight(JOINT_HEIGHT);
   paintLayout->setContentsMargins(5, 5, 5, 5);

   paintButton = new QPushButton("Paint", paintWidget);
   paintButton->setCheckable(true);

   myQSpinBox* bSpin = new myQSpinBox(paintWidget);
   bSpin->setObjectName(name);
   bSpin->setMinimumHeight(JOINT_HEIGHT);
   bSpin->setRange(BRUSH_MIN, BRUSH_MAX);
   bSpin->setPrefix("Size=");
   // do not allow the brush size to wrap
   bSpin->setWrapping(false);

   // connect the brush spin box to the canvas widget
   connect( bSpin,         SIGNAL(valueChanged(int)),
            canvasWidget,  SLOT  (changeBrushSize(int)));

   // connect the button to the canvas widget
   connect( paintButton,  SIGNAL (toggled(bool)),
            canvasWidget, SLOT   (togglePaint(bool)));
   // connect the button to change the text
   connect( paintButton,  SIGNAL (toggled(bool)),
            this,         SLOT   (togglePaintText(bool)));

   brushSizeSpin = bSpin;

   paintLayout->addWidget(paintButton, 0, 0);
   paintLayout->addWidget(bSpin, 0, 1);

   return paintWidget;
}

QWidget* Window::initControls()
{
   QWidget* controlPanel = new QWidget(this);
   QWidget*    carWidget = createCarControls();
   QWidget*  lightWidget = createLightWidget();
   // TODO: fill in
   return controlPanel;
}

QWidget* Window::createCarControls()
{
   QString           name = "car";
   QWidget*     carWidget = new QWidget(this);
   QGridLayout* carLayout = new QGridLayout(carWidget);

   carWidget->setObjectName(name);
   carWidget->setMinimumHeight(JOINT_HEIGHT);

   return carWidget;
}

QWidget* Window::createLabelControls()
{
   QString           name = "label";
   QWidget*   lightWidget = new QWidget(this);
   QGridLayout*    layout = new QGridLayout(carWidget);

   carWidget->setObjectName(name);
   carWidget->setMinimumHeight(JOINT_HEIGHT);
   
   return lightWidget;
}

