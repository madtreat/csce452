
#include "window.h"
#include "canvas.h"
#include "canvaswidget.h"

#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QTimer>
#include <QPushButton>

Window::Window()
: QWidget()
{
   // Create the main/top-level grid layout
   QGridLayout* layout = new QGridLayout(this);
   layout->setContentsMargins(0, 0, 0, 0);

   //--------------------------------------------------------//
   // Create the canvas and its container widget
   //--------------------------------------------------------//
   canvas       = new Canvas();
   canvasWidget = new CanvasWidget(canvas, this);
   
   // Add to main grid layout
   layout->addWidget(canvasWidget, 0, 0);

   //--------------------------------------------------------//
   // Create the control panel layout and widgets
   //--------------------------------------------------------//
   QWidget*     controlPanel  = new QWidget(this);
   //controlPanel->setStyleSheet("QWidget {background-color: black; forground: red}");
   QVBoxLayout* controlLayout = new QVBoxLayout(controlPanel);

   // Control Panel Label
   QLabel*      controlLabel = new QLabel(tr("Controls"));
   controlLabel->setAlignment(Qt::AlignHCenter);
   controlLayout->addWidget(controlLabel);

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
   // Joint 1 Controls: widget { gridlayout { label, spinbox } }
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
   QWidget*     joint1   = new QWidget(this);
   QGridLayout* j1Layout = new QGridLayout(joint1);
   joint1->setStyleSheet(getControlStyle(Qt::blue));
   j1Layout->setContentsMargins(5, 5, 5, 5);

   QLabel*      j1Label  = new QLabel(tr("Joint 1"), joint1);
   j1Label->setAlignment(Qt::AlignCenter);
   j1Layout->addWidget(j1Label, 0, 0);

   QSpinBox*    j1Spin   = new QSpinBox(joint1);
   j1Spin->setRange(0, 300);
   j1Spin->setSuffix(" px");
   j1Spin->setWrapping(false); // do not allow the P joint to wrap
   j1Layout->addWidget(j1Spin, 0, 1);

   controlLayout->addWidget(joint1);

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
   // Joint 2 Controls: widget { gridlayout { label, spinbox } }
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
   QWidget*     joint2   = new QWidget(this);
   QGridLayout* j2Layout = new QGridLayout(joint2);
   joint2->setStyleSheet(getControlStyle(Qt::red));
   j2Layout->setContentsMargins(5, 5, 5, 5);

   QLabel*      j2Label  = new QLabel(tr("Joint 2"), joint2);
   j2Label->setAlignment(Qt::AlignCenter);
   j2Layout->addWidget(j2Label, 0, 0);

   QSpinBox*    j2Spin   = new QSpinBox(joint2);
   j2Spin->setRange(0, 359);
   j2Spin->setSuffix(" px");
   j2Spin->setWrapping(true); // allow the R joint to wrap
   j2Layout->addWidget(j2Spin, 0, 1);

   controlLayout->addWidget(joint2);

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
   // Joint 3 Controls: widget { gridlayout { label, spinbox } }
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
   QWidget*     joint3   = new QWidget(this);
   QGridLayout* j3Layout = new QGridLayout(joint3);
   joint3->setStyleSheet(getControlStyle(Qt::green));
   j3Layout->setContentsMargins(5, 5, 5, 5);

   QLabel*      j3Label  = new QLabel(tr("Joint 3"), joint3);
   j3Label->setAlignment(Qt::AlignCenter);
   j3Layout->addWidget(j3Label, 0, 0);

   QSpinBox*    j3Spin   = new QSpinBox(joint3);
   j3Spin->setRange(0, 359);
   j3Spin->setSuffix(" px");
   j3Spin->setWrapping(true); // allow the R joint to wrap
   j3Layout->addWidget(j3Spin, 0, 1);
   
   controlLayout->addWidget(joint3);

   // - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
   // Add the brush activator button to the control panel
   // - - - - - - - - - - - - - - - - - - - - - - - - - - - -//
   QWidget*     paintWidget = new QWidget(this);
   QGridLayout* paintLayout = new QGridLayout(paintWidget);
   paintWidget->setStyleSheet(getControlStyle(Qt::yellow));
   paintLayout->setContentsMargins(5, 5, 5, 5);

   QPushButton* paintButton = new QPushButton("Paint", paintWidget);
   paintButton->setCheckable(true);
   paintLayout->addWidget(paintButton, 0, 0);

   controlLayout->addWidget(paintWidget);

   //--------------------------------------------------------//
   // Add control panel to main grid layout
   // ...After adding some vertical spacing to the bottom
   //--------------------------------------------------------//
   controlLayout->addSpacing(250);
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

QString Window::getControlStyle(QColor widget)
{
   QString style;
   
   // set widget color
   style += "QWidget {background-color: ";
   style += widget.name();
   //style += "; margin: 5 5 5 5";
   style += ";}";

   // set label color
   style += "QLabel {background-color: ";
   style += "white";
   style += "; color: ";
   style += "black";//widget.name();
   style += "; padding: 0 5 0 5";
   style += ";}";

   // set spinbox color
   style += "QSpinBox {background-color: ";
   style += "white";
   style += "; color: ";
   style += "black";//widget.name();
   style += ";}";

   // set push button color
   style += "QPushButton {background-color: ";
   style += "black";
   style += "; color: ";
   style += "red";
   style += "; padding: 0 5 0 5";
   style += ";}";

   return style;
}
