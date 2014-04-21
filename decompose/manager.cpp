
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

// Called from window
void Manager::timeStep()
{
	
}

// Find a path from robot to destination, avoiding obstacles
void Manager::generatePath()
{
   // Step 1: decompose free space into cells
   Cells cells = decompose();


   // Step 2: generate connectivity graph


   // Step 3: find a path from robot to destination


   // Complete!
}

Cells Manager::decompose()
{
}

