
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

//typedef Position Node;

struct Cell {
   Position pos;     // node position in this cell (center? random?)
   Position TL;      // Top Left
   Position TR;      // Top Right
   Position BL;      // Bottom Left
   Position BR;      // Bottom Right
   bool     isValid; // is this cell valid? true; is this cell in collision? false
};
typedef std::vector<Cell>  Path; // the path from src cell to dest cell
typedef std::vector<Cell>  CRow; // a cell row
typedef std::vector<CRow>  Cells;// a 2D grid of cells (of varying sizes)

// an edge is a line between two positions
struct Edge {
   //Cell src;
   Cell dest;
};
typedef std::vector<Edge>  Edges;

// a graph node is a node and its list of edges
struct Node {
   Cell  cell;
   Edges edges;
   bool  visited;
};

//typedef std::vector<Edge>  Graph; // plain-list style
//typedef std::vector<Edges> Graph; // adjacency-list style
typedef std::vector<Node>  Graph;

#endif

