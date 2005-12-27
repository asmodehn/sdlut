#include "SDLwrap.hh"

using namespace SDL;

//TODO :akeyboard, mouse, joystick,and general handler that measure some stats on event handling, critical or not.

int main( int argc, char* argv[])
{
    Logger testlog ("SDLtestInput");

    testlog << nl << "Test Input Started !" << std::endl;
    App::getInstance().setName ("SDLtestInput");

//EVENTS INITIALISED ALONG WITH VIDEO... Think about initializins the event by default, without actually creating the window...
    testlog << nl << "Initialising Window..." << std::endl;
	App::getInstance().initWindow(false,false,true,false);

	testlog << nl << "Displaying Window..." << std::endl;
    App::getInstance().getAppWindow()->reset(640,480);

    testlog << nl << "Main Loop..." << std::endl;
    App::getInstance().mainLoop();


}
