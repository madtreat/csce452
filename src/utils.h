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

// Pretty much synonymous with Axis
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

#endif

