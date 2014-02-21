
#include "canvas.h"

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
   std::cout << "END Canvas constructor" << std::endl;
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

void Canvas::circle(int x,int y)// circle for the paint
{
   int radius = 5; //radius is the size  
   // glColor3f(0,0,0);
   glBegin(GL_TRIANGLE_FAN);
   glVertex2f(x,y);
   for(double i=0; i<=360; ++i ) // a for loop that creates points around the mouse point 
   {
      glVertex2f(x+sin(i)*radius, y+cos(i)*radius); // using the unit circle 
   }
   glEnd(); 

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
   glBegin (GL_LINE_LOOP);
   glVertex2f (WIDTH-(WIDTH-10),HEIGHT-(HEIGHT-10));
   glVertex2f (WIDTH-(WIDTH-10),HEIGHT-10);
   glVertex2f(WIDTH-200,HEIGHT-10);
   glVertex2f(WIDTH-200,HEIGHT-(HEIGHT-10));
   glEnd();

   // this is the line in the bottom 

   glColor3f(0,0,0);
   circle(10+((WIDTH-210)/2)-150,HEIGHT-50);
   glBegin (GL_LINES); 
   glVertex2f (10+((WIDTH-210)/2)-150,HEIGHT-50);
   glVertex2f (10+((WIDTH-210)/2)+150,HEIGHT-50);
   glEnd(); 
}

