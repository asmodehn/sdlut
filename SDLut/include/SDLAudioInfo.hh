#ifndef SDL_AUDIO_HH
#define SDL_AUDIO_HH

/**
 * \class Audio
 *
 * \ingroup Audio
 *
 * \brief handles AudioSpec
 *
 * \author Alex
 *
 * \date 2006/09/01
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLConfig.hh"

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
		


	//This class handle the Audio Device.
	//Only one instance of this class should be used.
	class AudioInfo
	{
		friend class Mixer;
		friend class Sound;
		
		
		///> to store true if the spec is actually emulated by SDL.
		bool pointerCopy;

		protected :

			const SDL_AudioSpec * const _spec;
			
			//Copy Constructor from SDL_AudioSpec
			//This handle explicit casts
			explicit AudioInfo(const SDL_AudioSpec* as): _spec(as)
			{
				pointerCopy = true;
			}
			
			~AudioInfo(void) { if (!pointerCopy) delete _spec; }

		public :

	
			int frequency()
			{
				return _spec->freq;
			}

			unsigned int format()
			{
				return _spec->format;
			}

			unsigned int channels()
			{
				return _spec->channels;
			}

			unsigned long samples()
			{
				return _spec->samples;
			}

			void* userdata()
			{
				return _spec->userdata;
			}


	
	
	}; //class Audio


	} // namespace SDL
} // namespace RAGE



#endif
