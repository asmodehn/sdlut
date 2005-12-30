#ifndef SDL_WRAP_HH
#define SDL_WRAP_HH

/** This file gather all the header files a user need to include to be able to use SDLwrap
  * So the user just has to include SDLwrap to have full access to the whole wrapper
  */

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
#include "SDLApp.hh"
#include "SDLWindow.hh"
#include "SDLManager.hh"

/**
  * \defgroup Video
  *
  * \defgroup WindowManager
  */
#include "SDLVideoInfo.hh"
#include "SDLVideoSurface.hh"
#include "SDLGLSurface.hh"
#include "SDLGLManager.hh"
#include "SDLColor.hh"
#include "SDLCursor.hh"
#include "SDLOverlay.hh"
#include "SDLPoint.hh"
#include "SDLRect.hh"

/**
  * \defgroup EventHandling
  */
#include "SDLEventManager.hh"
#include "SDLMouse.hh"
#include "SDLKeyboard.hh"
#include "SDLJoystick.hh"

/**
  * \defgroup Audio
  * \defgroup CDROM
  * \defgroup Threads
  * \defgroup Timers
  */

/**
  * \defgroup Other
  */
#include "Interface3D.hh"
#include "Logger.hh"


//just a little usefull tip for mingw
#ifdef __MINGW32__
#ifdef main
#undef main
#endif
#endif


#endif
