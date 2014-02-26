
#include "brush.h"
#include "joint.h"

Brush::Brush(Link* _prev, int _x, int _y)
: Link(Joint(BASE_JOINT, 0, 0, _x, _y), 0, _prev, 0), 
diameter(10)
{}

