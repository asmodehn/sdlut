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
#include <stdexcept>
#include <vector>

//Debug Constants
#define SDLUserInput_DEBUG


//Error Messages
#define SDLERROR std::cerr << SDL_GetError() << std::endl
#define LIB_ERROR(str) std::cerr << " ERROR ==> " << str << std::endl

#endif
