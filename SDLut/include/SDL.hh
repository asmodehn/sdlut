#ifndef SDL_HH
#define SDL_HH

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
  * \defgroup WindowManager
  */
#include "SDLWindow.hh"
#include "SDLVideoInfo.hh"
#include "SDLVideoSurface.hh"
#include "SDLGLManager.hh"
#include "SDLEngine.hh"
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
 */
#include "SDLMixer.hh"
#include "SDLAudioInfo.hh"
#include "SDLSound.hh"

/**
  * \defgroup CDROM
  * \defgroup Threads
  */
/**
  * \defgroup Timers
  */
#include "SDLTimer.hh"
/**
  * \defgroup RWOps
  */
#include "SDLRWOps.hh"
/**
  * \defgroup Text
  */
#include "SDLFont.hh"


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
