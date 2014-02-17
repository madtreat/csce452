
#ifndef LINK_H_
#define LINK_H_

#include "joint.h"

/*
   By default, links should be created and attached starting at the base and
   working towards the End-Effector.  Thus a link will not know its next_link
   at the time of creation, and should have it set explicitly after creation.
 */
struct Link {
   /*
      The joint in this Link instance refers to the joint/axis connecting this
      link with the previous link in the arm.
    */
   Joint joint;
   int   length; // in pixels
   Link* prev_link;
   Link* next_link;

   Link(Joint _joint, int _len, Link* _prev = 0, Link* _next = 0);
};


#endif

