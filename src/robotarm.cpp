/*
Implements a specific configuration of the robot arm.
*/

#include "robotarm.h"
#include "joint.h"
#include "link.h"
#include "base.h"
#include "brush.h"

RobotArm::RobotArm()
{
	// Create the links of this paintbot, including predecessors
	Base*  base  = new Base(300);
	Link*  link1 = new Link(Joint(PRISMATIC, 0, 300), 150, base);
	Link*  link2 = new Link(Joint(REVOLUTE, 0, 360), 100, link1);
	Link*  link3 = new Link(Joint(REVOLUTE, 0, 360), 75, link2);
	Brush* brush = new Brush(link3);

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
}

RobotArm::~RobotArm()
{
	for (int i = 0; i < NUM_LINKS + 2; i++)
		delete links[i];
}

Link* RobotArm::getLink(int link)
{
	if (link < 0 || link > NUM_LINKS + 1)
		return 0;

	if (link == 0)
		return getBase();

	if (link == NUM_LINKS + 1)
		return getBrush();

	return links[link];
}

void RobotArm::moveJoint(Link* link, Motion motion)
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
			joint.rotation++;
			if (joint.rotation >= joint.range_max)
			{
				joint.rotation = joint.range_max;
			}
			break;
		}
	case CCW:
		{
			joint.rotation--;
			if (joint.rotation <= joint.range_min)
			{
				joint.rotation = joint.range_min;
			}
			break;
	case LEFT:
		{
			joint.X-= x_set;
			while( link->next_link != brush)
			{
				link = link->next_link;
				link->joint.X-= x_set;
			}
			brush.X-= x_set;
			break;
		}
	case RIGHT:
		{
			joint.X+= x_set;
			while( link->next_link != brush)
			{
				link = link->next_link;
				link->joint.X+= x_set;
			}
			brush.X+= x_set;
			break;
		}
	}
}
}


