
#include "window.h"
#include "canvas.h"
#include "canvaswidget.h"

#include <QLabel>
#include <QGridLayout>
#include <QTimer>

Window::Window()
: QWidget()
{
   canvas = new Canvas();
   //Widget*       native = new Widget(canvas, this);
   //QLabel*       nativeLabel = new QLabel(tr("Native"));
   //nativeLabel->setAlignment(Qt::AlignHCenter);

   CanvasWidget*  openGL      = new CanvasWidget(canvas, this);
   QLabel*        openGLLabel = new QLabel(tr("OpenGL"));
   openGLLabel->setAlignment(Qt::AlignHCenter);

   QGridLayout *layout = new QGridLayout();
   //layout->addWidget(native, 0, 0);
   layout->addWidget(openGL, 0, 1);
   //layout->addWidget(nativeLabel, 1, 0);
   layout->addWidget(openGLLabel, 1, 1);

   QTimer* timer = new QTimer(this);
   //connect(timer, SIGNAL(timeout()), native, SLOT(animate()));
   connect(timer, SIGNAL(timeout()), openGL, SLOT(animate()));
   timer->start();

   setWindowTitle("PaintBot");
}

Window::~Window()
{
   delete canvas;
}
