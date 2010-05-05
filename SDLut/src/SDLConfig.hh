#ifndef SDL_CONFIG_HH
#define SDL_CONFIG_HH

//use "conventional debug define"
#ifdef _DEBUG
#define DEBUG 1
#endif
//TODO : change all DEBUG here to SDLut_SDL_DEBUG and map it to DEBUG here.
//find a way to manage debug level also... ( for logging stuff in tights loops )

//TODO : make a macro to make it easier
//TODO : make our own exception class (with a macro to make launching easier and clear )

//Mandatory
#include "WkPlatform.h"

#include <SDL.h>
//Mandatory because we use RWOps in the wrapper, and we even wrap it
#include <SDL_rwops.h>
//same for threads
#include <SDL_thread.h>

//utils
#include "Logger.hh"

//TODO : look for a possibility to include all SDLs into SDLut::SDLut::SDL namespace after changed SDLut::SDL to SDLut::SDLut
#ifdef WK_OPENGL_FOUND
#include <SDL_opengl.h>
#endif

//Might be needed
//#if defined(WIN32) && !defined(GL_BGR)
//#define GL_BGR GL_BGR_EXT
//#endif

//Conditionals

#ifdef WK_SDLIMAGE_FOUND
#include "SDL_image.h"
#endif


#ifdef WK_SDLMIXER_FOUND
#include "SDL_mixer.h"
#endif

#ifdef WK_SDLNET_FOUND
#include "SDL_net.h"
#endif

#ifdef WK_SDLTTF_FOUND
#include "SDL_ttf.h"
#endif

//Global default declarations
namespace SDLut
{
//global, namespace visible, declaration for the SDLut logger. Will be initialized only once.
extern Core::Logger Log;

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
} Module;

std::string GetError(Module);

bool isCompiled(Module);
bool isLinked(Module);
bool Init(Module);
bool WasInit(Module);
void Quit(Module);

}

}


#if SDL_VERSION_ATLEAST(1, 2, 7)
#include "SDL_cpuinfo.h"
namespace SDLut
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

#endif



#endif
