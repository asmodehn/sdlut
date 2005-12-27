#include "SDLwrap.hh"

using namespace SDL;

int main( int argc, char* argv[])
{
    Logger testlog ("SDLtestInput");

    App::getInstance().setName ("SDLtestInput");
	App::getInstance().initWindow(false,false,true,false);
    App::getInstance().getAppWindow()->reset(640,480);
    App::getInstance().mainLoop();


}
