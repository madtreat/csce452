
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
#include <vector>

using namespace std;

const double PI = 3.1415926;

   Canvas::Canvas(RobotArm* _arm)
: robot(_arm),
painting(false)
{
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

// the paint brush draws circles on the canvas
// radius is the paint's radius
void Canvas::drawCircle(int x, int y, int radius)
{
   //glColor3f(0, 0, 0);
   //glBegin(GL_POLYGON);//TRIANGLE_FAN);
   glBegin(GL_TRIANGLE_FAN);
   glVertex2f(x,y);
   // create points around the mouse point
   for(int i = 0; i <= 360; i ++ )
   {
      // using the unit circle
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
   /*
      cout << robot->getLink(1)->joint.X << " " << robot->getLink(1)->joint.Y << endl;
      cout << robot->getLink(2)->joint.X << " " << robot->getLink(2)->joint.Y << endl;
      cout << robot->getLink(3)->joint.X << " " << robot->getLink(3)->joint.Y << endl;
      cout << robot->getLink(4)->joint.X << " " << robot->getLink(4)->joint.Y << endl;
   // */

   // draw the link
   glColor3f(r,g,b);
   //glLineWidth(5.0);
   //glBegin(GL_POLYGON);
   glBegin(GL_LINES);
   glVertex2f(x, y);
   glVertex2f(x1, y1);
   /*
      glVertex2f(x-5,y);
      glVertex2f(x+5,y);
      glVertex2f(x1+5,y1);
      glVertex2f(x1-5,y1);
   // */
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
   drawCircle ( ((WIDTH)/2)-150, HEIGHT-50, 5);
   glBegin (GL_LINES); 
   glVertex2f ( ((WIDTH)/2)-150, HEIGHT-50);
   glVertex2f ( ((WIDTH)/2)+150, HEIGHT-50);
   glEnd();

   // draw link 1 and joint
   drawLink(1, 0, 0, 1);
   drawJoint(1, 0, 0, 1);

   // draw link 2 and joint
   drawLink(2, 1, 0, 0);
   drawJoint(2, 1, 0, 0);

   // draw link 3 and joint
   drawLink(3, 0, 1, 0);
   drawJoint(3, 0, 1, 0);

   // draw the brush (link 4)
   drawJoint(4, 1, 1, 0);
}

void Canvas::paintCurrentLoc()
{

   Brush* b = static_cast<Brush*>(robot->getLink(RobotArm::LENGTH-1));
   glColor3f(1,0,0);
   //  drawCircle(b->joint.X, b->joint.Y, 5);
   paintspots.push_back(PaintSpots(b->joint.X,b->joint.Y));
}

void Canvas::drawPaint()
{
   for(int i= 0; i<paintspots.size(); i++ )
   {
      glColor3f(0,0,0);
      drawCircle(paintspots.at(i).X, paintspots.at(i).Y, 5);
   }

}
void Canvas::display ( void )
{
   glClear ( GL_COLOR_BUFFER_BIT );

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
        drawPaint();

}

