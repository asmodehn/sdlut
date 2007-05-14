#include "Audio/SDLChannel.hh"

#include "SDLConfig.hh"

namespace RAGE
{
	namespace SDL
	{

		Channel::Channel(const Sound * s, bool loop, bool autoplay, unsigned short volpct)
			: pvm_sound(s), pvm_cursor(0), pvm_playing(autoplay), pvm_loop(loop)
		{
			setVolume(volpct);
		}
			
		Channel::~Channel()
		{
			delete pvm_sound, pvm_sound = NULL;
		}

		
		void Channel::play()
		{
			pvm_playing = true;
		}
		
		void Channel::pause()
		{
			pvm_playing = false;
		}

		void Channel::stop()
		{
			pvm_playing = false;
			pvm_cursor = 0;
		}

		int Channel::setVolume(unsigned short volpct)
		{
			int res = pvm_volume;
			pvm_volume = static_cast<int>(volpct) * SDL_MIX_MAXVOLUME / 100;
			return res;
		}

	}
}
