#ifndef SDL_HH
#define SDL_HH

/*Checking memory leaks with VLD under Win32 only !*/
#ifdef WIN32
#ifdef VLD
#include "vld.h"
#endif
#endif


/* including the configuration header */
#include "WkPlatform.h"

/*! \mainpage SDLut Documentation
 *
 * \section intro_sec Introduction
 *
 * SDLut is a C++ wrapper over the <a href="http://libsdl.org">Smart DirectMedia Library</a>
 * SDLut works only with SDL v 1.2 at the moment
 * You are looking for SDL v1.3 support ? Contact us to help.
 *
 * \section build_sec Building
 *
 *
 * \section install_sec Installation
 *
 *
 *
 * \subsection tools_subsec Tools required:
 * - <a href="http://cmake.com">CMake</a> <BR>
 * - your favorite C++ compiler ( tested with g++ 4.X and Visual C ++ 2008 )
 * - <a href="http://libsdl.org">SDL</a>
 *
 * Optional libraries
 * - SDL_image ( needed to support multiple image formats )
 * - SDL_net
 * - SDL_ttf
 * - SDL_mixer
 *
 * If your platform has an OpenGL installation, it will be detected, and SDLut will use it for faster and nicer rendering
 * Otherwise SDL

 * \subsection running Running the program
 * In a command window, etc etc...
 *
 * \section copyright Copyright and License
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * \section contact Contact Us
 * SDLut developers :
 * - <a href="mailto:asmodehn@gna.org?subject=SDLut Contact">Asmodehn</a>
 * - <a href="mailto:xorfacx@gna.org?subject=SDLut Contact">XorfacX</a>
 *
 * <BR><BR>
 *
 */



/** This file gather all the header files a user need to include to be able to use SDLut::SDL
  * So the user just has to include SDL.hh to have full access to the whole SDLut wrapper
 *
 * Is this file actually needed ??? maybe SDLApp can play the same role, isnt it ?
  */

/**
  * \defgroup SDLut
  * This Module provides a set of classes to make the use of SDL in C++ much more convenient.
  * The classes in this namespace wrap the following SDL commands :
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
  * TODO : include UML diagram in png, from ArgoUML
  *
  */
#include "SDLVersion.hh"
#include "SDLApp.hh"
#include "SDLManager.hh"

/**
  * \defgroup SDLut::video
  *
  * This Module provides a set of classes to make the use of SDL in C++ much more convenient.
  * The classes in this namespace wrap the following SDL commands :
  *
  * <ul>
  * <li>SDL_GetVideoSurface - Returns a pointer to the current display surface
  * <li>SDL_GetVideoInfo - Returns a pointer to information about the video hardware
  * <li>SDL_VideoDriverName - Obtain the name of the video driver
  * <li>SDL_ListModes - Returns a pointer to an array of available screen dimensions for the given format and video flags
  * <li>SDL_VideoModeOK - Checks to see if a particular video mode is supported.
  * <li>SDL_SetVideoMode - Sets up a video mode with the specified width, height and bits-per-pixel.
  * <li>SDL_UpdateRect - Makes sure the given area is updated on the given screen.
  * <li>SDL_UpdateRects - Makes sure the given list of rectangles is updated on the given screen.
  * <li>SDL_Flip - Swaps screen buffers
  * <li>SDL_SetColors - Sets a portion of the colormap for the given 8-bit surface.
  * <li>SDL_SetPalette - Sets the colors in the palette of an 8-bit surface.
  * <li>SDL_SetGamma - Sets the color gamma function for the display
  * <li>SDL_GetGammaRamp - Gets the color gamma lookup tables for the display
  * <li>SDL_SetGammaRamp - Sets the color gamma lookup tables for the display
  * <li>SDL_MapRGB - Maps a RGB color value to a pixel format.
  * <li>SDL_MapRGBA - Maps a RGBA color value to a pixel format.
  * <li>SDL_GetRGB - Gets RGB values from a pixel in the specified pixel format.
  * <li>SDL_GetRGBA - Gets RGBA values from a pixel in the specified pixel format.
  * <li>SDL_CreateRGBSurface - Creates an empty SDL_Surface
  * <li>SDL_CreateRGBSurfaceFrom - Creates an SDL_Surface from pixel data
  * <li>SDL_FreeSurface - Frees (deletes) a SDL_Surface
  * <li>SDL_LockSurface - Locks a surface for direct access.
  * <li>SDL_UnlockSurface - Unlocks a previously locked surface.
  * <li>SDL_ConvertSurface - Converts a surface to the same format as another surface.
  * <li>SDL_DisplayFormat - Converts a surface to the display format
  * <li>SDL_DisplayFormatAlpha - Converts a surface to the display format
  * <li>SDL_LoadBMP - Loads a Windows BMP file into an SDL_Surface.
  * <li>SDL_SaveBMP - Saves an SDL_Surface as a Windows BMP file.
  * <li>SDL_SetColorKey - Sets the color key (transparent pixel) in a blittable surface and RLE acceleration.
  * <li>SDL_SetAlpha - Adjusts the alpha properties of a surface
  * <li>SDL_SetClipRect - Sets the clipping rectangle for a surface.
  * <li>SDL_GetClipRect - Gets the clipping rectangle for a surface.
  * <li>SDL_BlitSurface - This function performs a fast blit from the source surface to the destination surface.
  * <li>SDL_FillRect - This function performs a fast fill of the given rectangle with some color
  * <li>SDL_GL_LoadLibrary - Specifies an OpenGL library
  * <li>SDL_GL_GetProcAddress - Gets the address of a GL function
  * <li>SDL_GL_GetAttribute - Gets the value of a special SDL/OpenGL attribute
  * <li>SDL_GL_SetAttribute - Sets a special SDL/OpenGL attribute
  * <li>SDL_GL_SwapBuffers - Swaps OpenGL framebuffers/Update Display
  * <li>SDL_GLattr - SDL GL Attributes
  * <li>SDL_CreateYUVOverlay - Creates a YUV video overlay
  * <li>SDL_LockYUVOverlay - Locks an overlay
  * <li>SDL_UnlockYUVOverlay - Unlocks an overlay
  * <li>SDL_DisplayYUVOverlay - Blits the overlay to the display
  * <li>SDL_FreeYUVOverlay - Frees a YUV video overlay
  * <li>SDL_Rect - Defines a rectangular area
  * <li>SDL_Color - Format independent color description
  * <li>SDL_Palette - Color palette for 8-bit pixel formats
  * <li>SDL_PixelFormat - Stores surface format information
  * <li>SDL_Surface - Graphical Surface Structure
  * <li>SDL_VideoInfo - Video Target information
  * <li>SDL_Overlay - YUV video overlay
  *
  * TODO : include UML diagram in png, from ArgoUML
  *
  */
//#include "Video/internal/SDLWindow.hh"
//#include "Video/SDLVideoInfo.hh"
//#include "Video/SDLVideoSurface.hh"
//#include "Video/SDLRGBSurface.hh"
//#include "Video/SDLGLManager.hh"
//#include "Video/SDLEngine.hh"
//#include "Video/SDLOverlay.hh"
#include "Video/Color.hh"
#include "Video/Display.hh"
#include "Video/ScreenBuffer.hh"
#include "Video/Image.hh"
#include "Video/ImageLoader.hh"
#include "Video/Rect.hh"

/**
  * \defgroup SDLut::system
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
  * \defgroup SDLut::network
  */
#include "Network/SDLSocketTCP.hh"

/**
  * \defgroup SDLut::input
  */
#include "Input/SDLMouse.hh"
#include "Input/SDLCursor.hh"
#include "Input/SDLKeyboard.hh"
#include "Input/SDLJoystick.hh"

/**
  * \defgroup SDLut::audio
 */
#include "Audio/SDLMixer.hh"
#include "Audio/SDLSound.hh"

/**
  * \defgroup SDLut::font
  */
#include "Font/SDLFont.hh"
#include "Font/Text.hh"

//Build platform useful definitions
// TODO : check These should be in WkPlatform now...
// Guichan extensions shouldnt be here
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
