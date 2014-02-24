project(paintbot)

# Open GL dependencies
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIR})

# Qt 4 dependencies
#find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)

# Qt 5 dependencies
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5OpenGL)
set(CMAKE_AUTOMOC ON)
#include(${QT_USE_FILE})

# List of source files
set(SOURCES
   main.cpp
   base.cpp
   brush.cpp
   canvas.cpp
   canvaswidget.cpp
   joint.cpp
   link.cpp
   robotarm.cpp
   window.cpp
)

# List of header files used
# NOTE:  this list EXCLUDES the header files that define Qt subclasses
#        as they require some processing first.  They should be in HEADERS_MOC.
set(HEADERS
   base.h
   brush.h
   canvas.h
   joint.h
   link.h
   robotarm.h
)

# Necessary for Qt to compile
set(HEADERS_MOC
   canvaswidget.h
   window.h
)
#QT4_WRAP_CPP(MOC_SRC ${HEADERS_MOC})

# Create the executable
add_executable(paintbot ${SOURCES} ${HEADERS} ${MOC_SRC})

# Link to the correct/necessary libraries
target_link_libraries(paintbot
   ${QT_LIBRARIES}
   ${OPENGL_LIBRARIES}
   ${GLUT_LIBRARY}
)

# Link proper Qt Modules to the executable
qt5_use_modules(paintbot
   Widgets
   Core
   Gui
   OpenGL
)

