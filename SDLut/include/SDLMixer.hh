#ifndef SDL_MIXER_HH
#define SDL_MIXER_HH

/**
 * \class Mixer
 *
 * \ingroup Audio
 * 
 * \author Alex
 *
 * \date 2006/09/01
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLConfig.hh"
#include "SDLSound.hh"
#include "SDLAudioInfo.hh"


namespace RAGE
{
	namespace SDL
	{

//This class handle the playing of sounds, and some basic mixing features.
class Mixer
{
	//To store the Hardware audio format
	AudioInfo * _hwspec;

	bool _autoConvert;
	
	//here we store a converted version of the Sound depending on Audio Specs
	//these are the sound currently being played and their order is not the same as the previous vectors.
	static std::vector<const Sound*> _channels;
	static std::vector<int>_channelscursor;
	static std::vector<bool> _activechannels;
	static std::vector<bool> _loopchannels;

		
	public:
		//this function is the callback called by the SDL audio framework.
		static void callback(void *userdata, Uint8 *stream, int len);

		
		typedef enum {
			Stopped = SDL_AUDIO_STOPPED,
			Playing = SDL_AUDIO_PLAYING,
			Paused = SDL_AUDIO_PAUSED
		} Status;

		//SDLemulated : runtime dynamic conversion from asked format to obtained format.
		//false to preconvert all sounds.
		//true to preconvert only to asked format. SDL will do runtime conversion if needed for obtained format.
		Mixer(int frequency = 44100,unsigned short channels = 2,unsigned short samples = 512, bool SDLemulated = false);
		Mixer(const Mixer& m);
		~Mixer();

		
		//global Audio methods
		std::string getDriverName();
		Status GetStatus();
		void PauseAll(void) { SDL_PauseAudio(1); }
		void PlayAll(void) { SDL_PauseAudio(0); }
		
		//To convert a Sound and store it internally.
		int mixSound(const Sound& sound, bool loop = true, bool autoplay = true);
		int freeChannel(int index);
		void stopChannel(int index);
		void playChannel(int index);
		void pauseChannel(int index);
		int setChannelsNumber(int);
	
}; //class Mixer

	}
}
#endif

