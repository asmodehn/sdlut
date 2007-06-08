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
#include "Audio/SDLMixer.hh"

#include "SDLSoundImpl.hh"
#include "SDLChannelImpl.hh"
#include "SDLAudioInfo.hh"

#include <vector>

namespace RAGE
{
	namespace SDL
	{

//This class handle the playing of sounds, and some basic mixing features.
class MixerImpl : public MixerIf
{
	//To store the Hardware audio format
	AudioInfo _hwspec;

	//here we store a converted version of the Sound depending on Audio Specs
	//these are the sound currently being played and their order is not the same as the previous vectors.
	static std::vector<ChannelImpl*> pvm_channels;
	
	public:
		//this function is the callback called by the SDL audio framework.
		static void callback(void *userdata, unsigned char *stream, int len);

		//SDLemulated : runtime dynamic conversion from asked format to obtained format.
		//false to preconvert all sounds.
		//true to preconvert only to asked format. SDL will do runtime conversion if needed for obtained format.
		MixerImpl(int frequency = 44100,unsigned short channels = 2,unsigned short samples = 512) throw (std::logic_error);
		MixerImpl(const MixerImpl& m);
		virtual ~MixerImpl();

		
		bool isMIXImpl() { return false;}
	
		//global Audio methods
		std::string getDriverName();

		//TO REMOVE BEGIN
		//Status GetStatus();
		void PauseAll(void);
		void PlayAll(void);
		//TO REMOVE END

		//TO IMPLEMENT
		bool isPlaying(int index) {return true;}
		//TO IMPLEMENT
		bool isPaused(int index) {return true;}

		//TO IMPLEMENT
		int playChannel(const SoundIf& sound, int volumepct = 100, int loops = 0, int fadeintime = 0, int index = -1) {return 0;}
		
		//To convert a Sound and store it internally.
		int mixSound(const SoundIf& sound, bool loop = true, bool autoplay = true, unsigned short volumepct = 100);

		//TO REMOVE
		ChannelImpl & getChannel(int index);

		void pauseChannel(int index) {}
		void resumeChannel(int index) {}
		int stopChannel(int index, int fadeouttime = 0) {return 0;}

		//TO REMOVE
		int freeChannel(int index);
		
		int setChannelsNumber(int);

		
		bool playMusic(const MusicIf& music, int volumepct = 100, int loops = 1, int fadeintime = 0, int index = -1) {return true;}

		void pauseMusic() {}
		void resumeMusic() {}
		void rewindMusic() {}
		bool setMusicPosition(double pos) {return true;}
		int setMusicVolume( int volumepct ) { return 0; }
		
		bool stopMusic( int fadeouttime = 0) {return true;}
	
}; //class Mixer

	}
}
#endif

