cmake_minimum_required(VERSION 2.8.9)
project(paintbot)

set(SOURCES
)

set(HEADERS
   armconfig.h
)

#set(HEADERS_NO_MOC)

add_executable(paintbot ${SOURCES} ${HEADERS})
target_link_libraries(paintbot
# openGL lib
)
