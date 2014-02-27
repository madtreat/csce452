
#ifndef CANVAS_H_
#define CANVAS_H_

#include "joint.h"
#include "link.h"
#include "base.h"
#include "brush.h"
#include <vector>

class RobotArm;
struct PaintSpots
{
   int X;
   int Y;
   PaintSpots(int _x, int _y) : X(_x), Y(_y) {}
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
      std::vector<PaintSpots> paintspots;
};

#endif

