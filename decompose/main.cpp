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
	
	
   Window w(manager);
   w.show();

   cout << "Starting Braitenberg Vehicles..." << endl;

   return app.exec();
}

