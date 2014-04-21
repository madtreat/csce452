
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

	
	void setBox1 (Position pos)	{box1 = pos;}
	void setBox2 (Position pos) 	{box2 = pos;}
	void setBox3 (Position pos)	{box3 = pos;}
	void setRobot(Position pos)	{robot= pos;}
	void setDest (Position pos)	{dest = pos;}
	
	Box 			getBox1()	const {return box1; }
	Box 			getBox2()	const {return box2; }
	Box 			getBox3()	const {return box3; }
	Robot 		getRobot()	const {return robot;}
	Destination getDest()	const {return dest; }
	
private:
	Box 			box1;
	Box 			box2;
	Box 			box3;
	Robot 		robot;
	Destination dest;
};

#endif

