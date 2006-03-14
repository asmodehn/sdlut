#include "SDLRWOps.hh"

namespace RAGE {
	namespace SDL{

		RWOps::RWOps() throw (std::logic_error)
		try : _rwops(NULL)
		{
			if(NULL==(_rwops=SDL_AllocRW()))
				throw std::logic_error("Initialising empty RWOps failed");

		}
		catch (std::exception & e)
		{
			Log << "Exception cought in RWOps Constructor : " << e.what();
		};


		RWOps::RWOps(const std::string & file, const char *mode) throw (std::logic_error)
				try : _rwops(NULL)
		{
			if(NULL==(_rwops=SDL_RWFromFile(file.c_str(),mode)))
				throw std::logic_error("Initialising RWOps from " + file +" failed");

		}
		catch (std::exception & e)
		{
			Log << "Exception cought in RWOps Constructor : " << e.what();
		};

		RWOps::RWOps(FILE *fp, int autoclose) throw (std::logic_error)
				try : _rwops(NULL)
		{
			if(NULL==(_rwops=SDL_RWFromFP(fp,autoclose)))
				throw std::logic_error("Initialising RWOps from FP failed");

		}
		catch (std::exception & e)
		{
			Log << "Exception cought in RWOps Constructor : " << e.what();
		};

		RWOps::RWOps(void *mem, int size) throw (std::logic_error)
			try : _rwops(NULL)
		{
			if(NULL==(_rwops=SDL_RWFromMem(mem,size)))
				throw std::logic_error("Initialising RWOps from mem failed");

		}
		catch (std::exception & e)
		{
			Log << "Exception cought in RWOps Constructor : " << e.what();
		};
		
		RWOps::RWOps(const void *mem, int size) throw (std::logic_error)
			try : _rwops(NULL)
		{
			if(NULL==(_rwops=SDL_RWFromConstMem(mem,size)))
				throw std::logic_error("Initialising RWOps from const mem failed");

		}
		catch (std::exception & e)
		{
			Log << "Exception cought in RWOps Constructor : " << e.what();
		};

		RWOps::~RWOps()
		{
			SDL_FreeRW(_rwops);
		}
	}
}