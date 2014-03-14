
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

Window::Window()
: QWidget()
{
   initStyles();
   initCanvas();
   initLayout();
   initControlPanel();

   initJointControls();
   controlLayout->addSpacing(15);
   initWorldControls();
   controlLayout->addSpacing(15);
   initBrushControls();

   //--------------------------------------------------------//
   // Add control panel to main grid layout
   //--------------------------------------------------------//
   layout->addWidget(controlPanel, 0, 1);

   QTimer* timer = new QTimer(this);
   connect(timer, SIGNAL(timeout()), canvasWidget, SLOT(animate()));
   timer->start();

   setWindowTitle("PaintBot");
}

Window::~Window()
{
   delete canvas;
}

void Window::initStyles()
{
   //QFile file("../src/styles.qss");
   QFile file(":/style");
   file.open(QFile::ReadOnly);
   
   controlPanelStyle = QLatin1String(file.readAll());
   qDebug() << "STYLE READ:";
   qDebug() << controlPanelStyle;
}

void Window::initCanvas()
{
   //--------------------------------------------------------//
   // Create the canvas and its container widget
   //--------------------------------------------------------//
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

void Window::initControlPanel()
{
   //--------------------------------------------------------//
   // Create the control panel layout and widgets
   //--------------------------------------------------------//
   QSizePolicy policy(QSizePolicy::Fixed, QSizePolicy::Fixed);

   controlPanel  = new QWidget(this);
   controlPanel->setMinimumWidth(CONTROL_WIDTH);
   controlPanel->setSizePolicy(policy);
   controlPanel->setStyleSheet(controlPanelStyle);
   controlLayout = new QVBoxLayout(controlPanel);

   // Control Panel Label
   QLabel*      controlLabel = new QLabel(tr("Controls"));
   controlLabel->setAlignment(Qt::AlignHCenter);
   controlLayout->addWidget(controlLabel);
}

void Window::initJointControls()
{
   QLabel* label = new QLabel("Joint Mode", this);
   label->setAlignment(Qt::AlignHCenter);

   QWidget* joint1 = createJointControl(1, Qt::blue);
   QWidget* joint2 = createJointControl(2, Qt::red);
   QWidget* joint3 = createJointControl(3, Qt::green);

   QWidget* jointControls = new QWidget(this);

   QVBoxLayout* jointLayout = new QVBoxLayout(jointControls);
   jointLayout->addWidget(label);
   jointLayout->addWidget(joint1);
   jointLayout->addWidget(joint2);
   jointLayout->addWidget(joint3);
   controlLayout->addWidget(jointControls);
}

void Window::initWorldControls()
{
   QLabel* label = new QLabel("World Mode", this);
   label->setAlignment(Qt::AlignHCenter);

   QWidget* joint1 = createWorldControl(1, Qt::blue);
   QWidget* joint2 = createWorldControl(2, Qt::red);
   QWidget* joint3 = createWorldControl(3, Qt::green);

   QWidget* worldControls = new QWidget(this);

   QVBoxLayout* worldLayout = new QVBoxLayout(worldControls);
   worldLayout->addWidget(label);
   worldLayout->addWidget(joint1);
   worldLayout->addWidget(joint2);
   worldLayout->addWidget(joint3);
   controlLayout->addWidget(worldControls);
}

void Window::initBrushControls()
{
   QWidget* brush = createBrushControl();

   controlLayout->addWidget(brush);
}

void Window::togglePaintText(bool enabled)
{
   if (enabled)
      paintButton->setText("Stop Painting");
   else
      paintButton->setText("Paint");
}

QWidget* Window::createJointControl
(
   int    id,     // which joint is this? 
   QColor color   // the color of this joint
)
{
   // This joint
   Joint j        = arm->getLink(id)->joint;
   QString name   = "joint" + QString::number(id);
   QString label  = "Joint " + QString::number(id);

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
   // Joint Controls: widget { gridlayout { label, spinbox } }
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
   QWidget*     joint   = new QWidget(this);
   QGridLayout* jLayout = new QGridLayout(joint);
   joint->setObjectName(name);
   joint->setMinimumHeight(JOINT_HEIGHT);
   jLayout->setContentsMargins(5, 5, 5, 5);

   QLabel*      jLabel  = new QLabel(label, joint);
   jLabel->setAlignment(Qt::AlignCenter);
   jLayout->addWidget(jLabel, 0, 0);

   QSpinBox*    jSpin   = new QSpinBox(joint);
   jSpin->setObjectName(name);
   jSpin->setMinimumHeight(JOINT_HEIGHT);
   jSpin->setRange(j.range_min, j.range_max);

   if (j.type == REVOLUTE)
      jSpin->setSuffix(" deg");
   else
      jSpin->setSuffix(" px");

   // allow the joint to wrap if revolute
   jSpin->setWrapping(j.type == REVOLUTE);

   // Connect the signal to the joint's slot
   if (id == 1)
   {
      connect( jSpin,         SIGNAL(valueChanged(int)),
               canvasWidget,  SLOT  (changeJoint1(int)));
   }
   else if (id == 2)
   {
      connect( jSpin,         SIGNAL(valueChanged(int)),
               canvasWidget,  SLOT  (changeJoint2(int)));
   }
   else if (id == 3)
   {
      connect( jSpin,         SIGNAL(valueChanged(int)),
               canvasWidget,  SLOT  (changeJoint3(int)));
   }
   
   // set the default value afterward connecting so it will update the canvas
   jSpin->setValue(j.rotation);
   jLayout->addWidget(jSpin, 0, 1);

   return joint;
}

QWidget* Window::createWorldControl(int id, QColor color)
{
   // This joint
   Joint j = arm->getLink(id)->joint;
   QString name   = "joint" + QString::number(id);
   QString label  = "Joint " + QString::number(id);

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
   // Joint Controls: widget { gridlayout { label, spinbox } }
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
   QWidget* joint       = new QWidget(this);
   QGridLayout* jLayout = new QGridLayout(joint);

   joint->setObjectName(name);
   joint->setMinimumHeight(JOINT_HEIGHT);
   jLayout->setContentsMargins(5, 5, 5, 5);

   QLabel*      jLabel  = new QLabel(label, joint);
   jLabel->setAlignment(Qt::AlignCenter);
   jLayout->addWidget(jLabel, 0, 0);

   QSpinBox*    jSpin   = new QSpinBox(joint);
   jSpin->setObjectName(name);
   jSpin->setMinimumHeight(JOINT_HEIGHT);
   jSpin->setRange(j.range_min, j.range_max);

   if (j.type == REVOLUTE)
      jSpin->setSuffix(" deg");
   else
      jSpin->setSuffix(" px");

   // allow the joint to wrap if revolute
   jSpin->setWrapping(j.type == REVOLUTE);

   // Connect the signal to the joint's slot
   if (id == 1)
   {
      connect( jSpin,         SIGNAL(valueChanged(int)),
               canvasWidget,  SLOT  (changeJoint1(int)));
   }
   else if (id == 2)
   {
      connect( jSpin,         SIGNAL(valueChanged(int)),
               canvasWidget,  SLOT  (changeJoint2(int)));
   }
   else if (id == 3)
   {
      connect( jSpin,         SIGNAL(valueChanged(int)),
               canvasWidget,  SLOT  (changeJoint3(int)));
   }
   
   // set the default value afterward connecting so it will update the canvas
   jSpin->setValue(j.rotation);
   jLayout->addWidget(jSpin, 0, 1);

   return joint;
}

QWidget* Window::createBrushControl()
{
   QString name = "brush";

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
   // Add the brush activator button to the control panel
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
   QWidget*     paintWidget = new QWidget(this);
   QGridLayout* paintLayout = new QGridLayout(paintWidget);

   paintWidget->setObjectName(name);
   paintWidget->setMinimumHeight(JOINT_HEIGHT);
   paintLayout->setContentsMargins(5, 5, 5, 5);

   paintButton = new QPushButton("Paint", paintWidget);
   paintButton->setCheckable(true);

   // connect the button to the canvas widget
   connect( paintButton,  SIGNAL (toggled(bool)),
            canvasWidget, SLOT   (togglePaint(bool)));
   // connect the button to change the text
   connect( paintButton,  SIGNAL (toggled(bool)),
            this,         SLOT   (togglePaintText(bool)));

   paintLayout->addWidget(paintButton, 0, 0);

   return paintWidget;
}

