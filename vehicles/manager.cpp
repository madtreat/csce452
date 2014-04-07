
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

//TODO: Add fringe case for same intense at certain dist
// Update positions of each car in list
void Manager::timeStep()
{
	cout << "TIMESTEP\n";
	printCarLocs();
	printLightLocs();
	
	int anglenum = 4;
	// This is where the math happens!
	for (int i=0; i<cars.size(); i++)
	{
		Car car = cars[i];
		Position s1 = car.getSensorPos(1);
		Position s2 = car.getSensorPos(2);
		cout << "Current Car: " << i <<endl;
		cout << "(" << cars[i].getX() << ", " << cars[i].getY() << ") " << cars[i].getR() << " degs " <<endl;
		int total = 0;
		for (int j=0; j<lights.size(); j++)
		{
			Light light = lights[j];
			cout << "Current Light: " << j <<endl;
			int intense1 = 100/sqrt(pow(s1.X-light.X,2) + pow(s1.Y-light.Y,2));
			int intense2 = 100/sqrt(pow(s2.X-light.X,2) + pow(s2.Y-light.Y,2));
			cout << intense1 << " :: " << intense2 << endl;
			int diff = intense2 - intense1;
			total+=diff;
		}
		cars[i].setR(car.getR() + (total*anglenum));
		cars[i].setX(ceil(cars[i].getX() - 3*(double)cos(cars[i].getR_rad())));
		cars[i].setY(ceil(cars[i].getY() - 3*sin(cars[i].getR_rad())));
		if (cars[i].getX() > WIDTH)
		{
			cars[i].setX(0);
		}
		else if (cars[i].getX() <= 0)
		{
			cars[i].setX(WIDTH);
		}
		if (cars[i].getY() > HEIGHT)
		{
			cars[i].setY(0);
		}
		else if (cars[i].getY() <= 0)
		{
			cars[i].setY(HEIGHT);
		}
		cars[i].calcSensorPos();
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