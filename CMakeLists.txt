cmake_minimum_required(VERSION 2.8.07)
project(paintbot)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

add_subdirectory(paintbot)
add_subdirectory(vehicles)

