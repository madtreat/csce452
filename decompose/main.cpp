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
	for (int i=0; i<NUM_BOXES; i++)
	{
		int x = rand() % (WIDTH-BUFFER*2) + BUFFER;
		int y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
		Position pos(x,y);
		manager->setBox(i, pos);
		cout << "Box " << i << ": (" << x << ", " << y << ")\n";
	}
	
	// Set box sizes
	manager->setBoxSize(0, BOX0_SIZE);
	manager->setBoxSize(1, BOX1_SIZE);
	manager->setBoxSize(2, BOX2_SIZE);
	
	// Robot
	Position posR;
	do
	{
		int x = rand() % (WIDTH-BUFFER*2) + BUFFER;
		int y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
		posR = Position(x,y);
	}
	while (manager->isCollision(posR) != -1);
	manager->setRobot(posR);
	
	// Destination
	Position posD;
	do
	{
		int x = rand() % (WIDTH-BUFFER*2) + BUFFER;
		int y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
		posD = Position(x,y);
	}
	while (manager->isCollision(posD) != -1);
	manager->setDest(posD);
	
	
   Window w(manager);
   w.show();

   cout << "Starting Robot Motion Planner..." << endl;

   return app.exec();
}

