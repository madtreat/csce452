
#ifndef CONSTS_H_
#define CONSTS_H_

#include <vector>
#include <ostream>

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
	
	void operator=(const Position& other) {
		X = other.X;
		Y = other.Y;
	}
};

inline std::ostream& operator<<(std::ostream& os, const Position& pos) {
   os << "Pos(" << pos.X << ", " << pos.Y << ")";
   return os;
}

typedef Position Robot;
typedef Position Destination;

struct Box {
   Position pos;
   int      size;
	Box(Position _pos = Position(), int _size = 0) : pos(_pos), size(_size) {};
};

inline std::ostream& operator<<(std::ostream& os, const Box& box) {
   os << "Box at " << box.pos << " of size " << box.size;
   return os;
}

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
	
	void operator=(const Cell& other) {
		pos = other.pos;
		L = other.L;
		R = other.R;
		T = other.T;
		B = other.B;
		TL = other.TL;
		TR = other.TR;
		BL = other.BL;
		BR = other.BR;
		isValid = other.isValid;
	}
};

inline std::ostream& operator<<(std::ostream& os, const Cell& cell) {
   os << "Cell at " << cell.pos << " isValid (" << cell.isValid << ")";
   return os;
}

inline bool operator==(const Cell& lhs, const Cell& rhs) {
   if (  (lhs.pos.X == rhs.pos.X) &&
         (lhs.pos.Y == rhs.pos.Y) )
      return true;
   return false;
}

typedef std::vector<Cell>  Path; // the path from src cell to dest cell
typedef std::vector<Cell>  CRow; // a cell row
typedef std::vector<CRow>  Cells;// a 2D grid of cells (of varying sizes)

struct Node;

// an edge is a line between two positions
struct Edge {
   Node* src;
   Node* dest;
   int   weight;

	void operator=(const Edge& other) {
      src  = other.src;
      dest = other.dest;
   }
};

typedef std::vector<Edge>  Edges;

// a graph node is a node and its list of edges
struct Node {
   Cell  cell;
   Edges edges;
   bool  visited;
   bool  spset; // is this node part of the shortest path?
   int   dist;  // distance for Dijkstra's Algorithm

   Edge hasEdge(Node* dest) {
      for (int i = 0; i < edges.size(); i++)
         if (edges[i].dest->cell == dest->cell)
            return edges[i];
      return Edge();
   }
};

inline bool operator==(const Node& lhs, const Node& rhs) {
   if (lhs.cell == rhs.cell)
      return true;
   return false;
}

typedef std::vector<Node*>  Nodes;
typedef std::vector<Node*>  Graph;

#endif

