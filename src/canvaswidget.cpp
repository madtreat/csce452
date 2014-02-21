
#include "canvaswidget.h"
#include "canvas.h"

#include <iostream>


CanvasWidget::CanvasWidget(Canvas* _canvas, QWidget* _parent)
: QGLWidget(QGLFormat(QGL::SampleBuffers), _parent),
  canvas(_canvas)
{
   setFixedSize(Canvas::WIDTH, Canvas::HEIGHT);
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

/*
void CanvasWidget::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //QMatrix4x4 mMatrix;
   //QMatrix4x4 vMatrix;

   //shaderProgram.bind();
   //shaderProgram.setUniformValue("mvpMatrix", pMatrix + vMatrix + mMatrix);
   //shaderProgram.setUniformValue("color", QColor(Qt::white));
   //shaderProgram.setAttributeArray("vertex", vertices.constData());
   //shaderProgram.enableAttributeArray("vertex");

   //glDrawArrays(GL_TRIANGLES, 0, vertices.size());
   //shaderProgram.disableAttributeArray("vertex");
   //shaderProgram.release();
}
// */

