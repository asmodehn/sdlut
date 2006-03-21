#include "SDL.hh"
using namespace RAGE;
using namespace RAGE::SDL;




//Main Program
int main(int argc, char** argv)
{

    Logger testlog("Test Log");
    App::getInstance().setName ("SDLtest");
    App::getInstance().initVideo(false,false,true,false);

	RWOps iconfile("data/SDL_icon.bmp","rb");

	iconfile.dumpCode("SDL_icon.c","_defaultIcon");


    return 0;
}


