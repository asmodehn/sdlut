#include "SDLConfig.hh"

namespace RAGE
{

    namespace SDL
    {

        Logger Log("RAGE::SDL");

        std::string GetError(void)
        {
            return SDL_GetError();
        }

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
