#include "Video/ScreenBuffer.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

ScreenBuffer::ScreenBuffer(int width, int height, int bpp, Manager* manager) throw (std::logic_error)
        : m_width(width), m_height(height),m_bpp(bpp), pm_manager(manager), m_background(RGBColor(0,0,0))
{

    //setting the static videoInfo to be used by all surfaces...
    BaseSurface::_vinfo = &m_videoinfo;

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
        width = VideoSurface::getVideoInfo()->get_current_width();
        height = VideoSurface::getVideoInfo()->get_current_height();
    }

    if ( bpp == 0 ) //here 0 means autodetection
    {
        bpp=VideoSurface::getSuggestedBPP(width, height);
    }
    else
    {
        //TODO : check that the value of bpp asked for is supported...
    }

    m_width = width;
    m_height = height;
    m_bpp = bpp;


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
        : m_width(sb.m_width), m_height(sb.m_height),m_bpp(sb.m_bpp), pm_manager(sb.pm_manager), m_background(sb.m_background)
{
    //warning no protection offered here in case of wrong / unsupported size ( for the moment )
}

ScreenBuffer::~ScreenBuffer()
{
    BaseSurface::_vinfo = NULL;
}



bool ScreenBuffer::setResizable(bool val)
{
    bool res = true;
    if (!m_screen.get()) //if not already created, set the static flag.
        VideoSurface::setResizable(val);
    else if (m_screen->isResizableset() !=val ) //if called inside mainLoop while screen is active
    {
        hide();
        VideoSurface::setResizable(val); //set static flag
        if (! show()) //reset the screen
            res=false;
    }
    return res;
}

bool ScreenBuffer::setFullscreen(bool val)
{
#ifdef DEBUG
    Log << nl << "Window::setFullscreen(" << val << ") called" << std::endl;
#endif

    bool res = true;
    if (!m_screen.get())
    {
        VideoSurface::setFullscreen(val);
    }
    else
    {
#ifdef DEBUG
        Log << nl << m_screen->isFullScreenset() << " != " << val << std::endl;
#endif
        if (m_screen->isFullScreenset() != val ) //if called inside mainLoop while screen is active
        {
            hide();
            VideoSurface::setFullscreen(val);
            if (! show() )//resetDisplay(m_screen->getWidth(),m_screen->getHeight(),m_screen->getBPP()))
            {
                res=false;
            }
        }
    }

#ifdef DEBUG
    Log << nl << "Window::setFullscreen(" << val << ") done" << std::endl;
#endif
    return res;
}

bool ScreenBuffer::setNoFrame(bool val)
{
    bool res = true;
    if (!m_screen.get())
        VideoSurface::setNoFrame(val);
    else if (m_screen->isNoFrameset() !=val )  //if called inside mainLoop while screen is active
    {
        hide();
        VideoSurface::setNoFrame(val);
        if (! show() ) //resetDisplay(m_screen->getWidth(),m_screen->getHeight(),m_screen->getBPP()))
            res=false;
    }
    return res;
}

#ifdef WK_OPENGL_FOUND
bool ScreenBuffer::setOpenGL(bool val)
{
    bool res = true;

    if (!m_screen.get())
    {
        if ( val )
        {
            pm_manager->enableOpenGL();
        }
        else
        {
            pm_manager->disableOpenGL();
        }

    }
    else if ( m_screen->isOpenGLset() !=val ) //if called inside mainLoop while screen is active
    {
        hide();

        if ( val )
        {
            pm_manager->enableOpenGL();
        }
        else
        {
            pm_manager->disableOpenGL();
        }

        if (! show() )//resetDisplay(m_screen->getWidth(),m_screen->getHeight(),m_screen->getBPP()))
            res=false;
    }
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
        return ( SDL_FULLSCREEN & VideoSurface::_defaultflags ) != 0;
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
        return ( SDL_RESIZABLE & VideoSurface::_defaultflags ) != 0;
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
        //check through SDLManager
        return pm_manager->isOpenGLEnabled();
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
        return ( SDL_NOFRAME & VideoSurface::_defaultflags ) != 0;
    }
}

void ScreenBuffer::applyBGColor() const
{
    if (m_screen.get()) // if auto pointer valid
    {
#ifdef WK_OPENGL_FOUND
        if (m_screen->isOpenGLset())
        {
            glClearColor(static_cast<float> (m_background.getR() ) / 255.0f, static_cast<float> (m_background.getG() ) / 255.0f,static_cast<float> (m_background.getB() ) / 255.0f,0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        else
        {
#endif
            //TODO background can be null, andthis will not be called.... ( speed improvemnt )
            m_screen->fill(m_background);
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
    {			//if reset is wanted the buffer shoul be recreated
        return true;
    }
    //else the screen hasnt been displayed yet, or has been hidden.
    bool res = false;

    Log << nl <<"SDL is using " << m_width << "x" << m_height << "@" <<m_bpp;
    //create a new screen
    try
    {
        if ( isOpenGL() )
        {
            m_screen.reset(new VideoGLSurface(m_width, m_height, m_bpp));
        }
        else
        {
            m_screen.reset(new VideoSurface(m_width, m_height, m_bpp));
        }
        //initializing engine
        m_engine.init(m_width, m_height);

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

        //calling our engine resize method
        res = res && m_engine.resize(width,height);

        //this order otherwise we lose opengl context from the engine just after the resize ( reinit )
        //because screen resize recreates the window, and lose opengl context as documented in SDL docs...
    }
    else
    {
        if (width>0)
        {
            m_width = width;
        }
        if (height>0)
        {
            m_height= height;
        }
    }
#ifdef DEBUG
    Log << nl << "ScreenBuffer::resize() done.";
#endif

    m_screen->refresh();

    return res;
}

bool ScreenBuffer::renderpass( unsigned long framerate, unsigned long& lastframe)
{
    //calling our engine render function ( on top of user render )
    //TODO : add a timer to display logos if not demo release...
    m_engine.render(*m_screen);

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
    if ( m_screen->getRenderer() == OpenGL )
    {
        m_screen->refresh();
    }
    else
    {
        //now refreshing only what is needed
        m_screen->update(refreshlist);
        m_screen->update(oldlist);
        oldlist=refreshlist;
    }
    //clear can be done here, just in case we filled it up in OpenGL by mistake
    refreshlist.clear();


    //Log << nl << "after :" << SDL_GetTicks() - lastframe ;

    lastframe=SDL_GetTicks();

    return true; //not used for now
}

void ScreenBuffer::setClipRect( const Rect& clipr )
{
    m_screen->setClipRect(clipr);
}


Rect ScreenBuffer::getClipRect( void ) const
{
    return m_screen->getClipRect();
}

bool ScreenBuffer::fill (const RGBAColor& color, const Rect& dest_rect)
{
    m_screen.get()->fill(color,dest_rect);
    return true; //todo
}

bool ScreenBuffer::blit (const Image& src, Rect& dest_rect, const Rect& src_rect)
{
    //optimising the surface if necessary
    const_cast<Image&>(src).convertToDisplayFormat(m_screen->getRenderer());

    //careful... we need double polymorphism here in the end...
    m_screen.get()->blit( *(src.m_img) , dest_rect, src_rect );

    // adding recangle to the list of rectangle to refresh
    refreshlist.push_back(dest_rect);
    //TODO: TEST extensively...

    return true; //todo
}


} // SDL
} // RAGE
