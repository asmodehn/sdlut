#ifndef SDL_VideoSurface_HH
#define SDL_VideoSurface_HH

#include "Video/internal/SDLBaseSurface.hh"
#include "Video/internal/SDLRGBSurface.hh" //to help with backup of screen surface
#include "Video/internal/SDLVideoInfo.hh"

#ifdef WK_OPENGL_FOUND
#include "Video/internal/OpenGL/SDLGLSurface.hh"
#include "Video/internal/OpenGL/OGLVideoInfo.hh"
#endif

#include <iostream>
#include <vector>
#include <list>

namespace SDLut
{
namespace video
{
class ScreenBuffer;

namespace internal
{



/**
 * \class Videosurface
 *
 * \brief A class to wrap SDL_Surface only when it is a Video one
 *
 * This class is meant to be used along with a engine. If there is no Engine provided it will use its own.
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

class VideoSurface : public BaseSurface
{

    friend class Overlay;
    friend class video::ScreenBuffer;
    friend class Manager;

protected:

#ifdef WK_OPENGL_FOUND
    //instance holding the actual display capabilities used
    //set after SDL_SetVideoMode
    OGL::OGLVideoInfo ptm_vinfo;
#else
    const VideoInfo ptm_vinfo;
#endif

public:
    virtual Renderer getRenderer()
    {
        return SDL;
    }

protected:

    Color ptm_background;

    //Constructor
    ///The user needs to pass a VideoInfo object that contains the settings for the video surface to be created
    VideoSurface( const VideoInfo & vi ) throw (std::logic_error);

public:

    //Destructor
    virtual ~VideoSurface();
    //this kind of surface shouldnt be deleted by hand. the raw SDL methods takes care of it

    //to resize the display
    virtual bool resize (int width, int height);
    //to flip the videosurface
    virtual bool refresh(void);

    virtual PixelColor getpixel(int x, int y);
    virtual void setpixel(int x, int y, PixelColor pixel);

    //Blit src surface on this surface
    //Blit using non const surface, as the video surface might change the blitted src surface for optimisation, updates or other reasons...
    //Beware ! The final blitting rectangle is saved in dest_rect.
    inline bool blit (RGBSurface& src, Rect& dest_rect)
    {
        Rect src_rect(0,0,src.getWidth(), src.getHeight());
        return blit(src, dest_rect, src_rect);
    }
    //Blit src into the current surface.
    virtual bool blit (RGBSurface& src, Rect& dest_rect, const Rect& src_rect);


    //Fill
    virtual bool fill (const PixelColor& color);
    virtual bool fill (const PixelColor& color, Rect dest_rect);

    //Maybe in Window only ?
    bool update(Rect r);
    bool update(std::vector<Rect> rlist);
    //May be using a default value.. depending on what has to be done for GLWindow

    //Accessors
    bool isOpenGLset(void) const;
    bool isFullScreenset(void) const;
    bool isResizableset(void) const;
    bool isNoFrameset(void) const;
    bool isAnyFormatset(void) const;
    virtual bool isDoubleBufset(void) const;
    //unused
    bool isASyncBlitset(void) const;
    bool isHWPaletteset(void) const;

    ///static method returning current video mode.
    /// if called before Videosurface creation, contains best available mode
#ifdef WK_OPENGL_FOUND
    const OGL::OGLVideoInfo& getVideoInfo()
    {
        return ptm_vinfo;
    } ///access method to be used by derivated classes
#else
    const VideoInfo& getVideoInfo()
    {
        return ptm_vinfo;
    } ///access method to be used by derivated classes
#endif

    friend RAGE::Logger & operator << (RAGE::Logger & log, const VideoSurface & surf);
};

}
}
} //namespace SDLut::SDL

#endif
