csce452project1
===============

Project 1 for CSCE 452 - Create a PaintBot program with 3 links, 2 revolute joints and a prismatic joint.

Notes:
This project requires OpenGL installed on this machine to be run.
   # On Ubuntu
   $ sudo apt-get install libgles2-mesa-dev

This project uses CMake as a build tool.  
   # On Ubuntu
   $ sudo apt-get install cmake

To build out of source (recommended),
execute the following steps from the root directory of the project:
   $ mkdir build
   $ cd build
   $ cmake ..
   $ make

and to run the project:
   $ ./src/paintbot

