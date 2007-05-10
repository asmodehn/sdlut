
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
	testlog << SDL::App::getInstance().getMixer().GetStatus();

	//TODO : play something here

	//if argument we load the sound
	if ( argc > 1)
	{
		testlog << nl<<  "Loading sound";
		//SDL::Sound wavefile(argv[1]);
		
		testlog << nl<<  "setting mixer channels";
		int wav_channel_1 = SDL::App::getInstance().getMixer().mixSound(SDL::Sound(argv[1]), false, false);
		//int wav_channel_1 = SDL::App::getInstance().getMixer()->mixSound(wavefile,true, false);
		//int wav_channel_2 = SDL::App::getInstance().getMixer()->mixSound(wavefile,false, false);
		
		testlog << nl<<  "playing channel 1";
		SDL::App::getInstance().getMixer().playChannel(wav_channel_1);
		SDL::Delay(1000);

		//testlog << nl<<  "playing channel 2";
		//SDL::App::getInstance().getMixer()->toggleChannel(wav_channel_2);

		SDL::Delay(1000);
		//SDL::App::getInstance().getMixer()->freeChannel(wav_channel_2);
		SDL::App::getInstance().getMixer().freeChannel(wav_channel_1);
	}

	return 0;
}
