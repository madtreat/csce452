
#ifndef CAR_H_
#define CAR_H_

struct Position {
   int X;
   int Y;
   Position(int _x = 0; int _y = 0) : X(_x), Y(_y);
};

class Car {
public:
   Car(Position _pos, bool _directMapping = 1);
   ~Car();

   void     calcSensorPos(int _sensor);
   Position getSensorPos(int _sensor);

private:
   int      length;  // pixels
   int      width;   // pixels
   int      speed;   // pixels per second

   int      sensorOffsetLength; // 
   int      sensorOffsetWidth;
   int      THETA;   // angle defining sensor positions

   Position pos;
   Position sensor1;
   Position sensor2;

   // True:
   //   wheels1 <--> sensor1
   //   wheels2 <--> sensor2
   // False:
   //   wheels1 <--> sensor2
   //   wheels2 <--> sensor1
   bool     direct;
};

#endif

