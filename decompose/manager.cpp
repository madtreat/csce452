
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

// Return the node with this cell
Node* Manager::getNode(const Cell& cell) const
{
   for (int i = 0; i < graph.size(); i++)
      if (cell == graph[i]->cell)
         return graph[i];
   
   return NULL;
}

// Called from window
void Manager::timeStep()
{
	
}

// Find a path from robot to destination, avoiding obstacles
void Manager::generatePath()
{
   // clear out our last path
   cells.clear();
   graph.clear();
   path.clear();

   // Step 1: decompose free space into cells
   decompose();

   // Step 2: generate connectivity graph
   connectCells();

   // Step 3: find a path from robot to destination
   path = dijkstra(graph);

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
         Cell cell;
         cell.L  = xcoords[i-1];
         cell.R  = xcoords[i];
         cell.T  = ycoords[j-1];
         cell.B  = ycoords[j];
         cell.TL = Position(cell.L, cell.T);
         cell.TR = Position(cell.R, cell.B);
         cell.BL = Position(cell.L, cell.T);
         cell.BR = Position(cell.R, cell.B);
         
         int nodeX = cell.L + ( cell.R - cell.L ) / 2;
         int nodeY = cell.T + ( cell.B - cell.T ) / 2;
         Position pos(nodeX, nodeY);
         cell.pos = pos;

         // if this cell position is within a box, make it an invalid cell (but keep it...
         // useful for graph construction)
         if (isCollision(pos) != -1)
            cell.isValid = false;
         else
            cell.isValid = true;

         row.push_back(cell);

         Node* node = new Node();
         node->cell = cell;
         graph.push_back(node);

         cout << "Cell made with node = (" << nodeX << ", " << nodeY << ")" << endl;
      }
      cells.push_back(row);
   }
}

// generate a connectivity graph based on the vector of cells given
void Manager::connectCells()
{
   // loop through rows
   for (int i = 0; i < cells.size(); i++)
   {
      // loop through columns in this row
      for (int j = 0; j < cells[i].size(); j++)
      {
         // Only add an edge to a node if BOTH this cell and its neighbor are valid
         Node* node    = new Node();
         node->cell    = cells[i][j];
         node->visited = false;
         node->dist    = 0;

         Edges edges;

         // right neighbor
         if ( ( j+1 < cells.size() ) && 
              cells[i][j].isValid && 
              cells[i][j+1].isValid )
         {
            Edge edge;
            edge.dest = getNode(cells[i][j+1]);
            edges.push_back(edge);
         }

         // bottom neighbor
         if ( ( i+1 < cells.size() ) && 
              cells[i][j].isValid && 
              cells[i+1][j].isValid )
         {
            Edge edge;
            edge.dest = getNode(cells[i+1][j]);
            edges.push_back(edge);
         }

         // left neighbor
         if ( ( j-1 >= 0 ) && 
              cells[i][j].isValid && 
              cells[i][j-1].isValid )
         {
            Edge edge;
            edge.dest = getNode(cells[i][j-1]);
            edges.push_back(edge);
         }

         // top neighbor
         if ( ( i-1 >= 0 ) && 
              cells[i][j].isValid && 
              cells[i-1][j].isValid )
         {
            Edge edge;
            edge.dest = getNode(cells[i-1][j]);
            edges.push_back(edge);
         }

         node->edges = edges;
         graph.push_back(node);
      }
   }
}

// Find the shortest path from the robot to destination using
// Dijkstra's SSSP Algorithm
Path Manager::dijkstra(Graph)
{
   Cell srcCell;
   Cell destCell;
   Path path;
   
   // find the source node (the cell containing the robot)
   bool foundSrc = false;
   bool foundDest = false;
   for (int i = 0; i < cells.size(); i++)
   {
      for (int j = 0; j < cells[i].size(); i++)
      {
         Cell cell = cells[i][j];
         if ( (robot.X >= cell.L) &&
              (robot.X <  cell.R) &&
              (robot.Y >= cell.T) &&
              (robot.Y <  cell.B) )
         {
            srcCell = cell;
            foundSrc = true;
         }
         if ( (dest.X >= cell.L) &&
              (dest.X <  cell.R) &&
              (dest.Y >= cell.T) &&
              (dest.Y <  cell.B) )
         {
            destCell = cell;
            foundDest = true;
         }
      }
      if (foundSrc && foundDest)
         break;
   }

   // check errors: robot or dest inside a box
   if (!srcCell.isValid && !destCell.isValid)
   {
      cout << "ERROR: invalid parameters" << endl;
      cout << "robot or dest may be inside a box" << endl;
      return path;
   }

   path.push_back(srcCell);

   // find the starting cell (srcCell) in terms of the graph's nodes
   Node* currentNode = NULL;
   Node* destNode = NULL;
   for (int i = 0; i < graph.size(); i++)
   {
      if (graph[i]->cell == srcCell)
      {
         currentNode = graph[i];
      }
      if (graph[i]->cell == destCell)
      {
         destNode = graph[i];
      }
   }

   // Dijkstra's Algorithm
   while (true)
   {
      // if current is destination, we have found a path
      if (currentNode == destNode)
      {
         cout << "Path found!" << endl;
         break;
      }
      // loop through neighbors
      for (int n = 0; n < currentNode->edges.size(); n++)
      {
         Node* neighbor = currentNode->edges[n].dest;
         // if not visited...
         if (!neighbor->visited)
         {
            // update neighbor distance if smaller via this path
            int newDist = currentNode->dist + 1;
            if (neighbor->dist > newDist)
               neighbor->dist = newDist;
         }
      }
      // mark this node as visited
      currentNode->visited = true;

      // traverse to find the next node
      int nextDist = 999999;
      Node* nextNode = NULL;
      for (int n = 0; n < currentNode->edges.size(); n++)
      {
         if (currentNode->edges[n].dest->dist < nextDist)
         {
            nextDist = currentNode->edges[n].dest->dist;
            nextNode = currentNode->edges[n].dest;
         }
      }

      currentNode = nextNode;
      path.push_back(currentNode->cell);
   }
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
