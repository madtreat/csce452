
#ifndef CONSTS_H_
#define CONSTS_H_

#include <vector>


const double PI = 3.1415926;
const int WIDTH  = 500;		//Window Size
const int HEIGHT = 500;		//Window Size

const int NUM_BOXES = 3;
const int BOX0_SIZE = 200/2;
const int BOX1_SIZE = 150/2;
const int BOX2_SIZE = 100/2;
const int ROBOT_RADIUS = 5;
const int DEST_RADIUS = 5; 

const int BUFFER = 50; // 50 pixel buffer for randomly generated locations
// meaning nothing can be randomly generated along the outer 50 pixels
// of the canvas

struct Position {
   int X;
   int Y;
   Position(int _x = -1, int _y = -1) : X(_x), Y(_y) {};
};
typedef Position Robot;
typedef Position Destination;

struct Box {
   Position pos;
   int      size;
	Box(Position _pos = Position(), int _size = 0) : pos(_pos), size(_size) {};
};
typedef std::vector<Box>   Boxes;

struct Cell {
   Position pos;     // node position in this cell (center? random?)
   int      L;       // Left Edge
   int      R;       // Right Edge
   int      T;       // Top Edge
   int      B;       // Bottom Edge
   Position TL;      // Top Left Vertex
   Position TR;      // Top Right Vertex
   Position BL;      // Bottom Left Vertex
   Position BR;      // Bottom Right Vertex
   bool     isValid; // is this cell valid? true; is this cell in collision? false
};

inline bool operator==(const Cell& lhs, const Cell& rhs) {
   if ( (lhs.pos.X == rhs.pos.X) &&
         (lhs.pos.Y == rhs.pos.Y) )
      return true;
   else
      return false;
}

typedef std::vector<Cell>  Path; // the path from src cell to dest cell
typedef std::vector<Cell>  CRow; // a cell row
typedef std::vector<CRow>  Cells;// a 2D grid of cells (of varying sizes)

struct Edge;
typedef std::vector<Edge>  Edges;

// a graph node is a node and its list of edges
struct Node {
   Cell  cell;
   Edges edges;
   bool  visited;
   int   dist; // distance for Dijkstra's Algorithm
};

inline bool operator==(const Node& lhs, const Node& rhs) {
   if (lhs.cell == rhs.cell)
      return true;
   else
      return false;
}

// an edge is a line between two positions
struct Edge {
   //Cell src;
   Node* dest;
};

typedef std::vector<Node*>  Graph;

#endif

