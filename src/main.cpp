/*
   Basic main function
 */

#include "robotarm.h"
#include "window.h"
#include "link.h"

#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
   QApplication app(argc, argv);
   Window w;
   w.show();

   cout << "Starting PaintBot..." << endl;

   return app.exec();
}

