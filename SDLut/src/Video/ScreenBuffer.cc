#include "Video/ScreenBuffer.hh"
#include "SDLConfig.hh"

using namespace RAGE;

namespace SDLut
{
namespace video
{

ScreenBuffer::ScreenBuffer(int width, int height, int bpp, Manager* manager) throw (std::logic_error)
        : m_width(width), m_height(height),m_bpp(bpp), fullRefreshNeeded(true), pm_manager(manager), m_background(Color(0,0,0))
{

//setting the required flags...
#ifdef WK_OPENGL_FOUND
        //OpenGL set by default
        setOpenGL(true);
#endif
        //default
        setFullscreen(false);
        setResizable(true);
        setNoFrame(false);

#ifdef WK_OPENGL_FOUND
    //Here SDL_Init(SDL_VIDEO) has already been called
    internal::VideoSurface::sptm_vinfo = new internal::OGL::OGLVideoInfo();
#else
    //Here SDL_Init(SDL_VIDEO) has already been called
    internal::VideoSurface::sptm_vinfo = new internal::VideoInfo();
#endif

    setSize( width, height );

    setBPP ( bpp );



    //but beware about bpp == 0...
    if (m_bpp == 0 )
    {//0 as return code mean the current format is not supported
        Log << nl << "The requested video mode is not supported under any bit depth. Screen creation cancelled !";
        throw std::logic_error("VideoSurface::getSuggestedBPP(width, height) returned 0");
    }

    //we need a manager to manage settings
    if (! pm_manager )
    {
        Log << nl << "The requested SDLManager hasnt been properly passed to ScreenBuffer Constructor. Screen creation cancelled !";
        throw std::logic_error("SDL::Manager manager parameter points to 0x0");
    }
}

//recreating Engine here to make sure both origin and destination engines are independant.
//maybe not really needed, but safer in case of copy ( or should we completely forbid copy ? )
ScreenBuffer::ScreenBuffer( const ScreenBuffer & sb )
        : m_width(sb.m_width), m_height(sb.m_height),m_bpp(sb.m_bpp), fullRefreshNeeded(true),pm_manager(sb.pm_manager), m_background(sb.m_background)
{
    //also what about video surface flags ?
    //warning no protection offered here in case of wrong / unsupported size ( for the moment )
}

ScreenBuffer::~ScreenBuffer()
{
}


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
        width = internal::VideoSurface::getVideoInfo()->getCurrentWidth();
        height = internal::VideoSurface::getVideoInfo()->getCurrentHeight();
    }

    m_width = width;
    m_height = height;

}

void ScreenBuffer::setBPP(int bpp)
{

    if ( bpp == 0 ) //here 0 means autodetection
    {
        bpp=internal::VideoSurface::getSuggestedBPP(m_width, m_height);
    }
    else
    {
        //TODO : check that the value of bpp asked for is supported...
    }

    m_bpp = bpp;

}

bool ScreenBuffer::setResizable(bool val)
{
    bool res = true;
    if (!m_screen.get()) //if not already created, set the static flag.
    {
        internal::VideoSurface::setResizable(val);
    }
    else if (m_screen->isResizableset() !=val ) //if called inside mainLoop while screen is active
    {
        hide();
        internal::VideoSurface::setResizable(val); //set static flag
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
        internal::VideoSurface::setFullscreen(val);
    }
    else
    {
#ifdef DEBUG
        Log << nl << m_screen->isFullScreenset() << " != " << val << std::endl;
#endif
        if (m_screen->isFullScreenset() != val ) //if called inside mainLoop while screen is active
        {
            hide();
            internal::VideoSurface::setFullscreen(val);
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
        internal::VideoSurface::setNoFrame(val);
    else if (m_screen->isNoFrameset() !=val )  //if called inside mainLoop while screen is active
    {
        hide();
        internal::VideoSurface::setNoFrame(val);
        if (! show() ) //resetDisplay(m_screen->getWidth(),m_screen->getHeight(),m_screen->getBPP()))
            res=false;
    }
    return res;
}

#ifdef WK_OPENGL_FOUND
bool ScreenBuffer::setOpenGL(bool val)
{

#ifdef DEBUG
    Log << nl << "ScreenBuffer::setOpenGL(" << val << ") called" << std::endl;
#endif

    bool res = true;
    if (!m_screen.get())
    {
        internal::VideoSurface::setOpenGL(val);
    }
    else
    {
        if (m_screen->isOpenGLset() != val ) //if called inside mainLoop while screen is active
        {
            hide();
            internal::VideoSurface::setOpenGL(val);
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
        return ( SDL_FULLSCREEN & internal::VideoSurface::ptm_defaultflags ) != 0;
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
        return ( SDL_RESIZABLE & internal::VideoSurface::ptm_defaultflags ) != 0;
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
        return (SDL_OPENGL & internal::VideoSurface::ptm_defaultflags ) != 0;
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
        return ( SDL_NOFRAME & internal::VideoSurface::ptm_defaultflags ) != 0;
    }
}

void ScreenBuffer::applyBGColor() const
{
    if (m_screen.get()) // if auto pointer valid
    {

        //TODO : TEST alpha transparent background color...
#ifdef WK_OPENGL_FOUND
        if (m_screen->isOpenGLset())
        {

//            glClearColor(0.0f,0.0f,0.0f,0.0f); // default opengl
            glClearColor(static_cast<float> (m_background.getR() ) / 255.0f, static_cast<float> (m_background.getG() ) / 255.0f,static_cast<float> (m_background.getB() ) / 255.0f, 1.0f-(static_cast<float>(m_background.getA()) / 255.0f));
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        else
        {
#endif
            m_screen->fill(m_screen->getPixelFormat().getPixelColor(m_background));
#ifdef WK_OPENGL_FOUND
        }
#endif
    }
}



bool ScreenBuffer::show()
{
#ifdef DEBUG
    Log << nl << "SceenBuffer::show() called ..." << std::endl;
#endif
    if ( m_screen.get() != NULL ) // no need to reset the display
    {			//if reset is wanted the buffer should be recreated
        return true;
    }
    //else the screen hasnt been displayed yet, or has been hidden.
    bool res = false;

    Log << nl <<"SDL is using " << m_width << "x" << m_height << "@" <<m_bpp;
    //create a new screen
    try
    {
        #ifdef WK_OPENGL_FOUND
        m_screen.reset(new internal::OGL::VideoGLSurface(m_width, m_height, m_bpp));
        #else
        m_screen.reset(new internal::VideoSurface(m_width, m_height, m_bpp));
        #endif

        //initializing engine
        m_engine.reset(new internal::SDLEngine());

        requestFullRefresh();
        res=true;
    }
    catch (std::exception & e)
    {
        Log << nl << " Exception caught in Window::resetDisplay() : " << e.what();
        res=false;
    }
#ifdef DEBUG
    Log << nl << "ScreenBuffer::show() done." << std::endl;
#endif
    return res;
}

bool ScreenBuffer::hide()
{
    delete m_screen.release();// to test...
    return true; //not used for now
}

bool ScreenBuffer::resize (int width, int height)
{

#ifdef DEBUG
    Log << nl << "Screen::resize() called ...";
#endif

    bool res = true;

    if (m_screen.get())
    {
        res = res && m_screen->resize(width,height);//doesnt keep content

        //resetting our Engine. Useful if OpenGL dependent : need to reload the new created context
        //resizing engine doesnt make much sense though.
        m_engine.reset(new internal::SDLEngine());

        //We do need to resetthis order otherwise we lose opengl context from the engine just after the resize ( reinit )
        //because screen resize recreates the window, and lose opengl context as documented in SDL docs...
    }
    else
    {
        setSize( (width>0) ? width : 0 , (height>0) ? height : 0 );
    }
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

    //TODO : we can here compute what part of the screen should be refreshed...
    //for the user render callback, we can ask/expect a refresh zone in return...

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
        if ( fullRefreshNeeded ) // first render, or periodically to avoid problems...
        {
            fullRefreshNeeded = false;
            m_screen->refresh();
            oldlist.clear(); // we dont need to refresh the old ones the next time.
        }
        else
        {

            //now refreshing only what is needed
            m_screen->update(refreshlist);
            m_screen->update(oldlist);
            oldlist=refreshlist;
            //clear should be done here
            refreshlist.clear();
        }
    }


    //Log << nl << "after :" << SDL_GetTicks() - lastframe ;

    lastframe=SDL_GetTicks();

    return true; //not used for now
}

void ScreenBuffer::setClipRect( const Rect& clipr )
{
    m_screen->setClipRect(clipr);
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

bool ScreenBuffer::fill (const Color& color, const Rect& dest_rect)
{
    m_screen->fill(m_screen->getPixelFormat().getPixelColor(color),dest_rect);
    return true; //todo
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
