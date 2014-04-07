/*
   Basic main function
 */

#include "window.h"
#include "consts.h"
#include "car.h"
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

   // parse args
   int numCars = 0;
   int numLights = 0;
   int c = 0;

   // get command line args
   while((c = getopt (argc, argv, "c:l:")) != -1)
   switch(c)
   {
      case 'c': // number of cars
         numCars = atoi(optarg);
         break;

      case 'l': // number of lights
         numLights = atoi(optarg);
         break; 

      default:
         printUsage();
         exit(1);
   }

   // create the manager to hold the new cars
   Manager* manager = new Manager();

   // create randomly placed cars
   for (int i = 0; i < numCars; i++)
   {
      int x = rand() % (WIDTH-BUFFER*2) + BUFFER;
      int y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
      Position pos(x, y);
      int dir = rand() % 2;
      Car car(pos, (bool) dir);
      manager->addNewCar(car);
   }

   // create randomly placed lights
   for (int i = 0; i < numLights; i++)
   {
      int x = rand() % (WIDTH-BUFFER*2) + BUFFER;
      int y = rand() % (HEIGHT-BUFFER*2) + BUFFER;
      Light pos(x, y);
      manager->addNewLight(pos);
   }

   Window w(manager);
   w.show();

   cout << "Starting Braitenberg Vehicles..." << endl;

   return app.exec();
}

