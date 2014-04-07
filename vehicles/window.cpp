
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
#include <QComboBox>

#include <unistd.h>

Window::Window()
: QWidget()
{
   initStyles();
   initCanvas();
   initLayout();

   QWidget* controlLabel = initControlPanel();
   QWidget*     carPanel = initCarControls();
   QWidget*   lightPanel = initLightControls();

   controlLayout->addWidget(controlLabel, 0, 0);
   controlLayout->addWidget(carPanel,     1, 0);
   controlLayout->addWidget(lightPanel,   2, 0);

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
   manager      = new Manager();
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

void Window::togglePaintText(bool enabled)
{
   /*
   if (enabled)
      paintButton->setText("Stop Painting");
   else
      paintButton->setText("Paint");
   // */
}

void Window::toggleJointControlsVisible(bool enabled)
{
   //jointControls->setVisible(enabled);
   /*
   if (enabled)
      jointButton->setText("Joint Mode");
   else
      jointButton->setText("Show Joint Mode");
   // */
}

void Window::toggleWorldControlsVisible(bool enabled)
{
   //worldControls->setVisible(enabled);
   /*
   if (enabled)
      worldButton->setText("World Mode");
   else
      worldButton->setText("Show World Mode");
   // */
}

void Window::updateBrushPos()
{
   //if (!brushSpinX || !brushSpinY)
   //   return;

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
   //if (!joint1Spin || !joint2Spin || !joint3Spin)
   //   return;

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

void Window::carSelected(int index)
{
   // update X and Y
   // enable/disable delete button (disable if top/empty selected)
   // change text of create/modify button (modify = apply?)
   // read K (direct or inverted light/wheel mapping)
}

void Window::keyPressEvent(QKeyEvent* event)
{
   qDebug() << "Key Pressed" << event->key();
   if (event->key() == Qt::Key_Space)
   {
      qDebug() << "Toggling paint in canvas widget...";
      //paintButton->toggle();
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

QWidget* Window::initCarControls()
{
   QString           name = "car";
   QWidget*     carWidget = new QWidget(this);
   QGridLayout* carLayout = new QGridLayout(carWidget);

   carWidget->setObjectName(name);
   carWidget->setMinimumHeight(JOINT_HEIGHT);

   // combo box containing list of cars
   QComboBox* combo = new QComboBox(this);
   combo->setEditable(false);
   //combo.setWidth(COMBO_WIDTH);
   connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(carSelected(int)));

   // textedit for X and Y
   QSpinBox* xpos = new QSpinBox(this);
   xpos->setObjectName(name);
   xpos->setValue(WIDTH/2);

   QSpinBox* ypos = new QSpinBox(this);
   ypos->setObjectName(name);
   ypos->setValue(HEIGHT/2);

   // create button (modify button)
   createCarButton = new QPushButton("Create", this);
   connect(createCarButton, SIGNAL(clicked()), this, SLOT(createCarClicked()));

   // delete button
   deleteCarButton = new QPushButton("Delete", this);
   connect(deleteCarButton, SIGNAL(clicked()), this, SLOT(deleteCarClicked()));

   carLayout->addWidget(combo, 0, 0, 1, 2);
   carLayout->addWidget(xpos, 1, 0);
   carLayout->addWidget(ypos, 1, 1);
   carLayout->addWidget(createCarButton, 2, 0, 1, 2);
   carLayout->addWidget(deleteCarButton, 3, 0, 1, 2);

   return carWidget;
}

QWidget* Window::initLightControls()
{
   QString           name = "lights";
   QWidget*   lightWidget = new QWidget(this);
   QGridLayout*    layout = new QGridLayout(lightWidget);

   lightWidget->setObjectName(name);
   lightWidget->setMinimumHeight(JOINT_HEIGHT);
   
   return lightWidget;
}

