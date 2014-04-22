
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
   void decompose();
   Graph connectCells() const;
   Path  dijkstra(Graph g);
	int isCollision(Position pos);
	
	void clearCells()	{cells.clear();}

	// SET Functions
	void setBox(int boxNum, Position pos);
	void setBoxSize(int boxNum, int size);
	void setRobot(Position pos)	{robot= pos;}
	void setDest(Position pos)	{dest = pos;}

	// GET Functions
   Box         getBox(int boxNum);
	Robot 		getRobot()	const {return robot;}
	Destination getDest()	const {return dest;}
   Cell        getCell(int row, int col); 
	int			getCellRows()	const	{return cells.size();}
	int			getCellCols()	const	{return cells[0].size();}
	Position		getPathNode(int nodeNum);
	int			getPathNodesLength();
	
private:
   Boxes       boxes;	//typedef'd to std::vector<Box>
	Robot 		robot;
	Destination dest;
   Cells       cells;	//typedef'd to std::vector<Cell>
};

#endif
