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
   Link*  link1 = new Link(Joint(PRISMATIC, 0, 300,  20, 190, 430), 150, base);
   Link*  link2 = new Link(Joint(REVOLUTE,  0, 360,   0, 190, 280), 100, link1);
   Link*  link3 = new Link(Joint(REVOLUTE,  0, 360,   0, 190, 180),  75, link2);
   Brush* brush = new Brush(link3,                       190, 105);

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
	// get Brush
	int curX = brush->joint.X;
	int curY = brush->joint.Y;
   int l2X = links[2]->joint.X;
   int l2Y = links[2]->joint.Y;
	// get link lengths (should be 100 and 75 respectively)
   int l1len = links[1]->length;
	int l2len = links[2]->length;
	int l3len = links[3]->length;

   int deltaX_2 = 0;
   int deltaY_2 = 0;
   long int hyp_2 = 1;
   int numer = 0;
   int denom = 1;

   int link1X = newX;

   double theta2 = 0;
   double theta2_deg = 0;
   double theta3 = 0;
   double theta3_deg = 0;
   double phi1 = 0;
   double phi2 = 0;

   while (true)
   {
      deltaX_2 = pow((link1X - links[2]->joint.X), 2);
      deltaY_2 = pow((newY   - links[2]->joint.Y), 2);
      hyp_2  = deltaX_2 + deltaY_2;

      // law of cosines
      numer  = pow(l2len, 2) + pow(l3len, 2) - hyp_2;
      denom  = 2 * l2len * l3len;

      //Theta3 = cos^-1((-(X3 - X0)^2 - (Y3 - L0)^2 + L3^2 + L2^2) / (L3 * L2))
      double t3val = ( -hyp_2 + pow(l2len, 2) + pow(l3len, 2) ) / denom;
      theta3 = acos( t3val );

      //Phi2 = cos^-1(((X3 - X0)^2 + (Y3 - L0)^2 - L3^2 + L2^2) / (sqrt((X3 - X0)^2 + (Y3 - L0)^2) * L2))
      double p2val =  ( hyp_2 + pow(l2len, 2) - pow(l3len, 2) ) / 
                        ( 2 * l2len * sqrt(hyp_2));
      phi2 = acos(p2val);
      //Phi1 = cos^-1(((X3 - X0)^2 + (Y3 - L0)^2 + L1^2  - (X3 - X0)^2 - (Y3)^2) / (2sqrt((X3 - X0)^2 + (Y3 - L0)^2) * L1))

      double p1val = ( hyp_2 + pow(l1len, 2) - deltaX_2 - pow(newY, 2) /
                        ( 2 * l1len * sqrt(hyp_2)));
      phi1 = acos( p1val );



      if (abs(t3val) > 1.0 || abs(p2val) > 1.0 )//|| abs(p1val) > 1.0)
      {
         if (newY == 105)
         {
            phi1 = 0;
            phi2 = 0;
            theta2 = 0;
            theta3 = 0;
         }
         else
         {
            link1X += 5;
         }
      }
      else
      {
         break;
      }
   
      theta2 = phi1 - phi2;

      theta2_deg = theta2 * 180.0/PI;
      theta3_deg = theta3 * 180.0/PI;
      
      double angle2 = theta2_deg;
      double angle3 = theta3_deg;
   }   
   

   /*
   cout << "dist:    "<< hyp_2 << endl;
   cout << "numer:   "<< numer << endl;
   cout << "denom:   "<< denom << endl;
   cout << "div:     "<< (double) numer / (double) denom << endl;
   // */
   
   /*
   cout << "     theta2 : " << theta2 << endl;
   cout << "     theta3 : " << theta3 << endl;
   cout << "       phi1 : " << phi1 << endl;
   cout << "       phi2 : " << phi2 << endl;
   cout << "     theta2d: " << theta2_deg << endl;
   cout << "     theta3d: " << theta3_deg << endl;
   cout << "sin(theta)2 : " << sin(theta2) << endl;
   cout << "sin(theta)3 : " << sin(theta3) << endl;
   cout << "  sin(phi)1 : " << sin(phi1) << endl;
   cout << "  sin(phi)2 : " << sin(phi2) << endl;
   cout << "sin(theta)2d: " << sin(theta2_deg) << endl;
   cout << "sin(theta)3d: " << sin(theta3_deg) << endl;
   // */


   // assign them
   if (link1X < OFFSET_X)
      link1X = OFFSET_X;
   if (link1X > 640-OFFSET_X)
      link1X = 640-OFFSET_X;
   
   // need to take the offset into account
   links[1]->joint.X = link1X;//newX;
   links[2]->joint.X = link1X;//newX;

   /*
   links[3]->joint.X = l2X + l2len * ( cos(phi2)        + sin(phi2) );
   links[3]->joint.Y = l2Y + l2len * ( -1.0*sin(phi2)   + cos(phi2) );
   // */

   links[3]->joint.X = l2X + l2len * sin(phi2);//theta3_deg);
   if (newY <= 280)//-25)
   {
      links[3]->joint.Y = l2Y + l2len * -cos(phi2);//theta3_deg);
   }
   /*
   else if (newY > 280-25 && newY < 280+25)
   {
      links[3]->joint.Y = l2Y + l2len * cos(90-phi2);
   }
   // */
   else
   {
      links[3]->joint.Y = l2Y + l2len * cos(phi2);//theta3_deg);
   }


   links[4]->joint.X = newX;
   links[4]->joint.Y = newY;

   /*
   cout << "angle 2R: " << theta2 << endl;
   cout << "angle 3R: " << theta3 << endl;
   // convert angles to degrees
   //angle2 = angle2 * (double) 180/ (double) PI;// - 90;
   //angle3 = angle3 * (double) 180/ (double) PI;// - 90;
   cout << "angle 2 : " << theta2_deg << endl;
   cout << "angle 3 : " << theta3_deg << endl;
   // */

   // pray they work
   // prayer();
}


