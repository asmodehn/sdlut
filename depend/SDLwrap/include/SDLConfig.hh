#ifndef SDLCONFIG_HH
#define SDLCONFIG_HH

//Forced Config
#undef OPENGL //engine call seems to work... 3D part postponed...
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


//Error Messages
#define SDLERROR std::cerr << SDL_GetError() << std::endl
#define LIB_ERROR(str) std::cerr << " ERROR ==> " << str << std::endl

/**
 * \class SDLConfig
 *
 * \ingroup Other
 * 
 * \brief This class gather the common objects that all the SDL classes may be able to access
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

class SDLConfig
{
  static Logger *	_SDLlog;
public:
  SDLConfig(void) {_SDLlog->setLogfile("SDLwrap.log");}
  static inline  Logger * getLog(void) {return _SDLlog;}
};

#endif
