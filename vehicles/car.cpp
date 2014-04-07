
#include "car.h"
#include <cmath>

#include <iostream>
using namespace std;

Car::Car(Position _pos, bool _directMapping)
: length(16),
width(9),
speed(5),
rotation(90),
sensorOffsetLength( (int) (length/2) + 3),
sensorOffsetWidth(3),
pos(_pos),
direct(_directMapping)
{
   double numer = (double) (sensorOffsetWidth);
   double denom = (double) (sensorOffsetLength);
   THETA = atan( numer / denom );
	calcSensorPos();
}

Car::~Car()
{
}

void Car::calcSensorPos()
{
	double rot_rad = getR_rad();
	int dist = sqrt(pow(sensorOffsetLength,2)+pow(sensorOffsetWidth,2));
	
   sensor1.X = pos.X - (dist * cos(-(THETA+rot_rad)));
   sensor1.Y = pos.Y + (dist * sin(-(THETA+rot_rad))); // minus for coordinate frame

   sensor2.X = pos.X - (dist * cos(-(-THETA+rot_rad)));
   sensor2.Y = pos.Y + (dist * sin(-(-THETA+rot_rad))); // plus for coordinate frame
	
	cout << "s(T) " << sin(THETA) << endl;
	cout << "c(T) " << cos(THETA) << endl;
	cout << "Car S1: (" << sensor1.X << ", " << sensor1.Y << ")" <<endl;
	cout << "Car S2: (" << sensor2.X << ", " << sensor2.Y << ")" <<endl;
}

Position Car::getSensorPos(int _sensor) const
{
   switch(_sensor)
   {
      case 1:
         return sensor1;
         break;
      case 2:
         return sensor2;
         break;
      default:
         return Position();
         break;
   }
}

