
#include "manager.h"

#include <iostream>
#include <cmath>

using namespace std;


Manager::Manager()
{
}

Manager::~Manager()
{
}

// Called from window
void Manager::timeStep()
{
	
}

// Find a path from robot to destination, avoiding obstacles
void Manager::generatePath()
{
   // Step 1: decompose free space into cells
   Cells cells = decompose();


   // Step 2: generate connectivity graph


   // Step 3: find a path from robot to destination


   // Complete!
}

Cells Manager::decompose()
{
   vector<int> edgeCoords;
   // decompose the area into cells based on the box locations
   for (int i = 0; i < NUM_BOXES; i++)
   {
      edgeCoords.push_back(boxes[i].pos.X - (boxes[i].size/2) );
   }

   Cells cells;

   return cells;
}

// Return index of box that collides
// Return -1 on no collision
int Manager::isCollision(Position pos)
{	
	int X = pos.X;
	int Y = pos.Y;
	for (int i=0; i<NUM_BOXES; i++)
	{
		if ( ( X < boxes[i].pos.X+(boxes[i].size/2) ) &&
			  ( X > boxes[i].pos.X-(boxes[i].size/2) ) &&
			  ( Y < boxes[i].pos.Y+(boxes[i].size/2) ) &&
			  ( Y > boxes[i].pos.Y-(boxes[i].size/2) ) )
			return i;
	}
	
	return -1;
}

void Manager::setBox(int boxNum, Position pos)
{
	boxes[boxNum].pos = pos;
}

void Manager::setBoxSize(int boxNum, int size)
{
	boxes[boxNum].size = size;
}

Box Manager::getBox(int boxNum)
{
	return boxes[boxNum];
}
