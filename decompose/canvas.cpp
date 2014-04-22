
#include "canvas.h"
#include "consts.h"
#include "manager.h"

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
#include <algorithm>
#include <iostream>

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
   int X = manager->getBox(boxNum).pos.X;
   int Y = manager->getBox(boxNum).pos.Y;
	int boxRadius = manager->getBox(boxNum).size;

   if(boxNum == 0)
   {	
      glColor3f(1,0,0);
   }
   else if(boxNum == 1)
   {
      glColor3f(0,1,0);
   }
   else if(boxNum == 2)
   {
      glColor3f(0,0,1);
   }
	
	glBegin(GL_QUADS);
		glVertex2f(X+(boxRadius),Y-(boxRadius));
		glVertex2f(X-(boxRadius),Y-(boxRadius));
		glVertex2f(X-(boxRadius),Y+(boxRadius));
		glVertex2f(X+(boxRadius),Y+(boxRadius));
	glEnd();

   glFlush();
}

void Canvas::drawRobot()
{
   int X = manager->getRobot().X;
   int Y = manager->getRobot().Y;

   glColor3f(0,0,0);
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
   int X = manager->getDest().X;
   int Y = manager->getDest().Y;

   glColor3f(.8,0,.8);
   glBegin(GL_TRIANGLE_FAN);
      glVertex2f(X,Y);

      for(int i=0; i<=360; i++)
      {
         glVertex2f(X +sin(i)*DEST_RADIUS, Y + cos(i)*DEST_RADIUS);
      }
   glEnd();
	
   glFlush(); 
}

void Canvas::drawCellNode(int row, int col)
{  

   int X = manager->getCell(row, col).pos.X;
   int Y = manager->getCell(row, col).pos.Y;
   glColor3f(1,1,0);
   glBegin(GL_TRIANGLE_FAN);
      glVertex2f(X,Y);

      for(int i=0; i<=360; i++)
      {
         glVertex2f(X +sin(i)*3, Y + cos(i)*3);
      }
   glEnd();
   
   glFlush();   
}

void Canvas::drawCellBorders(int row, int col)
{
	int X1 = manager->getCell(row, col).TR.X;
	int Y1 = manager->getCell(row, col).TR.Y;
	int X2 = manager->getCell(row, col).TL.X;
	int Y2 = manager->getCell(row, col).TL.Y;
	int X3 = manager->getCell(row, col).BL.X;
	int Y3 = manager->getCell(row, col).BL.Y;
	int X4 = manager->getCell(row, col).BR.X;
	int Y4 = manager->getCell(row, col).BR.Y;
	
	glColor3f(0,0,0);
	
	glPushAttrib(GL_ENABLE_BIT); 

	glLineStipple(1, 0x8888);		// Spacing of dotted lines from 0x0000(no line) to 0xFFFF(black line)
	glEnable(GL_LINE_STIPPLE);
	
   glBegin(GL_LINES);
      glVertex2f(X1,Y1);
		glVertex2f(X4,Y4);
		
		glVertex2f(X4,Y4);
		glVertex2f(X3,Y3);
   glEnd();
	
	glPopAttrib();
   
   glFlush();   
	
}

void Canvas::drawCells()
{
	for (int i=0; i<manager->getCellRows(); i++)
	{
		for (int j=0; j<manager->getCellCols(); j++)
		{
			drawCellNode(i,j);
			drawCellBorders(i,j);
		}		
	}
}

void Canvas::drawPath()
{
	glColor3f(1,1,0);
	glBegin(GL_LINES);
	glVertex2f(manager->getRobot().X,manager->getRobot().Y);	
	for (int i=0; i<manager->getPathNodesLength(); i++)
	{
		glVertex2f(manager->getPathNode(i).X,manager->getPathNode(i).Y);	
	}
	glVertex2f(manager->getDest().X,manager->getDest().Y);	
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

	drawBox(0);
	drawBox(1);
	drawBox(2);
	drawRobot();
	drawDest();
	drawCells();
	drawPath();
}

