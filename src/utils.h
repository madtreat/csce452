/*
   Basic utility and common constants, structures and enumerations, etc.
 */


#ifndef UTILS_H_
#define UTILS_H_

enum JointType {
   BASE_JOINT  = 0,
   REVOLUTE    = 1,
   PRISMATIC   = 2
};

struct Joint {
   JointType type;
   int       range_min;
   int       range_max;
};

struct Link {
   Joint joint;
   int   length;
   Link* prev_link;
   Link* next_link;

   Link(Joint _joint, int _len, Link* _prev = NULL, Link* _next = NULL) 
    : joint(_joint),
      length(_len),
      prev_link(_prev),
      next_link(_next)
   {}
};

struct Base : public Link {
   Base(int _len, Link* _next = NULL) 
    : joint(BASE_JOINT),
      length(_len),
      prev_link(NULL),
      next_link(_next)
   {}
};

struct Brush : public Link {
   Brush(Link* _prev = NULL)
    : joint(BASE_JOINT),
      length(0),
      prev_link(_prev),
      next_link(NULL)
   {}
};

#endif

