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

   AppType    type = SERVER;
   QString address = "localhost";
   int        port = 51315;
   int       delay = 2;
   
   // parse args
   ConnectionInfo info;
   info.type   = type;
   info.host   = QHostAddress(address);
   info.port   = (quint16) port;
   info.delay  = delay;

   Window w(info);
   w.show();

   cout << "Starting PaintBot..." << endl;

   return app.exec();
}

