cmake_minimum_required(VERSION 2.8.9)
project(paintbot)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

set(SOURCES
   main.cpp
   base.cpp
   brush.cpp
   canvas.cpp
   joint.cpp
   link.cpp
   robotarm.cpp
)

set(HEADERS
   base.h
   brush.h
   canvas.h
   joint.h
   link.h
   robotarm.h
)

#set(HEADERS_NO_MOC)

add_executable(paintbot ${SOURCES} ${HEADERS})
target_link_libraries(paintbot
   ${OPENGL_LIBRARIES}
   ${GLUT_LIBRARY}
)
