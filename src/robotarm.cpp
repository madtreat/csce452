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
#include <stdio.h>

using namespace std;

const double PI = 3.1415926;

RobotArm::RobotArm()
{
   // TODO: make these not hard coded
   // Create the links of this paintbot, including predecessors
   Base*  base  = new Base(300);
   Link*  link1 = new Link(Joint(PRISMATIC, 0, 300,   5, 175, 430), 150, base);
   Link*  link2 = new Link(Joint(REVOLUTE,  0, 360,   0, 175, 280), 100, link1);
   Link*  link3 = new Link(Joint(REVOLUTE,  0, 360,   0, 175, 180),  75, link2);
   Brush* brush = new Brush(link3,                       175, 105);

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
   /*
	cout << link1->joint.X << " " << link1->joint.Y << endl;
   cout << link2->joint.X << " " << link2->joint.Y << endl;
   cout << link3->joint.X << " " << link3->joint.Y << endl;
   cout << brush->joint.X << " " << brush->joint.Y << endl;
	// */
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

// Rotation joint
void RobotArm::rotateJoint(Link* link, Motion motion, int deg)
{
	//TODO: Remove this if when sure it isnt going to break
	if (motion == CW || motion == CCW)// either link 2 or 3 
   {
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
      if (link->prev_link)  // usually for link 2 and 3 case 
      {
         int newrot = link->prev_link->joint.rot_abs + link->joint.rotation;
         if (newrot >= 360 || newrot < 0)
            newrot %= 360;
         link->joint.rot_abs = newrot;
			/*
			cout << "Link: " << link->length << " -- ";
			cout << "rot_abs: " << link->joint.rot_abs << " - ";
			cout << "rot: " << link->joint.rotation << endl;
			// */
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
			/*
			cout << "NextLink: " << link->length << " -- ";
			cout << "rot_abs: " << link->joint.rot_abs << " - ";
			cout << "rot: " << link->joint.rotation << endl;
			// */

         int curX = link->joint.X;
         int curY = link->joint.Y;
         int len  = link->prev_link->length;

         //double rad = (double) degDiff * ((double)PI/(double)180);
         double rad = (double) link->prev_link->joint.rot_abs * ((double)PI/(double)180);

         //int nextX = curX + (curX*cos(rad) - curX*sin(rad));
         //int nextY = curY + (curY*sin(rad) + curY*cos(rad));
			
         int nextX = frameX - ( (len)*cos(rad) );// - ( (len)*sin(rad) );
         int nextY = frameY - ( (len)*sin(rad) );// + ( (len)*cos(rad) );

         //cout << "   deg = " << deg << ", rad = " << rad << " for link len = " << len << endl;
         link->joint.X = nextX;
         link->joint.Y = nextY;

         frameX = nextX;
         frameY = nextY;
      }
   }
}

// Translate prismatic Joint
void RobotArm::translateJoint(Link* link, Motion motion, int amt)
{
	//TODO: Remove this if when sure
   if (motion == LEFT || motion == RIGHT)
   {
      int xoffset = 0;
      if (motion == LEFT)
         xoffset = -abs(amt - link->joint.rotation);
      else // motion == RIGHT
         xoffset = abs(amt - link->joint.rotation);

      link->joint.X = OFFSET_X + amt;
      link->joint.rotation = amt;

      while( link->next_link != getBrush())
      {
         link = link->next_link;
         link->joint.X += xoffset;
      }
      getBrush()->joint.X += xoffset;
   }
}

// Translate brush using x and y buttons
void RobotArm::translateBrush(Link* brush, Motion motion, int newVal)
{
	// get Brush
	int curX = brush->joint.X;
	int curY = brush->joint.Y;
	// set range using joint 1
	int softMin = links[1]->joint.range_min;
	int softMax = links[1]->joint.range_max;
	// get link1
	int link1X = links[1]->joint.X;
	int link1Y = links[1]->joint.Y;
	// get link2
	int link2X = links[2]->joint.X;
	int link2Y = links[2]->joint.Y;
	// get link lengths (should be 100 and 75 respectively)
	int l2len = links[2]->length;
	int l3len = links[3]->length;

   // total distanced moved in this direction
   int diff = abs(curX - newVal);
		
   // world mode
   if (motion & X)
   {
      // if within the soft caps, easy movement
      // link 1 at min range
      if ( (link1X + OFFSET_X > softMin) && 
      // link 1 at max range
           (link1X + OFFSET_X < softMax) )
      {
         // move all joints left
         // use a relative position (in link 1's range)
         translateJoint(links[1], LEFT, links[1]->joint.rotation - diff); //--links[1]->joint.X);
      }
      // if not within the soft caps, difficult movement
      else
      {
         // not really distance, but did not want to sqrt, then square it
         // is really dist ^ 2 (c^2)
         long int dist_  = pow((newVal - link2X), 2) + pow((curY - link2Y), 2);

         // law of cosines
         int numer  = pow(l2len, 2) + pow(l3len, 2) - dist_;
         int denom  = 2 * l2len * l3len; // 15000
         double angle3 = acos( (double)numer / (double)denom );

         // law of sines
         double angle2 = asin( sin ( angle3 ) / sqrt(dist_) * links[3]->length );
         
         //*
         cout << "dist:    "<< dist_ << endl
               << "numer:   "<< numer << endl
               << "denom:   "<< denom << endl
               << "div:     "<< (double)numer / (double)denom << endl;
         // */

         cout << "angle 2R: " << angle2 << endl;
         cout << "angle 3R: " << angle3 << endl;
         // convert angles to degrees
         angle2 *= 180/PI;
         angle3 *= 180/PI;
         
         std::cout << std::endl;
         std::cout << "*l1: " << links[1]->joint.X << " " << links[1]->joint.Y << std::endl;
         std::cout << "*l2: " << links[2]->joint.X << " " << links[2]->joint.Y << std::endl;
         std::cout << "*l3: " << links[3]->joint.X << " " << links[3]->joint.Y << std::endl;
         std::cout << "*br: " << links[4]->joint.X << " " << links[4]->joint.Y << std::endl;
         std::cout << std::endl;
         
         // use them
         //Motion dir1 = 
         //translateJoint(links[1], RIGHT, links[1]->joint.rotation - diff);

         Motion dir2 = ( (int)angle2 < links[2]->joint.rotation) ? CW : CCW;
         rotateJoint(links[2], dir2, (int)angle2);
         
         Motion dir3 = ( (int)angle3 < links[3]->joint.rotation) ? CW : CCW;
         rotateJoint(links[3], dir3, (int)angle3);
         cout << "angle 2: "<< (int)angle2 << endl;
         cout << "angle 3: " << (int)angle3 << endl;
         
         // pray they work
      }
   }
	else if (motion & Y)
	{
      /*
		// If y is decreasing using Brush y- button
      if (motion == Y_DEC) 
      {
			
      }
		// Same as above except better!
      else if (motion == Y_INC)
      {
      // */
      // not really distance, but did not want to sqrt, then square it
      // is really dist ^ 2 (c^2)
      long int dist_  = pow((curX - link2X), 2) + pow((newVal - link2Y), 2);

      // law of cosines
      int numer  = pow(l2len, 2) + pow(l3len, 2) - dist_;
      int denom  = 2 * l2len * l3len; // 15000
      double angle3 = acos( (double)numer / (double)denom );

      // law of sines
      double angle2 = asin( sin ( angle3 ) / sqrt(dist_) * links[3]->length );
      
      //*
      cout << "dist:    "<< dist_ << endl
            << "numer:   "<< numer << endl
            << "denom:   "<< denom << endl
            << "div:     "<< (double)numer / (double)denom << endl;
      // */

      cout << "angle 2R: " << angle2 << endl;
      cout << "angle 3R: " << angle3 << endl;
      // convert angles to degrees
      angle2 *= 180/PI;
      angle3 *= 180/PI;
      
      std::cout << std::endl;
      std::cout << "*l1: " << links[1]->joint.X << " " << links[1]->joint.Y << std::endl;
      std::cout << "*l2: " << links[2]->joint.X << " " << links[2]->joint.Y << std::endl;
      std::cout << "*l3: " << links[3]->joint.X << " " << links[3]->joint.Y << std::endl;
      std::cout << "*br: " << links[4]->joint.X << " " << links[4]->joint.Y << std::endl;
      std::cout << std::endl;
      
      // use them
      Motion dir2 = ( (int)angle2 < links[2]->joint.rotation) ? CW : CCW;
      rotateJoint(links[2], dir2, (int)angle2);
      
      Motion dir3 = ( (int)angle3 < links[3]->joint.rotation) ? CCW : CW;
      rotateJoint(links[3], dir3, -(int)angle3);
      cout << "angle 2: "<< (int)angle2 << endl;
      cout << "angle 3: " << (int)angle3 << endl;
      
      // pray they work
      // prayer();
      //}
	}
}


