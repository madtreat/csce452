/*
Implements a specific configuration of the robot arm.
*/

#include "robotarm.h"
#include "joint.h"
#include "link.h"
#include "base.h"
#include "brush.h"

#include <math.h>
#include <iostream>

using namespace std;

const int PI = 3.1415926;

RobotArm::RobotArm()
{
	// Create the links of this paintbot, including predecessors
	Base*  base  = new Base(300);
	Link*  link1 = new Link(Joint(PRISMATIC, 0, 300, 0, 320, 430), 150, base);
	Link*  link2 = new Link(Joint(REVOLUTE,  0, 360, 0, 320, 280), 100, link1);
	Link*  link3 = new Link(Joint(REVOLUTE,  0, 360, 0, 320, 180), 75, link2);
	Brush* brush = new Brush(link3, 320, 105);

	// Set the successor links
	base->next_link = link1;
	link1->next_link = link2;
	link2->next_link = link3;
	link3->next_link = brush;

	// Add to the list
	links[0] = base;
	links[1] = link1;
	links[2] = link2;
	links[3] = link3;
	links[4] = brush;
   cout << link1->joint.X << " " << link1->joint.Y << endl;// << " " << x1 << " " << y1 << endl;
   cout << link2->joint.X << " " << link2->joint.Y << endl;// << " " << x1 << " " << y1 << endl;
   cout << link3->joint.X << " " << link3->joint.Y << endl;// << " " << x1 << " " << y1 << endl;
   cout << brush->joint.X << " " << brush->joint.Y << endl;// << " " << x1 << " " << y1 << endl;
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
	int x_set = 1;

	// get the link's current position
	Joint joint = link->joint;
	// translate (if prismatic joint) or 
	//    rotate (if revolute joint)
	// in the correct direction (motion)
	switch(motion)
	{
	case CW:
		{
         //std::cout << "moving link CW" << std::endl;
         int deg = -amt;
			joint.rotation += deg;
			if (joint.rotation >= joint.range_max)
			{
            // loop back to the beginning
				joint.rotation = joint.range_min;//joint.range_max;
			}
         
         // update next link's position based on the current frame's X and Y
         int frameX = joint.X;
         int frameY = joint.Y;
         int linkLen = link->length;
         while ((link = link->next_link) != 0)
         {
            //cout << "   Link len = " << link->length << endl;
            int curX = link->joint.X;
            int curY = link->joint.Y;
            double rad = (double) deg * ((double)PI/(double)180);
            int nextX = curX + (curX*cos(rad) - curX*sin(rad));
            int nextY = curY + (curY*sin(rad) + curY*cos(rad));
            //cout << "   rad = " << rad << endl;
            //cout << "   cos = " << cos(rad) << endl;
            //cout << "   sin = " << sin(rad) << endl;
            link->joint.X = nextX;
            link->joint.Y = nextY;
         }

			break;
		}
	case CCW:
		{
         int deg = amt;
			joint.rotation += deg;
			if (joint.rotation <= joint.range_min)
			{
            // loop back to the end
				joint.rotation = joint.range_max;//joint.range_min;
			}

         // update next link's position based on the current frame's X and Y
         int frameX = joint.X;
         int frameY = joint.Y;
         int linkLen = link->length;
         while ((link = link->next_link) != 0)
         {
            //cout << "   Link len = " << link->length << endl;
            int curX = link->joint.X;
            int curY = link->joint.Y;
            double rad = (double) deg * ((double)PI/(double)180);
            int nextX = curX + (curX*cos(rad) - curX*sin(rad));
            int nextY = curY + (curY*sin(rad) + curY*cos(rad));
            //cout << "   rad = " << rad << endl;
            //cout << "   cos = " << cos(rad) << endl;
            //cout << "   sin = " << sin(rad) << endl;
            link->joint.X = nextX;
            link->joint.Y = nextY;
         }

			break;
      }
	case LEFT:
		{
			joint.X-= x_set;
			while( link->next_link != getBrush())
			{
				link = link->next_link;
				link->joint.X-= x_set;
			}
			getBrush()->joint.X-= x_set;
			break;
		}
	case RIGHT:
		{
			joint.X+= x_set;
			while( link->next_link != getBrush())
			{
				link = link->next_link;
				link->joint.X+= x_set;
			}
			getBrush()->joint.X+= x_set;
			break;
		}
	}
}


