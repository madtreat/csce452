/*
   Basic main function
 */

#include "robotarm.h"
#include "window.h"
#include "link.h"
#include "stdio.h"
#include "stdlib.h"
#include <QApplication>
#include <QDebug>
#include <iostream>
#include <unistd.h>

using namespace std;

void printUsage()
{
   cout << "Usage: paintbot (-s | -c) (-h host) (-p port) (-d delay)" << endl;
   cout << "   Where" << endl; 
   cout << "         -s    Run as a server" << endl;
   cout << "         -c    Run as a client" << endl;
   cout << "         -p    Use the port given" << endl;
   cout << "                  REQUIRED FOR: server, client" << endl;
   cout << "         -h    Use the host address given" << endl;
   cout << "                  REQUIRED FOR: client" << endl;
   cout << "         -d    Use the delay given" << endl;
   cout << "                  OPTIONAL" << endl;
   cout << "   Note that if no -s or -c argument is specified, this will run as" << endl;
   cout << "   a basic (connectionless) standalone application" << endl;
}

int main(int argc, char* argv[])
{
   QApplication app(argc, argv);

   AppType    type = SERVER;
   QString address = "";
   int        port = 0;
   int       delay = 0;
   bool server = false; 
   bool client = false; 
   // parse args
   int c;

   // get command line args
   while((c = getopt (argc, argv, "scd:p:h")) != -1)
      switch(c) {
         case 's': // run as server using port 
            server = true; 
            cout <<" in server"<<endl; 
            break;

         case 'c': // run client using host n port 
            client = true; 
            cout << "in client"<<endl; 
            break;

         case 'd': // initialize delay
            delay = atoi(optarg);
            cout<< " delay = "<<delay<<endl;
            break;

         case 'p': // port 
            port = atoi(optarg);
            cout<< " port = "<<port<<endl; 
            break; 

         case 'h': // set up the host 
            address = optarg; 
            qDebug() <<" address ="<<address; 
            break; 

         default:
            abort();
      }

   if (server && client)
   {
      printUsage();
      return 1;
   }

   if(server && port == 0)
   {
      cout << "Invalid server configuration" << endl << endl;
      printUsage();
      return 1;
   }

   if(client && (port == 0 || address == "" ))
   {
      cout << "Invalid client configuration" << endl << endl;
      printUsage();
      return 1;
   }

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

