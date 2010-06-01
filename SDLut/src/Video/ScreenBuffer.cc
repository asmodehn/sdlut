#include "Video/ScreenBuffer.hh"
#include "SDLConfig.hh"

using namespace Core;

namespace SDLut
{
namespace video
{

ScreenBuffer::ScreenBuffer(const ScreenInfo& scinf, Manager* manager) throw (std::logic_error)
try :
    fullRefreshNeeded(true), pm_manager(manager), m_scinfo()
{
    Log << nl << "Creating new ScreenBuffer. ScreenInfo Requested " << scinf;
#ifdef WK_SDLut_FOUND_OPENGL
    m_screen.reset(new internal::OGL::VideoGLSurface(scinf.m_videoinfo));
#else
    m_screen.reset(new internal::VideoSurface(scinf.m_videoinfo));
#endif

    m_scinfo.reset(new ScreenInfo(m_screen->getVideoInfo()));

    //m_bgsurf.reset(new Image(m_screen->getWidth(), m_screen->getHeight(),m_screen->getBPP()));
    //m_bgsurf->fill(m_background);

    //initializing engine
    m_engine.reset(new internal::SDLEngine());


    //TO TEST, maybe not needed anymore
    requestFullRefresh();

    Log << nl <<"ScreenInfo Obtained " << *m_scinfo ;

    //we need a manager to manage settings
    if (! pm_manager )
    {
        Log << nl << "The requested SDLManager hasnt been properly passed to ScreenBuffer Constructor. Screen creation cancelled !";
        throw std::logic_error("SDL::Manager manager parameter points to 0x0");
    }
}
catch (std::exception & e)
{
    Log << nl << " Exception caught in ScreenBuffer Constructor : " << e.what();
}


//recreating Engine here to make sure both origin and destination engines are independant.
//maybe not really needed, but safer in case of copy ( or should we completely forbid copy ? )
ScreenBuffer::ScreenBuffer( const ScreenBuffer & sb )
        : fullRefreshNeeded(true),pm_manager(sb.pm_manager), m_scinfo(0)
{
    //WHAT TO DO HERE ??
    //also what about video surface flags ?
    //warning no protection offered here in case of wrong / unsupported size ( for the moment )
}

ScreenBuffer::~ScreenBuffer()
{
}

/*
void ScreenBuffer::setSize(int width, int height)
{
    //force usage of DEFAULT_DISPLAY_WIDTH & DEFAULT_DISPLAY_HEIGHT when only one param is equal to 0.
    if ((width == 0 && height != 0) || (width != 0 && height == 0))
    {
        width = DEFAULT_DISPLAY_WIDTH;
        height = DEFAULT_DISPLAY_HEIGHT;
    }
    //TODO get rid of default display size and try 4/3 size, or pick first of suggested size by video info

    //Both equal to 0 means use dekstop/current mode.
    if (width == 0 && height == 0)
    {
        width = m_bestvideoinfo.getCurrentWidth();
        height = m_bestvideoinfo.getCurrentHeight();
    }

    m_width = width;
    m_height = height;

}

void ScreenBuffer::setBPP(int bpp)
{

    if ( bpp == 0 ) //here 0 means autodetection
    {
        bpp=m_videoinfo.getSuggestedBPP(m_width, m_height);
    }
    else
    {
        //TODO : check that the value of bpp asked for is supported...
    }

    m_videoinfo.bpp = bpp;

}

bool ScreenBuffer::setResizable(bool val)
{
    bool res = true;
    if (!m_screen.get()) //if not already created, set the requested videoinfo
    {
        m_videoinfo.request().setResizable(val);
    }
    else if (m_screen->isResizableset() !=val ) //if called inside mainLoop while screen is active
    {
        hide();
        m_videoinfo.request().setResizable(val); //set new requested videoinfo
        if (! show()) //reset the screen
            res=false;
    }
    return res;
}

bool ScreenBuffer::setFullscreen(bool val)
{
#ifdef DEBUG
    Log << nl << "ScreenBuffer::setFullscreen(" << val << ") called" << std::endl;
#endif

    bool res = true;
    if (!m_screen.get())
    {
        m_videoinfo.request().setFullscreen(val);
    }
    else
    {
#ifdef DEBUG
        Log << nl << m_screen->isFullScreenset() << " != " << val << std::endl;
#endif
        if (m_screen->isFullScreenset() != val ) //if called inside mainLoop while screen is active
        {
            hide();
            m_videoinfo.request().setFullscreen(val);
            if (! show() )//resetDisplay(m_screen->getWidth(),m_screen->getHeight(),m_screen->getBPP()))
            {
                res=false;
            }
        }
    }

#ifdef DEBUG
    Log << nl << "ScreenBuffer::setFullscreen(" << val << ") done" << std::endl;
#endif
    return res;
}

bool ScreenBuffer::setNoFrame(bool val)
{
    bool res = true;
    if (!m_screen.get())
        m_videoinfo.request().setNoFrame(val);
    else if (m_screen->isNoFrameset() !=val )  //if called inside mainLoop while screen is active
    {
        hide();
        m_videoinfo.request().setNoFrame(val);
        if (! show() ) //resetDisplay(m_screen->getWidth(),m_screen->getHeight(),m_screen->getBPP()))
            res=false;
    }
    return res;
}

#ifdef WK_SDLut_FOUND_OPENGL
bool ScreenBuffer::setOpenGL(bool val)
{

#ifdef DEBUG
    Log << nl << "ScreenBuffer::setOpenGL(" << val << ") called" << std::endl;
#endif

    bool res = true;
    if (!m_screen.get())
    {
        m_videoinfo.request().setOpenGL(val);
    }
    else
    {
        if (m_screen->isOpenGLset() != val ) //if called inside mainLoop while screen is active
        {
            hide();
            m_videoinfo.request().setOpenGL(val);
            if (! show() )//resetDisplay(m_screen->getWidth(),m_screen->getHeight(),m_screen->getBPP()))
            {
                res=false;
            }
        }
    }

#ifdef DEBUG
    Log << nl << "ScreenBuffer::setOpenGL(" << val << ") done" << std::endl;
#endif
    return res;
}
#endif

//to check the current properties of the display
bool ScreenBuffer::isFullscreen()
{
    if (m_screen.get())
    {
        return m_screen->isFullScreenset();
    }
    else
    {
        return ( SDL_FULLSCREEN & m_videoinfo.request().getNewSurfaceFlags() ) != 0;
    }
}
bool ScreenBuffer::isResizable()
{
    if (m_screen.get())
    {
        return m_screen->isResizableset();
    }
    else
    {
        return ( SDL_RESIZABLE & m_videoinfo.request().getNewSurfaceFlags() ) != 0;
    }
}
bool ScreenBuffer::isOpenGL()
{
    if (m_screen.get())
    {
        //accurate check
        return m_screen->isOpenGLset();
    }
    else
    {
        return (SDL_OPENGL & m_videoinfo.request().getNewSurfaceFlags() ) != 0;
    }
}
bool ScreenBuffer::isNoFrame()
{

    if (m_screen.get())
    {
        return m_screen->isNoFrameset();
    }
    else
    {
        return ( SDL_NOFRAME & m_videoinfo.request().getNewSurfaceFlags() ) != 0;
    }
}
*/


unsigned int ScreenBuffer::getWidth()
{
    return m_screen->getWidth();
}
unsigned int ScreenBuffer::getHeight()
{
    return m_screen->getHeight();
}
unsigned short ScreenBuffer::getBPP()
{
    return static_cast<unsigned short>( m_screen->getVideoInfo().getPixelFormat().getBitsPerPixel() );
}

bool ScreenBuffer::resize (unsigned int width,unsigned int height)
{

#ifdef DEBUG
    Log << nl << "Screen::resize() called ...";
#endif

    bool res = true;

    //NEW DESIGN : always the case
    //if (m_screen.get())
    //{
    res = res && m_screen->resize(width,height);//doesnt keep content


    //We do need to resetthis order otherwise we lose opengl context from the engine just after the resize ( reinit )
    //because screen resize recreates the window, and lose opengl context as documented in SDL docs...
    //}
    //else
    //{
    //    m_scinfo->requestSize( (width>0) ? width : 0 , (height>0) ? height : 0 );
    //}

    //resizing background surface
    //m_bgsurf->resize(m_screen->getWidth(), m_screen->getHeight());
    //m_bgsurf->fill(m_background);

    //resetting our Engine. Useful if OpenGL dependent : need to reload the new created context
    //resizing engine doesnt make much sense though.
    m_engine.reset(new internal::SDLEngine());


#ifdef DEBUG
    Log << nl << "ScreenBuffer::resize() done.";
#endif

    requestFullRefresh();
    m_screen->refresh();

    return res;
}

bool ScreenBuffer::renderpass( unsigned long framerate, unsigned long& lastframe)
{
    //calling our engine render function ( on top of user render )
    //TODO : add a timer to display logos if not demo release...

    m_engine->render(*m_screen);

    return true; //todo
}

bool ScreenBuffer::refresh( unsigned long framerate, unsigned long& lastframe)
{
    //refresh screen
    //Log << nl << "before :" << SDL_GetTicks() - lastframe ;
    if ( SDL_GetTicks() - lastframe < 1000/framerate)//wait if needed - IMPORTANT otherwise the next value is far too high (not 0)
        SDL_Delay( 1000/framerate - ( SDL_GetTicks() - lastframe ) );

    //TODO : this could be handled by calling a virtual function and letting inheritance do the rest, which would be nicer.
    //However it implies that the VideoSurface itself would manage list of rectangles to refresh...
    // Maybe later...
    if ( m_screen->getRenderer() == internal::OpenGL )
    {
        m_screen->refresh();

        //clear just in case ( shouldnt change anything )
        refreshlist.clear();
    }
    else
    {
        Color black(128,0,0);
        if ( fullRefreshNeeded ) // first render, or periodically to avoid problems...
        {
            fullRefreshNeeded = false;
            m_screen->refresh();

            oldlist.clear(); // we dont need to refresh the old ones the next time.
        }
        else
        {

            //now refreshing only what is needed
            //these have been cleared previously
            //just need to update them
            m_screen->erase(oldlist);

            //display new blits
            m_screen->update(refreshlist);

            oldlist=refreshlist;

            refreshlist.clear();
        }



    }


    //Log << nl << "after :" << SDL_GetTicks() - lastframe ;

    lastframe=SDL_GetTicks();

    return true; //not used for now
}

bool ScreenBuffer::captureBMP(std::string filename) const
{
    m_screen->saveBMP(filename);
    return true;
}




//pixel drawing function
Color ScreenBuffer::getColorAt(unsigned int x, unsigned int y)
{
    Color res;
    //We need to check the pixel is in the ScreenBuffer
    if (x >= 0 && y >= 0 && x < getWidth() && y < getHeight())
    {
        res = m_screen->getVideoInfo().getPixelFormat().getColor(m_screen->getpixel(x, y));
    }
    else
    {
        throw std::logic_error("Trying to get a pixel outside of ScreenBuffer range");
    }
    return res;
}

void ScreenBuffer::setColorAt(unsigned int x,unsigned int y, const Color & pixel)
{
    //We need to check the pixel is in the ScreenBuffer
    if (x >= 0 && y >= 0 && x < getWidth() && y < getHeight())
    {
        PixelColor pcolor = m_screen->getVideoInfo().getPixelFormat().getPixelColor(pixel);
        //we need to take care about alpha blending.
        //we need to maintain same behaviour as the blitting with alpha.
        //http://www.libsdl.org/cgi/docwiki.cgi/SDL_SetAlpha
        if ( m_screen->getVideoInfo().getPixelFormat().getAmask() == 0 ) //screen doesnt support alpha pixel format
        {
            if ( !m_screen->isOpenGLset() ) // screen is not opengl : alpha blending pixel not supported
            {
                if ( pixel.hasAlpha() ) // we have alpha
                {
                    //reset color with preblending computation
                    pcolor = m_screen->getVideoInfo().getPixelFormat().getPixelColor(blend(pixel,m_screen->getVideoInfo().getPixelFormat().getColor(m_screen->getpixel(x,y))));
                }
            }
            else//m_screen->isOpenGLset() -> we can keep alpha
            {
                //adding Alpha to pixel color
                //as the SDL_pixelformat for OpenGL discards alpha information
                PixelColor alpha = pixel.getA() ;
                PixelColor properalpha = (alpha << (m_screen->getVideoInfo().getPixelFormat().getBitsPerPixel() - m_screen->getVideoInfo().getPixelFormat().getAloss()) );
                pcolor = pcolor | properalpha ;
            }
        }
        else //pcolor should be properly set
        {
            //Really is there one screen that support this ??
            //GLPixelFormat ??
        }

        m_screen->setpixel(x, y,pcolor);
        refreshlist.push_back(Rect(x,y));
    }
    else
    {
        throw std::logic_error("Trying to set a pixel outside of ScreenBuffer range");
    }
}

void ScreenBuffer::setColorAt(Rect& dest_rect, const Color & pixel)
{
    //We need to check the rect is in the ScreenBuffer
    if (dest_rect.getx() >= 0 && dest_rect.gety() >= 0 && dest_rect.getx()+dest_rect.getw() < getWidth() && dest_rect.gety()+dest_rect.geth() < getHeight())
    {
        PixelColor pcolor = m_screen->getVideoInfo().getPixelFormat().getPixelColor(pixel);
        //we need to take care about alpha blending.
        //we need to maintain same behaviour as the blitting with alpha.
        //http://www.libsdl.org/cgi/docwiki.cgi/SDL_SetAlpha
        if ( m_screen->getVideoInfo().getPixelFormat().getAmask() == 0 ) //screen doesnt support alpha pixel format
        {
            if ( !m_screen->isOpenGLset() ) // screen is not opengl : alpha blending pixel not supported
            {
                if ( pixel.hasAlpha() ) // we have alpha
                {
                    //BUG HERE : how to handle transparency on a fill ????
                    //reset color with preblending computation
                    pcolor = m_screen->getVideoInfo().getPixelFormat().getPixelColor(blend(pixel,m_screen->getVideoInfo().getPixelFormat().getColor(m_screen->getpixel(dest_rect.getx(),dest_rect.gety()))));
                }
            }
            else//m_screen->isOpenGLset() -> we can keep alpha
            {
                //adding Alpha to pixel color
                //as the SDL_pixelformat for OpenGL discards alpha information
                PixelColor alpha = pixel.getA() ;
                PixelColor properalpha = (alpha << (m_screen->getVideoInfo().getPixelFormat().getBitsPerPixel() - m_screen->getVideoInfo().getPixelFormat().getAloss()) );
                pcolor = pcolor | properalpha ;
            }
        }
        else //pcolor should be properly set
        {
            //Really is there one screen that support this ??
            //GLPixelFormat ??
        }

        m_screen->fill(pcolor,dest_rect);
        refreshlist.push_back(dest_rect);
    }
    else
    {
        throw std::logic_error("Trying to set a pixel outside of ScreenBuffer range");
    }
}






void ScreenBuffer::resetClipRect( const Rect& clipr )
{
    m_screen->resetClipRect(clipr);
    //adding to refresh list here, in case we use applyBGColor with different color, we need to refresh it properly
    //NB we could also do the refresh when we set ApplyBG color, but that kill the point of smart refresh
    //if we applyBGcolor at everyrender, like now...
    //Now we kill the point of smart refresh only in the clip rect, which is slightly better... yet not perfect...
    //TODO FIX IT !!!
    //-> apply BG Color only when color actually change, and adapt refresh strategy accordingly.
    refreshlist.push_back(clipr);

}


Rect ScreenBuffer::getClipRect( void ) const
{
    return m_screen->getClipRect();
}

bool ScreenBuffer::blit (const Image& src, Rect& dest_rect, const Rect& src_rect)
{
    //NOTE :
    //conversion will be done in Video GLSurface, only if really needed to
    //handle the VideoGL -> blit RGBSurf case. And only this one.

    m_screen->blit( *(src.m_img) , dest_rect, src_rect );

    // adding recangle to the list of rectangle to refresh
    refreshlist.push_back(dest_rect);
    //TODO: TEST extensively...

    return true; //todo
}


} // SDL
} // SDLut
