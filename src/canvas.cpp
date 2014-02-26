
#include "canvas.h"
#include "joint.h"
#include "link.h"
#include "base.h"
#include "brush.h"
#include "robotarm.h"

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

using namespace std;

const int PI = 3.1415926;

Canvas::Canvas(RobotArm* _arm)
//: robot(_arm)
{
   robot = _arm;
   int argc = 1;
   char* argv[argc];
   argv[0] = "paintbot";
   glutInit(&argc, argv);
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

// the paint brush draws drawCircles on the canvas
// radius is the paint's radius
void Canvas::drawCircle(int x, int y, int radius)
{
   //glColor3f(0, 0, 0);
   //glBegin(GL_POLYGON);//TRIANGLE_FAN);
   glBegin(GL_TRIANGLE_FAN);
   glVertex2f(x,y);
   // create points around the mouse point
   //for(double i=0; i<=360; ++i )
   for(double i = 0; i <= 2*PI; i += (double) PI/ (double) 36 )
   {
      // useing the unit drawCircle
      glVertex2f(x+sin(i)*radius, y+cos(i)*radius);
   }
   glEnd();
}

void Canvas::drawLink(int linkNum, double r, double g, double b)
{
   // get the coordinates
   int x  = robot->getLink(linkNum)->joint.X;
   int y  = robot->getLink(linkNum)->joint.Y;
   int x1 = robot->getLink(linkNum+1)->joint.X;
   int y1 = robot->getLink(linkNum+1)->joint.Y;
   //cout << x << " " << y << " " << x1 << " " << y1 << endl;

   // draw the link
   glColor3f(r,g,b);
   glBegin(GL_POLYGON);
   glVertex2f(x-5,y);
   glVertex2f(x+5,y);
   glVertex2f(x1+5,y1);
   glVertex2f(x1-5,y1);
   glEnd();
}

void Canvas::drawJoint(int linkNum, double r, double g, double b)
{
   int x = robot->getLink(linkNum)->joint.X;
   int y = robot->getLink(linkNum)->joint.Y;
   glColor3f(r, g, b);
   drawCircle(x, y, 8);
}

void Canvas::drawRobot()
{
   // this is the line in the bottom for the base and prismatic joint 
   glLineWidth(6.0);
   glColor3f(0,0,0); // black prismatic axis/joint 1 - the sliding rail
   drawCircle(10+((WIDTH-210)/2)-150,HEIGHT-50,5);
   glBegin (GL_LINES); 
   glVertex2f (10+((WIDTH-210)/2)-150,HEIGHT-50);
   glVertex2f (10+((WIDTH-210)/2)+150,HEIGHT-50);
   glEnd();

   // draw link 1 and joint
   drawLink(1, 0.5, 0, 0);
   drawJoint(1, 0, 0, 1);
   //glColor3f(0,0,1);
   //drawCircle(x,y,8);
   
   // draw link 2 and joint
   drawLink(2, 0.4, 0.2, 0.2);
   drawJoint(2, 0, 1, 1);
   //glColor3f(0,1,1);
   //drawCircle(x1,y_1,6);

   // draw link 3 and joint
   drawLink(3, 0.5, 0.4, 0.3);
   drawJoint(3, 0, 1, 0);
   //glColor3f(0,1,0);
   //drawCircle(x2,y2,6);
   
   // draw the brush (link 4)
   drawJoint(4, 1, 0, 0);
   //glColor3f(1,0,0);
   //drawCircle(x3,y3,10);

   
   /*
   glColor3f(.5,0,0);
   glBegin(GL_POLYGON);
   glVertex2f(x-5,y);
   glVertex2f(x+5,y);
   glVertex2f(x1+5,y_1);
   glVertex2f(x1-5,y_1);
   glEnd();

   // draw link 2
   glColor3f(.4,.2,.2);
   glBegin(GL_POLYGON);
   glVertex2f(x1-5,y_1);
   glVertex2f(x1+5,y_1);
   glVertex2f(x2+5,y2);
   glVertex2f(x2-5,y2);
   glEnd();

   // draw link 3
   glColor3f(.5,.4,.3);
   glBegin(GL_POLYGON);
   glVertex2f(x2-5,y2);
   glVertex2f(x2+5,y2);
   glVertex2f(x3+5,y3);
   glVertex2f(x3-5,y3);
   glEnd();
   // */

   // joints 


/*
	for(int i = 0; i < RobotArm::LENGTH; i++ )
	{
      Joint joint = robot->getLink(i)->joint;
		if(joint.type== BASE_JOINT)// there is no movement 
      {
         glColor3f(1,0,0);
         drawCircle(10+((WIDTH-210)/2)-5,HEIGHT-50,6);
         glColor3f(0,0,1);
         drawCircle(10+((WIDTH-210)/2)-5,HEIGHT-50,7);
         // glBegin(GL_POLYGON);
         // glVertex2f (10+((WIDTH-210)/2)-5,HEIGHT-50);

         // glEnd();
      }
	}
   // */
}

void Canvas::paintCurrentLoc()
{
   Brush* b = static_cast<Brush*>(robot->getLink(RobotArm::LENGTH-1));
   drawCircle(b->joint.X, b->joint.Y, 5);
}

void Canvas::display ( void )
{
   glClear ( GL_COLOR_BUFFER_BIT );
   // the canvas sheet

   // set white canvas
   glColor3f (1,1,1);
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

   drawRobot();

   // if painting is turned on, paint a drawCircle wherever the brush is
   if (painting)
      paintCurrentLoc();
}

