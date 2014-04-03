
#include "base.h"
#include "joint.h"

Base::Base(int _len, Link* _next) 
: Link(Joint(BASE_JOINT, 0, 0), _len, 0, _next)
{}

