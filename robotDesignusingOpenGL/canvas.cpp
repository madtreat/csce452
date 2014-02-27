#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
#define PI 3.14159265
float angL3;
int x1 = 505;
int x2 = 505;
int x3= 505;
int x = 505; 
int y =550;
int y_1=400;
int y2 =300;
int y3= 225;
float angL2;
int translatefactor; 
void display();
void keyboard();
void circle(int x,int y, int rad)// circle for the paint
{
   //int radius = 5; //radius is the size  
   // glColor3f(0,0,0);
   glBegin(GL_TRIANGLE_FAN);
   glVertex2f(x,y);
   for(double i=0; i<=360; ++i ) // a for loop that creates points around the mouse point 
   {
      glVertex2f(x+sin(i)*rad, y+cos(i)*rad); // using the unit circle 
   }
   glEnd(); 

}
void display ( void )
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
   glVertex2f (WINDOW_WIDTH-(WINDOW_WIDTH-5),WINDOW_HEIGHT-(WINDOW_HEIGHT-5)); 
   glVertex2f (WINDOW_WIDTH-(WINDOW_WIDTH-5),WINDOW_HEIGHT-5);
   glVertex2f (WINDOW_WIDTH-5,WINDOW_HEIGHT-5);
   glVertex2f (WINDOW_WIDTH-10,WINDOW_HEIGHT-(WINDOW_HEIGHT-5));
   glEnd();
   glColor3f(1.0,0.25,0.0);
   glBegin (GL_LINE_LOOP);
   glVertex2f (WINDOW_WIDTH-(WINDOW_WIDTH-5),WINDOW_HEIGHT-(WINDOW_HEIGHT-5));
   glVertex2f (WINDOW_WIDTH-(WINDOW_WIDTH-5),WINDOW_HEIGHT-5);
   glVertex2f(WINDOW_WIDTH-5,WINDOW_HEIGHT-5);
   glVertex2f(WINDOW_WIDTH-5,WINDOW_HEIGHT-(WINDOW_HEIGHT-5));
   glEnd();

   // this is the line in the bottom 

   glColor3f(0,0,0);
   circle(5+((WINDOW_WIDTH)/2)-150,WINDOW_HEIGHT-50,5);
   glBegin (GL_LINES); 
   glVertex2f (5+((WINDOW_WIDTH)/2)-150,WINDOW_HEIGHT-50);
   glVertex2f (5+((WINDOW_WIDTH)/2)+150,WINDOW_HEIGHT-50);
   glEnd(); 

   //move from bottom up 
   /*
      if(x != 505) // translate
      {
      if(x<505)
      {translatefactor =505-x;}
      else 
      {translatefactor =x-505;}
   // check if link 2 rotated 
   if(y2 != 300 ) //rotate // need 
   {

   float slope = (y2-y_1)/(x2-x1);
   angL2 = atan(slope)*(180 / PI); // in radians so multiply by* 180 / PI;
   // need to check if link 3 was rotated 
   if(x3!=x2)//rotate link3
   {
   float slope3 = (y3-y2)/(x3-x2);
   angL3 = atan(slope3)*(180/PI);
   }
   else //no rotation 
   { angL3 = 0; 
   }

   }
   else 
   {
   angL2 = 0;
   if(x3!=x2)//rotate link3
   {
   float slope3 = (y3-y2)/(x3-x2);
   angL3 = atan(slope3)*(180/PI);
   }
   else //no rotation 
   { 
   angL3 = 0; 
   }
   }

   }
   else 
   {
   if(x2 != 505) //rotate
   {

   float slope = (y2-y_1)/(x2-x1);
   angL2 = atan(slope)*(180 / PI); // in radians so multiply by* 180 / PI;
   // need to check if link 3 was rotated 
   if(x3!=x2)//rotate link3
   {
   float slope3 = (y3-y2)/(x3-x2);
   angL3 = atan(slope3)*(180/PI);
   }
   else //no rotation 
   { angL3 = 0; 
   }

   }
   else 
   {
   angL2 = 0;
   if(x3!=x2)//rotate link3
   {
   float slope3 = (y3-y2)/(x3-x2);
   angL3 = atan(slope3)*(180/PI);
   }
   else //no rotation 
   { 
   angL3 = 0; 
   }
   }
   }




   //link 1 
   glLoadIdentity();
   glPushMatrix();
   glMatrixMode(GL_MODELVIEW);
   glTranslatef(x,y,0);
   glTranslatef(translatefactor,0,0);
   glColor3f(0,1,0);
   glBegin(GL_POLYGON);
   glVertex2f(0,0);
   glVertex2f(0,150);
   glVertex2f(10,0);
   glVertex2f(10,-150);

   glEnd();
   glPopMatrix();

   //link 2
   glLoadIdentity();
   glPushMatrix();
   glMatrixMode(GL_MODELVIEW);
   glTranslatef(x1,y_1,0);
   glTranslatef(translatefactor,0,0);
   glRotatef(angL2,0,0,1);
   glColor3f(0,1,0);
   glBegin(GL_LINES);
   glVertex2f(0,0);
   glVertex2f(0,-100);
   glEnd();
   glPopMatrix();

   //link 3
   glLoadIdentity();
   glPushMatrix();
   glMatrixMode(GL_MODELVIEW);
   glTranslatef(x2,y2,0);
   glTranslatef(translatefactor,0,0);
   glRotatef(angL3,0,0,1);
   glColor3f(0,1,0);
   glBegin(GL_LINES);
   glVertex2f(0,0);
   glVertex2f(0,-75);
   glEnd();
   glPopMatrix();
   */


      // the robot is basically rectangles attached by circles the variables 
      //x,x1,x2,x3,y,y_1,y2,y3 are the coordinates of joints which can be changed since assigned globally 
      // we can have a function that will take in the new coordinates and assign them to each variable based on the botton this can be seen
      // by clicking c in this program 
      glColor3f(.5,0,0);
   glBegin(GL_POLYGON);
   glVertex2f(x-5,y);
   glVertex2f(x+5,y);
   glVertex2f(x1+5,y_1);
   glVertex2f(x1-5,y_1);
   glEnd();

   glColor3f(.4,.2,.2);
   glBegin(GL_POLYGON);
   glVertex2f(x1-5,y_1);
   glVertex2f(x1+5,y_1);
   glVertex2f(x2+5,y2);
   glVertex2f(x2-5,y2);
   glEnd();

   glColor3f(.5,.4,.3);
   glBegin(GL_POLYGON);
   glVertex2f(x2-5,y2);
   glVertex2f(x2+5,y2);
   glVertex2f(x3+5,y3);
   glVertex2f(x3-5,y3);
   glEnd();
   // joints 
   glColor3f(0,0,1);
   circle(x,y,8);
   glColor3f(0,1,1);
   circle(x1,y_1,6);
   glColor3f(0,1,0);
   circle(x2,y2,6);
   glColor3f(1,0,0);
   circle(x3,y3,10);

   glFlush();
   glutSwapBuffers();

}

void keyboard ( unsigned char key, int xl, int yl )
{
   switch ( key )
   {
      case 'c':
         printf("value of x= %i",x);
         //translates to right
         x = x+10;  
         x1 = x1 + 10;
         x2 = x2+10;
         x3= x3+10;


         break;
      case GLUT_KEY_LEFT:
         x1 = x1 - 10;
         x2 = x2-10;
         x3= x3-10;
         x = x-10; 
         break; 
      case GLUT_KEY_UP:
         x1 = x1;
         x2 = x2-10;
         x3= x3-10;
         x = x; 
         y2 =y2-10;
         y3= y3;
         break;
      case GLUT_KEY_DOWN:

         break;
   }
   glutPostRedisplay ( );
}

void init ( void )
{
   glClearColor (0.752941,  0.752941, 0.752941, 0.0);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, WINDOW_WIDTH-1, WINDOW_HEIGHT-1, 0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}

void  mouse ( int button,int state, int xl, int yl )
{
   switch(button)
   {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
         {


         }
         break;
   }
   glutPostRedisplay ( );
}

int main ( int argc, char *argv[] )
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (WINDOW_WIDTH, WINDOW_HEIGHT); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("PaintBot");
   init ();
   glutDisplayFunc(display);
   glutMouseFunc ( mouse );
   glutKeyboardFunc ( keyboard );
   glutMainLoop ( );
   return 0;
}
