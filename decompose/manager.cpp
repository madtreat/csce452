
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
	pathDrawn = false;
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
   clearCells();

   // Step 1: decompose free space into cells
   decompose();

   // Step 2: generate connectivity graph
   connectCells();

   // Step 3: find a path from robot to destination
   path = dijkstra(graph);
	if (path.size() > 0)
		pathDrawn = true;

   // Complete!
}

void Manager::decompose()
{
   vector<int> xcoords;
   vector<int> ycoords;

   xcoords.push_back(0);
   ycoords.push_back(0);
   // decompose the area into cells based on the box locations
   for (int i = 0; i < NUM_BOXES; i++)
   {
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
         cell.TR = Position(cell.R, cell.T);
         cell.BL = Position(cell.L, cell.B);
         cell.BR = Position(cell.R, cell.B);
         
         int nodeX = cell.L + ( cell.R - cell.L ) / 2;
         int nodeY = cell.T + ( cell.B - cell.T ) / 2;
         Position pos(nodeX, nodeY);
         cell.pos = pos;

         // if this cell position is within a box, make it an invalid cell (but keep it...
         // useful for graph construction)
         if (isCollision(pos) == -1)
            cell.isValid = true;
         else
            cell.isValid = false;

         row.push_back(cell);

         Node* node = new Node();
         node->cell = cell;
         node->visited = false;
         node->dist = 999999;
         graph.push_back(node);
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

         // right neighbor
         if ( ( j+1 < cells.size() ) && 
              cells[i][j].isValid && 
              cells[i][j+1].isValid )
         {
            Edge edge;
            edge.dest = getNode(cells[i][j+1]);
            node->edges.push_back(edge);
         }

         // bottom neighbor
         if ( ( i+1 < cells.size() ) && 
              cells[i][j].isValid && 
              cells[i+1][j].isValid )
         {
            Edge edge;
            edge.dest = getNode(cells[i+1][j]);
            node->edges.push_back(edge);
         }

         // left neighbor
         if ( ( j-1 >= 0 ) && 
              cells[i][j].isValid && 
              cells[i][j-1].isValid )
         {
            Edge edge;
            edge.dest = getNode(cells[i][j-1]);
            node->edges.push_back(edge);
         }

         // top neighbor
         if ( ( i-1 >= 0 ) && 
              cells[i][j].isValid && 
              cells[i-1][j].isValid )
         {
            Edge edge;
            edge.dest = getNode(cells[i-1][j]);
            node->edges.push_back(edge);
         }

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
      for (int j = 0; j < cells[i].size(); j++)
      {
         Cell cell = cells[i][j];
         //printf("Cell: L=%d, R=%d, T=%d, B=%d\n", cell.L, cell.R, cell.T, cell.B);
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
   if (!srcCell.isValid || !destCell.isValid)
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
	
	if ( currentNode == NULL || destNode == NULL)
	{
		cout << "ERROR: Null R and D nodes" << endl;
		return path;
	}

   cout << "Beginning Dijkstra's Algorithm" << endl;
   // Dijkstra's Algorithm
   while (true)
   {
      // if current and destination are in same cell, we have found a path!
      cout << "   Checking path complete..." << endl;
      if (*currentNode == *destNode)
      {
         cout << "Path found!" << endl;
         break;
      }

      // loop through neighbors,
      // updating their distances from the source
      cout << "   Checking neighbors of current..." << endl;
      for (int n = 0; n < currentNode->edges.size(); n++)
      {
         Node* neighbor = currentNode->edges[n].dest;
         cout << "      neighbors: cell at " << neighbor->cell.pos << "..." << endl;
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
      cout << "   Finding next cell..." << endl;
      for (int n = 0; n < currentNode->edges.size(); n++)
      {
         Node* neighbor = currentNode->edges[n].dest;
         cout << "      cell at " << neighbor->cell.pos << "..." << endl;
         if (neighbor->dist < nextDist)
         {
            nextDist = neighbor->dist;
            nextNode = neighbor;
         }
      }
		
		if (nextNode != NULL)
		{
         cout << "Updating to next cell at " << nextNode->cell.pos << "..." << endl;
			currentNode = nextNode;
			path.push_back(currentNode->cell);
		}
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
	if (boxNum >= 0 && boxNum < boxes.size() )
		boxes[boxNum].pos = pos;
	else cout << "Error: Out of Bounds in setBox" <<endl;
}

void Manager::setBoxSize(int boxNum, int size)
{
	if (boxNum >= 0 && boxNum < boxes.size() )
		boxes[boxNum].size = size;
	else cout << "Error: Out of Bounds in setBoxSize" <<endl;
}

Box Manager::getBox(int boxNum)
{
	if (boxNum >= 0 && boxNum < boxes.size() )
		return boxes[boxNum];
   return Box();
}

Cell Manager::getCell(int row, int col)
{
	if ( ( row >= 0 && row < cells.size() ) &&
		  ( col >= 0 && col < cells[row].size() ) )
			return cells[row][col];
   return Cell();
}

Position Manager::getPathNode(int nodeNum)
{
	return Position();
}

int Manager::getPathNodesLength()
{
	return 0;
}

void Manager::clearCells()
{
	cells.clear();
	graph.clear();
   path.clear();
	pathDrawn = false;
}
 
