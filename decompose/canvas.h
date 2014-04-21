
#ifndef CANVAS_H_
#define CANVAS_H_

#include "manager.h"

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

private:
   Manager* manager;
	
};

#endif

