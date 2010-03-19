#ifndef SDL_VideoSurface_HH
#define SDL_VideoSurface_HH

#include "Video/internal/SDLBaseSurface.hh"
#include "Video/internal/SDLRGBSurface.hh" //to help with backup of screen surface
#include "Video/internal/SDLVideoInfo.hh"

#include <iostream>
#include <vector>
#include <list>

namespace SDLut
{
namespace video
{
    class ScreenBuffer;

    namespace internal {



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
    //managing one static member for all instances to store "SDL advised" display capabilities
    //Initialized by ScreenBuffer, after SDL_Init(SDL_VIDEO ) but before SDL_SetVideoMode
    static const VideoInfo * sptm_vinfo;

    //instance holding the actual display capabilities used
    //set after SDL_SetVideoMode
    VideoInfo ptm_vinfo;

public:
    virtual Renderer getRenderer()
    {
        return SDL;
    }

protected:
    static unsigned long ptm_defaultflags; // TODO : check : redundant with video info content ???

    Color ptm_background;




    //Constructor
    //Note : The user should not be able to set raw SDL flags manually.
    VideoSurface(int width, int height, int bpp) throw (std::logic_error);

public:

    static std::vector<int> availableWidth,availableHeight;

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


    //those methods just changes the static flags used on display creation.
    //use the App::methods to also reset the display.
    static void setOpenGL(bool val);
    static void setFullscreen(bool val);
    static void setResizable(bool val);
    static void setNoFrame(bool val);
    static void setDoubleBuf(bool val);
    static void setAnyFormat(bool val);
    static void setSWSurface(bool val);
    static void setHWSurface(bool val);
    static void setHWPalette(bool val);
    static void setAsyncBlit(bool val);

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

    static bool checkAvailableSize( const PixelFormat & fmt );
    static bool checkAvailableSize( void);
    static int getSuggestedBPP(int width, int height);

    ///static method returning best available video mode
    static const VideoInfo * getVideoInfo()
    {
        assert (sptm_vinfo);
        return sptm_vinfo;
    } ///access method to be used by derivated classes

    ///instance method, returning currently used video mode
    const VideoInfo & getInfo()
    {
        return ptm_vinfo;
    } ///access method to be used by derivated classes


    /**
     * Use a list of "standard" PC resolutions (width * height), test if they fit with the user computer and return the list of available ones.
     *
     * Return, the list of available resolutions sorted by width than height.
     **/
    static std::auto_ptr<std::list<std::pair<int, int> > > Get_Resolution_List();

    friend RAGE::Logger & operator << (RAGE::Logger & log, const VideoSurface & surf);
};

    }
}
} //namespace SDLut::SDL

#endif
