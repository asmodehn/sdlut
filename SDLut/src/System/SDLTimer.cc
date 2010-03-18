#include "System/SDLTimer.hh"
#include "System/SDLNewTimer.hh"
#include "SDLConfig.hh"

using namespace RAGE;

namespace SDLut
{
namespace system
{

Mutex TimerMtx;

void TimerLog(const std::string& text)
{
    ScopedLock lock(TimerMtx);
    Log << nl << text << std::endl;
}



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
    if ( res != 0)
    {
        Log << nl << "Tick " << GetTicks() << " SDL_Timer " << res << " launched." ;
    }
    else
    {
        Log << nl << "Tick " << GetTicks() << "SDL_Timer " << res << " launch FAILED !";
    }
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


//NewTimer implementatino

NewTimer::NewTimer()
        : m_timerid(0), m_cb(0), m_args(0)
{
}

NewTimer::NewTimer(const NewTimer & nt)
        : m_timerid(0), m_cb(0), m_args(0)
{
}


NewTimer::~NewTimer()
{
    //ALWAYS BE SURE THE TIMER IS HALTED BEFORE TRYING TO DESTRUCT IT !!
    abort();
    //TODO : think of a way to "detach" it. Destruct the Timer object, but keep the timer running... have a look at boost threads...

    //Callback and argument delete should be handled by auto_ptr...


}

bool NewTimer::start(SDL_TimerID *& tid,unsigned int interval, unsigned int callback(unsigned int,void*) , void *param)
{
    if (m_cb.get())
    {
        //ScopedLock lock(mtx);

        //no argument s here so we are using normal Adapter
        m_timerid = AddGlobalTimer(interval,callback,param);
        tid = &m_timerid;
    }
    return (m_timerid != 0 );
}


//return true if abort successful. return false if abortion failed ( the timer may already have stopped for example )
bool NewTimer::abort()
{
    //TODO, find the meaning of error / success if timer already finished ? or never existed ?
    bool res = true;
    if ( m_timerid!= 0 )
    {
        //ScopedLock lock(mtx);
        res = RemoveGlobalTimer(m_timerid);
        m_timerid = 0;
    }
    return res;
}



}
}
