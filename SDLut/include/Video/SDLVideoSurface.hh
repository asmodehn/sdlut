#ifndef SDL_VideoSurface_HH
#define SDL_VideoSurface_HH

/**
 * \class VideoSurface
 *
 * \ingroup Video
 * \ingroup WindowManager
 *
 * \brief This class is handle a video surface.
 *
 * This class has a derivative if your display is 3d (OpenGL).
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "Video/SDLBaseSurface.hh"
#include "Video/SDLRGBSurface.hh" //to help with backup of screen surface

#include <iostream>
#include <vector>
#include <list>

namespace RAGE
{
namespace SDL
{


/**
 * \class Videosurface
 *
 * \ingroup Video
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
    friend class ScreenBuffer;
    friend class Manager;

public:
    virtual Renderer getRenderer()
    {
        return SDL;
    }

protected:
    static unsigned long _defaultflags;

    RGBAColor _background;




    //Constructor
    //Note : The user should not be able to set raw SDL flags manually.
    VideoSurface(int width, int height, int bpp) throw (std::logic_error);

public:

    static std::vector<int> availableWidth,availableHeight;

    //Destructor
    virtual ~VideoSurface();
    //this kind of surface shouldnt be deleted by hand. the raw SDL methods takes care of it

    //to resize the display
    virtual bool resize (int width, int height, bool keepcontent = false);
    //to flip the videosurface
    virtual bool refresh(void);

    virtual RGBAColor getpixel(int x, int y);
    virtual void setpixel(int x, int y, RGBAColor pixel);

    //Blit src surface on this surface
    //Blit using non const surface, as the video surface might change the blitted src surface for optimisation, updates or other reasons...
    inline bool blit (RGBSurface& src, const Point& dest_pos=Point())
    {
        //bydefault we blit the entire surface onto a surface of the same size
        Rect dest_rect(dest_pos,src.getWidth(), src.getHeight());
        return blit(src, dest_rect);
    }
    inline bool blit (RGBSurface& src, const Point& dest_pos, const Rect& src_rect)
    {
        Rect dest_rect(dest_pos,src_rect.getw(), src_rect.geth());
        return blit(src, dest_rect, src_rect);
    }
    //Beware ! The final blitting rectangle is saved in dest_rect.
    inline bool blit (RGBSurface& src, Rect& dest_rect)
    {
        Rect src_rect(src.getWidth(), src.getHeight());
        return blit(src, dest_rect, src_rect);
    }
    //Blit src into the current surface.
    virtual bool blit (RGBSurface& src, Rect& dest_rect, const Rect& src_rect);


    //Fill
    virtual bool fill (const RGBAColor& color);

protected : // Pixel Color should be used only internally, because of its complexity in different formats
    virtual bool fill (const PixelColor& color);

public :
    virtual bool fill (const RGBAColor& color, Rect dest_rect);

protected : // Pixel Color should be used only internally, because of its complexity in different formats
    virtual bool fill (const PixelColor& color, Rect dest_rect);

public:

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

    static bool checkAvailableSize( const PixelFormat * fmt );
    static bool checkAvailableSize( void);
    static int getSuggestedBPP(int width, int height);

    /**
     * Use a list of "standard" PC resolutions (width * height), test if they fit with the user computer and return the list of available ones.
     *
     * Return, the list of available resolutions sorted by width than height.
     **/
    static std::auto_ptr<std::list<std::pair<int, int> > > Get_Resolution_List();

    friend Logger & operator << (Logger & log, const VideoSurface & surf);
};
}
} //namespace RAGE::SDL

#endif
