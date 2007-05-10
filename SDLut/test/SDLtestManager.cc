
/* Test program to try managing initialization and quit for SDL
*/

#include "SDL.hh"
using namespace RAGE;

int main(int argc, char *argv[])
{
	Logger testlog("testManager");

	SDL::App::getInstance().setName ("RAGE::SDL Functionnal testing - Manager");

	testlog << nl << " Init minimal... " ;
	testlog << ( (SDL::App::getInstance().init()) ? "OK": "FAILED" ) << std::endl;

	SDL::Manager manager= SDL::App::getInstance().getManager();
	testlog << nl << manager;

	return 0;
}

