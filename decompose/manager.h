
#ifndef MANAGER_H_
#define MANAGER_H_

#include "consts.h"


class Manager
{

public:
   Manager();
   ~Manager();
   
   Node* getNode(const Cell& cell) const;

	void  timeStep();
   void  generatePath();
   void  decompose();
   void  connectCells();
   Path  dijkstra(Graph g);
	int   isCollision(Position pos);

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
	
private:
   Boxes       boxes;	// typedef'd to std::vector<Box>
	Robot 		robot;
	Destination dest;
   Cells       cells;	// typedef'd to std::vector<Cell>
   Graph       graph;   // typedef'd to std::vector<Node*>
   Path        path;    // typedef'd to std::vector<Cell>
};

#endif
