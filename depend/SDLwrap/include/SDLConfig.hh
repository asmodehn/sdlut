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
#define DEFAULT_WINDOW_ICON "../data/SDL.ico"

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
	    bool useLinked;
	    SDL_version compiled;

	    public:
            Version()
        {
#if SDL_VERSION_ATLEAST(1, 2, 0)
	Log << nl << "Compiled with SDL 1.2 or newer" << std::endl;
#else
	Log << nl << "Compiled with SDL older than 1.2" << std::endl;
#endif
             SDL_VERSION(&compiled);
        }

	    void switchLinked() { useLinked = true ; }
	    void switchCompiled() { useLinked = false ; }

	    int getmajor() { if (useLinked) return SDL_Linked_Version()->major; else return compiled.major; }
	    int getminor() { if (useLinked) return SDL_Linked_Version()->minor; else return compiled.minor; }
	    int getpatch() { if (useLinked) return SDL_Linked_Version()->patch; else return compiled.patch; }

	    //check if link and compiled matches
	    bool check() {return SDL_Linked_Version()->major == compiled.major && SDL_Linked_Version()->minor == compiled.minor && SDL_Linked_Version()->patch == compiled.patch;}

	    void debug()
	    {
	        bool oldLinkflag = useLinked;
	        switchCompiled();
	        Log << nl <<"Compiled version: "<< getmajor() <<"."<< getminor() <<"."<< getpatch();
            switchLinked();
            Log << nl << "Linked version: " << getmajor() <<"."<< getminor() <<"."<< getpatch();
            useLinked = oldLinkflag;
        }
	};

	static Version version;

}
#endif
