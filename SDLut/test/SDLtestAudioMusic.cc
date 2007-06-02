
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

	//if argument we load the sound
	if ( argc > 1)
	{
		testlog << nl<<  "Loading music";
		SDL::Music sndfile(argv[1]);

		SDL::App::getInstance().getMixer().playMusic(sndfile);
		testlog << nl<<  "playing music ";

		SDL::Delay(3000);

		SDL::App::getInstance().getMixer().stopMusic();

	}

	return 0;
}
