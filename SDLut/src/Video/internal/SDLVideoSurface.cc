#include "Video/internal/SDLVideoSurface.hh"
#include "SDLConfig.hh"
//#include <sstream>

using namespace Core;

namespace SDLut
{
namespace video
{
namespace internal
{

//Constructor
VideoSurface::VideoSurface( const VideoInfo & vi) throw (std::logic_error)
try
:
    BaseSurface(SDL_SetVideoMode(vi.getRequestedWidth(),vi.getRequestedHeight(),vi.getRequestedBPP(),vi.ptm_videoflags )),
    ptm_vinfo(getWidth(),getHeight(),getBPP(),getFlags()),
    ptm_background(0,0,0)
{
#ifdef DEBUG
    Log << nl << "VideoSurface::VideoSurface( "<< vi.getRequestedWidth()<<", "<<vi.getRequestedHeight()<<", "<<vi.getRequestedBPP()<<", "<<vi.ptm_videoflags<<") called ...";
#endif

    if (!initialized())
    {
        Log << nl <<"Unable to set " << vi.getCurrentWidth() << " x " << vi.getCurrentHeight() << " display surface : ";
        throw std::logic_error("SDL_SetVideoMode() return NULL");
    }

#ifdef DEBUG
    Log << nl << "VideoSurface::VideoSurface( "<< vi.getRequestedWidth()<<", "<<vi.getRequestedHeight()<<", "<<vi.getRequestedBPP()<<", "<<vi.ptm_videoflags<<") done.";
#endif

}
catch (std::exception &e)
{
    Log << nl << "VideoSurface:: Exception in Constructor !" <<
    nl << e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

VideoSurface::~VideoSurface()
{
}



bool VideoSurface::refresh(void)
{
    return SDL_Flip(ptm_surf.get()) == 0;
}

bool VideoSurface::resize(int width, int height)
{

#ifdef DEBUG
    Log << nl << "VideoSurface::resize(" << width << ", " << height << ") called...";
#endif

    bool res;
    //BEWARE : should match DisplaySurface Constructor code
    std::auto_ptr<SDL_Surface> newSurf( SDL_SetVideoMode(width,height,getBPP(),getFlags()) );

    if (!newSurf.get()) //SetVideoMode has failed
    {
        Log << "Unable to resize to " << width << " x " << height << " 2D display surface " << nl << GetError();

#ifdef DEBUG
        Log << nl << "VideoSurface::resize(" << width << ", " << height << ") failed.";
#endif
        res = false;
    }
    else
    {

        ptm_surf=newSurf;

#ifdef DEBUG
        Log << nl << "VideoSurface::resize(" << width << ", " << height << ") succeeded.";
#endif
        res = true;
    }

    return (res && initialized());
}


PixelColor VideoSurface::getpixel(int x, int y)
{
    return BaseSurface::getpixel(x, y);
}

void VideoSurface::setpixel(int x, int y, PixelColor pixel)
{
    return BaseSurface::setpixel( x, y, pixel );
}



bool VideoSurface::blit (RGBSurface& src, Rect& dest_rect, const Rect& src_rect)
{
#if (DEBUG == 2)
    Log << nl << "VideoSurface::blit (const RGBSurface& src," << dest_rect << ", " << src_rect << ") called...";
#endif
    if ( ! src.optimised )
    {
        src.convertToDisplayFormat();
    }
    bool res = BaseSurface::blit(src,dest_rect, src_rect);

#if (DEBUG == 2)
    Log << nl << "VideoSurface::blit (const RGBSurface& src," << dest_rect << ", " << src_rect << ") done.";
#endif
    return res;
}


//Fill
/*bool VideoSurface::fill (const Color& color)
{
    return fill(getPixelFormat().getValueFromColor(color));
}*/

bool VideoSurface::fill (const PixelColor& color)
{
    Rect dest_rect(0,0,getWidth(), getHeight());
    return fill( color, dest_rect );
}

/*bool VideoSurface::fill (const Color& color, Rect dest_rect)
{
    return fill(getPixelFormat().getValueFromColor(color), dest_rect);
}*/


bool VideoSurface::fill (const PixelColor& color, Rect dest_rect)
{
    return BaseSurface::fill(color, dest_rect);
}


bool VideoSurface::update(Rect r)
{
    SDL_UpdateRect(ptm_surf.get(), r.getx(), r.gety(), r.getw(), r.geth());
    return true;
}

bool VideoSurface::update(std::vector<Rect> rlist)
{
    //fill(_background);

    /* this breaks as soon as a rect is a bit out of the screen : known issue in SDL 1.2 */
    /* therefore we cant use it until we manage the clipping here... */
    /*
    SDL_Rect* list = new SDL_Rect[rlist.size()];
    for (unsigned int i=0; i<rlist.size() ; i++)
        list[i]=*(rlist[i]._rect);
    SDL_UpdateRects(_surf.get(), rlist.size(), list);
    */

    for ( unsigned int i=0; i<rlist.size(); i++)
    {
        SDL_UpdateRect(ptm_surf.get(), rlist[i].getx(), rlist[i].gety(), rlist[i].getw(), rlist[i].geth());
    }

    return true;
}




//Accessors
//NB : here ptm_surf HAS TO BE CREATED and USABLE.
//RAII also on surfaces
bool VideoSurface::isOpenGLset(void) const
{
    return ( SDL_OPENGL & (ptm_surf->flags) ) != 0;
}
bool VideoSurface::isFullScreenset(void) const
{
    return ( SDL_FULLSCREEN & (ptm_surf->flags)) != 0;
}
bool VideoSurface::isResizableset(void) const
{
    return ( SDL_RESIZABLE & (ptm_surf->flags)) != 0;
}
bool VideoSurface::isNoFrameset(void) const
{
    return ( SDL_NOFRAME & (ptm_surf->flags)) != 0;
}
bool VideoSurface::isAnyFormatset(void) const
{
    return ( SDL_ANYFORMAT & (ptm_surf->flags)) != 0;
}
bool VideoSurface::isDoubleBufset(void) const
{
    return ( SDL_DOUBLEBUF & (ptm_surf->flags)) != 0;
}
//unused
bool VideoSurface::isASyncBlitset(void) const
{
    return ( SDL_ASYNCBLIT & (ptm_surf->flags)) != 0;
}
bool VideoSurface::isHWPaletteset(void) const
{
    return ( SDL_HWPALETTE & (ptm_surf->flags)) != 0;
}


Core::Logger & operator << (Core::Logger & log, const VideoSurface & surf)
{
    //log << static_cast<BaseSurface>(surf);
    log << nl<<std::boolalpha << "- Fullscreen ? " << surf.isFullScreenset() << nl
    << "- Resizable ? " << surf.isResizableset() << nl
    << "- NoFrame ? " << surf.isNoFrameset() <<nl
    << "- AnyFormat ? " << surf.isAnyFormatset() << nl
    << "- Double Buffered ? " << surf.isDoubleBufset();
    return log;
}

}
}
} //namespace SDLut::SDL
