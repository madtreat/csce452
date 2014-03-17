
#ifndef CANVASWIDGET_H_
#define CANVASWIDGET_H_

#include <QGLWidget>
#include <QMatrix>
#include <QVector>
#include <QGLShaderProgram>

class Canvas;
class RobotArm;

class CanvasWidget : public QGLWidget
{
   Q_OBJECT

public:
   CanvasWidget(Canvas* _canvas, RobotArm* _arm, QWidget* _parent = 0);
   ~CanvasWidget();
   
   QSize sizeHint() const;
   void printJointLocs() const;

public slots:
   void animate();
   void changeBrushSize(int);
   void changeJoint1(int);
   void changeJoint2(int);
   void changeJoint3(int);
   void changeJoint1LocX(int);
   void changeJoint1LocY(int);
   void changeJoint2LocX(int);
   void changeJoint2LocY(int);
   void changeJoint3LocX(int);
   void changeJoint3LocY(int);
   void togglePaint(bool);

protected:
   void paintEvent(QPaintEvent *event);
   void initializeGL();
   void resizeGL(int width, int height);
   /*
   void paintGL();
   // */

private:
   Canvas* canvas;
   RobotArm* robot;

   // remember the old values for the joint configurations
   int brushSize;
   int joint1rot;
   int joint2rot;
   int joint3rot;
};

#endif

