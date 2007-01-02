
/* Test program to try the Audio wrapper
*/

#include <stdio.h>

#include "SDL.hh"
using namespace RAGE;

int main(int argc, char *argv[])
{
	Logger testlog("testAudio");

	testlog << nl << "initAudio()";
	testlog << SDL::App::getInstance().initAudio();

	testlog << nl <<"getStatus()";
	testlog << SDL::App::getInstance().getMixer()->GetStatus();

	//TODO : play something here

	//if argument we load the sound
	if ( argc > 1)
	{
		testlog << nl<<  "creating sound";
		SDL::Sound wavefile(argv[1]);
		testlog << nl<<"mixing Sound";
		SDL::App::getInstance().getMixer()->mixSound(wavefile);
		testlog << nl<<"play";
		SDL::App::getInstance().getMixer()->Play();
		SDL::Delay(6000);
	}
	//otherwise we dont use any.


	return 0;
}
