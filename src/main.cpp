/*
   Basic main function
 */

#include "robotarm.h"
#include "link.h"
#include "canvas.h"

#include <iostream>

int main(int argc, char* argv[])
{
   std::cout << "Starting PaintBot..." << std::endl;
   RobotArm* arm = new RobotArm();
   Canvas* canvas = new Canvas(argc, argv);

   return 0;
}

