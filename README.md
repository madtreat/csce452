csce452project1
===============

Project 1 for CSCE 452 - Create a PaintBot program with 3 links, 2 revolute joints and a prismatic joint.

Notes:
This project requires OpenGL installed on this machine to be run.
   # On Ubuntu
   $ sudo apt-get install libgles2-mesa-dev

This project uses CMake as a build tool.  (Must be version 2.8.9 or higher)
   # On Ubuntu
   $ sudo apt-get install cmake
	
	
This project uses qt5 for the graphical interface.
	Download the latest library from http://qt-project.org/downloads
	Be sure to select the library that includes OpenGL
	

To build out of source (recommended),
execute the following steps from the root directory of the project:
   $ mkdir build
   $ cd build
   $ cmake ..
   $ make

and to run the project (from the build directory):
   $ ./src/paintbot

arguments:
   -s [port]         Run as server on [port]
   -c [host] [port]  Run as client connecting to [host] on [port]
   -d [delay]        Add delay in [delay] seconds
                     If -s or -c does not exist run as standard with no connections
                     -s and -c can not be used at the same time
