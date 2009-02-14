#ifndef SDLSCOPEDLOCK_HH
#define SDLSCOPEDLOCK_HH

#include "System/SDLMutex.hh"

#include <stdexcept>

namespace RAGE
{
    namespace SDL
    {

        /**
        * \class ScopedLock
        *
        * \ingroup System
        *
        * \brief This class is a wrapper for Mutex, with RAII design
        *
        * \author Alex
        *
        * \date 2007/06/14
        *
        * Contact: asmodehn@gna.org
        *
        */

	class ScopedLock //TODO need to prevent copy here...
	{
		Mutex& pvm_mutex;
		
		public :
			ScopedLock(Mutex& mtx) throw (std::logic_error);
			~ScopedLock();			
	};
    }
}

#endif
