
#ifndef JOINT_H_
#define JOINT_H_

enum JointType {
   BASE_JOINT  = 0,  // no movement
   REVOLUTE    = 1,  // allows rotation and no displacement
   PRISMATIC   = 2   // allows displacement and no rotation
};

// Pretty much synonymous with Axis
struct Joint {
   JointType type;
   int       range_min;
   int       range_max;
   int		 rotation;
   int		 X;
   int 		 Y;

   Joint(JointType _type, int _min, int _max, int _rot=0, int _X=0, int _Y=0);
};

#endif

