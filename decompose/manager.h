
#ifndef MANAGER_H_
#define MANAGER_H_

#include "consts.h"


class Manager
{

public:
   Manager();
   ~Manager();
	
	bool pathDrawn;
   
   Node* getNode(const Cell& cell) const;
   bool  isValidCell(int r, int c) const;
   

	void  timeStep();
   void  generatePath();
   void  decompose();
   void  connectCells();
   int   minDistance();
   void  dijkstra();
	int 	isCollision(Position pos);
	void 	clearCells();

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
   
   Position    findCellIndex(Cell c) const;
	
private:
   Boxes       boxes;	// typedef'd to std::vector<Box>
	Robot 		robot;
	Destination dest;

   Cells       cells;	// typedef'd to std::vector<Cell>
   Nodes       nodes;
   Path        path;    // typedef'd to std::vector<Cell>
	
   Node*       srcNode;
   Node*       destNode;
};

#endif
