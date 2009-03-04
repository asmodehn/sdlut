#include "System/SDLTimer.hh"
#include "System/SDLNewTimer.hh"
#include "SDLConfig.hh"

namespace RAGE
{
    namespace SDL
    {
	    //Mutex TimerMtx;

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
			//TimerMtx.lock();
			SDL_TimerID res = SDL_AddTimer(std::max<unsigned int>(interval,1),static_cast<SDL_NewTimerCallback>(callback),param);
			//TimerMtx.unlock();
		    
#ifdef DEBUG
			if ( res != 0) { Log << nl << "Tick " << GetTicks() << " SDL_Timer " << res << " launched." ; }
			else { Log << nl << "Tick " << GetTicks() << "SDL_Timer " << res << " launch FAILED !"; }
#endif
		    
		    return res;
	    }
	    
	    bool RemoveGlobalTimer(SDL_TimerID t)
	    {
			//TimerMtx.lock();
		    if ( SDL_RemoveTimer(t) == SDL_TRUE )
		    {
				//TimerMtx.unlock();
#ifdef DEBUG
			Log << nl << "Tick " << GetTicks()<< "SDL_Timer " << t << " aborted.";
#endif
			return true;
		    }
			//TimerMtx.unlock();
#ifdef DEBUG
			Log << nl << "Tick " << GetTicks()<< "SDL_Timer " << t << " not aborted.";
#endif
		    return false;
	    }


		
   }
}
