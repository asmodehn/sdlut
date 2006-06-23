#include "SDLConfig.hh"

namespace RAGE
{

    namespace SDL
    {

        Logger Log("RAGE::SDL");

        std::string GetError(Module mod)
        {
			bool error = false;
			std::string res;
			if (mod == Main)
				res = SDL_GetError();
			if(mod == Net)
#ifdef HAVE_SDLNET
				res = SDLNet_GetError();
#else
				res = "RAGE::SDL not build with SDL_net !"; error=true;
#endif

			if (error)
				res = "Wrong call to RAGE::SDL::GetError()" ;

			return res; // shouldnt happen since we have a default value for mod
        }

namespace TTF{
			std::string GetError()
			{
				std::string res;
#ifdef HAVE_SDLTTF
				res = TTF_GetError();
#else
				res = "RAGE::SDL not build with SDL_ttf !"; error=true;
#endif
				return res;
			}


			//checks if compiled Version is different from 0.0.0
			bool isCompiled()
			{
				Version v;
				return !(v.getcompiledmajor() == 0 && v.getcompiledminor() == 0 && v.getcompiledpatch() == 0);
			}

			//checks if linked version is different from 0.0.0
			bool isLinked()
			{
				Version v;
				return !(v.getlinkedmajor() == 0 && v.getlinkedminor() == 0 && v.getlinkedpatch() == 0);
			}


Version::Version()
        {
#ifdef DEBUG
            Log << nl << "Version::Version() called ...";
#endif
#ifdef HAVE_SDLTTF
            TTF_VERSION(&_compiled);
            _linked.major = TTF_Linked_Version()->major;
            _linked.minor = TTF_Linked_Version()->minor;
            _linked.patch = TTF_Linked_Version()->patch;
#else
			
			_compiled.major = 0;
            _compiled.minor = 0;
            _compiled.patch = 0;
			_linked.major = 0;
            _linked.minor = 0;
            _linked.patch = 0;

#endif
#ifdef DEBUG

            Log << nl << "Version::Version() done.";
#endif

        }

        Version::~Version()
        {
#ifdef DEBUG
            Log << nl << "Version::~Version() called ...";
#endif

#ifdef DEBUG

            Log << nl << "Version::~Version() done.";
#endif

        }
        int Version::getcompiledmajor() const
        {
            return _compiled.major;
        }
        int Version::getcompiledminor() const
        {
            return _compiled.minor;
        }
        int Version::getcompiledpatch() const
        {
            return _compiled.patch;
        }

        int Version::getlinkedmajor() const
        {
            return _linked.major;
        }
        int Version::getlinkedminor() const
        {
            return _linked.minor;
        }
        int Version::getlinkedpatch() const
        {
            return _linked.patch;
        }

		//return true if linked and compiled version are not null and matches exactly
		bool Version::isValid() const
		{
			return isCompiled() && isLinked() && (_linked.major == _compiled.major) && (_linked.minor == _compiled.minor) && (_linked.patch == _compiled.patch);
		}
				
				//return true if linked is not null and superior or equal to compiled
		bool Version::isSupported() const
		{
			return isCompiled() && isLinked() && (_linked.major >= _compiled.major) && (_linked.minor >= _compiled.minor) && (_linked.patch >= _compiled.patch);
		}


        Logger & operator << (Logger& log, const Version & v)
        {
			log << nl << "Compiled ?" << std::boolalpha << isCompiled();
			log << nl << "Linked ?" << std::boolalpha << isLinked();
            log << nl <<"Compiled version: "<< v.getcompiledmajor() <<"."<< v.getcompiledminor() <<"."<< v.getcompiledpatch();
            log << nl << "Linked version: " << v.getcompiledmajor() <<"."<< v.getcompiledminor() <<"."<< v.getcompiledpatch();
			log << nl << "isValid : " << std::boolalpha << v.isValid();
			log << nl << "isSupported : " << std::boolalpha << v.isSupported();
            return log;
        }



		} //namespace TTF


        Version::Version()
        {
#ifdef DEBUG
            Log << nl << "Version::Version() called ...";
#endif

            SDL_VERSION(&_compiled);
            _linked.major = SDL_Linked_Version()->major;
            _linked.minor = SDL_Linked_Version()->minor;
            _linked.patch = SDL_Linked_Version()->patch;
#ifdef DEBUG

            Log << nl << "Version::Version() done.";
#endif

        }

        Version::~Version()
        {
#ifdef DEBUG
            Log << nl << "Version::~Version() called ...";
#endif

#ifdef DEBUG

            Log << nl << "Version::~Version() done.";
#endif

        }
        int Version::getcompiledmajor() const
        {
            return _compiled.major;
        }
        int Version::getcompiledminor() const
        {
            return _compiled.minor;
        }
        int Version::getcompiledpatch() const
        {
            return _compiled.patch;
        }

        int Version::getlinkedmajor() const
        {
            return _linked.major;
        }
        int Version::getlinkedminor() const
        {
            return _linked.minor;
        }
        int Version::getlinkedpatch() const
        {
            return _linked.patch;
        }

        //check if link and compiled matches
        bool Version::check() const
        {
#if SDL_VERSION_ATLEAST(1, 2, 0)
            Log << nl << "Compiled with SDL 1.2 or newer" << std::endl;
#else

            Log << nl << "Compiled with SDL older than 1.2" << std::endl;
#endif

            return (_linked.major == _compiled.major) && (_linked.minor == _compiled.minor) && (_linked.patch == _compiled.patch);
        }

        Logger & operator << (Logger& log, const Version & v)
        {
            log << nl <<"Compiled version: "<< v.getcompiledmajor() <<"."<< v.getcompiledminor() <<"."<< v.getcompiledpatch();
            log << nl << "Linked version: " << v.getcompiledmajor() <<"."<< v.getcompiledminor() <<"."<< v.getcompiledpatch();
            return log;
        }

#if SDL_VERSION_ATLEAST(1, 2, 7)
        bool CPU::hasRDTSC()
        {
            return ( SDL_HasRDTSC() !=0) ;
        }
        bool CPU::hasMMX()
        {
            return (SDL_HasMMX()!=0);
        }
        bool CPU::hasMMXExt()
        {
            return (SDL_HasMMXExt()!=0);
        }
        bool CPU::has3DNow()
        {
            return (SDL_Has3DNow()!=0);
        }
        bool CPU::has3DNowExt()
        {
            return (SDL_Has3DNowExt()!=0);
        }
        //        bool CPU::hasSSE()
        //        {
        //            return (SDL_hasSSE()!=0);
        //        }
        //        bool CPU::hasSSEExt()
        //        {
        //            return (SDL_hasSSEExt()!=0);
        //        }
        bool CPU::hasAltiVec()
        {
            return (SDL_HasAltiVec()!=0);
        }

#endif

    }
}
