
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

void CanvasWidget::printJointLocs() const
{
   std::cout << robot->getLink(1)->joint.X << " " << robot->getLink(1)->joint.Y << std::endl;
   std::cout << robot->getLink(2)->joint.X << " " << robot->getLink(2)->joint.Y << std::endl;
   std::cout << robot->getLink(3)->joint.X << " " << robot->getLink(3)->joint.Y << std::endl;
   std::cout << robot->getLink(4)->joint.X << " " << robot->getLink(4)->joint.Y << std::endl;
}

void CanvasWidget::animate()
{
   repaint();
}

void CanvasWidget::changeJoint1(int newVal)
{
   std::cout << "about to move joint 1" << endl;
   printJointLocs();
   Motion motion = (newVal < joint1rot) ? LEFT : RIGHT;
   robot->moveJoint(robot->getLink(1), motion, newVal);
   
   joint1rot = newVal;
   std::cout << "joint 1 changing" << std::endl;
   printJointLocs();
}

void CanvasWidget::changeJoint2(int newVal)
{
   Motion motion = (newVal < joint2rot) ? CW : CCW;
   robot->moveJoint(robot->getLink(2), motion, newVal);
   
   joint2rot = newVal;
   std::cout << "joint 2 changing" << std::endl;
   printJointLocs();
}

void CanvasWidget::changeJoint3(int newVal)
{
   Motion motion = (newVal < joint3rot) ? CW : CCW;
   robot->moveJoint(robot->getLink(3), motion, newVal);
   
   joint3rot = newVal;
   std::cout << "joint 3 changing" << std::endl;
   printJointLocs();
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

