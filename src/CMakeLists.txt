cmake_minimum_required(VERSION 2.8.9)
project(paintbot)

set(SOURCES
   main.cpp
   base.cpp
   brush.cpp
   joint.cpp
   link.cpp
   robotarm.cpp
)

set(HEADERS
   base.h
   brush.h
   joint.h
   link.h
   robotarm.h
)

#set(HEADERS_NO_MOC)

add_executable(paintbot ${SOURCES} ${HEADERS})
#target_link_libraries(paintbot
# openGL lib
#)
