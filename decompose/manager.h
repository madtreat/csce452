
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
   Graph connectCells(Cells cells) const;
   Path  dijkstra(Graph g);
	int isCollision(Position pos);

	// SET Functions
	void setBox(int boxNum, Position pos);
	void setBoxSize(int boxNum, int size);
	void setRobot(Position pos)	{robot= pos;}
	void setDest(Position pos)	{dest = pos;}

	// GET Functions
   Box         getBox(int boxNum);
	Robot 		getRobot()	const {return robot;}
	Destination getDest()	const {return dest;}
   Cell        getCell(int cellNum); 
	int			getCellsLength()	const	{return cells.size();}
	
private:
   Boxes       boxes;	//typedef'd to std::vector<Box>
	Robot 		robot;
	Destination dest;
   Cells       cells;	//typedef'd to std::vector<Cell>
};

#endif
