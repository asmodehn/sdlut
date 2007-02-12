#ifndef SDL_VIDEOINFO_HH
#define SDL_VIDEOINFO_HH

/**
 * \class VideoInfo
 *
 * \ingroup Video
 *
 * \brief A class to wrap SDL_VideoInfo
 *
 * A simple wrap...
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "Logger.hh"
#include "SDLPixelFormat.hh"

#include <iostream>
#include <stdexcept>

//Declaring SDL types for late binding.
struct SDL_VideoInfo;

namespace RAGE
{
    namespace SDL
    {

        class VideoInfo
        {
            friend class Window;

        private:
            //Actual VideoInfo pointer
            //read-only access
            //the address of the SDL_VideoInfo struct should not change
            const SDL_VideoInfo* const _info;

        protected:
            PixelFormat * _pformat; //dynamically constructed when needed
            //Constructor
            VideoInfo() throw (std::logic_error);

        public:

            ~VideoInfo();

            //return true if hardware acceleration is enabled
	    bool isHWAvailable() const;
            //return true if a window manager is available
	    bool isWMAvailable() const;
            //return true if hardware to hardware blits are accelerated
	    bool isBlitHWAccelAvailable() const;
            //return true if hardware to hardware colorkey blits are accelerated
	    bool isBlitHWCCAccelAvailable() const;
            //return true if hardware to hardware alpha blits are accelerated
	    bool isBlitHWAAccelAvailable() const;
            //return true if software to hardware blits are accelerated
	    bool isBlitSWAccelAvailable() const;
            //return true if software to hardware colorkey blits are accelerated
	    bool isBlitSWCCAccelAvailable() const;
            //return true if software to hardware alpha blits are accelerated
	    bool isBlitSWAAccelAvailable() const;
            //return true if color fills are accelerated
	    bool isBlitFillAccelAvailable() const;
            //return the total amount of video memory in kilobytes
	    unsigned long videoMemSize() const;

            std::string getDriverName(void) const;

            //return the SDLPixelFormat for the current video device
            PixelFormat * getPixelFormat() const;

            //display all detected informations about graphics
            friend Logger & operator << (Logger & ostr, const VideoInfo & vinfo);
        };
    }
} //namespace RAGE::SDL
#endif
