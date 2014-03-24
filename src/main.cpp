/*
   Basic main function
 */

#include "robotarm.h"
#include "window.h"
#include "link.h"

#include <QApplication>
#include <iostream>

using namespace std;

void printUsage()
{
   cout<<"paintbot (-s |-c) (-h host) (-p port) (-d delay)"<<endl;
   //cout<<"  Where"<<endl; 
    	
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
  while((c = getopt (argc, argv, "s:h:p:c:d:")) != -1)
    switch(c) {
      case 's': // run as server using port 
        server = true; 
        break;

      case 'c': // run client using host n port 
        client = true; 
        break;

      case 'd': // initialize delay
        delay = atoi(optarg);
        break;

      case 'p': // port 
        port = atoi(optarg);
	break; 

      case 'h': // set up the host 
	 address = optarg; 
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
	printUsage();
	return 1;
	}

    if(client && (port == 0 || address == "" ))
	{
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

