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
	
   // create randomly placed obstacles

	//Box 1
	int x = rand() % (WIDTH-BUFFER*2) + BUFFER;
	int y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
	Position pos1(x,y);
	manager->setBox1(pos1);
	cout << "Box1: (" << x << ", " << y << ")\n";
	
	//Box 2
	x = rand() % (WIDTH-BUFFER*2) + BUFFER;
	y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
	Position pos2(x,y);
	manager->setBox2(pos2);
	cout << "Box2: (" << x << ", " << y << ")\n";
	
	//Box 3
	x = rand() % (WIDTH-BUFFER*2) + BUFFER;
	y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
	Position pos3(x,y);
	manager->setBox3(pos3);
	cout << "Box3: (" << x << ", " << y << ")\n";
	
   Window w(manager);
   w.show();

   cout << "Starting Robot Motion Planner..." << endl;

   return app.exec();
}

