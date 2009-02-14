#ifndef SDLCONDITION_HH
#define SDLCONDITION_HH

#include "System/SDLMutex.hh"

#include <memory>
#include <stdexcept>

//forward declaration for late time binding...
struct SDL_cond;

namespace RAGE
{
    namespace SDL
    {

        /**
        * \class Condition
        *
        * \ingroup System
        *
        * \brief This class is a wrapper for Condition
        *
        * \author Alex
        *
        * \date 2007/06/14
        *
        * Contact: asmodehn@gna.org
        *
        */

	class Condition
	{
		SDL_cond* pvm_cond;

		public :
			Condition() throw (std::logic_error);
			~Condition();

			inline SDL_cond & get_rSDL() const
			{
				return *pvm_cond;
			}
			
			bool wait (Mutex& mtx);
			//returns true if cond signalled, false otherwise (timeout or error)
			bool wait (Mutex & mtx, unsigned long timeout);
			bool signal ();
			bool broadcast ();
	};

    }
}

#endif
