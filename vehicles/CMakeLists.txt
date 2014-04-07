project(vehicles)

# Open GL dependencies
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

# Qt 4 dependencies
#find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)

# Qt 5 dependencies
site_name(host)
if (APPLE)
   message(STATUS "Setting CMAKE_PREFIX_PATH for Madison")
   message(STATUS "   SITE_NAME = " ${host})
   # Mac only (for Madison)
   # machine name: maka
   set(CMAKE_PREFIX_PATH /opt/local/share/qt5/5.2.1/clang_64/lib/cmake)
elseif(${host} STREQUAL "violeta-VirtualBox")
   message(STATUS "Setting CMAKE_PREFIX_PATH for Violeta")
   # for Violeta
   # machine name: violeta-VirtualBox
   set(CMAKE_PREFIX_PATH /home/violeta/Qt5.2.1/5.2.1/gcc_64/lib/cmake)
elseif(${host} STREQUAL "ubuntu")
   message(STATUS "Setting CMAKE_PREFIX_PATH for Matthew")
   # for Matthew
   # machine name: ubuntu
   set(CMAKE_PREFIX_PATH /home/user/Qt5.2.1/5.2.1/gcc/lib/cmake)
endif()

find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Network)
find_package(Qt5OpenGL)
set(CMAKE_AUTOMOC ON)
#include(${QT_USE_FILE})

# List of source files
set(SOURCES
   main.cpp
   canvas.cpp
   canvaswidget.cpp
   car.cpp
	manager.cpp
   window.cpp
)

# List of header files used
# NOTE:  this list EXCLUDES the header files that define Qt subclasses
#        as they require some processing first.  They should be in HEADERS_MOC.
set(HEADERS
   canvas.h
   car.h
   consts.h
	manager.h
)

# Necessary for Qt to compile
set(HEADERS_MOC
   canvaswidget.h
   window.h
)

# Resources (.qrc file(s), contains locations to icons, stylesheets, etc.)
set(RESOURCES
   resources.qrc
)

# Use the appropriate resources
qt5_add_resources(RESOURCES_ADDED ${RESOURCES} )
set_source_files_properties(${RESOURCES_ADDED} PROPERTIES GENERATED ON)

# Create the executable
add_executable(vehicles 
   ${SOURCES} 
   ${HEADERS} 
   ${MOC_SRC} 
   ${RESOURCES_ADDED}
)

# Link to the correct/necessary libraries
target_link_libraries(vehicles
   ${QT_LIBRARIES}
   ${OPENGL_LIBRARIES}
   ${GLUT_LIBRARY}
)

# Link proper Qt Modules to the executable
qt5_use_modules(vehicles
   Widgets
   Core
   Gui
   Network
   OpenGL
)

