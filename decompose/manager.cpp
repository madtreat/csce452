
#include "manager.h"

#include <iostream>
#include <algorithm>
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
   vector<int> xcoords;
   vector<int> ycoords;

   xcoords.push_back(0);
   ycoords.push_back(0);
   // decompose the area into cells based on the box locations
   for (int i = 0; i < NUM_BOXES; i++)
   {
      xcoords.push_back( boxes[i].pos.X - (boxes[i].size/2) );
      xcoords.push_back( boxes[i].pos.X + (boxes[i].size/2) );
      ycoords.push_back( boxes[i].pos.Y - (boxes[i].size/2) );
      ycoords.push_back( boxes[i].pos.Y + (boxes[i].size/2) );
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
         int nodeX = ( xcoords[i] - xcoords[i-1] ) / 2;
         int nodeY = ( ycoords[i] - ycoords[i-1] ) / 2;
         Position nodePos(nodeX, nodeY);
         
         // if this node position is within a box, skip to the next vertical cell
         if (isCollision(nodePos) != -1)
            break;

         Cell cell;
         cell.TL = Position(xcoords[i-1], ycoords[i-1]);
         cell.TR = Position(xcoords[i],   ycoords[i-1]);
         cell.BL = Position(xcoords[i-1], ycoords[i]);
         cell.BR = Position(xcoords[i],   ycoords[i]);
         
         cell.node = (Node) nodePos;
         cells.push_back(cell);
         cout << "Cell made with node = (" << nodeX << ", " << nodeY << ")" << endl;
      }
   }

   return cells;
}

