#include "SDL.hh"
#include "Logger.hh"
using namespace RAGE;
using namespace RAGE::SDL;

Logger Log("Test Net");


//Main Program
int main(int argc, char** argv)
{

    Logger testlog("Test Log");

    //Setup example

    App::getInstance().setName ("RAGE::SDL test - Network");
    
	
	Log << nl << App::getInstance().init();
	
	Log << nl << App::getInstance().initNet();

	
	return 0;
}


