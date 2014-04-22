
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
   decompose();

   // Step 2: generate connectivity graph
   Graph graph = connectCells();

   // Step 3: find a path from robot to destination
   Path path = dijkstra(graph);

   // Complete!
}

void Manager::decompose()
{
	cells.clear();
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
   for (int i = 1; i < xcoords.size(); i++)
   {
      CRow row;
      for (int j = 1; j < ycoords.size(); j++)
      {
         int nodeX = xcoords[i-1] + ( xcoords[i] - xcoords[i-1] ) / 2;
         int nodeY = ycoords[j-1] + ( ycoords[j] - ycoords[j-1] ) / 2;
         Position pos(nodeX, nodeY);
         
         Cell cell;
         cell.TL = Position(xcoords[i-1], ycoords[j-1]);
         cell.TR = Position(xcoords[i],   ycoords[j-1]);
         cell.BL = Position(xcoords[i-1], ycoords[j]);
         cell.BR = Position(xcoords[i],   ycoords[j]);
         
         cell.pos = pos;

         // if this cell position is within a box, make it an invalid cell (but keep it...
         // useful for graph construction)
         if (isCollision(pos) != -1)
            cell.isValid = false;
         else
            cell.isValid = true;

         row.push_back(cell);
         cout << "Cell made with node = (" << nodeX << ", " << nodeY << ")" << endl;
      }
      cells.push_back(row);
   }
}

// generate a connectivity graph based on the vector of cells given
Graph Manager::connectCells() const
{
   Graph g;

   // loop through rows
   for (int i = 0; i < cells.size(); i++)
   {
      // loop through columns in this row
      for (int j = 0; j < cells[i].size(); j++)
      {
         // Only add an edge to a node if BOTH this cell and its neighbor are valid
         Node node;
         node.cell    = cells[i][j];
         node.visited = false;

         Edges edges;

         // right neighbor
         if ( ( j+1 < cells.size() ) && 
              cells[i][j].isValid && 
              cells[i][j+1].isValid )
         {
            Edge edge;
            edge.dest = cells[i][j+1];
            edges.push_back(edge);
         }

         // bottom neighbor
         if ( ( i+1 < cells.size() ) && 
              cells[i][j].isValid && 
              cells[i+1][j].isValid )
         {
            Edge edge;
            edge.dest = cells[i+1][j];
            edges.push_back(edge);
         }

         // left neighbor
         if ( ( j-1 >= 0 ) && 
              cells[i][j].isValid && 
              cells[i][j-1].isValid )
         {
            Edge edge;
            edge.dest = cells[i][j-1];
            edges.push_back(edge);
         }

         // top neighbor
         if ( ( i-1 >= 0 ) && 
              cells[i][j].isValid && 
              cells[i-1][j].isValid )
         {
            Edge edge;
            edge.dest = cells[i-1][j];
            edges.push_back(edge);
         }

         node.edges = edges;
         g.push_back(node);
      }
   }

   return g;
}

Path Manager::dijkstra(Graph g)
{
   Path path;

   return path;
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

Cell Manager::getCell(int row, int col)
{
   return cells[row][col];
}
