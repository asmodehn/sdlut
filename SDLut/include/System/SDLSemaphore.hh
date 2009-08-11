#ifndef SDLSEMAPHORE_HH
#define SDLSEMAPHORE_HH

#include <memory>
#include <stdexcept>

//forward declaration for late time binding...
typedef struct SDL_semaphore SDL_sem;

namespace RAGE
{
namespace SDL
{

/**
* \class Semaphore
*
* \ingroup System
*
* \brief This class is a wrapper for Semaphore
*
* \author Alex
*
* \date 2007/06/14
*
* Contact: asmodehn@gna.org
*
*/

class Semaphore
{
    SDL_sem* pvm_sem;

public :
    Semaphore(unsigned long initialValue = 0) throw (std::logic_error);
    ~Semaphore();

    inline SDL_sem & get_rSDL() const
    {
        return *pvm_sem;
    }

    //returns true on success, false on error
    bool wait(); //blocking wait

    //returns true on success, false on failure or error
    bool trywait(); //non blocking wait

    //returns true on success, false on failure or error
    bool wait(unsigned long timeout); //blocking wait with timeout

    //returns true on success, false on error
    bool post();

    //return the current value of the semaphore
    unsigned long value();
};
}
}

#endif
