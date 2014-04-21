
#include "manager.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;


Manager::Manager()
{
	for (int i=0; i<NUM_BOXES; i++)
	{
		boxes.push_back(Box());
	}
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
   vector<int> xcoords;
   vector<int> ycoords;

   xcoords.push_back(0);
   ycoords.push_back(0);
   // decompose the area into cells based on the box locations
   for (int i = 0; i < NUM_BOXES; i++)
   {
      cout << "box[" << i << "] = (" << boxes[i].pos.X << "," << boxes[i].pos.Y << ")" << endl;
      xcoords.push_back( boxes[i].pos.X - boxes[i].size );
      xcoords.push_back( boxes[i].pos.X + boxes[i].size );
      ycoords.push_back( boxes[i].pos.Y - boxes[i].size );
      ycoords.push_back( boxes[i].pos.Y + boxes[i].size );
   }
   xcoords.push_back(WIDTH);
   ycoords.push_back(HEIGHT);

   // sort the edge coordinates
   sort(xcoords.begin(), xcoords.end());
   sort(ycoords.begin(), ycoords.end());

   // remove duplicates (if boxes have same edge coordinate)
   xcoords.erase( unique(xcoords.begin(), xcoords.end()), xcoords.end() );
   ycoords.erase( unique(ycoords.begin(), ycoords.end()), ycoords.end() );

   // create cells based on edge coordinates
   Cells cells;

   for (int i = 1; i < xcoords.size(); i++)
   {
      for (int j = 1; j < ycoords.size(); j++)
      {
         int nodeX = xcoords[i-1] + ( xcoords[i] - xcoords[i-1] ) / 2;
         int nodeY = ycoords[i-1] + ( ycoords[j] - ycoords[j-1] ) / 2;
         Position nodePos(nodeX, nodeY);
         
         // if this node position is within a box, skip to the next vertical cell
         if (isCollision(nodePos) != -1)
            break;

         Cell cell;
         cell.TL = Position(xcoords[i-1], ycoords[j-1]);
         cell.TR = Position(xcoords[i],   ycoords[j-1]);
         cell.BL = Position(xcoords[i-1], ycoords[j]);
         cell.BR = Position(xcoords[i],   ycoords[j]);
         
         cell.node = (Node) nodePos;
         cells.push_back(cell);
         cout << "Cell made with node = (" << nodeX << ", " << nodeY << ")" << endl;
      }
   }

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
		if ( ( X < boxes[i].pos.X + (boxes[i].size) ) &&
			  ( X > boxes[i].pos.X - (boxes[i].size) ) &&
			  ( Y < boxes[i].pos.Y + (boxes[i].size) ) &&
			  ( Y > boxes[i].pos.Y - (boxes[i].size) ) )
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

Cell Manager::getCell(int cellNum)
{
   return cells[cellNum];
}
