/*
   Basic main function
 */

#include "robotarm.h"
#include "link.h"
#include "canvas.h"
#include "canvaswidget.h"
#include "window.h"

#include <QApplication>
#include <iostream>

int main(int argc, char* argv[])
{
   QApplication app(argc, argv);
   Window w;
   w.show();

   std::cout << "Starting PaintBot..." << std::endl;
   RobotArm* arm = new RobotArm();

   return app.exec();
}

