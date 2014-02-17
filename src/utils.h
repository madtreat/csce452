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

   Joint(JointType _type, int _min, int _max)
    : type(_type),
      range_min(_min),
      range_max(_max)
   {}
};

struct Link {
   Joint joint;
   int   length;
   Link* prev_link;
   Link* next_link;

   Link(Joint _joint, int _len, Link* _prev = 0, Link* _next = 0) 
    : joint(_joint),
      length(_len),
      prev_link(_prev),
      next_link(_next)
   {}
};

struct Base : public Link {
   Base(int _len, Link* _next = 0) 
    : Link(Joint(BASE_JOINT, 0, 0), _len, 0, _next)
   {}
};

struct Brush : public Link {
   Brush(Link* _prev = 0)
    : Link(Joint(BASE_JOINT, 0, 0), 0, _prev, 0)
   {}
};

#endif

