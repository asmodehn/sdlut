#ifndef SDL_SOUND_HH
#define SDL_SOUND_HH

/**
 * \class Sound
 *
 * \ingroup Audio
 *
 * \brief Class handling a sound
 *
 * \author Alex
 *
 * \date 2006/09/01
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLAudioInfo.hh"
#include "SDLRWOps.hh"
#include <string>
#include <stdexcept>
#include <map>

namespace RAGE
{
	namespace SDL
	{

//classes interaction :
//Sound doesnt know Audio, or Mixer.
// 1 -
//Audio doesnt need to know Sound, and doesnt know Mixer either.
//Mixer knows them both to make them work together.
// 2 - better...
//Audio doesnt know Sound, but knows Mixer, and can send it the Specs on creation time.
//Mixer Doesnt know Audio, but knows Sound.

//TODO : Redesign to have the same design scheme as the Video : AudioInfo and Mixer like VideoInfo and Window... (callback in Mixer, but similar creation scheme)
//Might choose 1 instead of 2...
		

	//This class stores a Sound (original - not converted to Audio format yet )
	class Sound
{/*
		//total number of sound (internal SDL)
	static int resourcecount;
		//index of the current Sound (internal SDL reference)
	int resourceindex;*/

	friend class Mixer;

	AudioInfo _aInfo;

	//should be shared to decrease memory usage.
	std::auto_ptr<RWOps> pvm_OriginalData;

	//true if this sound has already been converted.
	bool converted;
	//Length and data of the Sound
	unsigned long _length;
	unsigned char *_buf;

	//manage if the sound is looping after it end
	bool _loop_status;

	public:

		//Sound Loader
		Sound(std::string filename, bool loop_status = false) throw (std::logic_error);
		//Sound Copy ( careful with conversion )
		Sound( const Sound & s)  throw (std::logic_error);
		//Sound destructor
		~Sound();

		bool Convert (unsigned short DestinationFormat,unsigned short DestinationChannels,int DestinationFrequency);
		
	
};//class Sound

	}
}

#endif
