/*
   Implements a specific configuration of the robot arm.
 */

#include "robotarm.h"
#include "joint.h"
#include "link.h"
#include "base.h"
#include "brush.h"

#include <cmath>
#include <iostream>

using namespace std;

const double PI = 3.1415926;

RobotArm::RobotArm()
{
   // Create the links of this paintbot, including predecessors
   Base*  base  = new Base(300);
   Link*  link1 = new Link(Joint(PRISMATIC, 0, 300, 150, 320, 430), 150, base);
   Link*  link2 = new Link(Joint(REVOLUTE,  0, 360,   0, 320, 280), 100, link1);
   Link*  link3 = new Link(Joint(REVOLUTE,  0, 360,   0, 320, 180), 75, link2);
   Brush* brush = new Brush(link3, 320, 105);

   // Set the successor links
   base->next_link = link1;
   link1->next_link = link2;
   link2->next_link = link3;
   link3->next_link = brush;

   // Fix link1
   link1->joint.rot_abs = 90;

   // Add to the list
   links[0] = base;
   links[1] = link1;
   links[2] = link2;
   links[3] = link3;
   links[4] = brush;
   cout << link1->joint.X << " " << link1->joint.Y << endl;
   cout << link2->joint.X << " " << link2->joint.Y << endl;
   cout << link3->joint.X << " " << link3->joint.Y << endl;
   cout << brush->joint.X << " " << brush->joint.Y << endl;
}

RobotArm::~RobotArm()
{
   for (int i = 0; i < LENGTH; i++)
      delete links[i];
}

Link* RobotArm::getLink(int link)
{
   if (link < 0 || link >= LENGTH)
      return 0;

   if (link == 0)
      return getBase();

   if (link == NUM_LINKS + 1)
      return getBrush();

   return links[link];
}

void RobotArm::moveJoint(Link* link, Motion motion, int amt)
{
   // offset for X values to center them on the canvas
   int OFFSET = 640/2 - 150;

   // translate (if prismatic joint) or 
   //    rotate (if revolute joint)
   // in the correct direction (motion)
   if (motion == CW || motion == CCW)
   {
      int deg = amt;

      // set this link's rotation to the new value
      link->joint.rotation = deg;
      if (link->joint.rotation < link->joint.range_min)
      {
         // loop back to the end
         link->joint.rotation = link->joint.range_max;//joint.range_min;
      }
      else if (link->joint.rotation > link->joint.range_max)
      {
         // loop back to the beginning
         link->joint.rotation = link->joint.range_min;
      }

      // update absolute rotation
      if (link->prev_link)
      {
         int newrot = link->prev_link->joint.rot_abs + link->joint.rotation;
         if (newrot >= 360 || newrot < 0)
            newrot %= 360;
         link->joint.rot_abs = newrot;
			cout << "Link: " << link->length << " -- ";
			cout << "rot_abs: " << link->joint.rot_abs << " - ";
			cout << "rot: " << link->joint.rotation << endl;
      }
      else
      {
         link->joint.rot_abs = link->joint.rotation;
      }
      
      // update next link's position based on the current frame's X and Y
      int frameX   = link->joint.X;
      int frameY   = link->joint.Y;

      //while ((link = link->next_link) != 0)
      while (link->next_link != 0)
      {
			// LINK IS NOW NEXT LINK IN CHAIN	--
         link = link->next_link;
         //link->joint.rotation += link->prev_link->joint.rot_abs;

         int newrot = link->prev_link->joint.rot_abs + link->joint.rotation;
         if (newrot >= 360 || newrot < 0)
            newrot %= 360;
         link->joint.rot_abs = newrot;
			cout << "NextLink: " << link->length << " -- ";
			cout << "rot_abs: " << link->joint.rot_abs << " - ";
			cout << "rot: " << link->joint.rotation << endl;

         int curX = link->joint.X;
         int curY = link->joint.Y;
         int len  = link->prev_link->length;

         //double rad = (double) degDiff * ((double)PI/(double)180);
         double rad = (double) link->prev_link->joint.rot_abs * ((double)PI/(double)180);

         //int nextX = curX + (curX*cos(rad) - curX*sin(rad));
         //int nextY = curY + (curY*sin(rad) + curY*cos(rad));
			
         int nextX = frameX - ( (len)*cos(rad) );// - ( (len)*sin(rad) );
         int nextY = frameY - ( (len)*sin(rad) );// + ( (len)*cos(rad) );

         cout << "   deg = " << deg << ", rad = " << rad << " for link len = " << len << endl;
         link->joint.X = nextX;
         link->joint.Y = nextY;

         frameX = nextX;
         frameY = nextY;
      }
   }

   if (motion == LEFT || motion == RIGHT)
   {
      int xoffset = 0;
      if (motion == LEFT)
         xoffset = -abs(amt - link->joint.rotation);
      else // motion == RIGHT
         xoffset = abs(amt - link->joint.rotation);

      link->joint.X = OFFSET + amt;
      link->joint.rotation = amt;

      while( link->next_link != getBrush())
      {
         link = link->next_link;
         link->joint.X += xoffset;
      }
      getBrush()->joint.X += xoffset;
   }
}


