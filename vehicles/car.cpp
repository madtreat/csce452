
#include "car.h"
#include <cmath>

Car::Car(Position _pos, bool _directMapping)
: length(16),
width(9),
speed(5),
sensorOffsetLength( (int) (length/2) + 3),
sensorOffsetWidth(2),
pos(_pos),
direct(_directMapping)
{
   double numer = (double) (sensorOffsetWidth);
   double denom = (double) (sensorOffsetLength);
   THETA = (int) atan( numer / denom );
}

Car::~Car()
{
}

void Car::calcSensorPos()
{
   sensor1.X = pos.X + (sensorOffsetLength * sin(THETA));
   sensor1.Y = pos.Y - (sensorOffsetWidth * cos(THETA)); // minus for coordinate frame

   sensor2.X = pos.X + (sensorOffsetLength * sin(THETA));
   sensor2.Y = pos.Y + (sensorOffsetWidth * cos(THETA)); // plus for coordinate frame
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

