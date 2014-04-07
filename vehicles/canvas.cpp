
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

//TODO: Possible: change wheels and sensors to scale with car size
//TODO: update wheel positions
void Canvas::drawCars()
{
	for (int i=0; i<manager->getCars().size(); i++)
	{
		Car car = manager->getCar(i);
		//Car car = Car(Position(100,100),true);
		int X = car.getX();
		int Y = car.getY();
		double R = car.getR_rad();
		Position s1 = car.getSensorPos(1);
		Position s2 = car.getSensorPos(2);
		
		// Change color based on if car is inverted
		if (car.getDirect())
		{
			glColor3f(1,0,0);		// Red
		}
		else
		{
			glColor3f(0,0,1);		// Blue
		}
		
		// Draw car body
		glBegin(GL_QUADS);
			glVertex2f(X + (-CAR_LENGTH*cos(R) - -CAR_WIDTH*sin(R)), Y + (-CAR_LENGTH*sin(R) + -CAR_WIDTH*cos(R)) );
			glVertex2f(X + (-CAR_LENGTH*cos(R) -  CAR_WIDTH*sin(R)), Y + (-CAR_LENGTH*sin(R) +  CAR_WIDTH*cos(R)) );
			glVertex2f(X + ( CAR_LENGTH*cos(R) -  CAR_WIDTH*sin(R)), Y + ( CAR_LENGTH*sin(R) +  CAR_WIDTH*cos(R)) );
			glVertex2f(X + ( CAR_LENGTH*cos(R) - -CAR_WIDTH*sin(R)), Y + ( CAR_LENGTH*sin(R) + -CAR_WIDTH*cos(R)) );
		glEnd();
		
		/*// Draw wheels	
		glColor3f(0,0,0);
		glBegin(GL_QUADS);
			// Left Tire
			glVertex2f((X-CAR_WIDTH) + (-4*cos(R) - -2*sin(R)), (Y+(CAR_LENGTH/2)+2) + (-4*sin(R) + -2*cos(R)) );
			glVertex2f((X-CAR_WIDTH) + (-4*cos(R) -  2*sin(R)), (Y+(CAR_LENGTH/2)+2) + (-4*sin(R) +  2*cos(R)) );
			glVertex2f((X-CAR_WIDTH) + ( 4*cos(R) -  2*sin(R)), (Y+(CAR_LENGTH/2)+2) + ( 4*sin(R) +  2*cos(R)) );
			glVertex2f((X-CAR_WIDTH) + ( 4*cos(R) - -2*sin(R)), (Y+(CAR_LENGTH/2)+2) + ( 4*sin(R) + -2*cos(R)) );
			// Right Tire
			glVertex2f((X+CAR_WIDTH) + (-4*cos(R) - -2*sin(R)), (Y+(CAR_LENGTH/2)+2) + (-4*sin(R) + -2*cos(R)) );
			glVertex2f((X+CAR_WIDTH) + (-4*cos(R) -  2*sin(R)), (Y+(CAR_LENGTH/2)+2) + (-4*sin(R) +  2*cos(R)) );
			glVertex2f((X+CAR_WIDTH) + ( 4*cos(R) -  2*sin(R)), (Y+(CAR_LENGTH/2)+2) + ( 4*sin(R) +  2*cos(R)) );
			glVertex2f((X+CAR_WIDTH) + ( 4*cos(R) - -2*sin(R)), (Y+(CAR_LENGTH/2)+2) + ( 4*sin(R) + -2*cos(R)) );
		glEnd();
		*/
		// Draw sensors
		glColor3f(0,0,1);
		glBegin(GL_QUADS);
			// Left Sensor
			glVertex2f(s1.X + (-2*cos(R) - -2*sin(R)), s1.Y + (-2*sin(R) + -2*cos(R)) );
			glVertex2f(s1.X + (-2*cos(R) -  2*sin(R)), s1.Y + (-2*sin(R) +  2*cos(R)) );
			glVertex2f(s1.X + ( 2*cos(R) -  2*sin(R)), s1.Y + ( 2*sin(R) +  2*cos(R)) );
			glVertex2f(s1.X + ( 2*cos(R) - -2*sin(R)), s1.Y + ( 2*sin(R) + -2*cos(R)) );
			// Right Sensor
			glVertex2f(s2.X + (-2*cos(R) - -2*sin(R)), s2.Y + (-2*sin(R) + -2*cos(R)) );
			glVertex2f(s2.X + (-2*cos(R) -  2*sin(R)), s2.Y + (-2*sin(R) +  2*cos(R)) );
			glVertex2f(s2.X + ( 2*cos(R) -  2*sin(R)), s2.Y + ( 2*sin(R) +  2*cos(R)) );
			glVertex2f(s2.X + ( 2*cos(R) - -2*sin(R)), s2.Y + ( 2*sin(R) + -2*cos(R)) );
		glEnd();
	}
	glFlush();
}

void Canvas::drawLights()
{
	for (int i=0; i<manager->getLights().size(); i++)
	{
		Light light = manager->getLight(i);
		//Light light = Light(50,50);
		int X = light.X;
		int Y = light.Y;
		
		glColor3f(1,1,0);
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f(X,Y);
			// create points around the mouse point
			for(int j=0; j<=360; j++)
			{
				// using the unit circle
				glVertex2f(X + sin(j)*LIGHT_RADIUS, Y + cos(j)*LIGHT_RADIUS);
			}
		glEnd();
	}
	glFlush();
}

void Canvas::display ( void )
{
   glClear ( GL_COLOR_BUFFER_BIT );

   // set greyish canvas
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

