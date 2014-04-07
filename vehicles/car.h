
#ifndef CAR_H_
#define CAR_H_

#include "consts.h"
#include <vector>


class Car;
typedef std::vector<Car> Cars;

class Car {
public:
   Car(Position _pos = Position(), bool _directMapping = 1);
   ~Car();

   void     setX(int _x) {pos.X = _x;}
   void     setY(int _y) {pos.Y = _y;}
   void     setPos(Position _pos) {pos = _pos;}
   void     setDirect(bool _direct) {direct = _direct;}

   int      getX()	   const {return pos.X;}
   int      getY()	   const {return pos.Y;}
	int		getR()	   const {return rotation;}
	double	getR_rad()  const {return (double)rotation * (PI/180.0);}		//Rotation in radians
	bool		getDirect() const {return direct;}

   void     calcSensorPos();
   Position getSensorPos(int _sensor) const;

private:
   int      length;  // pixels
   int      width;   // pixels
   int      speed;   // pixels per second
	int		rotation;// degrees (0 = right)

   int      sensorOffsetLength; // 
   int      sensorOffsetWidth;
   int      THETA;   // angle defining sensor positions

   Position pos;
   Sensor   sensor1;
   Sensor   sensor2;

   // True:		(Direct)
   //   wheels1 <--> sensor1
   //   wheels2 <--> sensor2
   // False:	(Inverse)
   //   wheels1 <--> sensor2
   //   wheels2 <--> sensor1
   bool     direct;
};

#endif

