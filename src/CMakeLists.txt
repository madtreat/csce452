cmake_minimum_required(VERSION 2.8.9)
project(paintbot)

set(SOURCES
   main.cpp
   robotarm.cpp
   link.cpp
   base.cpp
   brush.cpp
)

set(HEADERS
   robotarm.h
   utils.h
   link.h
   base.h
   brush.h
)

#set(HEADERS_NO_MOC)

add_executable(paintbot ${SOURCES} ${HEADERS})
#target_link_libraries(paintbot
# openGL lib
#)
