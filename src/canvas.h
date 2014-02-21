
#ifndef CANVAS_H_
#define CANVAS_H_

#include "joint.h"
#include "link.h"
#include "base.h"
#include "brush.h"
class Canvas
{
public:
   static const int WIDTH  = 640;
   static const int HEIGHT = 480;
   
   Canvas();
   ~Canvas();

   void init();

   static void circle(int x, int y, int radius);
   static void display();
   static void Robot(Joint joint[],Link L, Brush b);
private:
   
};

#endif

