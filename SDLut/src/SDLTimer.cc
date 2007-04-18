#include "SDLTimer.hh"
#include "SDLConfig.hh"

namespace RAGE
{
    namespace SDL
    {
	    
	//Simple SDL_delay implementation
	    void Delay(long millisec)
	    {
		    SDL_Delay((millisec));
	    }
	    long GetTicks()
	    {
		    return static_cast<long>(SDL_GetTicks());
	    }

	    
	    SDL_TimerID AddGlobalTimer(unsigned int interval, unsigned int callback(unsigned int,void*) , void *param)
	    {
		    return SDL_AddTimer(interval,static_cast<SDL_NewTimerCallback>(callback),param);
	    }
	    
	    bool RemoveGlobalTimer(SDL_TimerID t)
	    {
		    return SDL_RemoveTimer(t) == SDL_TRUE;
	    }


		
   }
}
