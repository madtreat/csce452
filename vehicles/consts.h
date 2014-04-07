
#ifndef CONSTS_H_
#define CONSTS_H_

#include <vector>

const double PI = 3.1415926;
const int WIDTH  = 800;		//Window Size
const int HEIGHT = 600;		//Window Size
const int CAR_LENGTH = 11;
const int CAR_WIDTH = 8;
const int LIGHT_RADIUS = 5;


struct Position {
   int X;
   int Y;
   Position(int _x = -1, int _y = -1) : X(_x), Y(_y) {};
	
	int	getX() const {return X;}
   int	getY() const {return Y;}
};

typedef Position Sensor;
typedef Position Light;
typedef std::vector<Light> Lights;

#endif

