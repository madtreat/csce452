
#include "manager.h"

#include <iostream>
#include <cmath>

using namespace std;


Manager::Manager()
{
	cars = Cars();
	lights = Lights();
}

Manager::~Manager()
{
}

// Update positions of each car in list
void Manager::timeStep()
{
	cout << "TIMESTEP\n";
	//addNewCar(Car());
	printCarLocs();
	// This is where the math happens!
	for (int i=0; i<cars.size(); i++)
	{
		
	}
}

void Manager::printCarLocs() const
{
	cout << "Cars:\n";
	for (int i=0; i<cars.size(); i++)
	{
		cout << "\t" << i << ": (" << cars[i].getX() << ", " << cars[i].getY() << ") " << cars[i].getR() << " degs ";
		if (cars[i].getDirect())
			cout << "[Direct]" << endl;
		else
			cout << "[Inverse]" << endl;
	}
}

void Manager::printLightLocs() const
{
	cout << "Lights:\n";
	for (int i=0; i<lights.size(); i++)
	{
		cout << "\t" << i << ": (" << lights[i].getX() << ", " << lights[i].getY() << ")" << endl;
	}
}

void Manager::addNewCar(Car car)
{
   cars.push_back(car);
}

void Manager::addNewLight(Light light)
{
   lights.push_back(light);
}

void Manager::deleteCar(int car)
{
   cars.erase(cars.begin() + car - 1);
}

void Manager::deleteLight(int light)
{
   lights.erase(lights.begin() + light - 1);
}

void Manager::updateCarPos(int carID, int newX, int newY, bool directMapping)
{
   Car car = cars[carID];
   car.setX(newX);
   car.setY(newY);
   car.setDirect(directMapping);
}

void Manager::updateLightPos(int lightID, int newX, int newY)
{
   Light light = lights[lightID];
   light.X = newX;
   light.Y = newY;
}