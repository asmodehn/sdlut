
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
		testlog << nl<<  "Loading sound";
		SDL::Sound sndfile(argv[1]);

		int chan = SDL::App::getInstance().getMixer().playChannel(sndfile);
		testlog << nl<<  "playing channel " << chan;

		SDL::Delay(3000);

		SDL::App::getInstance().getMixer().stopChannel(chan);

	}

	return 0;
}
