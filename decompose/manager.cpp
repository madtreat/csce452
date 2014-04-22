
#include "manager.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <list>

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
   {
      if (cell == graph[i]->cell)
      {
         return graph[i];
      }
   }
   
   return NULL;
}

// Return true if cell is within boundaries and the cell is not in a box
bool Manager::isValidCell(int r, int c) const
{
   // check boundaries first, then check if cell is in a box
   bool validCell = 
          (r >= 0 && r < cells.size()) &&
          (c >= 0 && c < cells[0].size()) &&
          cells[r][c].isValid;
   return validCell;
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
   dijkstra();
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
         Cell cell  = cells[i][j];
         Node* node = getNode(cell);
         Edge edge;
         edge.weight = 1;
         edge.src = node;

         // if this cell is not valid, move to the next
         if (!isValidCell(i, j))
         {
            continue;
         }

         // update the source and dest nodes
         //printf("Cell: L=%d, R=%d, T=%d, B=%d\n", cell.L, cell.R, cell.T, cell.B);
         if ( (robot.X >= cell.L) &&
              (robot.X <  cell.R) &&
              (robot.Y >= cell.T) &&
              (robot.Y <  cell.B) )
         {
            srcNode = node;
         }
         if ( (dest.X >= cell.L) &&
              (dest.X <  cell.R) &&
              (dest.Y >= cell.T) &&
              (dest.Y <  cell.B) )
         {
            destNode = node;
         }

         // right neighbor
         if (isValidCell(i, j+1))
         {
            edge.dest = getNode(cells[i][j+1]);
            node->edges.push_back(edge);
            edges.push_back(edge);
         }

         // bottom neighbor
         if (isValidCell(i+1, j))
         {
            edge.dest = getNode(cells[i+1][j]);
            node->edges.push_back(edge);
            edges.push_back(edge);
         }

         // left neighbor
         if (isValidCell(i, j-1))
         {
            edge.dest = getNode(cells[i][j-1]);
            node->edges.push_back(edge);
            edges.push_back(edge);
         }

         // top neighbor
         if (isValidCell(i-1, j))
         {
            edge.dest = getNode(cells[i-1][j]);
            node->edges.push_back(edge);
            edges.push_back(edge);
         }

         nodes.push_back(node);
         graph.push_back(node);
      }
   }
}

// utility function for Dijkstra's algorithm
// dist is the list of shortest distance paths
// spset[i] is true if node i is in the shortest path
int Manager::minDistance()//int dist[], bool spset[])
{
   int min = 999999;
   int minIndex;
   for (int n = 0; n < nodes.size(); n++)
   {
      if (nodes[n]->spset == false && nodes[n]->dist <= min)
      {
         min = nodes[n]->dist;
         minIndex = n;
      }
   }
   return minIndex;
}

// Find the shortest path from the robot to destination using
// Dijkstra's SSSP Algorithm
void Manager::dijkstra()
{
   // Preparation for the algorithm
   cout << endl << "Beginning Dijkstra's Algorithm..." << endl;
   // check errors: robot or dest inside a box
   if ( !srcNode || 
        !srcNode->cell.isValid || 
        !destNode || 
        !destNode->cell.isValid)
   {
      cout << "ERROR: invalid parameters" << endl;
      cout << "robot or dest may be inside a box" << endl;
      return;
   }

   // find the starting cell (srcCell) in terms of the graph's nodes
   Node* currentNode = srcNode;



   // the actual Dijkstra Algorithm
   // have path member already
   path.push_back(srcNode->cell);
   //int dist[nodes.size()];

   // set of nodes to include in path
   //bool spset[nodes.size()];

   // distances are already infinite

   // set distance of source node to 0 (and visited)
   //dist[src] = 0;
   srcNode->dist = 0;
   srcNode->visited = true;

   for (int i = 0; i < nodes.size(); i++)
   {
      // find the minimum distance node
      int u = minDistance();//dist, shortestPath);
      nodes[u]->spset = true; // mark that node as part of the shortest path set
      nodes[u]->visited = true;
      path.push_back(nodes[u]->cell);

      if (nodes[u] == destNode)
      {
         break;
      }

      // update dist value of adjacent nodes of the picked node
      for (int n = 0; n < nodes.size(); n++)
      {
         Edge edge = nodes[u]->hasEdge(nodes[n]);
         // update the distance of node n if ...
         if (!nodes[n]->spset &&          // not already in spset
             edge.dest &&                 // there is an edge from u to n
             nodes[u]->dist != 999999 &&  // total weight from u to n is < ...
             nodes[u]->dist + edge.weight < nodes[n]->dist) // current dist
         {
            nodes[n]->dist = nodes[u]->dist + edge.weight;
         }
      }
   }









	
   // Dijkstra's Algorithm
   /*
   Nodes visitedNodes;
   visitedNodes.push_back(currentNode);
   while (true)
   {
      // if current and destination are in same cell, we have found a path!
      cout << "=============================================" << endl;
      cout << "   Checking path complete...nodesVisited=" << visitedNodes.size() << endl;
      if (*currentNode == *destNode || visitedNodes.size() == graph.size())
      {
         cout << "Path found!" << endl;
         break;
      }

      // loop through neighbors,
      // updating their distances from the source
      
      cout << "   Checking neighbors of current cell: " << findCellIndex(currentNode->cell) << endl;
      for (int n = 0; n < currentNode->edges.size(); n++)
      {
         Node* neighbor = currentNode->edges[n].dest;
         cout << "      neighbors: " << findCellIndex(neighbor->cell) << "...";
         cout << "dist=" << neighbor->dist <<endl;
         // if not visited...
         if (!neighbor->visited)
         {
            // update neighbor distance if smaller via this path
            int newDist = currentNode->dist + 1;
            if (neighbor->dist > newDist)
               neighbor->dist = newDist;
         }
      }

      // traverse to find the next node
      int nextDist = 999999;
      Node* nextNode = NULL;
      cout << "   Finding next cell..." << endl;
      for (int n = 0; n < currentNode->edges.size(); n++)
      {
         Node* neighbor = currentNode->edges[n].dest;
         cout << "      " << findCellIndex(neighbor->cell) << "...visited=" << neighbor->visited << "...dist=" << neighbor->dist << endl;
         if ( (*neighbor == *destNode) || 
              (!neighbor->visited && 
                neighbor->dist < nextDist) )
         {
            nextDist = neighbor->dist;
            nextNode = neighbor;
         }
      }
		
		if (nextNode != NULL)
		{
         cout << "Updating to next cell " << findCellIndex(nextNode->cell) << "...dist=" << nextNode->dist << endl;
			currentNode = nextNode;
         // mark this node as visited
         currentNode->visited = true;
         visitedNodes.push_back(currentNode);
			path.push_back(currentNode->cell);
		}
      else
      {
         cout << "ERROR: nextNode is null" << endl;
      }
   }
   
   // now that all nodes have a shortest distance from the source node, find
   // the shortest path by traversing backwards from the destination
   /*
   currentNode = destNode;
   list<Cell> cellPath;
   cellPath.push_front(destNode->cell);
   while (true)
   {
      Node* prevNode = currentNode->edges[0].src;
      for (int i = 0; i < currentNode->edges.size(); i++)
      {
         Node* neighbor = currentNode->edges[i].src;
         // find the shortest dist neighbor
         if (neighbor->dist < prevNode->dist)
         {
            prevNode = neighbor;
            if (*prevNode == *destNode)
               break;
         }
      }
      cellPath.push_front(prevNode->cell);
      currentNode = prevNode;
   }
   path = Path(cellPath.begin(), cellPath.end());
   // */
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
	return path[nodeNum].pos;//Position();
}

int Manager::getPathNodesLength()
{
	return path.size();
}

Position Manager::findCellIndex(Cell c) const
{
   for (int i=0; i<cells.size(); i++)
   {
      for (int j=0; j<cells[i].size(); j++)
      {
         if (cells[i][j] == c)
            return Position(i,j);
      }
   }
   
   return Position();
}

void Manager::clearCells()
{
	cells.clear();
	graph.clear();
   path.clear();
	pathDrawn = false;
}
 
