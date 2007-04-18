#include "SDLAudioInfo.hh"
#include "SDLConfig.hh"

namespace RAGE
{
	namespace SDL
	{

		//class AudioInfo

			//Copy Constructor from SDL_AudioSpec
			//This handle explicit casts
		AudioInfo::AudioInfo(const SDL_AudioSpec* as): _spec(as)
		{
		}
			
		AudioInfo::~AudioInfo(void)
		{
			delete _spec;
		}

		
		int AudioInfo::frequency()
		{
			return _spec->freq;
		}

		unsigned int AudioInfo::format()
		{
			return _spec->format;
		}

		unsigned int AudioInfo::channels()
		{
			return _spec->channels;
		}

		unsigned long AudioInfo::samples()
		{
			return _spec->samples;
		}

		void* AudioInfo::userdata()
		{
			return _spec->userdata;
		}



		


		
		
	} //namespace SDL
}//namespace RAGE
