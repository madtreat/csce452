
#ifndef CONSTS_H_
#define CONSTS_H_

#include <vector>

const int WIDTH  = 640;
const int HEIGHT = 480;

struct Position {
   int X;
   int Y;
   Position(int _x = -1, int _y = -1) : X(_x), Y(_y) {};
};

typedef Position Sensor;
typedef Position Light;
typedef std::vector<Light> Lights;

#endif

