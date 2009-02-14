#include "System/SDLScopedLock.hh"
#include "SDLConfig.hh"

namespace RAGE
{
	namespace SDL
	{

		ScopedLock::ScopedLock(Mutex& mtx) throw(std::logic_error)
		try : pvm_mutex(mtx)
		{
			if (! pvm_mutex.lock())
				throw std::logic_error(" Failed Lock !");
		}
		catch (std::exception &e)
        {
            Log << nl << "Exception catched in ScopedLock Constructor !"  << nl <<
            e.what() << nl << GetError() << std::endl;
        }
		
		ScopedLock::~ScopedLock()
		{
			if (! pvm_mutex.unlock())
				Log << nl << " Failed Unlock !" << std::endl;
		}
		
	}
}
