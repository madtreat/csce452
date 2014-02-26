
#include "canvaswidget.h"
#include "canvas.h"
#include "robotarm.h"

#include <iostream>


CanvasWidget::CanvasWidget(Canvas* _canvas, RobotArm* _arm, QWidget* _parent)
: QGLWidget(QGLFormat(QGL::SampleBuffers), _parent),
  canvas(_canvas),
  robot(_arm),
  joint1rot(0),
  joint2rot(0),
  joint3rot(0)
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

void CanvasWidget::changeJoint1(int newVal)
{
   Motion motion = (newVal < joint1rot) ? CW : CCW;
   int amount = abs(newVal - joint1rot);
   robot->moveJoint(robot->getLink(1), motion, amount);
   
   joint1rot = newVal;
}

void CanvasWidget::changeJoint2(int newVal)
{
   Motion motion = (newVal < joint2rot) ? CW : CCW;
   int amount = abs(newVal - joint2rot);
   robot->moveJoint(robot->getLink(2), motion, amount);
   
   joint2rot = newVal;
}

void CanvasWidget::changeJoint3(int newVal)
{
   Motion motion = (newVal < joint3rot) ? CW : CCW;
   int amount = abs(newVal - joint3rot);
   robot->moveJoint(robot->getLink(3), motion, amount);
   
   joint3rot = newVal;
}

/*
   If enabled, turn on the canvas' painting
   If not enabled, the canvas should not add new paint circles
 */
void CanvasWidget::togglePaint(bool enabled)
{
   canvas->setPainting(enabled);
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

