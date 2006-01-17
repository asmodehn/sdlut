#ifndef SDL_CONFIG_HH
#define SDL_CONFIG_HH

//Forced Config
//#undef HAVE_OPENGL //engine call seems to work... 3D part postponed...
#undef THREAD

//#if defined (_MSC_VER) && (_MSC_VER >= 1020)
//#pragma warning(disable:4290)	// Disable MSVC++ warning: C4290: C++ exception specification ignored.
//#endif
//imported into CMake now...

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

        std::string GetError(void);

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
            static inline bool hasRDTSC();
            static inline bool hasMMX();
            static inline bool hasMMXExt();
            static inline bool has3DNow();
            static inline bool has3DNowExt();
            //static inline bool hasSSE();
            //static inline bool hasSSEExt();
            static inline bool hasAltiVec();

        };
#endif

    }
}

#endif
