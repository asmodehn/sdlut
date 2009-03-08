#ifndef SDLMUTEX_HH
#define SDLMUTEX_HH

//forward declaration for late time binding...
struct SDL_mutex;

namespace RAGE
{
    namespace SDL
    {

        /**
        * \class Mutex
        *
        * \ingroup System
        *
        * \brief This class is a wrapper for Mutex
        *
        * \author Alex
        *
        * \date 2007/06/14
        *
        * Contact: asmodehn@gna.org
        *
        */

//TODO : check, maybe it s possible to inline everything ( lighter SDL interface ? )

	class Mutex
	{
		SDL_mutex* pvm_mutex;
		
		public :
			Mutex();
			~Mutex();

			inline SDL_mutex & get_rSDL() const
			{
				return *pvm_mutex;
			}
			
			bool lock();
			bool unlock();
	};

    } // SDL
}// RAGE

#endif
