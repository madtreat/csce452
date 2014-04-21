
#ifndef CANVAS_H_
#define CANVAS_H_

#include "manager.h"
#include <vector>

class Canvas
{
public:

   Canvas(Manager* _man);
   ~Canvas();

   void init();
	void display();
   void drawBox(int boxNum);
   void drawRobot();
   void drawDest(); 
   void drawCellNode(int cellNum);
   
private:
   Manager* manager;
	
};

#endif

