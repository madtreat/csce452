
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

void Canvas::drawBox(int boxNum)
{
   Box box; 
   int X = box.X;
   int Y = box.Y;

   if(boxNum == 1)
   {
      glColor3f(1,.5,0);
      glBegin(GL_QUADS);
         glVertex2f(X-(BOX1_SIZE/2),Y-(BOX1_SIZE/2));
         glVertex2f(X+(BOX1_SIZE/2),Y-(BOX1_SIZE/2));
         glVertex2f(X+(BOX1_SIZE/2),Y+(BOX1_SIZE/2));
         glVertex2f(X-(BOX1_SIZE/2),Y+(BOX1_SIZE/2));
      glEnd();
   }
   else if(boxNum == 2)
   {
      glColor3f(0,1,0);
            glBegin(GL_QUADS);
         glVertex2f(X-(BOX2_SIZE/2),Y-(BOX2_SIZE/2));
         glVertex2f(X+(BOX2_SIZE/2),Y-(BOX2_SIZE/2));
         glVertex2f(X+(BOX2_SIZE/2),Y+(BOX2_SIZE/2));
         glVertex2f(X-(BOX2_SIZE/2),Y+(BOX2_SIZE/2));
      glEnd();  
   }
   else if(boxNum == 3)
   {
      glColor3f(0,0,1);
         glBegin(GL_QUADS);
         glVertex2f(X-(BOX3_SIZE/2),Y-(BOX3_SIZE/2));
         glVertex2f(X+(BOX3_SIZE/2),Y-(BOX3_SIZE/2));
         glVertex2f(X+(BOX3_SIZE/2),Y+(BOX3_SIZE/2));
         glVertex2f(X-(BOX3_SIZE/2),Y+(BOX3_SIZE/2));
      glEnd(); 
 
   }

   glFlush();
}

void Canvas::drawRobot()
{
   Robot robot;
   
   int X = robot.X; 
   int Y = robot.Y;

   glColor3f(1,1,0);
   glBegin(GL_TRIANGLE_FAN);
      glVertex2f(X,Y);

      for(int i=0; i<=360; i++)
      {
         glVertex2f(X +sin(i)*ROBOT_RADIUS, Y + cos(i)*ROBOT_RADIUS);
      }
   glEnd();

   glFlush(); 

}

void Canvas::drawDest()
{
   Destination Dest;
   
   int X = Dest.X; 
   int Y = Dest.Y; 

   glColor3f(1,0,0);
   glBegin(GL_TRIANGLE_FAN);
      glVertex2f(X,Y);

      for(int i=0; i<=360; i++)
      {
         glVertex2f(X +sin(i)*DEST_RADIUS, Y + cos(i)*DEST_RADIUS);
      }
   glEnd();
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

//drawBox(1);
//drawBox(2);
//drawBox(3);
//drawRobot();
//drawDest();
}

