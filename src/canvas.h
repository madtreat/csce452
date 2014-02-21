
#ifndef CANVAS_H_
#define CANVAS_H_

#include "joint.h"
#include "link.h"
#include "base.h"
#include "brush.h"
class Canvas
{
public:
   static const int WIDTH  = 1200;
   static const int HEIGHT = 600;
   
   Canvas(int argc, char* argv[]);
   ~Canvas();

   void init();

   static void circle(int x, int y, int radius);
   static void display();
   static void keyboard(unsigned char key, int x, int y);
   static void mouseMove(int x, int y);
   static void Robot(Joint joint[],Link L, Brush b);
private:
   
};

#endif

