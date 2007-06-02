#ifndef SDLMIXEREXTEND_HH
#define SDLMIXEREXTEND_HH

#include "Audio/Default/SDLMixerImpl.hh"
#include "SDLSoundExtend.hh"
#include "SDLMusicExtend.hh"

namespace RAGE
{
namespace SDL
{

//if SDL_Mixer is used, provide a class to be used as a bridge.
//this way the client doesnt have to take care of which function is available
#ifdef HAVE_SDLMIXER

	//TODO : verify the meaning of samples and chunksize depending on mix or default. just to make sure...
	class MixerExtend : public MixerIf
	{
		int numtimesopened;
		int frequency;
		int channels;
		unsigned short format;

		private:
		bool QuerySpec();
		
		public:
		MixerExtend(int frequency ,unsigned short channels ,unsigned short samples) throw (std::logic_error);
		virtual ~MixerExtend();
		
		bool isMIXImpl() { return true;}

		//get the actual frequency used ( conversion auto )
		int GetFrequencyUsed();
		//get the actual channels number used ( conversion auto )
		int GetChannelsUsed();
		//get the number of times the device has been opened
		int GetTimesDevOpen();
		
		std::string getDriverName();
		int NbrChannelsPlaying();
		int NbrChannelsPaused();
		bool isPlaying(int whichchannel);
		bool isPaused(int whichchannel);
		bool isFadingIn(int whichchannel);
		bool isFadingOut(int whichchannel);

		//To play a sound on a Channel.
		int playChannel(const SoundIf& sound, int volumepct = 100, int loops = 1, int fadeintime = 0, int index = -1);
		
		void pauseChannel(int index);
		void pauseAllChannels() { pauseChannel(-1); }
		
		void resumeChannel(int index);
		void resumeAllChannels() { return resumeChannel(-1); }
		
		int stopChannel(int index, int fadeouttime = 0);
		int stopAllChannels(int fadeouttime = 0) { return stopChannel(-1, fadeouttime); }
		
		int setChannelsNumber(int nbr);

		//To play a music
		bool playMusic(const MusicIf& music, int volumepct = 100, int loops = 1, int fadeintime = 0, int index = -1);

		void pauseMusic();
		void resumeMusic();
		void rewindMusic();
		bool setMusicPosition(double pos);
		//TODO
		//void setMusicCMD();

		bool stopMusic(int fadeouttime = 0);
	
		

		
	};

	
#endif
}
}
#endif

