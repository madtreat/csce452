
#ifndef CANVASWIDGET_H_
#define CANVASWIDGET_H_

#include "consts.h"
#include <QGLWidget>
#include <QMatrix>
#include <QVector>
#include <QGLShaderProgram>


class Canvas;

class CanvasWidget : public QGLWidget
{
   Q_OBJECT

public:
   CanvasWidget(Canvas* _canvas, QWidget* _parent = 0);
   ~CanvasWidget();
   
   QSize sizeHint() const;

signals:
   void jointsChanged();
   void brushPosChanged();

public slots:
   void animate();

protected:
   void paintEvent(QPaintEvent *event);
   void initializeGL();
   void resizeGL(int width, int height);

private:
   Canvas*  canvas;
};

#endif

