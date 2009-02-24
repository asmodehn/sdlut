#include "Video/SDLWindow.hh"
#include "System/SDLEventManager.hh"
#include "SDLConfig.hh"
#include "SDLResources.inc"

namespace RAGE
{
    namespace SDL
    {


        bool Window::iconify(void)
        {
            return ( SDL_WM_IconifyWindow() != 0 );
        }

        void Window::grabInput()
        {
            SDL_WM_GrabInput( SDL_GRAB_ON );
        }

        void Window::releaseInput()
        {
            SDL_WM_GrabInput( SDL_GRAB_OFF );
        }

        bool Window::isInputGrabbed()
        {
            return SDL_WM_GrabInput( SDL_GRAB_QUERY ) == SDL_GRAB_ON;
        }

        void Window::setCaption(std::string title, std::string iconname)
        {
            _title=title;
            _iconname=iconname;
            SDL_WM_SetCaption(_title.c_str(), _iconname.c_str());
            //seticon needed or ?
        }

        void Window::setIcon(const RGBSurface & icon)
        {
	    _icon = icon;
            SDL_WM_SetIcon( const_cast<SDL_Surface*>(&_icon.get_rSDL()) , NULL);
        }

        //old version
        void Window::getCaption(std::string & title, std::string & iconname)
        {
            char t[256]= {}; //size ??
            char i[256]= {}; //size ??
            SDL_WM_GetCaption((char**)&t,(char**)&i); // to test on gcc.. be careful about long strings...
            title=std::string(t);
            iconname=std::string(i);
        }

        std::string Window::getTitle()
        {
            char t[256]= {}; //size ??
            SDL_WM_GetCaption((char**)&t,NULL); // to test on gcc.. be careful about long strings...
            return std::string(t);

        }
        std::string Window::getIconName()
        {
            char i[256]= {}; //size ??
            SDL_WM_GetCaption(NULL,(char**)&i); // to test on gcc.. be careful about long strings...
            return std::string(i);
        }

        bool Window::setResizable(bool val)
        {
            bool res = true;
            if (!pvm_screen.get())
                VideoSurface::setResizable(val);
            else if (pvm_screen->isResizableset() !=val ) //if called inside mainLoop while screen is active
            {
				VideoSurface::setResizable(val);
                if (! resetDisplay(pvm_screen->getWidth(),pvm_screen->getHeight(),pvm_screen->getBPP()))
                    res=false;
            }
            return res;
        }

        bool Window::setFullscreen(bool val)
        {
#ifdef DEBUG
            Log << nl << "Window::setFullscreen(" << val << ") called" << std::endl;
#endif

            bool res = true;
            if (!pvm_screen.get())
	    {
                VideoSurface::setFullscreen(val);
	    }
            else
            {
#ifdef DEBUG
                Log << nl << pvm_screen->isFullScreenset() << " != " << val << std::endl;
#endif

                if (pvm_screen->isFullScreenset() != val ) //if called inside mainLoop while screen is active
                {
			VideoSurface::setFullscreen(val);
			if (! resetDisplay(pvm_screen->getWidth(),pvm_screen->getHeight(),pvm_screen->getBPP()))
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

        bool Window::setNoFrame(bool val)
        {
            bool res = true;
            if (!pvm_screen.get())
                VideoSurface::setNoFrame(val);
            else if (pvm_screen->isNoFrameset() !=val )  //if called inside mainLoop while screen is active
            {
				VideoSurface::setNoFrame(val);
                if (! resetDisplay(pvm_screen->getWidth(),pvm_screen->getHeight(),pvm_screen->getBPP()))
                    res=false;
            }
            return res;
        }
#ifdef HAVE_OPENGL
        bool Window::setOpenGL(bool val)
        {
            bool res = true;

			if (val)
			{
				setEngine(new DefaultGLEngine());
				_userengine=false;
			}
			else
			{
				setEngine(new DefaultEngine());
				_userengine=false;
			}

            if (!pvm_screen.get())
			{
				VideoSurface::setOpenGL(val);
			}
            else if ( pvm_screen->isOpenGLset() !=val ) //if called inside mainLoop while screen is active
            {
                VideoSurface::setOpenGL(val);
                if (! resetDisplay(pvm_screen->getWidth(),pvm_screen->getHeight(),pvm_screen->getBPP()))
                    res=false;
            }
            return res;
        }
#endif

	//to check the current properties of the display
	bool Window::isFullscreen()
	{
		if (pvm_screen.get())
		{
			return pvm_screen->isFullScreenset();
		}
		else
		{
			return ( SDL_FULLSCREEN & VideoSurface::_defaultflags ) != 0;
		}
	}
	bool Window::isResizable()
	{
		if (pvm_screen.get())
		{
			return pvm_screen->isResizableset();
		}
		else
		{
			return ( SDL_RESIZABLE & VideoSurface::_defaultflags ) != 0;
		}
	}
	bool Window::isOpenGL()
	{
		if (pvm_screen.get())
		{
			return pvm_screen->isOpenGLset();
		}
		else
		{
			return ( SDL_OPENGL & VideoSurface::_defaultflags ) != 0;
		}
	}
	bool Window::isNoFrame()
	{

		if (pvm_screen.get())
		{
			return pvm_screen->isNoFrameset();
		}
		else
		{
			return ( SDL_NOFRAME & VideoSurface::_defaultflags ) != 0;
		}
	}

        Window::Window(std::string title)
		 :	_title(title),
			_background(Color(0,0,0)),
			pvm_screen(0),
			_icon ( RWOps( _defaultIcon, sizeof(_defaultIcon))),
			myLoadingScreen(NULL),
			ShowingLoadingScreen(false),
			m_exitMainLoop(false)
        {
#ifdef DEBUG
            Log << nl << "Window::Window(" << title << ") called ..." ;
#endif

            try
            {
		_engine = new DefaultEngine();
                _userengine=false;
            }
            catch (std::exception &e)
            {
                Log << nl << e.what() << std::endl;
            }

            //setting the static videoInfo to be used by all surfaces...
            BaseSurface::_vinfo = &pvm_videoinfo;

            setCaption(_title,"DefaultIcon");
	    SDL_WM_SetIcon( const_cast<SDL_Surface*>(&_icon.get_rSDL()) , NULL);

#ifdef DEBUG

            Log << nl << "Window::Window(" << title << ") done @ "<< this ;
#endif

        }


        Window::~Window()
        {
#ifdef DEBUG
            Log << nl << "Window::~Window() called ..." << std::endl;
#endif			
            if (!_userengine) //if the user set his own engine , he is responsible for deleting it
                delete _engine, _engine = NULL;

			if (myLoadingScreen != NULL)
				delete myLoadingScreen, myLoadingScreen = NULL;

            BaseSurface::_vinfo = NULL;
#ifdef DEBUG

            Log << nl << "Window::~Window() done." << std::endl;
#endif

        }


        void Window::applyBGColor() const
            {
                if (pvm_screen.get()) // if auto pointer valid
				{
#ifdef HAVE_OPENGL
					if (pvm_screen->isOpenGLset())
					{
						glClearColor(static_cast<float> (_background.getR() ) / 255.0f, static_cast<float> (_background.getG() ) / 255.0f,static_cast<float> (_background.getB() ) / 255.0f,0.0f);
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					}
					else
					{
#endif
						//TODO background can be null, andthis will not be called.... ( speed improvemnt )
						pvm_screen->fill(_background);
#ifdef HAVE_OPENGL
					}
#endif
				}
            }

        void Window::setEngine (Engine *engine)
        {
#ifdef DEBUG
            Log << nl << "Window::setEngine(" << engine << ") called ...";
#endif
            assert(engine);
			if(!_userengine)
				delete _engine, _engine=NULL;
            _userengine=true;
            _engine=engine;

#ifdef DEBUG
            Log << nl << "Window::setEngine(" << engine << ") done.";

#endif

        }

        bool Window::resetDisplay( unsigned int width, unsigned int height, unsigned int bpp)
        {
#ifdef DEBUG
            Log << nl << "Window::resetDisplay( " << width << ", " << height << ", " << bpp << ") called ..." << std::endl;
#endif
	bool res = false;

		//force usage of DEFAULT_DISPLAY_WIDTH & DEFAULT_DISPLAY_HEIGHT when only one param is equal to 0. 
		if ((width == 0 && height != 0) || (width != 0 && height == 0))
		{
			width = DEFAULT_DISPLAY_WIDTH;
			height = DEFAULT_DISPLAY_HEIGHT;
		}
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
            //but beware about bpp == 0...
            if (bpp == 0 )
            {//0 as return code mean the current format is not supported
                Log << nl << "The requested video mode is not supported under any bit depth. Display reset cancelled !";
            }
            else
            {
                Log << nl << "SDL will use " << width << "x" << height << "@" <<bpp;
                //create a new screen
                try
                {
                        pvm_screen.reset(new VideoSurface(width, height, bpp));
			_engine->init(width, height);
                        applyBGColor();
			res=true;
                }
                catch(std::exception & e)
                {
                    Log << nl << " Exception caught in Window::resetDisplay() : " << e.what();
		    res=false;
                }
            }
#ifdef DEBUG
            Log << nl << "Window::resetDisplay(" << width << "," << height << ", " << bpp << ") done." << std::endl;
#endif

            return res;
        }

        bool Window::resizeDisplay (int width, int height) const
        {

#ifdef DEBUG
            Log << nl << "Window::resize() called ...";
            assert (pvm_screen.get());
#endif

	    bool res = true;

            if (pvm_screen.get())
            {
                res = res && pvm_screen->resize(width,height);//doesnt keep content
		res = res && _engine->resize(width,height);
		//this order otherwise we lose opengl context from the engine just after the resize ( reinit )
		//because screen resize recreates the window, and lose opengl context as documented in SDL docs...
		applyBGColor();
            }

#ifdef DEBUG
            Log << nl << "Window::resize() done.";
#endif

		//Forcing the refresh (display the backcolor)
		pvm_screen->refresh();

            return res;
        }

		void Window::ShowLoadingScreen(
			const std::string& Loading_BG_Filename,
			const std::string& Loading_Global_Msg,
			#ifdef HAVE_SDLTTF
				const Font& Loading_Global_Msg_Font,
			#endif
			const std::string& Loading_Specific_Msg,
			#ifdef HAVE_SDLTTF
				const Font& Loading_Specific_Msg_Font,
			#endif
			const Rect& Progress_Bar_Infos /*=Rect()*/ )
        {
		try
        {
		#ifdef DEBUG
            Log << nl << "Window::ShowLoadingScreen() called ..." << std::endl;
		#endif
			ShowingLoadingScreen = true;

			//Screen->getVideoInfo()->getPixelFormat()->getBitsPerPixel();

			applyBGColor();

			if (myLoadingScreen != NULL)
				delete myLoadingScreen, myLoadingScreen = NULL;

			myLoadingScreen = new LoadingScreen(std::auto_ptr<RGBSurface>(new RGBSurface(Loading_BG_Filename)), Loading_Global_Msg, Loading_Global_Msg_Font, Loading_Specific_Msg, Loading_Specific_Msg_Font, Progress_Bar_Infos );

			myLoadingScreen->render(pvm_screen);

		#ifdef DEBUG
            Log << nl << "Window::ShowLoadingScreen() done." << std::endl;
		#endif

		}
		catch(std::exception & e)
        {
			Log << nl << "Exception caught in Window::ShowLoadingScreen() : " << e.what();
			throw std::logic_error( "Exception caught in Window::ShowLoadingScreen() : " + (std::string)e.what() );
		} catch (...) {
			Log << nl << "Unhandled Exception in Window::ShowLoadingScreen()";
			throw std::logic_error( "Unhandled Exception in Window::ShowLoadingScreen()" );
		}
		}

		void Window::UpdateLoadingScreen( const unsigned short& Progress_Percent, const std::string& Loading_Specific_Msg )
		{
		try
        {
			if (ShowingLoadingScreen && myLoadingScreen != NULL )
			{			
				myLoadingScreen->Progress_Percent = std::min(100, std::max(0, (int)Progress_Percent)); //force the progression to be between 0 and 100
				myLoadingScreen->Loading_Specific_Msg = Loading_Specific_Msg;
				myLoadingScreen->render(pvm_screen);
			}
			else
			{
			#ifdef DEBUG
				throw std::logic_error( "Trying to update a loading screen that doesn't exists." );
			#endif
			}
			
		}
		catch(std::exception & e)
        {
			Log << nl << "Exception caught in Window::UpdateLoadingScreen() : " << e.what();
			throw std::logic_error( "Exception caught in Window::UpdateLoadingScreen() : " + (std::string)e.what() );
		} catch (...) {
			Log << nl << "Unhandled Exception in Window::UpdateLoadingScreen()";
			throw std::logic_error( "Unhandled Exception in Window::UpdateLoadingScreen()" );
		}
		}

		void Window::HideLoadingScreen()
		{
		try
        {
		#ifdef DEBUG
            Log << nl << "Window::HideLoadingScreen() called ..." << std::endl;
		#endif

			ShowingLoadingScreen = false;

			if (myLoadingScreen != NULL)
				delete myLoadingScreen, myLoadingScreen = NULL;

		#ifdef DEBUG
            Log << nl << "Window::HideLoadingScreen() done." << std::endl;
		#endif

		}
		catch(std::exception & e)
        {
			Log << nl << "Exception caught in Window::HideLoadingScreen() : " << e.what();
			throw std::logic_error( "Exception caught in Window::HideLoadingScreen() : " + (std::string)e.what() );
		} catch (...) {
			Log << nl << "Unhandled Exception in Window::HideLoadingScreen()";
			throw std::logic_error( "Unhandled Exception in Window::HideLoadingScreen()" );
		}
		}

        bool Window::mainLoop(unsigned int framerate, unsigned int eventrate)
        {
			if (ShowingLoadingScreen)
			{
				 framerate = 1, eventrate = 1;
			}
			assert(framerate > 0 && "framerate must be greater than 0 !");
			bool res = false;

#ifdef DEBUG
            assert (pvm_screen.get());
			assert (_engine);
#endif

            if (pvm_screen.get())
            {
				unsigned long lastframe = SDL_GetTicks();
				unsigned long lastevent = SDL_GetTicks();
				unsigned long newlastrender= SDL_GetTicks();
				unsigned long lastrender= newlastrender;
				while (! m_exitMainLoop )
				{
					//handling all the events
					//
					if ( SDL_GetTicks() - lastevent >= 1000/eventrate)//wait if needed - IMPORTANT otherwise the next value is far too high (not 0)
					{
						pvm_eventmanager.handleAll();
						lastevent = SDL_GetTicks();
					}

					//applying the background
					if (!ShowingLoadingScreen)
						applyBGColor();

					//calling engine for prerender and render events
					newlastrender = SDL_GetTicks();
					_engine->prerender( newlastrender - lastrender);
					lastrender = newlastrender;
					if (!ShowingLoadingScreen)
						_engine->render(*pvm_screen);
	
					//refresh screen
					//Log << nl << "before :" << SDL_GetTicks() - lastframe ;
					if ( SDL_GetTicks() - lastframe < 1000/framerate)//wait if needed - IMPORTANT otherwise the next value is far too high (not 0)
						SDL_Delay( 1000/framerate - ( SDL_GetTicks() - lastframe ) );

					pvm_screen->refresh();
					//Log << nl << "after :" << SDL_GetTicks() - lastframe ;

					lastframe=SDL_GetTicks();

					//calling engine for postrender events
					_engine ->postrender();

				}
				res = true;
                }
                else
                {
                    Log << nl << "ERROR : DisplaySurface @ " << pvm_screen.get() << " can't be used !" << std::endl;
                    Log  << nl <<" Ignoring mainLoop call." << std::endl;
                }

            if (!res)
            {
                Log  << nl << "An error occured when trying to launch the main loop, make sure you have initialized everything." << std::endl;
                Log  << nl <<" Ignoring mainLoop call." << std::endl;
            }
            return res;

        }




    }
}
