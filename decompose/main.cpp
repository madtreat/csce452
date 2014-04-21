/*
   Basic main function
 */

#include "window.h"
#include "consts.h"
#include "manager.h"

#include <QApplication>
#include <QDebug>

#include <cmath>
#include <iostream>
#include <unistd.h>

using namespace std;

void printUsage()
{
   cout << "Usage: vehicles (-c num_cars) (-l num_lights)" << endl;
   cout << "   Where" << endl; 
   cout << "         -c    Number of cars to create initially" << endl;
   cout << "         -l    Number of lights to create initially" << endl;
}

int main(int argc, char* argv[])
{
   QApplication app(argc, argv);

   // create the manager
   Manager* manager = new Manager();
	
   // Create randomly placed obstacles

	// Box 1
	int x = rand() % (WIDTH-BUFFER*2) + BUFFER;
	int y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
	Position pos1(x,y);
	manager->setBox1(pos1);
	cout << "Box1: (" << x << ", " << y << ")\n";
	
	// Box 2
	x = rand() % (WIDTH-BUFFER*2) + BUFFER;
	y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
	Position pos2(x,y);
	manager->setBox2(pos2);
	cout << "Box2: (" << x << ", " << y << ")\n";
	
	// Box 3
	x = rand() % (WIDTH-BUFFER*2) + BUFFER;
	y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
	Position pos3(x,y);
	manager->setBox3(pos3);
	cout << "Box3: (" << x << ", " << y << ")\n";
	
	// Robot
	bool collision = true;
	while (collision)
	{
		collision = false;
		x = rand() % (WIDTH-BUFFER*2) + BUFFER;
		y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
		// Box 1
		if (	 x < manager->getBox1().X+(BOX1_SIZE/2) && x > manager->getBox1().X-(BOX1_SIZE/2))
			if (y < manager->getBox1().Y+(BOX1_SIZE/2) && y > manager->getBox1().Y-(BOX1_SIZE/2))
				collision = true;
		// Box 2
		if (	 x < manager->getBox2().X+(BOX2_SIZE/2) && x > manager->getBox2().X-(BOX2_SIZE/2))
			if (y < manager->getBox2().Y+(BOX2_SIZE/2) && y > manager->getBox2().Y-(BOX2_SIZE/2))
				collision = true;
		// Box 3
		if (	 x < manager->getBox3().X+(BOX3_SIZE/2) && x > manager->getBox3().X-(BOX3_SIZE/2))
			if (y < manager->getBox3().Y+(BOX3_SIZE/2) && y > manager->getBox3().Y-(BOX3_SIZE/2))
				collision = true;
	}
	Position posR(x,y);
	manager->setRobot(posR);
	
	// Destination
	collision = true;
	while (collision)
	{
		collision = false;
		x = rand() % (WIDTH-BUFFER*2) + BUFFER;
		y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
		// Box 1
		if (	 x < manager->getBox1().X+(BOX1_SIZE/2) && x > manager->getBox1().X-(BOX1_SIZE/2))
			if (y < manager->getBox1().Y+(BOX1_SIZE/2) && y > manager->getBox1().Y-(BOX1_SIZE/2))
				collision = true;
		// Box 2
		if (	 x < manager->getBox2().X+(BOX2_SIZE/2) && x > manager->getBox2().X-(BOX2_SIZE/2))
			if (y < manager->getBox2().Y+(BOX2_SIZE/2) && y > manager->getBox2().Y-(BOX2_SIZE/2))
				collision = true;
		// Box 3
		if (	 x < manager->getBox3().X+(BOX3_SIZE/2) && x > manager->getBox3().X-(BOX3_SIZE/2))
			if (y < manager->getBox3().Y+(BOX3_SIZE/2) && y > manager->getBox3().Y-(BOX3_SIZE/2))
				collision = true;
	}
	Position posD(x,y);
	manager->setDest(posD);
	
   Window w(manager);
   w.show();

   cout << "Starting Robot Motion Planner..." << endl;

   return app.exec();
}

