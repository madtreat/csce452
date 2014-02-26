
#ifndef BRUSH_H_
#define BRUSH_H_

#include "link.h"

struct Brush : public Link
{
   int diameter; // diameter of brush in pixels
   Brush(Link* _prev = 0);
};

#endif

