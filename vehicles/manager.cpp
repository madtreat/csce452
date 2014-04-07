
#include "manager.h"

#include <iostream>
#include <cmath>

using namespace std;


Manager::Manager()
{
}

Manager::~Manager()
{
}

void Manager::printCarLocs() const
{
}

void Manager::printLightLocs() const
{
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