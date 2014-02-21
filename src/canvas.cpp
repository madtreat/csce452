
#include "canvas.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <gl/glut.h>
#include <gl/gl.h>
#endif

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "joint.h"
#include "link.h"
#include "base.h"
#include "brush.h"

Canvas::Canvas(int argc, char* argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (WIDTH, HEIGHT); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("PaintBot");

   init ();
   glutDisplayFunc (display);
   glutMotionFunc (mouseMove);
   glutKeyboardFunc (keyboard);
   glutMainLoop ( );
}

Canvas::~Canvas()
{
}

void Canvas::init ( void )
{
   glClearColor (0.752941,  0.752941, 0.752941, 0.0);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, WIDTH-1, HEIGHT-1, 0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}

void Canvas::circle(int x,int y,int radius)// circle for the paint
{
    //radius is the size  
   // glColor3f(0,0,0);
   glBegin(GL_TRIANGLE_FAN);
   glVertex2f(x,y);
   for(double i=0; i<=360; ++i ) // a for loop that creates points around the mouse point 
   {
      glVertex2f(x+sin(i)*radius, y+cos(i)*radius); // using the unit circle 
   }
   glEnd(); 

}
void Canvas::Robot(Joint joint[3],Link L, Brush b)
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
void Canvas::display ( void )
{
   char jointtext[8][80]; 

   strcpy(jointtext[0],"Joint 1");

   strcpy(jointtext[1],"Joint 2");

   strcpy(jointtext[2],"Joint 3");

   strcpy(jointtext[3],"PAINT!");

   int numberofjointtexts=3;
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

   glLineWidth(2.0);
   glColor3f(1,1,1);
   glBegin (GL_LINES); 
   glVertex2f (10+((WIDTH-210)/2)-145,HEIGHT-50);
   glVertex2f (10+((WIDTH-210)/2)+145,HEIGHT-50);
   glEnd(); 

   // Button Placement 
   glColor3f(0.662941,0.662941, 0.662941);
   // PAINT button 
   glBegin(GL_POLYGON);
   glVertex2f(1050,375);
   glVertex2f(1050,413);
   glVertex2f(1150,413);
   glVertex2f(1150,375);
   glEnd();

   //joint 1 countrol panel
   //counterclockwise
   glBegin(GL_POLYGON);
   glVertex2f(((WIDTH-200)+20),50);
   glVertex2f(((WIDTH-200)+20),100);
   glVertex2f((((WIDTH-200)+20))+70,100);
   glVertex2f((((WIDTH-200)+20))+70,50);
   glEnd(); 
   //clockwise 

   glBegin(GL_POLYGON);
   glVertex2f(((WIDTH-200)+110),50);
   glVertex2f(((WIDTH-200)+110),100);
   glVertex2f((((WIDTH-200)+110))+70,100);
   glVertex2f((((WIDTH-200)+110))+70,50);
   glEnd(); 

   //joint 2 countrol panel
   //counterclockwise 	
   glBegin(GL_POLYGON);
   glVertex2f(((WIDTH-200)+20),145);
   glVertex2f(((WIDTH-200)+20),195);
   glVertex2f((((WIDTH-200)+20))+70,195);
   glVertex2f((((WIDTH-200)+20))+70,145);
   glEnd(); 
   //clockwise 

   glBegin(GL_POLYGON);
   glVertex2f(((WIDTH-200)+110),145);
   glVertex2f(((WIDTH-200)+110),195);
   glVertex2f((((WIDTH-200)+110))+70,195);
   glVertex2f((((WIDTH-200)+110))+70,145);
   glEnd(); 

   //joint 3 countrol panel
   //counterclockwise 	
   glBegin(GL_POLYGON);
   glVertex2f(((WIDTH-200)+20),240);
   glVertex2f(((WIDTH-200)+20),290);
   glVertex2f((((WIDTH-200)+20))+70,290);
   glVertex2f((((WIDTH-200)+20))+70,240);
   glEnd(); 
   //clockwise 

   glBegin(GL_POLYGON);
   glVertex2f(((WIDTH-200)+110),240);
   glVertex2f(((WIDTH-200)+110),290);
   glVertex2f((((WIDTH-200)+110))+70,290);
   glVertex2f((((WIDTH-200)+110))+70,240);
   glEnd(); 

   //words 
   int Position=30;
   int a = 0; 


   glColor3f(1,0,0);
   for (int i = 0; i< numberofjointtexts; i++)
   {
      int lengthOfjointtext = (int)strlen(jointtext[i]);
      a=0;
      for(int j =0; j< lengthOfjointtext; j++)
      {
         glRasterPos2f(((WIDTH-200)+20)+a , Position);
         glutBitmapCharacter(GLUT_BITMAP_8_BY_13,jointtext[i][j]);
         a=a+8;
      }
      Position = Position +100;
   }


   a=0; 
   for (int h=0; h < 6; h++)
   {
      glRasterPos2f(((WIDTH-200)+80)+a , 400);
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13,jointtext[3][h]);
      a=a+8;
   }
   // 3d effect on button 
   glLineWidth(3.0);
   glColor3f(0.8,0.8, 0.8);
   glBegin(GL_LINES);
   glVertex2f(1050,375);
   glVertex2f(1055,380);
   glEnd();
   glBegin(GL_LINES);
   glVertex2f(1050,413);
   glVertex2f(1055,408);
   glEnd();
   glBegin(GL_LINES);
   glVertex2f(1145,408);
   glVertex2f(1150,413);
   glEnd();

   glBegin(GL_LINES);
   glVertex2f(1150,375);
   glVertex2f(1145,380);
   glEnd();

   glBegin(GL_LINE_LOOP);
   glVertex2f(1055,380);
   glVertex2f(1055,408);
   glVertex2f(1145,408);
   glVertex2f(1145,380);
   glEnd();

   // Robot ARm design
   //first link SteelBlue = color red 0.137255 green 0.419608 blue 0.556863
glColor3f(0.137255,0.419608,0.556863);
glBegin(GL_POLYGON);
glVertex2f(497,558);
glVertex2f(513,558);
glVertex2f(513,408);
glVertex2f(497,408);
glEnd();
//second link
//glLoadIdentity();
//glPushMatrix();
//glTranslatef(505,-300,0);
//glRotatef(45,0,0,1);
glColor3f(0.247255,0.329608,0.366863);
glBegin(GL_POLYGON);
glVertex2f(497,408);
glVertex2f(513,408);
glVertex2f(513,292);
glVertex2f(497,292);
glEnd();
//glPopMatrix();
//third link

glColor3f(0,1,0);
glBegin(GL_POLYGON);
glVertex2f(497,308);
glVertex2f(513,308);
glVertex2f(513,217);
glVertex2f(497,217);
glEnd();

	//first joint 
	glColor3f(0,0,1);
	circle(10+((WIDTH-210)/2),HEIGHT-50,6);
	glColor3f(1,0,0);
	circle(10+((WIDTH-210)/2),HEIGHT-50,2); 
	//second joint  
   	glColor3f(0,0,1);
	circle(10+((WIDTH-210)/2),(HEIGHT-50)-150,6);
	glColor3f(1,0,0);
	circle(10+((WIDTH-210)/2),(HEIGHT-50)-150,2);
	//third joint 
	glColor3f(0,0,1);
	circle(10+((WIDTH-210)/2),(HEIGHT-50)-250,6);
	glColor3f(1,0,0);
	circle(10+((WIDTH-210)/2),(HEIGHT-50)-250,2);
	//paintbrush 	
	glColor3f(0,0,1);
	circle(10+((WIDTH-210)/2),(HEIGHT-50)-325,10);
	glColor3f(1,0,0);
	circle(10+((WIDTH-210)/2),(HEIGHT-50)-325,5);
	
   glFlush ( );
}

void Canvas::keyboard ( unsigned char key, int x, int y )
{
   switch ( key )
   {
   }
   glutPostRedisplay ( );
}

void Canvas::mouseMove ( int x, int y )
{
   glutPostRedisplay ( );
}

