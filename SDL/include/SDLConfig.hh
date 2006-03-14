#ifndef SDL_CONFIG_HH
#define SDL_CONFIG_HH

//Forced Config
//#undef HAVE_OPENGL //engine call seems to work... 3D part postponed...
#undef THREAD

//Normal Setup
#define DEFAULT_DISPLAY_WIDTH 640
#define DEFAULT_DISPLAY_HEIGHT 480
#define DEFAULT_DISPLAY_BPP 0 //0 for current display pixel mode
//beware ! 0 only usable for Display Surface, not for RGB ones !!
#define DEFAULT_WINDOW_TITLE "RAGE::SDL"
#define DEFAULT_WINDOW_ICON "data/SDL_icon.bmp"

#define DEFAULT_RGB_WIDTH 640
#define DEFAULT_RGB_HEIGHT 480
#define DEFAULT_RGB_BPP 16 //0 for current display pixel mode


//Mandatory
#include <SDL.h>
//Mandatory because we use RWOps for the wrapper, and we even wrap it
#include <SDL_rwops.h>
//Mandatory because we also wrap OpenGL
//TODO : NO_OPENGL option in build
#include <SDL_opengl.h>


//Conditionals

#ifdef HAVE_SDLIMAGE
#include "SDL_image.h"
#endif

#ifdef HAVE_SDLTTF
#include "SDL_ttf.h"
#endif

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

#ifdef DEBUG
#include <cassert>
#endif

//REMINDER : For audio, (SDL_mixer) have alook at http://gameprogrammer.com/gpwiki/Audio_lib

/**
 * \class Version
 *
 * \ingroup General
 *
 * \brief This class provides access to both linked and compiled SDL versions and specific CPU features check...
 *
 * \author Alex
 *
 * \date 2005/12/26
 *
 * Contact: asmodehn@gna.org
 *
 */
namespace RAGE
{

    namespace SDL
    {
            //global, namespace visible, declaration :
            extern Logger Log;

typedef enum
{
	Main
#ifdef HAVE_SDLIMAGE
	,Image
#endif
#ifdef HAVE_SDLTTF
	,TTF
#endif
}Module;


        std::string GetError(Module = Main);

        class Version
        {
            SDL_version _compiled;
            SDL_version _linked;

        public:
            Version();
            ~Version();

            int getcompiledmajor() const;
            int getcompiledminor() const;
            int getcompiledpatch() const;
            int getlinkedmajor() const;
            int getlinkedminor() const;
            int getlinkedpatch() const;

            //check if link and compiled matches
            bool check() const;

            friend Logger & operator << (Logger& log, const Version & v);
        };

#if SDL_VERSION_ATLEAST(1, 2, 7)

        class CPU
        {
        public:
            static bool hasRDTSC();
            static bool hasMMX();
            static bool hasMMXExt();
            static bool has3DNow();
            static bool has3DNowExt();
            //static bool hasSSE();
            //static bool hasSSEExt();
            static bool hasAltiVec();

        };
#endif

    }
}

#endif
