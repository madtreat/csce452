
#include "canvas.h"
#include "joint.h"
#include "link.h"
#include "base.h"
#include "brush.h"

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


Canvas::Canvas()
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
void Canvas::circle(int x, int y, int radius)
{
   //glColor3f(0,0,0);
   glBegin(GL_TRIANGLE_FAN);
   glVertex2f(x,y);
   // create points around the mouse point
   for(double i=0; i<=360; ++i )
   {
      // useing the unit circle
      glVertex2f(x+sin(i)*radius, y+cos(i)*radius);
   }
   glEnd();
}

void Canvas::Robot(Joint joint[3], Link L, Brush b)
{
	for(int i = 0; i<3; i++ )
	{
		if(joint[i].type== BASE_JOINT)// there is no movement 
      {
         glColor3f(1,0,0);
         circle(10+((WIDTH-210)/2)-5,HEIGHT-50,6);
         glColor3f(0,0,1);
         circle(10+((WIDTH-210)/2)-5,HEIGHT-50,7);
         // glBegin(GL_POLYGON);
         // glVertex2f (10+((WIDTH-210)/2)-5,HEIGHT-50);

         // glEnd();
      }
	}
}

void Canvas::DrawLinks(Link* link[5])
{
	glColor3f(0,0,0);
	for (int i=0; i<5; i++)
	{
		// I dont know why this isnt working
		std::cout << "x: " << link[i]->joint.X << " y: " << link[i]->joint.Y << std::endl;
		circle(link[i]->joint.X,link[i]->joint.Y,100);
		glFlush ( );
	}
}

void Canvas::display ( void )
{
   glClear ( GL_COLOR_BUFFER_BIT );
   // the canvas sheet

   glColor3f (1,1,1);
   glBegin (GL_POLYGON);
   glVertex2f (WIDTH-(WIDTH-10),HEIGHT-(HEIGHT-10)); 
   glVertex2f (WIDTH-(WIDTH-10),HEIGHT-10);
   glVertex2f (WIDTH-200,HEIGHT-10);
   glVertex2f (WIDTH-200,HEIGHT-(HEIGHT-10));
   glEnd();
   glColor3f(1.0,0.25,0.0);

   glLineWidth(3.0);
   glBegin (GL_LINE_LOOP);
   glVertex2f (WIDTH-(WIDTH-10),HEIGHT-(HEIGHT-10));
   glVertex2f (WIDTH-(WIDTH-10),HEIGHT-10);
   glVertex2f(WIDTH-200,HEIGHT-10);
   glVertex2f(WIDTH-200,HEIGHT-(HEIGHT-10));
   glEnd();

   // this is the line in the bottom for the parasetic joint 
   glLineWidth(6.0);
   glColor3f(0,0,0);
   circle(10+((WIDTH-210)/2)-150,HEIGHT-50,5);
   glBegin (GL_LINES); 
   glVertex2f (10+((WIDTH-210)/2)-150,HEIGHT-50);
   glVertex2f (10+((WIDTH-210)/2)+150,HEIGHT-50);
   glEnd(); 
}

