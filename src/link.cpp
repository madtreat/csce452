
#include "link.h"

Link::Link(Joint _joint, int _len, Link* _prev, Link* _next) 
: joint(_joint),
  length(_len),
  prev_link(_prev),
  next_link(_next)
{}

