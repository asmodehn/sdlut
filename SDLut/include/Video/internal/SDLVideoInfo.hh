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
#include "WkPlatform.h"

#include "SDLPixelFormat.hh"

#include <iostream>
#include <vector>
#include <list>
#include <memory>
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

//TODO : We should make more clear the separation between what is "requested" when we create a videoSurface
// and what is actually read-only, as a result of VideoSurface creation. Both are tightly related though.
class VideoInfo
{
    friend class ScreenInfo;
    friend class SDLut::video::internal::VideoSurface;

    //forbidden assignement
    const VideoInfo& operator=(const VideoInfo& vi)
    {
        return vi;
    }

    bool pointerCopy;

protected:
    //Actual VideoInfo pointer
    //read-only access
    //the address of the SDL_VideoInfo struct should not change

    const SDL_VideoInfo* const pvm_sdl_vinfo;

    //Wrapper for the VideoInfo's pixel format
    //VideoInfo is a read-only structure
    //therefore PixelFormat is supposed to be constant.
    const PixelFormat * const ptm_pformat;




    //BEWARE : this is managed by SDL. we get it from SDL as read-only, and we dont free it either
    std::vector<int> availableWidth,availableHeight;



    unsigned long ptm_videoflags;
    unsigned int ptm_requestedWidth;
    unsigned int ptm_requestedHeight;
    unsigned short ptm_requestedBPP;

    //Default Constructor
    VideoInfo( );
    //Constructor (an existeng videosurface can pass its flags here)
    VideoInfo( unsigned int width, unsigned int height, unsigned int bpp, unsigned long vflags );
    //Copy Constructor : sharing the member pointer
    VideoInfo( const VideoInfo& vi);

public:

    bool checkAvailableSize( const PixelFormat & fmt );
    bool checkAvailableSize( void);
    int getSuggestedBPP(int width, int height);

    /**
     * Use a list of "standard" PC resolutions (width * height), test if they fit with the user computer and return the list of available ones.
     *
     * Return, the list of available resolutions sorted by width then height.
     **/
    static std::auto_ptr<std::list<std::pair<int, int> > > Get_Resolution_List();

    virtual ~VideoInfo();

    ///these methods just changes the static flags used on display creation.
	///they will return false if the requested bpp is not available with these flags.
	///Therefore it is advised to set the flags before the bpp
    virtual bool requestOpenGL(bool val);
    bool requestFullscreen(bool val);
    bool requestResizable(bool val);
    bool requestNoFrame(bool val);
    virtual bool requestDoubleBuf(bool val);
    bool requestAnyFormat(bool val);
    bool requestSWSurface(bool val);
    bool requestHWSurface(bool val);
    bool requestHWPalette(bool val);
    bool requestAsyncBlit(bool val);

	///returns the suggested bpp for this width and height
    unsigned short requestSize(unsigned int width, unsigned int height);
	/// set and returns the suggested bpp closest to the bpp requested
	/// therefore it s usually better to set bpp at last to make sure the videosurface can be created.
    unsigned short requestBPP(unsigned short bpp);

    unsigned int getRequestedWidth() const
    {
        return ptm_requestedWidth;
    }
    unsigned int getRequestedHeight() const
    {
        return ptm_requestedHeight;
    }
    unsigned short getRequestedBPP() const
    {
        return ptm_requestedBPP;
    }

    bool isOpenGL() const;
    bool isFullscreen() const;
    bool isResizable() const;
    bool isNoFrame() const;
    bool isDoubleBuf() const;
    bool isAnyFormat() const;
    bool isSWSurface() const;
    bool isHWSurface() const;
    bool isHWPalette() const;
    bool isAsyncBlit() const;


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
    friend Core::Logger & operator << (Core::Logger & ostr, const VideoInfo & vinfo);
};


}
}
} //namespace SDLut::SDL
#endif
