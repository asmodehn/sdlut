#include "Video/ScreenBuffer.hh"
#include "SDLConfig.hh"

namespace RAGE
{
	namespace SDL
	{

		ScreenBuffer::ScreenBuffer(int width, int height, int bpp) throw (std::logic_error)
		: m_width(width), m_height(height),m_bpp(bpp), m_background(RGBColor(0,0,0)),
		m_initcb(NULL),m_resizecb(NULL), m_newframecb(NULL), m_rendercb(NULL)
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
		}

        //recreating Engine here to make sure both origin and destination engines are independant.
        //maybe not really needed, but safer in case of copy ( or should we completely forbid copy ? )
		ScreenBuffer::ScreenBuffer( const ScreenBuffer & sb )
		: m_width(sb.m_width), m_height(sb.m_height),m_bpp(sb.m_bpp), m_background(sb.m_background),
		m_initcb(sb.m_initcb),m_resizecb(sb.m_resizecb), m_newframecb(sb.m_newframecb), m_rendercb(sb.m_rendercb)
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

#ifdef HAVE_OPENGL
        bool ScreenBuffer::setOpenGL(bool val)
        {
            bool res = true;

            if (!m_screen.get())
			{
				VideoSurface::setOpenGL(val);
			}
            else if ( m_screen->isOpenGLset() !=val ) //if called inside mainLoop while screen is active
            {
				hide();
                VideoSurface::setOpenGL(val);
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
			return m_screen->isOpenGLset();
		}
		else
		{
			return ( SDL_OPENGL & VideoSurface::_defaultflags ) != 0;
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
#ifdef HAVE_OPENGL
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
#ifdef HAVE_OPENGL
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

			//calling user init callback if it exists
			if ( m_initcb ) m_initcb->call( m_width, m_height );

			applyBGColor();
			res=true;
        }
        catch(std::exception & e)
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

			//calling user callback for resize if it exists
			if ( m_resizecb ) m_resizecb->call(width, height);
			//this order otherwise we lose opengl context from the engine just after the resize ( reinit )
			//because screen resize recreates the window, and lose opengl context as documented in SDL docs...
			applyBGColor();
		}
		else
		{
			if (width>0) { m_width = width; }
			if (height>0) { m_height= height; }
		}
#ifdef DEBUG
		Log << nl << "ScreenBuffer::resize() done.";
#endif

		//Forcing the refresh (display the backcolor)
		m_screen->refresh();

        return res;
	}

		bool ScreenBuffer::renderpass( unsigned long framerate, unsigned long& lastframe)
		{
		    //Callback for preparing new frame
		    if ( m_newframecb )
				m_newframecb->call( framerate, SDL_GetTicks() - lastframe );

			//applying the background
					//if (!ShowingLoadingScreen)
						applyBGColor();

					//if (!ShowingLoadingScreen)
                		if ( m_rendercb )
							m_rendercb->call( *m_screen );

                		//calling our engine render function ( on top of user render )
                		//TODO : add a timer if not demo release...
                		m_engine.render(*m_screen);

					//refresh screen
					//Log << nl << "before :" << SDL_GetTicks() - lastframe ;
					if ( SDL_GetTicks() - lastframe < 1000/framerate)//wait if needed - IMPORTANT otherwise the next value is far too high (not 0)
						SDL_Delay( 1000/framerate - ( SDL_GetTicks() - lastframe ) );

					m_screen->refresh();
					//Log << nl << "after :" << SDL_GetTicks() - lastframe ;

					lastframe=SDL_GetTicks();

					//calling engine for postrender events
					//m_engine ->postrender();

					return true; //not used for now
		}
		

	} // SDL
} // RAGE
