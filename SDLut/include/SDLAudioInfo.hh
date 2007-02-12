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

//declarign SDL_type for late binding
struct SDL_AudioSpec;

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
			explicit AudioInfo(const SDL_AudioSpec* as);
			
			~AudioInfo(void);

		public :

	
			int frequency();
			unsigned int format();
			unsigned int channels();
			unsigned long samples();
			void* userdata();


	
	
	}; //class Audio


	} // namespace SDL
} // namespace RAGE



#endif
