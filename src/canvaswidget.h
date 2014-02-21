
#ifndef CANVASWIDGET_H_
#define CANVASWIDGET_H_

#include <QGLWidget>
#include <QMatrix>
#include <QVector>
#include <QGLShaderProgram>

class Canvas;

class CanvasWidget : public QGLWidget
{
   Q_OBJECT

public:
   static const int WIDTH  = 640;
   static const int HEIGHT = 480;

   CanvasWidget(Canvas* _canvas, QWidget* _parent = 0);
   ~CanvasWidget();
   QSize sizeHint() const;

public slots:
   void animate();

protected:
   void paintEvent(QPaintEvent *event);
   //void initializeGL();
   //void resizeGL(int width, int height);
   //void paintGL();

private:
   //QMatrix4x4 pMatrix;
   //QGLShaderProgram shaderProgram;
   //QVector<QVector3D> vertices;

   Canvas* canvas;

};

#endif

