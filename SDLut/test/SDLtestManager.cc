
/* Test program to try managing initialization and quit for SDL
*/

#include "SDL.hh"
using namespace SDLut;

using namespace RAGE;

int main(int argc, char *argv[])
{
    RAGE::Logger testlog("testManager");

    App::getInstance().setName ("SDLut Functionnal testing - Manager");

    testlog << nl << " Init minimal... " ;
    testlog << ( (App::getInstance().init()) ? "OK": "FAILED" ) << std::endl;

    Manager manager= App::getInstance().getManager();
    testlog << nl << manager;

    return 0;
}

