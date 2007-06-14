#include "System/SDLThread.hh"
#include "SDLConfig.hh"


namespace RAGE
{
	namespace SDL
	{

		unsigned long getCurrentThreadID()
		{
			return static_cast<unsigned long>(SDL_ThreadID());
		}

		unsigned long getThreadID(Thread<class TClass> * t)
		{
			return static_cast<unsigned long>(SDL_GetThreadID(&t->get_rSDL()));
		}
		
		unsigned long runThread(Thread<class TClass> * t,int threadcall (void *), void *data)
		{
			
			t->pvm_thread = SDL_CreateThread(threadcall, data);
		}
		
		int waitThread(Thread<class TClass> * t)
		{
			int status;
			SDL_WaitThread(&t->get_rSDL(),&status);
			return status;
		}
		
		void killThread(Thread<class TClass> * t)
		{
			SDL_KillThread(&t->get_rSDL());
		}

		
	}
}
