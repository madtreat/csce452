/*
   Basic main function
 */

#include "robotarm.h"
#include "link.h"

#include <iostream>

int main(int argc, char* argv[])
{
   std::cout << "Starting PaintBot..." << std::endl;
   RobotArm* arm = new RobotArm();

   return 0;
}

