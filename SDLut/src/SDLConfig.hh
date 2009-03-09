#ifndef SDL_CONFIG_HH
#define SDL_CONFIG_HH

//use "conventional debug define"
#ifdef _DEBUG
#define DEBUG 1
#endif
//TODO : change all DEBUG here to RAGE_SDL_DEBUG and map it to DEBUG here.
//find a way to manage debug level also... ( for logging stuff in tights loops )

//Mandatory
#include "CMakeConfig.hh"
#include <SDL.h>
//Mandatory because we use RWOps in the wrapper, and we even wrap it
#include <SDL_rwops.h>
//same for threads
#include <SDL_thread.h>

//useful aliases
#define Color RGBColor

//utils
#include "Logger.hh"

//TODO : look for a possibility to include all SDLs into RAGE::SDLut::SDL namespace after changed RAGE::SDL to RAGE::SDLut
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


#ifdef HAVE_SDLMIXER
#include "SDL_mixer.h"
#endif

#ifdef HAVE_SDLNET
#include "SDL_net.h"
#endif

#ifdef HAVE_SDLTTF
#include "SDL_ttf.h"
#endif

//Global default declarations
namespace RAGE
{
	namespace SDL
	{
		//global, namespace visible, declaration for the SDLut logger. Will be initialized only once.
		extern Logger Log;

		std::string GetError();
		
		namespace Optional
		{
//list of modules
			typedef enum
			{
				Image,
				TTF,
				Mixer,
				Net
			}Module;
		
		std::string GetError(Module);

		bool isCompiled(Module);
		bool isLinked(Module);
		bool Init(Module);
		bool WasInit(Module);
		void Quit(Module);
			
		}

	}
}


#if SDL_VERSION_ATLEAST(1, 2, 7)
#include "SDL_cpuinfo.h"
namespace RAGE
{
	namespace SDL
	{
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
	}
}
#endif


	
#endif
