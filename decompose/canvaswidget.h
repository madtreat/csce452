
#ifndef CANVASWIDGET_H_
#define CANVASWIDGET_H_

#include "consts.h"
#include "robot.h"
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
   
	//TODO: Delete. cause moved to manager
	/*
	void printCarLocs() const;
   void printLightLocs() const;

   Cars     getCars() const {return cars;}
   Lights   getLights() const {return lights;}

   Car      getCar(int i) const {if (i >= cars.size()) return Car(); else return cars[i];}
   Light    getLight(int i) const {if (i >= lights.size()) return Light(); else return lights[i];}
	//*/

signals:
   void jointsChanged();
   void brushPosChanged();

public slots:
   void animate();
   
	//TODO: Delete. cause moved to manager
	/*
	void addNewCar(Car car);
   void addNewLight(Light light);
   void deleteCar(int car);
   void deleteLight(int light);
   void updateCarPos(int car, int newX, int newY, bool directMapping);
   void updateLightPos(int light, int newX, int newY);
	//*/

protected:
   void paintEvent(QPaintEvent *event);
   void initializeGL();
   void resizeGL(int width, int height);

private:
   Canvas*  canvas;
	
	//TODO: Delete. cause moved to manager
	/*
   Cars     cars;    // list of cars
   Lights   lights;  // list of lights
	*/
};

#endif

