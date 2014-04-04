
#include "window.h"
#include "canvas.h"
#include "canvaswidget.h"
#include "robotarm.h"

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

   setWindowTitle("Braitenberg Vehicles");
}

Window::~Window()
{
   delete canvas;
}

int Window::jointToNum(QString name)
{
   if (name == "Brush" || name == "BrushX" || name == "BrushY")
      return RobotArm::LENGTH-1; // the brush is link 4/joint 4

   // parse the last character of name ( "Joint1" | "Joint2" | etc. )
   QChar digit = name.at(name.size()-1);
   int num = digit.digitValue();

   if (num == -1)
      return 0;
   
   return num;
}

QString Window::numToJoint(int num)
{
   if (num == RobotArm::LENGTH-1)
      return "Brush";

   QString joint = "Joint";
   joint += QString::number(num);
   return joint;
}

void Window::changeJoint1(int newVal)
{
   QString name = "Joint1";
   notifyServer(name, newVal);
}

void Window::changeJoint2(int newVal)
{
   QString name = "Joint2";
   notifyServer(name, newVal);
}

void Window::changeJoint3(int newVal)
{
   QString name = "Joint3";
   notifyServer(name, newVal);
}

void Window::changeBrushX(int newVal)
{
   QString name = "BrushX";
   notifyServer(name, newVal);
}

void Window::changeBrushY(int newVal)
{
   QString name = "BrushY";
   notifyServer(name, newVal);
}

void Window::changeBrushSize(int newVal)
{
   QString name = "BrushSize";
   notifyServer(name, newVal);
}

void Window::changePainting(bool enabled)
{
   QString name = "Painting";
   if (enabled)
      notifyServer(name, 1);
   else
      notifyServer(name, 0);
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
   // Create RobotArm here so we can call canvas::drawLinks
   arm          = new RobotArm();
   canvas       = new Canvas(arm);
   canvasWidget = new CanvasWidget(canvas, arm, this);
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
   QWidget* jointPanel = new QWidget(this);
   jointPanel->setMinimumWidth(CONTROL_WIDTH);
   jointPanel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));//Fixed));

   jointControls = new QWidget(this);
   jointControls->setObjectName("container");

   QWidget* joint1 = createJointControl(1);
   QWidget* joint2 = createJointControl(2);
   QWidget* joint3 = createJointControl(3);

   QVBoxLayout* jointLayout = new QVBoxLayout(jointControls);
   jointLayout->setContentsMargins(0, 0, 0, 0);
   jointLayout->addWidget(joint1);
   jointLayout->addWidget(joint2);
   jointLayout->addWidget(joint3);

   QString label = "Joint Mode";
   jointButton = new QPushButton(label, this);
   jointButton->setObjectName("controls");
   jointButton->setCheckable(true);
   connect(jointButton, SIGNAL(toggled(bool)),
           this,        SLOT  (toggleJointControlsVisible(bool)));
   jointButton->setChecked(true);

   QVBoxLayout* panelLayout = new QVBoxLayout(jointPanel);
   panelLayout->setContentsMargins(5, 5, 5, 5);
   panelLayout->addWidget(jointButton);
   panelLayout->addWidget(jointControls);

   return jointPanel;
}

QWidget* Window::initWorldControls()
{
   QWidget* worldPanel = new QWidget(this);
   worldPanel->setMinimumWidth(CONTROL_WIDTH);
   worldPanel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred));//Fixed));

   worldControls = new QWidget(this);
   worldControls->setObjectName("container");

   //*
   //QWidget* joint1 = createWorldControl(1);
   QWidget* joint2 = createWorldControl(2);
   QWidget* joint3 = createWorldControl(3);
   // */
   QWidget* brush  = createWorldControl(4);

   QVBoxLayout* worldLayout = new QVBoxLayout(worldControls);
   worldLayout->setContentsMargins(0, 0, 0, 0);
   //worldLayout->addWidget(joint1);
   worldLayout->addWidget(brush);
   //*
   worldLayout->addWidget(joint2);
   worldLayout->addWidget(joint3);
   // */

   QString label = "World Mode";
   worldButton = new QPushButton(label, this);
   worldButton->setObjectName("controls");
   worldButton->setCheckable(true);
   connect(worldButton, SIGNAL(toggled(bool)),
           this,        SLOT  (toggleWorldControlsVisible(bool)));
   worldButton->setChecked(true);

   QVBoxLayout* panelLayout = new QVBoxLayout(worldPanel);
   panelLayout->setContentsMargins(5, 5, 5, 5);
   panelLayout->addWidget(worldButton);
   panelLayout->addWidget(worldControls);

   return worldPanel;
}

QWidget* Window::initBrushControls()
{
   QWidget* brushPanel = createBrushControl();

   return brushPanel;
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
   brushSpinX->setValue(arm->getBrush()->joint.X);
   brushSpinY->setValue(arm->getBrush()->joint.Y);

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
   joint1Spin->setValue(arm->getLink(1)->joint.rotation);
   joint2Spin->setValue(arm->getLink(2)->joint.rotation);
   joint3Spin->setValue(arm->getLink(3)->joint.rotation);

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
      int newX = 4 + arm->getBrush()->joint.X;
      //canvasWidget->changeBrushX(newX);
   }
   // move left
	if (event->key() == Qt::Key_A)
   {
      int newX = -4 + arm->getBrush()->joint.X;
      //canvasWidget->changeBrushX(newX);
   }
   // move up
	if (event->key() == Qt::Key_W)
   {
      int newY = -4 + arm->getBrush()->joint.Y;
      //canvasWidget->changeBrushY(newY);
   }
   // move down
	if (event->key() == Qt::Key_S)
   {
      int newY = 4 + arm->getBrush()->joint.Y;
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
   // This joint
   Joint j        = arm->getLink(id)->joint;
   QString name   = "joint" + QString::number(id);
   QString label  = "Joint " + QString::number(id);
   if (j.type == REVOLUTE)
      label += " (deg)";
   else
      label += " (px)";

   QWidget*     joint   = new QWidget(this);
   joint->setObjectName(name);
   joint->setMinimumHeight(JOINT_HEIGHT);

   QLabel*      jLabel  = new QLabel(label, joint);
   jLabel->setAlignment(Qt::AlignCenter);

   myQSpinBox*    jSpin1  = new myQSpinBox(joint);
   jSpin1->setObjectName(name);
   jSpin1->setMinimumHeight(JOINT_HEIGHT);
   jSpin1->setRange(j.range_min, j.range_max);
   jSpin1->setSuffix(" (x1)");
   jSpin1->setWrapping(j.type == REVOLUTE);
   jSpin1->setKeyboardTracking(false);

   myQSpinBox*    jSpin5  = new myQSpinBox(joint);
   jSpin5->setObjectName(name);
   jSpin5->setMinimumHeight(JOINT_HEIGHT);
   jSpin5->setRange(j.range_min, j.range_max);
   jSpin5->setSingleStep(5);
   jSpin5->setSuffix(" (x5)");
   jSpin5->setWrapping(j.type == REVOLUTE);
   jSpin5->setKeyboardTracking(false);

	// connect the spin boxes to each other
   connect( jSpin1,        SIGNAL(valueChanged(int)),
            jSpin5,        SLOT  (setValue(int)));
   connect( jSpin5,        SIGNAL(valueChanged(int)),
            jSpin1,        SLOT  (setValue(int)));
	
   // Connect the signals to the canvas widget's slot if this is not a client
   // if it IS a client, connect the signals to this class' slots to notify the server
   if (id == 1)
   {
      connect( jSpin1,        SIGNAL(valueChanged(int)),
               canvasWidget,  SLOT  (changeJoint1(int)));
      joint1Spin = jSpin5;
   }
   else if (id == 2)
   {
      connect( jSpin1,        SIGNAL(valueChanged(int)),
               canvasWidget,  SLOT  (changeJoint2(int)));
      joint2Spin = jSpin5;
   }
   else if (id == 3)
   {
      connect( jSpin1,        SIGNAL(valueChanged(int)),
               canvasWidget,  SLOT  (changeJoint3(int)));
      joint3Spin = jSpin5;
   }
   
   // set the default value after connecting so it will update the canvas
   jSpin1->setValue(j.rotation);

   // set tab order
   QWidget::setTabOrder(jSpin5, jSpin1);

   QGridLayout* jLayout = new QGridLayout(joint);
   jLayout->setContentsMargins(5, 5, 5, 5);
   jLayout->addWidget(jLabel, 0, 0, 1, 1);
   jLayout->addWidget(jSpin1, 2, 0, 1, 1);
   jLayout->addWidget(jSpin5, 1, 0, 1, 1);

   return joint;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
// World Controls: widget { gridlayout { label, spinbox, spinbox } }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
QWidget* Window::createWorldControl(int id)
{
   // This joint
   Joint j = arm->getLink(id)->joint;
   QString name  = "joint" + QString::number(id);
   QString label = "Joint " + QString::number(id);
   if (id == 4)
      label = "Brush";

   //QGroupBox* joint = new QGroupBox(label, this);
   QWidget* joint = new QWidget(this);
   joint->setObjectName(name);
   joint->setMinimumHeight(JOINT_HEIGHT);

   QLabel* jLabel = new QLabel(label, joint);
   jLabel->setAlignment(Qt::AlignCenter);

   myQSpinBox* jSpinX = new myQSpinBox(joint);
   jSpinX->setObjectName(name);
   jSpinX->setMinimumHeight(JOINT_HEIGHT);
   if (id == 4)
      jSpinX->setRange(arm->getBrush()->range_min_x, arm->getBrush()->range_max_x);
   else
      jSpinX->setRange(j.range_min, j.range_max);
   jSpinX->setPrefix("X=");
   jSpinX->setWrapping(j.type == REVOLUTE);
   jSpinX->setKeyboardTracking(false);

   myQSpinBox* jSpinY = new myQSpinBox(joint);
   jSpinY->setObjectName(name);
   jSpinY->setMinimumHeight(JOINT_HEIGHT);
   if (id == 4)
      jSpinY->setRange(arm->getBrush()->range_min_y, arm->getBrush()->range_max_y);
   else
      jSpinY->setRange(j.range_min, j.range_max);
   jSpinY->setPrefix("Y=");
   jSpinY->setWrapping(j.type == REVOLUTE);
   jSpinY->setKeyboardTracking(false);

   // Connect the signals to the canvas widget's slot if this is not a client
   // if it IS a client, connect the signals to this class' slots to notify the server
   if (id == 4)
   {
      connect( jSpinX,        SIGNAL(valueChanged(int)),
               canvasWidget,  SLOT  (changeBrushX(int)));
      connect( jSpinY,        SIGNAL(valueChanged(int)),
               canvasWidget,  SLOT  (changeBrushY(int)));
   }
   
   // set the default value after connecting so it will update the canvas
   jSpinX->setValue(j.X);
   jSpinY->setValue(j.Y);

   // set tab order
   QWidget::setTabOrder(jSpinX, jSpinY);
   brushSpinX = jSpinX;
   brushSpinY = jSpinY;

   QGridLayout* jLayout = new QGridLayout(joint);
   jLayout->setContentsMargins(5, 5, 5, 5);
   jLayout->addWidget(jLabel, 0, 0);
   jLayout->addWidget(jSpinX, 1, 0);
   jLayout->addWidget(jSpinY, 2, 0);

   return joint;
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

