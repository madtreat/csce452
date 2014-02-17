/*
   Configuration for the paint bot's arm
 */

#ifndef ARMCONFIG_H_
#define ARMCONFIG_H_

#include "utils.h"

struct Link;
struct Base;
struct Brush;

class RobotArm {
public:
   static const int NUM_LINKS = 3;

   RobotArm();
   ~RobotArm();

   Link* getLink(int link);
   Link* getBase()  {return links[0];}
   Link* getBrush() {return links[NUM_LINKS+1];}

private:
   // the size of links is NUM_LINKS + base + brush (hence the +2)
   Link* links[NUM_LINKS+2];
};

#endif

