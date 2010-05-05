#include "System/SDLCondition.hh"
#include "SDLConfig.hh"

using namespace Core;

namespace SDLut
{
namespace system
{

Condition::Condition() throw (std::logic_error)
try :
    pvm_cond(SDL_CreateCond())
{
    if ( pvm_cond == NULL )
    {
        throw new std::logic_error("SDL_CreateCond() returned NULL !");
    }

}
catch ( std::exception & e )
{
    Log << nl << "Exception caught in Condition Constructor !";
    Log << nl << e.what();
}

Condition::~Condition()
{
    SDL_DestroyCond(pvm_cond);
}


bool Condition::wait (Mutex & mtx)
{
    return SDL_CondWait(pvm_cond,&mtx.get_rSDL()) == 0;
}

bool Condition::wait (Mutex & mtx, unsigned long timeout)
{
    return SDL_CondWaitTimeout(pvm_cond,&mtx.get_rSDL(), static_cast<Uint32>(timeout)) == 0;
}

bool Condition::signal ()
{
    return SDL_CondSignal(pvm_cond) == 0;
}

bool Condition::broadcast ()
{
    return SDL_CondBroadcast(pvm_cond) == 0;
}


}
}
