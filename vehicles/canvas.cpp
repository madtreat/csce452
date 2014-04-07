
#include "canvas.h"
<<<<<<< HEAD

=======
#include "consts.h"
#include "joint.h"
#include "link.h"
#include "base.h"
#include "brush.h"
#include "robotarm.h"
>>>>>>> 53efdff0fefdf7a77df6889174610a28c2b17e31

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#elif __linux__
#include <GL/glut.h>
#include <GL/gl.h>
#else
#include <gl/glut.h>
#include <gl/gl.h>
#endif

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

   Canvas::Canvas(Manager* _man) 
:manager(_man)
{
	//TODO: Not sure if this is needed
	/*
   int argc = 1;
   char* argv[argc];
   argv[0] = "Braitenberg Vehicles";
   //glutInit(&argc, argv);
	// */
}

Canvas::~Canvas()
{
}

void Canvas::init ( void )
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, WIDTH-1, HEIGHT-1, 0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}

void Canvas::drawCars()
{
	for (int i=0; i<manager.getCars().size(); i++)
	{
		Car car = manager.getCar(i);
		int X = car.getX();
		int Y = car.getY();
		int r = car.getR();
		
	}
}

void Canvas::drawLights()
{
	Lights lights = manager.getLights();
}

/*
// the paint brush draws circles on the canvas
// radius is the paint's radius
void Canvas::drawCircle(int x, int y, int radius)
{
   
}

void Canvas::drawLink(int linkNum, double r, double g, double b)
{
   
}

void Canvas::drawJoint(int linkNum, double r, double g, double b)
{
   
}

void Canvas::drawRobot()
{
   
}

void Canvas::paintCurrentLoc()
{
	vector<PaintSpot>::iterator it;
   Brush* b = static_cast<Brush*>(robot->getLink(RobotArm::LENGTH-1));
   glColor3f(1,0,0);

   PaintSpot spot(b->joint.X, b->joint.Y, brushSize);
   it = find(paintspots.begin(), paintspots.end(), spot);
   if( it == paintspots.end()) 
   {
      paintspots.push_back(spot);
   }
}

void Canvas::drawPaint()
{
}
//*/

void Canvas::display ( void )
{
   glClear ( GL_COLOR_BUFFER_BIT );

   // set white canvas
   glColor3f (.5,.5,.5);
   glBegin (GL_POLYGON);
   glVertex2f (10, 10);
   glVertex2f (10, HEIGHT-10);
   glVertex2f (WIDTH-10, HEIGHT-10);
   glVertex2f (WIDTH-10, 10);
   glEnd();
   glColor3f(1.0,0.25,0.0);

   glLineWidth(3.0);
   glBegin (GL_LINE_LOOP);
   glVertex2f (10, 10);
   glVertex2f (10, HEIGHT-10);
   glVertex2f (WIDTH-10, HEIGHT-10);
   glVertex2f (WIDTH-10, 10);
   glEnd();

   //drawRobot();

}

