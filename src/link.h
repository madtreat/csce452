
#ifndef LINK_H_
#define LINK_H_

#include "utils.h"

/*
   By default, links should be created and attached starting at the base and
   working towards the End-Effector.  Thus a link will not know its next_link
   at the time of creation, and should have it set explicitly after creation.
 */
struct Link {
   Joint joint;
   int   length; // in pixels
   Link* prev_link;
   Link* next_link;

   Link(Joint _joint, int _len, Link* _prev = 0, Link* _next = 0);
};


#endif

