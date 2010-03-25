#ifndef SDL_VIDEOINFO_HH
#define SDL_VIDEOINFO_HH

/**
 * \class VideoInfo
 *
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

namespace SDLut
{
namespace video
{
namespace internal
{
class VideoSurface;

class VideoInfo
{
    friend class ScreenBuffer;
    friend class SDLut::video::internal::VideoSurface;

private:
    //Actual VideoInfo pointer
    //read-only access
    //the address of the SDL_VideoInfo struct should not change
    const SDL_VideoInfo* const pvm_sdl_vinfo;
    //BEWARE : this is managed by SDL. we get it from SDL as read-only, and we dont free it either

protected:
    //Accessor to the Video pixel format
    PixelFormat * ptm_pformat;

    //Constructor
    VideoInfo() throw (std::logic_error);
    //Copy Constructor : sharing the member pointer
    VideoInfo( const VideoInfo& vi);
    //Assignemt operator : sharing the member pointer
    VideoInfo& operator=(const VideoInfo& vi);

public:

    ~VideoInfo();

    //return true if hardware acceleration is enabled
    bool isHWAvailable() const;
    //return true if a window manager is available
    bool isWMAvailable() const;
    //return true if hardware to hardware blits are accelerated
    bool isBlitHWAccelAvailable() const;
    //return true if hardware to hardware colorkey blits are accelerated
    bool isBlitHWCKAccelAvailable() const;
    //return true if hardware to hardware alpha blits are accelerated
    bool isBlitHWAAccelAvailable() const;
    //return true if software to hardware blits are accelerated
    bool isBlitSWAccelAvailable() const;
    //return true if software to hardware colorkey blits are accelerated
    bool isBlitSWCKAccelAvailable() const;
    //return true if software to hardware alpha blits are accelerated
    bool isBlitSWAAccelAvailable() const;
    //return true if color fills are accelerated
    bool isBlitFillAccelAvailable() const;
    //return the total amount of video memory in kilobytes
    unsigned long videoMemSize() const;
    //return current width of video mode, or of the desktop mode if called before SDL_SetVideoMode
    unsigned int getCurrentWidth() const;
    //return current height of video mode, or of the desktop mode if called before SDL_SetVideoMode
    unsigned int getCurrentHeight() const;


    std::string getDriverName(void) const;

    //return the SDLPixelFormat for the current video device
    const PixelFormat & getPixelFormat() const;

    //display all detected informations about graphics
    friend RAGE::Logger & operator << (RAGE::Logger & ostr, const VideoInfo & vinfo);
};

}
}
} //namespace SDLut::SDL
#endif
