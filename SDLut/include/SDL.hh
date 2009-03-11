#ifndef SDL_HH
#define SDL_HH

/*Checking memory leaks with VLD under Win32 only !*/
#ifdef WIN32
	#ifdef VLD
		#include "vld.h"
	#endif
#endif

/** This file gather all the header files a user need to include to be able to use RAGE::SDL
  * So the user just has to include SDL.hh to have full access to the whole RAGE wrapper
 *
 * Is this file actually needed ??? maybe SDLApp can play the same role, isnt it ?
  */

/**
  * \defgroup Utils
  */
#include "Logger.hh"


/**
  * \defgroup General
  * This group provide many classes to make the use of SDL easier
  * Also provide a set of classes to manage the SDL Global functions :
  *
  * <ul>
  * <li>SDL_Init -- Initializes SDL
  * <li>SDL_InitSubSystem -- Initialize subsystems
  * <li>SDL_QuitSubSystem -- Shut down a subsystem
  * <li>SDL_Quit -- Shut down SDL
  * <li>SDL_WasInit -- Check which subsystems are initialized
  * <li>SDL_GetError -- Get SDL error string
  * <li>SDL_envvars -- SDL environment variables
  * </ul>
  *
  */
#include "SDLVersion.hh"
#include "SDLApp.hh"
#include "SDLManager.hh"

/**
  * \defgroup Video
  *
  */
#include "Video/SDLWindow.hh"
#include "Video/SDLVideoInfo.hh"
#include "Video/SDLVideoSurface.hh"
#include "Video/SDLGLManager.hh"
#include "Video/SDLEngine.hh"
#include "Video/SDLColor.hh"
#include "Video/SDLOverlay.hh"

/**
  * \defgroup System
  */
#include "System/SDLEvent.hh"
#include "System/SDLEventManager.hh"
#include "System/SDLTimer.hh"
#include "System/SDLNewTimer.hh"
#include "System/SDLRWOps.hh"
#include "System/SDLThread.hh"
#include "System/SDLNewThread.hh"
#include "System/SDLMutex.hh"
#include "System/SDLSemaphore.hh"
#include "System/SDLCondition.hh"

/**
  * \defgroup Network
  */
#include "Network/SDLSocketTCP.hh"

/**
  * \defgroup Input
  */
#include "Input/SDLMouse.hh"
#include "Input/SDLCursor.hh"
#include "Input/SDLKeyboard.hh"
#include "Input/SDLJoystick.hh"

/**
  * \defgroup Audio
 */
#include "Audio/SDLMixer.hh"
#include "Audio/SDLSound.hh"

/**
  * \defgroup Font
  */
#include "Font/SDLFont.hh"

/**
  * \defgroup Math
  */
#include "Math/SDLPoint.hh"
#include "Math/SDLRect.hh"

//Build platform useful definitions
#if defined (__MINGW32__) && defined(SDLUT_BUILD)
#define GCN_CORE_DECLSPEC __declspec(dllexport)

#elif defined (__MINGW32__) && defined(SDLUT_EXTENSION_BUILD)
#define GCN_EXTENSION_DECLSPEC __declspec(dllexport)
#define GCN_CORE_DECLSPEC __declspec(dllimport)

#elif defined (__MINGW32__) && defined(SDLUT_DLL_IMPORT)
#define GCN_CORE_DECLSPEC __declspec(dllimport)
#define GCN_EXTENSION_DECLSPEC __declspec(dllimport)

#elif defined(_MSC_VER) && defined(SDLUT_BUILD)
#define GCN_CORE_DECLSPEC _declspec(dllexport)

#elif defined(_MSC_VER) && defined(SDLUT_EXTENSION_BUILD)
#define GCN_CORE_DECLSPEC _declspec(dllimport)
#define GCN_EXTENSION_DECLSPEC _declspec(dllexport)

#endif

#ifndef SDLUT_CORE_DECLSPEC
#define SDLUT_CORE_DECLSPEC
#endif

#ifndef SDLUT_EXTENSION_DECLSPEC
#define SDLUT_EXTENSION_DECLSPEC
#endif

#ifndef NULL
#define NULL 0
#endif

//just a little usefull tip for mingw
#ifdef __MINGW32__
#ifdef main
#undef main
#endif
#endif

#ifdef WIN32
#ifdef main
#undef main
#endif
#endif


#endif
