
#ifndef CANVAS_H_
#define CANVAS_H_

#include "joint.h"
#include "link.h"
#include "base.h"
#include "brush.h"
#include <vector>

class RobotArm;

struct PaintSpot
{
   int X;
   int Y;
   int size; // radius

   PaintSpot(int _x, int _y, int _s) : X(_x), Y(_y), size(_s) {}
   bool operator==(const PaintSpot& other)
   {
      if( X == other.X &&
          Y == other.Y )
         return true; 
      return false; 
   }
};

class Canvas
{
public:
   static const int WIDTH  = 640;
   static const int HEIGHT = 480;

   Canvas(RobotArm* _arm);
   ~Canvas();

   void init();

   void setPainting(bool enabled) {painting = enabled;}
   void setBrushSize(int newSize) {brushSize = newSize;}

   void drawCircle(int x, int y, int radius);
   void drawLink  (int linkNum, double r, double g, double b);
   void drawJoint (int linkNum, double r, double g, double b);
   void drawRobot ();
   void paintCurrentLoc();
   void display();
   void drawPaint();

private:
   RobotArm* robot;
   bool painting;
   int brushSize;
   std::vector<PaintSpot> paintspots;
};

#endif

