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
void RobotArm::rotateJoint(Link* link, Motion, int deg)
{
   // set this link's rotation to the new value
   link->joint.rotation = deg;
   // loop back to the end
   if (link->joint.rotation < link->joint.range_min)
      link->joint.rotation = link->joint.range_max;
   // loop back to the beginning
   else if (link->joint.rotation > link->joint.range_max)
      link->joint.rotation = link->joint.range_min;

   // update absolute rotation
   if (link->prev_link)  // usually for link 2 and 3 case 
   {
      int newrot = link->prev_link->joint.rot_abs + link->joint.rotation;
      if (newrot >= 360 || newrot < 0)
         newrot %= 360;
      link->joint.rot_abs = newrot;
   }
   else
   {
      link->joint.rot_abs = link->joint.rotation;
   }
   
   // update next link's position based on the current frame's X and Y
   int frameX   = link->joint.X;
   int frameY   = link->joint.Y;

   while (link->next_link != 0)
   {
      // LINK IS NOW NEXT LINK IN CHAIN	--
      link = link->next_link;

      int newrot = link->prev_link->joint.rot_abs + link->joint.rotation;
      if (newrot >= 360 || newrot < 0)
         newrot %= 360;
      link->joint.rot_abs = newrot;

      int curX = link->joint.X;
      int curY = link->joint.Y;
      int len  = link->prev_link->length;

      double rad = (double) link->prev_link->joint.rot_abs * ((double)PI/(double)180);

      int nextX = frameX - (len) * cos(rad);
      int nextY = frameY - (len) * sin(rad);

      link->joint.X = nextX;
      link->joint.Y = nextY;

      frameX = nextX;
      frameY = nextY;
   }
}

// Translate prismatic Joint
void RobotArm::translateJoint(Link* link, Motion, int newX)
{
   if (newX < -5)
      newX = -5;
   if (newX > 465)
      newX = 465;
   int delta_x = newX - link->joint.rotation;

   link->joint.X = OFFSET_X + newX;
   link->joint.rotation = newX;

   while( link->next_link != getBrush())
   {
      link = link->next_link;
      link->joint.X += delta_x;
   }
   getBrush()->joint.X += delta_x;
}

// Translate the brush, computing the locations of all joints by 
// Inverse Kinematics
void RobotArm::translateBrush(Link* brush, int newX, int newY)
{
   //if (newX + OFFSET_X < 
	// get Brush
	int curX = brush->joint.X;
	int curY = brush->joint.Y;
	// get link lengths (should be 100 and 75 respectively)
   int l1len = links[1]->length;
	int l2len = links[2]->length;
	int l3len = links[3]->length;

   // total distanced moved in this direction
   int diff = abs(curX - newX);
		
   // not really distance, but did not want to sqrt, then square it
   // is really dist ^ 2 (c^2)
   int deltaX_2 = pow((newX - links[2]->joint.X), 2);
   int deltaY_2 = pow((newY - links[2]->joint.Y), 2);
   long int hyp_2  = deltaX_2 + deltaY_2;

   // law of cosines
   int numer  = pow(l2len, 2) + pow(l3len, 2) - hyp_2;
   int denom  = 2 * l2len * l3len;
   //double angle3 = acos( (double) numer / (double) denom );

   // law of sines
   //double angle2 = asin( ( sin(angle3) / sqrt(hyp_2) ) * l3len );
   
   
   /******************************************/

   /****      This is the difference      ****/
   // The following is team DROP DATABASE's code
   /******************************************/
   //Theta3 = cos^-1((-(X3 - X0)^2 - (Y3 - L0)^2 + L3^2 + L2^2) / (L3 * L2))
	double theta3 = acos( ( -hyp_2 + pow(l2len, 2) + pow(l3len, 2) ) / denom );
   // == our angle3
	//Phi2 = cos^-1(((X3 - X0)^2 + (Y3 - L0)^2 - L3^2 + L2^2) / (sqrt((X3 - X0)^2 + (Y3 - L0)^2) * L2))
	double phi2 = acos( ( hyp_2 + pow(l2len, 2) - pow(l3len, 2) ) / 
                       ( 2 * l2len * sqrt(hyp_2)));
	//Phi1 = cos^-1(((X3 - X0)^2 + (Y3 - L0)^2 + L1^2  - (X3 - X0)^2 - (Y3)^2) / (2sqrt((X3 - X0)^2 + (Y3 - L0)^2) * L1))
	double phi1 = acos( ( hyp_2 + pow(l1len, 2) - deltaX_2 - pow(newY, 2) /
                       ( 2 * l1len * sqrt(hyp_2))));
	double theta2 = phi1 - phi2;

   double theta2_deg = theta2 * 180.0/PI;
   double theta3_deg = theta3 * 180.0/PI;
   
   double angle2 = theta2_deg;
   double angle3 = theta3_deg;

   // assign them
   /*
   if (newX < links[1]->joint.range_min)
      links[1]->joint.X = links[1]->joint.range_min;
   else if (newX + OFFSET_X > links[1]->joint.range_max)
      links[1]->joint.X = links[1]->joint.range_max;
   // */
   // need to take the offset into account
   links[1]->joint.X = newX;

   /*
   links[2]->joint.X = links[2]->length * ( cos(theta2)        + sin(theta2) );
   links[2]->joint.Y = links[2]->joint.Y * ( -1.0*sin(theta2)   + cos(theta2) );

   links[3]->joint.X = links[3]->joint.X * ( cos(theta3)        + sin(theta3) );
   links[3]->joint.Y = links[3]->joint.Y * ( -1.0*sin(theta3)   + cos(theta3) );
   // */
   // I replaced the above with these to attempt combining theirs with ours
   rotateJoint(links[2], Motion(), (int) theta2);
   rotateJoint(links[3], Motion(), (int) 90-theta3);

   links[4]->joint.X = newX;
   links[4]->joint.Y = newY;

   /*
   cout << "dist:    "<< hyp_2 << endl
         << "numer:   "<< numer << endl
         << "denom:   "<< denom << endl
         << "div:     "<< (double) numer / (double) denom << endl;
   // */

   cout << "angle 2R: " << theta2 << endl;
   cout << "angle 3R: " << theta3 << endl;
   // convert angles to degrees
   //angle2 = angle2 * (double) 180/ (double) PI;// - 90;
   //angle3 = angle3 * (double) 180/ (double) PI;// - 90;
   cout << "angle 2 : " << theta2_deg << endl;
   cout << "angle 3 : " << theta3_deg << endl;
   
   /*
   std::cout << std::endl;
   std::cout << "*l1: " << links[1]->joint.X << " " << links[1]->joint.Y << std::endl;
   std::cout << "*l2: " << links[2]->joint.X << " " << links[2]->joint.Y << std::endl;
   std::cout << "*l3: " << links[3]->joint.X << " " << links[3]->joint.Y << std::endl;
   std::cout << "*br: " << links[4]->joint.X << " " << links[4]->joint.Y << std::endl;
   std::cout << std::endl;
   // */

   // use them
   /*
   translateJoint(links[1], RIGHT, links[1]->joint.rotation - diff);

   Motion dir2 = ( (int) angle2 < links[2]->joint.rotation) ? CW : CCW;
   rotateJoint(links[2], dir2, (int) angle2);
   
   Motion dir3 = ( (int) angle3 < links[3]->joint.rotation) ? CW : CCW;
   rotateJoint(links[3], dir3, (int) angle3);
   // */
   
   // pray they work
   // prayer();
}


