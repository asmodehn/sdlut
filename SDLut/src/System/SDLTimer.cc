#include "System/SDLTimer.hh"
#include "System/SDLNewTimer.hh"
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
		    SDL_TimerID res = SDL_AddTimer(max(interval,1),static_cast<SDL_NewTimerCallback>(callback),param);
		    
#ifdef DEBUG
			if ( res != 0) { Log << nl << "SDL_Timer " << res << " launched." ; }
			else { Log << nl << "SDL_Timer " << res << " launch FAILED !"; }
#endif
		    
		    return res;
	    }
	    
	    bool RemoveGlobalTimer(SDL_TimerID t)
	    {
		    if ( SDL_RemoveTimer(t) == SDL_TRUE )
		    {
#ifdef DEBUG
			Log << nl << "SDL_Timer " << t << " aborted.";
#endif
			return true;
		    }
		    return false;
	    }


		
   }
}
