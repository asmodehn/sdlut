
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
		testlog << nl<<  "Loading sound";
		SDL::Sound wavefile(argv[1]);
		
		testlog << nl<<"playing...";
		SDL::App::getInstance().getMixer()->Play();
		
		testlog << nl<<  "setting mixer channels";
		int wav_channel_1 = SDL::App::getInstance().getMixer()->mixSound(wavefile, false);
		int wav_channel_2 = SDL::App::getInstance().getMixer()->mixSound(wavefile, false);
		
		testlog << nl<<  "playing channel 1";
		SDL::App::getInstance().getMixer()->toggleChannel(wav_channel_1);
		SDL::Delay(1000);

		testlog << nl<<  "playing channel 2";
		SDL::App::getInstance().getMixer()->toggleChannel(wav_channel_2);
		SDL::Delay(6000);
	}

	return 0;
}
