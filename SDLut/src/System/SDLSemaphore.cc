#include "System/SDLSemaphore.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

Semaphore::Semaphore(unsigned long initialValue) throw (std::logic_error)
try :
    pvm_sem(SDL_CreateSemaphore(static_cast<Uint32>(initialValue)))
{
    if ( pvm_sem == NULL )
    {
        throw new std::logic_error("SDL_CreateSemaphore() returned NULL !");
    }

}
catch ( std::exception & e )
{
    Log << nl << "Exception caught in Semaphore Constructor !";
    Log << nl << e.what();
}

Semaphore::~Semaphore()
{
    SDL_DestroySemaphore(pvm_sem);
}

bool Semaphore::wait()
{
    return SDL_SemWait(pvm_sem) == 0;
}

bool Semaphore::trywait()
{
    return SDL_SemTryWait(pvm_sem) == 0;
}

bool Semaphore::wait(unsigned long timeout)
{
    return SDL_SemWaitTimeout(pvm_sem, static_cast<Uint32>(timeout) ) == 0;
}

bool Semaphore::post()
{
    return SDL_SemPost(pvm_sem) == 0;
}

unsigned long Semaphore::value()
{
    return static_cast<unsigned long>(SDL_SemValue(pvm_sem));
}


}
}
