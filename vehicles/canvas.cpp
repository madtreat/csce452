
#include "canvas.h"
#include "consts.h"

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
	const int car_length = 11;
	const int car_width = 8;
	//for (int i=0; i<manager->getCars().size(); i++)
	//{
		//Car car = manager->getCar(i);
		Car car = Car(Position(100,100),true);
		int X = car.getX();
		int Y = car.getY();
		double R = car.getR_rad();
		
		//TODO: change color based on K (inverted or not)
		//TODO: Possible: change wheels and sensors to scale with car size
		
		//Draw car body
		glColor3f(1,0,0);
		glBegin(GL_QUADS);
			glVertex2f(X + (-car_length*cos(R) - -car_width*sin(R)), Y + (-car_length*sin(R) + -car_width*cos(R)) );
			glVertex2f(X + (-car_length*cos(R) -  car_width*sin(R)), Y + (-car_length*sin(R) +  car_width*cos(R)) );
			glVertex2f(X + ( car_length*cos(R) -  car_width*sin(R)), Y + ( car_length*sin(R) +  car_width*cos(R)) );
			glVertex2f(X + ( car_length*cos(R) - -car_width*sin(R)), Y + ( car_length*sin(R) + -car_width*cos(R)) );
		glEnd();
		
		//Draw wheels	
		glColor3f(0,0,0);
		glBegin(GL_QUADS);
			//Left Tire
			glVertex2f((X-car_width) + (-4*cos(R) - -2*sin(R)), ((Y+(car_length/2)+2) + (-4*sin(R) + -2*cos(R))) );
			glVertex2f((X-car_width) + (-4*cos(R) -  2*sin(R)), ((Y+(car_length/2)+2) + (-4*sin(R) +  2*cos(R))) );
			glVertex2f((X-car_width) + ( 4*cos(R) -  2*sin(R)), ((Y+(car_length/2)+2) + ( 4*sin(R) +  2*cos(R))) );
			glVertex2f((X-car_width) + ( 4*cos(R) - -2*sin(R)), ((Y+(car_length/2)+2) + ( 4*sin(R) + -2*cos(R))) );
			//Right Tire
			glVertex2f((X+car_width) + (-4*cos(R) - -2*sin(R)), ((Y+(car_length/2)+2) + (-4*sin(R) + -2*cos(R))) );
			glVertex2f((X+car_width) + (-4*cos(R) -  2*sin(R)), ((Y+(car_length/2)+2) + (-4*sin(R) +  2*cos(R))) );
			glVertex2f((X+car_width) + ( 4*cos(R) -  2*sin(R)), ((Y+(car_length/2)+2) + ( 4*sin(R) +  2*cos(R))) );
			glVertex2f((X+car_width) + ( 4*cos(R) - -2*sin(R)), ((Y+(car_length/2)+2) + ( 4*sin(R) + -2*cos(R))) );
		glEnd();
		
		//Draw sensors
		glColor3f(0,0,0);
		glBegin(GL_QUADS);
			//Left Sensor
			glVertex2f((X-(car_width/2)) + (-2*cos(R) - -2*sin(R)), ((Y-car_length) + (-2*sin(R) + -2*cos(R))) );
			glVertex2f((X-(car_width/2)) + (-2*cos(R) -  2*sin(R)), ((Y-car_length) + (-2*sin(R) +  2*cos(R))) );
			glVertex2f((X-(car_width/2)) + ( 2*cos(R) -  2*sin(R)), ((Y-car_length) + ( 2*sin(R) +  2*cos(R))) );
			glVertex2f((X-(car_width/2)) + ( 2*cos(R) - -2*sin(R)), ((Y-car_length) + ( 2*sin(R) + -2*cos(R))) );
			//Right Sensor
			glVertex2f((X+(car_width/2)) + (-2*cos(R) - -2*sin(R)), ((Y-car_length) + (-2*sin(R) + -2*cos(R))) );
			glVertex2f((X+(car_width/2)) + (-2*cos(R) -  2*sin(R)), ((Y-car_length) + (-2*sin(R) +  2*cos(R))) );
			glVertex2f((X+(car_width/2)) + ( 2*cos(R) -  2*sin(R)), ((Y-car_length) + ( 2*sin(R) +  2*cos(R))) );
			glVertex2f((X+(car_width/2)) + ( 2*cos(R) - -2*sin(R)), ((Y-car_length) + ( 2*sin(R) + -2*cos(R))) );
		glEnd();
	//}
	glFlush();
}

void Canvas::drawLights()
{
	const int light_radius = 5;
	//for (int i=0; i<manager->getLights().size(); i++)
	//{
		//Light light = manager->getLight(i);
		Light light = Light(50,50);
		int X = light.X;
		int Y = light.Y;
		
		glColor3f(1,1,0);
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f(X,Y);
			// create points around the mouse point
			for(int j=0; j<=360; j++ )
			{
				// using the unit circle
				glVertex2f(X + sin(j)*light_radius, Y + cos(j)*light_radius);
			}
		glEnd();
	//}
	glFlush();
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
   glColor3f (.7,.7,.7);
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

   drawCars();
	drawLights();

}

