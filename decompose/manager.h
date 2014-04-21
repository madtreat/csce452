
#ifndef MANAGER_H_
#define MANAGER_H_

#include "consts.h"

class Manager
{

public:
   Manager();
   ~Manager();
   
	void timeStep();
   void generatePath();
   Cells decompose();

	
   // DEPRECATED: use setBox(int) instead
	void setBox1 (Position pos)	{boxes[0] = pos;}
	void setBox2 (Position pos) 	{boxes[1] = pos;}
	void setBox3 (Position pos)	{boxes[2] = pos;}
   void setBox  (int i, Position pos) {boxes[i] = pos;}
	void setRobot(Position pos)	{robot= pos;}
	void setDest (Position pos)	{dest = pos;}
	
   // DEPRECATED: use getBox(int) instead
	Box 			getBox1()	const {return boxes[0];}
	Box 			getBox2()	const {return boxes[1];}
	Box 			getBox3()	const {return boxes[2];}
   Box         getBox(int i) const {return boxes[i];}
	Robot 		getRobot()	const {return robot;}
	Destination getDest()	const {return dest;}
	
private:
   Boxes       boxes;
	Robot 		robot;
	Destination dest;
};

#endif

