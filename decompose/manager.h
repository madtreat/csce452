
#ifndef MANAGER_H_
#define MANAGER_H_

#include "consts.h"

class Manager
{

public:
   Manager();
   ~Manager();
   
	void timeStep();
   void generatePath();
	
   void printCarLocs() const;
   void printLightLocs() const;

   Cars     getCars() const {return cars;}
   Lights   getLights() const {return lights;}

   Car      getCar(int i) const {if (i >= cars.size()) return Car(); else return cars[i];}
   Light    getLight(int i) const {if (i >= lights.size()) return Light(); else return lights[i];}

   int  numCars() const {return cars.size();}
   int  numLights() const {return lights.size();}
	
	void addNewCar(Car car);
   void addNewLight(Light light);
   void deleteCar(int car);
   void deleteLight(int light);
   void updateCarPos(int car, int newX, int newY, bool directMapping);
   void updateLightPos(int light, int newX, int newY);
	
private:
   Cars     cars;    // list of cars
   Lights   lights;  // list of lights
};

#endif

