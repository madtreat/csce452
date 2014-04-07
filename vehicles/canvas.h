
#ifndef CANVAS_H_
#define CANVAS_H_

#include "manager.h"
#include <vector>

class RobotArm;

/*
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
//*/

class Canvas
{
public:

   Canvas(Manager* _man);
   ~Canvas();

   void init();
	void display();
	void drawCars();
	void drawLights();
	
	/*
   void setPainting(bool enabled) {painting = enabled;}
   void setBrushSize(int newSize) {brushSize = newSize;}

   void drawCircle(int x, int y, int radius);
   void drawLink  (int linkNum, double r, double g, double b);
   void drawJoint (int linkNum, double r, double g, double b);
   void drawRobot ();
   void paintCurrentLoc();
   
   void drawPaint();
	//*/

private:
   Manager* manager;
   //bool painting;
   //int brushSize;
   //std::vector<PaintSpot> paintspots;
};

#endif

