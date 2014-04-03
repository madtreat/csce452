Texas A&M University - CSCE 452
===============================
# Robotics and Spatial Intelligence

##PaintBot Projects
Project 1: Create a PaintBot program with 3 links, 2 revolute joints and a prismatic joint.

Project 2: Using the PaintBot in Project 1, add world controls using Inverse Kinematics.

Project 3: Convert Project 2 to a tele-operated (via a network) system, with optional delay.

##Braitenberg Vehicle Projects
Project 4: Create a Braitenberg Vehicle system.

Project 5: Currently undefined.

##Notes:
This project requires OpenGL installed on this machine to be run.
```bash
- # On Ubuntu
- $ sudo apt-get install libgles2-mesa-dev
```

This project uses CMake as a build tool.  (Must be version 2.8.9 or higher)
```bash
- # On Ubuntu
- $ sudo apt-get install cmake
```

	
This project uses qt5 for the graphical interface.
- Download the latest library from http://qt-project.org/downloads
- Be sure to select the library that includes OpenGL
	

##Execution:
To build out of source (recommended),
execute the following steps from the root directory of the project:
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

and to run an executable (from the build directory):
```bash
# to run the paintbot executable
$ ./paintbot/paintbot
# to run the braitenberg vehicles executable
$ ./vehicles/vehicles
```

arguments:
- -s [port]          - Run as server on [port]
- -c [host] [port]   - Run as client connecting to [host] on [port]
- -d [delay]         - Add delay in [delay] seconds.  If -s or -c does not exist, run as standard with no connections.  NOTE: -s and -c can not be used at the same time.
