
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

signals:
   void jointsChanged();

public slots:
   void animate();
   void changeBrushSize(int);
   void changeJoint1(int);
   void changeJoint2(int);
   void changeJoint3(int);
   void changeBrushLocX(int);
   void changeBrushLocY(int);
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

