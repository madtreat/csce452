
#ifndef BASE_H_
#define BASE_H_

#include "link.h"

struct Base : public Link
{
   Base(int _len, Link* _next = 0);
};

#endif

