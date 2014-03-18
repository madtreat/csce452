
#include "canvaswidget.h"
#include "canvas.h"
#include "robotarm.h"

#include <iostream>
#include <cmath>


CanvasWidget::CanvasWidget(Canvas* _canvas, RobotArm* _arm, QWidget* _parent)
: QGLWidget(QGLFormat(QGL::SampleBuffers), _parent),
  canvas(_canvas),
  robot(_arm),
  brushSize(5),
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
	std::cout << std::endl;
   std::cout << "l1: " << robot->getLink(1)->joint.X << " " << robot->getLink(1)->joint.Y << std::endl;
   std::cout << "l2: " << robot->getLink(2)->joint.X << " " << robot->getLink(2)->joint.Y << std::endl;
   std::cout << "l3: " << robot->getLink(3)->joint.X << " " << robot->getLink(3)->joint.Y << std::endl;
   std::cout << "br: " << robot->getLink(4)->joint.X << " " << robot->getLink(4)->joint.Y << std::endl;
	std::cout << std::endl;
}

void CanvasWidget::animate()
{
   repaint();
}

void CanvasWidget::changeBrushSize(int newSize)
{
   brushSize = newSize;
   canvas->setBrushSize(brushSize);
}

void CanvasWidget::changeJoint1(int newVal)
{
   Motion motion = (newVal < joint1rot) ? LEFT : RIGHT;
   robot->translateJoint(robot->getLink(1), motion, newVal);
   
   joint1rot = newVal;
   std::cout << "joint 1 changing" << std::endl;
   printJointLocs();
   emit jointsChanged();
}

void CanvasWidget::changeJoint2(int newVal)
{
   Motion motion = (newVal < joint2rot) ? CW : CCW;
   robot->rotateJoint(robot->getLink(2), motion, newVal);
   
   joint2rot = newVal;
   std::cout << "joint 2 changing" << std::endl;
   printJointLocs();
   emit jointsChanged();
}

void CanvasWidget::changeJoint3(int newVal)
{
   Motion motion = (newVal < joint3rot) ? CW : CCW;
   robot->rotateJoint(robot->getLink(3), motion, newVal);
   
   joint3rot = newVal;
   std::cout << "joint 3 changing" << std::endl;
   printJointLocs();
   emit jointsChanged();
}

void CanvasWidget::changeBrushLocX(int newVal)
{
   int prevX = robot->getBrush()->joint.X;
   if (newVal == prevX)
      return; // dont do anything if same

   robot->translateBrush(robot->getBrush(), newVal, robot->getBrush()->joint.Y);
   
   std::cout << "joint 4 X location changing" << std::endl;
   printJointLocs();
   emit brushPosChanged();
}

void CanvasWidget::changeBrushLocY(int newVal)
{
   int prevY = robot->getBrush()->joint.Y;
   if (newVal == prevY)
      return; // dont do anything if same

   robot->translateBrush(robot->getBrush(), robot->getBrush()->joint.X, newVal);
   
   std::cout << "joint 4 Y location changing" << std::endl;
   printJointLocs();
   emit brushPosChanged();
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

