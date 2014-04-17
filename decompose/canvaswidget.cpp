
#include "canvaswidget.h"
#include "consts.h"
#include "canvas.h"

#include <iostream>
#include <cmath>

using namespace std;


CanvasWidget::CanvasWidget(Canvas* _canvas, QWidget* _parent)
: QGLWidget(QGLFormat(QGL::SampleBuffers), _parent),
canvas(_canvas)
{
   setFixedSize(WIDTH, HEIGHT);
   setAutoFillBackground(false);
}

CanvasWidget::~CanvasWidget()
{
}

QSize CanvasWidget::sizeHint() const
{
   return QSize(640, 480);
}

void CanvasWidget::animate()
{
   repaint();
}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
   QPainter painter;
   painter.begin(this);
   painter.setRenderHint(QPainter::Antialiasing);
   canvas->display();
   painter.end();
}

void CanvasWidget::initializeGL()
{
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);

   qglClearColor(QColor(Qt::black));

   canvas->init();
}

void CanvasWidget::resizeGL(int width, int height)
{
   if (height == 0)
      height = 1;

   glViewport(0, 0, width, height);
}

