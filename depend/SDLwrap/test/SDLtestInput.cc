#include "SDLwrap.hh"

using namespace SDL;

int main( int argc, char* argv[])
{
    Logger testlog ("SDLtestInput");

    testlog << nl << "Test Input Started !" << std::endl;
    App::getInstance().setName ("SDLtestInput");

    testlog << nl << "Initialising Window..." << std::endl;
	App::getInstance().initWindow(false,false,true,false);

	testlog << nl << "Displaying Window..." << std::endl;
    App::getInstance().getAppWindow()->reset(640,480);

    testlog << nl << "Main Loop..." << std::endl;
    App::getInstance().mainLoop();


}
