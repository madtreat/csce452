
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

private:
   Manager* manager;
	
};

#endif

