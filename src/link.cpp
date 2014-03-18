
#include "link.h"

Link::Link(Joint _joint, int _len, Link* _prev, Link* _next) 
: joint(_joint),
  length(_len),
  prev_link(_prev),
  next_link(_next),
  range_min_x(-5),
  range_max_x(645),
  range_min_y(430-150-100-75),
  range_max_y(480-50+25)
{}

