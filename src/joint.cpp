
#include "joint.h"

Joint::Joint(JointType _type, int _min, int _max, int _rot, int _X, int _Y)
: type(_type),
  range_min(_min),
  range_max(_max),
  rotation(_rot),
  rot_abs(_rot),
  X(_X),
  Y(_Y)
{}

