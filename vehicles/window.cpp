
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

Window::Window()
: QWidget()
{
   initStyles();
   initCanvas();
   initLayout();

   setObjectName("main-window");
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
	timer->setInterval(1000);
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
   controlPanel->setMinimumWidth(2.8*COMBO_WIDTH);
   controlPanel->setSizePolicy(policy);
   controlPanel->setStyleSheet(controlPanelStyle);
   //controlPanel->setObjectName("container");

   controlLayout = new QGridLayout(controlPanel);

   // Control Panel Label
   QLabel* controlLabel = new QLabel(tr("Controls"));
   controlLabel->setAlignment(Qt::AlignHCenter);
   return controlLabel;
}

void Window::carSelected(int index)
{
   // TODO: DONE: update X and Y
   // TODO: enable/disable delete button (disable if top/empty selected)
   // TODO: change text of create/modify button (modify = apply?)
   Car car = manager->getCar(index);

   carSpinX->setValue(car.getX());
   carSpinY->setValue(car.getY());
   directBox->setChecked(car.getDirect());
}

void Window::lightSelected(int index)
{
   Car car = manager->getCar(index);

   lightSpinX->setValue(car.getX());
   lightSpinY->setValue(car.getY());
}

void Window::setCheckBoxText(int state)
{
   if (state == Qt::Checked)
   {
      directBox->setText("Direct Mapping");
   }
   else
   {
      directBox->setText("Indirect Mapping");
   }
}

void Window::createCarClicked()
{
   int x = carSpinX->value();
   int y = carSpinY->value();
   bool direct = directBox->isChecked();

   Car car(Position(x, y), direct);
   manager->addNewCar(car);

   QString name = "Car " + QString::number(manager->numCars());
   carComboBox->addItem(name);
}

void Window::deleteCarClicked()
{
}

void Window::createLightClicked()
{
   int x = lightSpinX->value();
   int y = lightSpinY->value();
   
   Light light(x, y);
   manager->addNewLight(light);

   QString name = "Light " + QString::number(manager->numLights());
   lightComboBox->addItem(name);
}

void Window::deleteLightClicked()
{
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

   // car control label
   QLabel* carLabel = new QLabel("Car Controls", this);
   carLabel->setAlignment(Qt::AlignHCenter);

   // combo box containing list of cars
   carComboBox = new QComboBox(this);
   carComboBox->setObjectName(name);
   carComboBox->setEditable(false);
   carComboBox->setMinimumWidth(COMBO_WIDTH);
   connect(carComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(carSelected(int)));

   // spin box for X pos
   QLabel* xlabel = new QLabel(" X =", this);
   xlabel->setObjectName(name);

   carSpinX = new QSpinBox(this);
   carSpinX->setObjectName(name);
   carSpinX->setRange(0, WIDTH);
   carSpinX->setValue(WIDTH/2);
   carSpinX->setWrapping(true); // looping is enabled

   // spin box for Y pos
   QLabel* ylabel = new QLabel(" Y =", this);
   ylabel->setObjectName(name);

   carSpinY = new QSpinBox(this);
   carSpinY->setObjectName(name);
   carSpinY->setRange(0, HEIGHT);
   carSpinY->setValue(HEIGHT/2);
   carSpinY->setWrapping(true); // looping is enabled

   // INVERSE or DIRECT mapping
   directBox = new QCheckBox("Direct Mapping", this);
   directBox->setObjectName(name);
   connect(directBox, SIGNAL(stateChanged(int)), this, SLOT(setCheckBoxText(int)));
   directBox->setChecked(true);

   // create button (modify button)
   createCarButton = new QPushButton("Create", this);
   createCarButton->setObjectName(name);
   connect(createCarButton, SIGNAL(clicked()), this, SLOT(createCarClicked()));

   // delete button
   deleteCarButton = new QPushButton("Delete", this);
   deleteCarButton->setObjectName(name);
   connect(deleteCarButton, SIGNAL(clicked()), this, SLOT(deleteCarClicked()));

   carLayout->addWidget(carLabel,   0, 0, 1, 2);
   carLayout->addWidget(carComboBox,1, 0, 1, 2);
   carLayout->addWidget(xlabel,     2, 0);
   carLayout->addWidget(carSpinX,   2, 1);
   carLayout->addWidget(ylabel,     3, 0);
   carLayout->addWidget(carSpinY,   3, 1);
   carLayout->addWidget(directBox,  4, 0, 1, 2);
   carLayout->addWidget(createCarButton, 5, 0, 1, 2);
   carLayout->addWidget(deleteCarButton, 6, 0, 1, 2);

   return carWidget;
}

QWidget* Window::initLightControls()
{
   QString           name   = "light";
   QWidget*   lightWidget   = new QWidget(this);
   QGridLayout* lightLayout = new QGridLayout(lightWidget);

   lightWidget->setObjectName(name);
   lightWidget->setMinimumHeight(JOINT_HEIGHT);

   // light control label
   QLabel* lightLabel = new QLabel("Light Controls", this);
   lightLabel->setAlignment(Qt::AlignHCenter);

   // combo box containing list of lights
   lightComboBox = new QComboBox(this);
   lightComboBox->setObjectName(name);
   lightComboBox->setEditable(false);
   lightComboBox->setMinimumWidth(COMBO_WIDTH);
   connect(lightComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(lightSelected(int)));

   // spin box for X pos
   QLabel* xlabel = new QLabel(" X =", this);
   xlabel->setObjectName(name);

   lightSpinX = new QSpinBox(this);
   lightSpinX->setObjectName(name);
   lightSpinX->setRange(0, WIDTH);
   lightSpinX->setValue(WIDTH/2);
   lightSpinX->setWrapping(true); // looping is enabled

   // spin box for Y pos
   QLabel* ylabel = new QLabel(" Y =", this);
   ylabel->setObjectName(name);

   lightSpinY = new QSpinBox(this);
   lightSpinY->setObjectName(name);
   lightSpinY->setRange(0, HEIGHT);
   lightSpinY->setValue(HEIGHT/2);
   lightSpinY->setWrapping(true); // looping is enabled

   // create button (modify button)
   createLightButton = new QPushButton("Create", this);
   createLightButton->setObjectName(name);
   connect(createLightButton, SIGNAL(clicked()), this, SLOT(createLightClicked()));

   // delete button
   deleteLightButton = new QPushButton("Delete", this);
   deleteLightButton->setObjectName(name);
   connect(deleteLightButton, SIGNAL(clicked()), this, SLOT(deleteLightClicked()));

   lightLayout->addWidget(lightLabel,  0, 0, 1, 2);
   lightLayout->addWidget(lightComboBox,1, 0, 1, 2);
   lightLayout->addWidget(xlabel,      2, 0);
   lightLayout->addWidget(lightSpinX,  2, 1);
   lightLayout->addWidget(ylabel,      3, 0);
   lightLayout->addWidget(lightSpinY,  3, 1);
   lightLayout->addWidget(createLightButton, 4, 0, 1, 2);
   lightLayout->addWidget(deleteLightButton, 5, 0, 1, 2); 

   return lightWidget;
}

