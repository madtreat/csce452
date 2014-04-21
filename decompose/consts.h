
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

struct Box {
   Position pos;
   int      size;
	Box(Position _pos = Position(), int _size = 0) : pos(_pos), size(_size) {};
};

typedef Position Robot;
typedef Position Destination;
typedef Position Node;

// an edge is a line between two positions
struct Edge {
   Node n1;
   Node n2;
};

struct Cell {
   Node     node; // node position in this cell (center? random?)
   Position TL; // Top Left
   Position TR; // Top Right
   Position BL; // Bottom Left
   Position BR; // Bottom Right
};

typedef std::vector<Box>  Boxes;
typedef std::vector<Cell> Cells;
typedef std::vector<Node> Nodes;

#endif

