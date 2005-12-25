#ifndef SDLCONFIG_HH
#define SDLCONFIG_HH

//Forced Config
//#undef HAVE_OPENGL //engine call seems to work... 3D part postponed...
#undef THREAD

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma warning(disable:4290)	// Disable MSVC++ warning: C4290: C++ exception specification ignored.
#endif

//Normal Setup
#define DEFAULT_DISPLAY_WIDTH 640
#define DEFAULT_DISPLAY_HEIGHT 480
#define DEFAULT_DISPLAY_BPP 0 //0 for current display pixel mode
//beware ! 0 only usable for Display Surface, not for RGB ones !!
#define DEFAULT_WINDOW_TITLE "My own SDL program"
#define DEFAULT_WINDOW_ICON "../data/SDL_icon.bmp"

#define DEFAULT_RGB_WIDTH 640
#define DEFAULT_RGB_HEIGHT 480
#define DEFAULT_RGB_BPP 16 //0 for current display pixel mode


//Mandatory
#include <SDL.h>
//Mandatory because we also wrap OpenGL
//TODO : NO_OPENGL option in build
#include <SDL_opengl.h>

//Conditionals

#ifdef THREAD
#include <SDL_thread.h>
#endif

#if SDL_VERSION_ATLEAST(1, 2, 7)
#include "SDL_cpuinfo.h"
#endif

//utils
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "Logger.hh"

//Debug Constants
#define SDLUserInput_DEBUG

/**
 * \class SDLConfig
 *
 * \ingroup Other
 *
 * \brief This class gather the common objects that all the SDL classes have to be able to access...
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

namespace SDL
{
	static Logger Log("SDLwrap");

	static inline std::string GetError(void) { return SDL_GetError(); }

	class Version
	{
	    SDL_version _compiled;
	    SDL_version _linked;

	    public:
            Version()
        {
          SDL_VERSION(&_compiled);
          _linked.major = SDL_Linked_Version()->major;
          _linked.minor = SDL_Linked_Version()->minor;
          _linked.patch = SDL_Linked_Version()->patch;
        }

	    int getcompiledmajor() const {return _compiled.major; }
	    int getcompiledminor() const {return _compiled.minor; }
	    int getcompiledpatch() const {return _compiled.patch; }

	    int getlinkedmajor() const { return _linked.major; }
	    int getlinkedminor() const { return _linked.minor; }
	    int getlinkedpatch() const { return _linked.patch; }

	    //check if link and compiled matches
	    bool check() const
	    {
#if SDL_VERSION_ATLEAST(1, 2, 0)
				Log << nl << "Compiled with SDL 1.2 or newer" << std::endl;
#else
				Log << nl << "Compiled with SDL older than 1.2" << std::endl;
#endif
	    	return (_linked.major == _compiled.major) && (_linked.minor == _compiled.minor) && (_linked.patch == _compiled.patch);
			}

	    friend Logger & operator << (Logger& log, const Version & v)
	    {
	        log << nl <<"Compiled version: "<< v.getcompiledmajor() <<"."<< v.getcompiledminor() <<"."<< v.getcompiledpatch();
            log << nl << "Linked version: " << v.getcompiledmajor() <<"."<< v.getcompiledminor() <<"."<< v.getcompiledpatch();
            return log;
        }
	};

#if SDL_VERSION_ATLEAST(1, 2, 7)
    class CPU
    {
        public:
        static inline bool hasRDTSC() { return SDL_HasRDTSC();}
        static inline bool hasMMX() { return SDL_HasMMX();}
        static inline bool hasMMXExt() { return SDL_HasMMXExt(); }
        static inline bool has3DNow() { return SDL_Has3DNow(); }
        static inline bool has3DNowExt() { return SDL_Has3DNowExt(); }
        //static inline bool hasSSE() { return SDL_hasSSE();}
        //static inline bool hasSSEExt() { return SDL_hasSSEExt();}
        static inline bool hasAltiVec() { return SDL_HasAltiVec();}

    };
#endif
	static Version version;

}
#endif
