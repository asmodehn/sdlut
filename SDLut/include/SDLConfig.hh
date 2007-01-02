#ifndef SDL_CONFIG_HH
#define SDL_CONFIG_HH

//Forced Config
#undef THREAD

//Normal Setup
#define DEFAULT_DISPLAY_WIDTH 640
#define DEFAULT_DISPLAY_HEIGHT 480
#define DEFAULT_DISPLAY_BPP 0 //0 for current display pixel mode
//beware ! 0 only usable for Display Surface, not for RGB ones !!
#define DEFAULT_WINDOW_TITLE "RAGE::SDL"

//Mandatory
#include "CMakeConfig.hh"
#include <SDL.h>
//Mandatory because we use RWOps in the wrapper, and we even wrap it
#include <SDL_rwops.h>

#ifdef HAVE_OPENGL
#include <SDL_opengl.h>
#endif

//Might be needed
//#if defined(WIN32) && !defined(GL_BGR)
//#define GL_BGR GL_BGR_EXT
//#endif

//Conditionals

#ifdef HAVE_SDLIMAGE
#include "SDL_image.h"
#endif

#ifdef HAVE_SDLNET
#include "SDL_net.h"
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
 * TODO : Replace Version structure by the same stuff than SDL version ( macros )
 *
 */
 
namespace RAGE
{

    namespace SDL
    {
            //global, namespace visible, declaration :
            extern Logger Log;

			//list of supported optional modules...
			//if those modules are used and there are not linked with RAGE::SDL, an error message will be returned.
typedef enum
{
	Main
	,Image
	,Net
}Module;


        std::string GetError(Module = Main);

		namespace TTF{

			//declaring the bridge class to access TTF features
			class Font;

			std::string GetError();

			//maybe derivate from SDL::Version ?
			class Version
	        {
		        SDL_version _compiled;
			    SDL_version _linked;

			public:
				Version();
				~Version();
	
				//Version is 0.0.0 if not available for some reason ( not compiled with or not linked )
		        int getcompiledmajor() const;
				int getcompiledminor() const;
				int getcompiledpatch() const;
				int getlinkedmajor() const;
				int getlinkedminor() const;
				int getlinkedpatch() const;
	
				

				//return true if linked and compiled version are not null and matches exactly
				bool isValid() const;
				
				//return true if linked is not null and superior or equal to compiled
				bool isSupported() const;
	
				//Display the version. Usefull for debugging purpose...
				friend Logger & operator << (Logger& log, const Version & v);
			};

			//checks if compiled Version is different from 0.0.0
			bool isCompiled();
			//checks if linked version is different from 0.0.0
			bool isLinked();
		}

		//declaring default namespace to contains all default builtins behaviour
		namespace Default{
			class Font;
			class Cursor;
		}

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
