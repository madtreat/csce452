
#include "canvaswidget.h"
#include "canvas.h"
#include "robotarm.h"

#include <iostream>
#include <cmath>

using namespace std;


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

void CanvasWidget::printCarLocs() const
{
	cout << endl;
   for (int i = 0; i < cars.size(); i++)
   {
      cout << "Car " << i << " (" << cars[i].getX() << ", " << cars[i].getY() << ")" << endl;
   }
}

void CanvasWidget::printLightLocs() const
{
	cout << endl;
   for (int i = 0; i < lights.size(); i++)
   {
      cout << "Car " << i << " (" << lights[i].X << ", " << lights[i].Y << ")" << endl;
   }
}

void CanvasWidget::addNewCar(Car car)
{
   cars.push_back(car);
}

void CanvasWidget::addNewLight(Light light)
{
   lights.push_back(light);
}

void CanvasWidget::deleteCar(int car)
{
   cars.erase(cars.begin() + car - 1);
}

void CanvasWidget::deleteLight(int light)
{
   lights.erase(lights.begin() + light - 1);
}

void CanvasWidget::updateCarPos(int carID, int newX, int newY, bool directMapping)
{
   Car car = cars[carID];
   car.setX(newX);
   car.setY(newY);
   car.setDirect(directMapping);
}

void CanvasWidget::updateLightPos(int lightID, int newX, int newY)
{
   Light light = lights[lightID];
   light.X = newX;
   light.Y = newY;
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

