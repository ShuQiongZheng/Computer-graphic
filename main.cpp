#include <QApplication>
#include <QVBoxLayout>
#include "Window.h"

int main(int argc, char *argv[])
{
     QApplication app(argc, argv);
     Window *window = new Window(NULL);

     // resize the window
     window->resize(512, 612);


     // show the label
     window->show();

     // start it running
     app.exec();

     // clean up
     //	delete controller;
     delete window;
	
     // return to caller 
     return 0;
 
     } // main()

