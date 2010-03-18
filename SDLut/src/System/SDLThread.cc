#include "System/SDLThread.hh"
#include "System/SDLNewThread.hh"
#include "SDLConfig.hh"


namespace SDLut
{
namespace SDL
{

unsigned long getCurrentThreadID()
{
    return static_cast<unsigned long>(SDL_ThreadID());
}

unsigned long getThreadID(SDL_Thread * sdlt)
{
    return static_cast<unsigned long>(SDL_GetThreadID(sdlt));
}

void runThread(SDL_Thread *& sdlt,int threadcall (void *), void *data)
{

    sdlt = SDL_CreateThread(threadcall, data);
}

int waitThread(SDL_Thread * sdlt)
{
    int status;
    SDL_WaitThread(sdlt,&status);
    return status;
}

//Not portable, doesnt work anymore, and shouldnt be used anyway
//void killThread(SDL_Thread * sdlt)
//{
//	SDL_KillThread(sdlt);
//}


}
}
