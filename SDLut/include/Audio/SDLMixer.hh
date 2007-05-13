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

#include "SDLSound.hh"
#include "SDLAudioInfo.hh"

#include <vector>

namespace RAGE
{
	namespace SDL
	{

//This class handle the playing of sounds, and some basic mixing features.
class Mixer
{
	//To store the Hardware audio format
	AudioInfo _hwspec;

	//here we store a converted version of the Sound depending on Audio Specs
	//these are the sound currently being played and their order is not the same as the previous vectors.
	static std::vector<const Sound*> _channels;
	static std::vector<unsigned long>_channelscursor;
	static std::vector<bool> _activechannels;
	static std::vector<bool> _loopchannels;
	static std::vector<int> _channelsvolume;
		
	public:
		//this function is the callback called by the SDL audio framework.
		static void callback(void *userdata, unsigned char *stream, int len);

		
		typedef enum {
			Stopped,
			Playing,
			Paused
		} Status;

		//SDLemulated : runtime dynamic conversion from asked format to obtained format.
		//false to preconvert all sounds.
		//true to preconvert only to asked format. SDL will do runtime conversion if needed for obtained format.
		Mixer(int frequency = 44100,unsigned short channels = 2,unsigned short samples = 512) throw (std::logic_error);
		Mixer(const Mixer& m);
		~Mixer();

		
		//global Audio methods
		std::string getDriverName();
		Status GetStatus();
		void PauseAll(void);
		void PlayAll(void);
		
		//To convert a Sound and store it internally.
		int mixSound(const Sound& sound, bool loop = true, bool autoplay = true, int volume = 100);
		int freeChannel(int index);
		void stopChannel(int index);
		void playChannel(int index);
		void pauseChannel(int index);
		int setChannelsNumber(int);

		//set volume in percent for a channel. NB channel default to max volume
		//returns the old volume
		int setvolumeChannel(int vol, int index);
	
}; //class Mixer

	}
}
#endif

