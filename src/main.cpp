/*
   Basic main function
 */

#include "robotarm.h"
#include "window.h"
#include "link.h"

#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
   QApplication app(argc, argv);
   Window w;
   w.show();

   cout << "Starting PaintBot..." << endl;
   /*RobotArm* arm = new RobotArm();
   cout << "old position for link 3: " << arm->getLink(3)->joint.X << " " << arm->getLink(3)->joint.Y << endl;
   arm->moveJoint(arm->getLink(2), CW, 70);
   cout << "new position for link 3: " << arm->getLink(3)->joint.X << " " << arm->getLink(3)->joint.Y << endl;
   arm->moveJoint(arm->getLink(2), CCW, 70);
   cout << "new position for link 3: " << arm->getLink(3)->joint.X << " " << arm->getLink(3)->joint.Y << endl;
   arm->moveJoint(arm->getLink(2), CCW, 70);
   cout << "new position for link 3: " << arm->getLink(3)->joint.X << " " << arm->getLink(3)->joint.Y << endl;*/

   return app.exec();
}

