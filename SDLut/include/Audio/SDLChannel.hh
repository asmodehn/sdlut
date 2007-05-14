#ifndef SDL_CHANNEL_HH
#define SDL_CHANNEL_HH

/**
 * \class Channel
 *
 * \ingroup Audio
 *
 * \brief Class handling a Channel in a mixer
 *
 * \author Alex
 *
 * \date 2006/09/01
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLSound.hh"

namespace RAGE
{
	namespace SDL
	{

class Channel
{
	
	const Sound * pvm_sound;
	unsigned long pvm_cursor;
	int pvm_volume;
	bool pvm_playing;
	bool pvm_loop;

	friend class Mixer;
	
	protected :
	Channel(const Sound * s, bool loop, bool autoplay, unsigned short volpct);

	public :
		
	~Channel();

	void play();
	void pause();
	void stop();
	//returns old volume absolute value
	int setVolume(unsigned short volpct);

	bool isPlaying() { return pvm_playing; }
		

	
};

	}
}

#endif // SDL_CHANNEL_HH
