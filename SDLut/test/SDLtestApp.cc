
/* Test program to try Application management...
*/

#include "SDL.hh"
using namespace SDLut;
using namespace SDLut::system;
using namespace RAGE;

int main(int argc, char *argv[])
{
    RAGE::Logger testlog("testApp");

    App::getInstance().setName ("SDLut::SDL Functionnal testing - App");

    //Minimum Init
    testlog << nl << " Minimum init... " << std::endl;
    testlog << ( (App::getInstance().init())? "OK" : "FAILED" );

    //Video Init
    testlog << nl << " Enabling Video... " << std::endl;
    testlog << ( (App::getInstance().initVideo(false,false,false))? "OK" : "FAILED" );

    //Audio Init
    testlog << nl << " Enabling Audio... " << std::endl;
    testlog << ( (App::getInstance().initAudio())? "OK" : "FAILED" );

    //Timer Init
    testlog << nl << " Enabling Timer... " << std::endl;
    testlog << ( (App::getInstance().initTimer())? "OK" : "FAILED" );

#ifdef WK_SDLTTF_FOUND
    //Font Init
    testlog << nl << " Enabling Text... " << std::endl;
    testlog << ( (App::getInstance().initText())? "OK" : "FAILED" );
#endif

    Delay(10000);
    return 0;
}

