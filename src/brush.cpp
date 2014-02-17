
#include "brush.h"
#include "utils.h"

Brush::Brush(Link* _prev)
: Link(Joint(BASE_JOINT, 0, 0), 0, _prev, 0), 
diameter(10)
{}

