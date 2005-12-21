#ifndef SDLCONFIG_HH
#define SDLCONFIG_HH

//Forced Config
//#undef HAVE_OPENGL //engine call seems to work... 3D part postponed...
#undef THREAD

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
static inline std::string GetError(void) { return SDL_GetError(); }

class Config
{
  static Logger *	_log;
public:
  Config(void) {_log->setLogfile("SDLwrap.log");}
  static inline  Logger * getLog(void) {return _log;}
  static inline  void addLog(std::string str, bool fatal = false)
  {
  	if (fatal)
  		str = " FATAL ERROR ==> " + str;
  	_log->add(str);
	}

  static Logger& getLogX() { return *_log; }
};
}
#endif
