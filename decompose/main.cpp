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
#include <time.h>

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
	
	srand(time(NULL));

   // create the manager
   Manager* manager = new Manager();
	
   // Create randomly placed obstacles
	Position pos;
	for (int i=0; i<NUM_BOXES; i++)
	{	
		do {
			int x = rand() % (WIDTH-BUFFER*2) + BUFFER;
			int y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
			pos = Position(x,y);
		}
		while (manager->isCollision(pos) != -1);
		manager->setBox(i, pos);
		cout << "Box " << i << ": (" << manager->getBox(i).pos.X << ", " << manager->getBox(i).pos.Y << ")\n";
	}
	
	// Set box sizes
	manager->setBoxSize(0, BOX0_SIZE);
	manager->setBoxSize(1, BOX1_SIZE);
	manager->setBoxSize(2, BOX2_SIZE);
	
	// Robot
	do {
		int x = rand() % (WIDTH-BUFFER*2) + BUFFER;
		int y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
		pos = Position(x,y);
	}
	while (manager->isCollision(pos) != -1);
	manager->setRobot(pos);
	
	// Destination
	do {
		int x = rand() % (WIDTH-BUFFER*2) + BUFFER;
		int y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
		pos = Position(x,y);
	}
	while (manager->isCollision(pos) != -1);
	manager->setDest(pos);
	
	
   Window w(manager);
   w.show();

   cout << "Starting Robot Motion Planner..." << endl;

   return app.exec();
}

