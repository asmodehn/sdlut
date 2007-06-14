#include "System/SDLMutex.hh"
#include "SDLConfig.hh"

namespace RAGE
{
	namespace SDL
	{

		Mutex::Mutex()
		: pvm_mutex(SDL_CreateMutex())
		{
		}
		
		Mutex::~Mutex()
		{
			SDL_DestroyMutex(pvm_mutex);
		}

		bool Mutex::lock()
		{
			return SDL_LockMutex(pvm_mutex) == 0;
		}
		
		bool Mutex::unlock()
		{
			return SDL_UnlockMutex(pvm_mutex) == 0;
		}
		
	}
}
