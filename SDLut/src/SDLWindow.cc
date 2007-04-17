#include "SDLWindow.hh"
#include "SDLEventManager.hh"
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
            SDL_WM_SetIcon( const_cast<SDL_Surface*>(_icon.get_pSDL()) , NULL);
        }

        //old version
        void Window::getCaption(std::string & title, std::string & iconname)
        {
            char * t="";
            char * i="" ;
            SDL_WM_GetCaption(&t,&i);
            title=std::string(t);
            iconname=std::string(i);
        }

        std::string Window::getTitle()
        {
            char * t = "" ;
            SDL_WM_GetCaption(&t,NULL);
            return std::string(t);

        }
        std::string Window::getIconName()
        {
            char * i  = "";
            SDL_WM_GetCaption(NULL,&i);
            return std::string(i);
        }

        bool Window::setResizable(bool val)
        {
            bool res = true;
            if (_screen == NULL )
                VideoSurface::setResizable(val);
            else if (_screen->isResizableset() !=val ) //if called inside mainLoop while screen is active
            {
				VideoSurface::setResizable(val);
                if (! resetDisplay(_screen->getWidth(),_screen->getHeight()))
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
            if (_screen == NULL )
                VideoSurface::setFullscreen(val);
            else
            {
#ifdef DEBUG
                Log << nl << _screen->isFullScreenset() << " != " << val << std::endl;
#endif

                if (_screen->isFullScreenset() != val ) //if called inside mainLoop while screen is active
                {
			VideoSurface::setFullscreen(val);
                    if (! resetDisplay(_screen->getWidth(),_screen->getHeight()))
                        res=false;
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
            if (_screen == NULL )
                VideoSurface::setNoFrame(val);
            else if (_screen->isNoFrameset() !=val )  //if called inside mainLoop while screen is active
            {
				VideoSurface::setNoFrame(val);
                if (! resetDisplay(_screen->getWidth(),_screen->getHeight()))
                    res=false;
            }
            return res;
        }
#ifdef HAVE_OPENGL
        bool Window::setOpenGL(bool val)
        {
            bool res = true;
			
			if (!_userengine && _engine!=NULL) delete _engine, _engine=NULL;

			if (val)
				_engine = new DefaultGLEngine();
			else
				_engine = new DefaultEngine();
			
            if (_screen == NULL )
			{
				VideoSurface::setOpenGL(val);
			}
            else if ( _screen->isOpenGLset() !=val ) //if called inside mainLoop while screen is active
            {
                VideoSurface::setOpenGL(val);
                if (! resetDisplay(_screen->getWidth(),_screen->getHeight()))
                    res=false;
            }
            return res;
        }
#endif

	//to check the current properties of the display
	bool Window::isFullscreen()
	{
		if (_screen!=NULL)
		{
			return _screen->isFullScreenset();
		}
		else
		{
			return ( SDL_FULLSCREEN & VideoSurface::_defaultflags ) != 0;
		}
	}
	bool Window::isResizable()
	{
		if (_screen!=NULL)
		{
			return _screen->isResizableset();
		}
		else
		{
			return ( SDL_RESIZABLE & VideoSurface::_defaultflags ) != 0;
		}
	}
	bool Window::isOpenGL()
	{
		if (_screen!=NULL)
		{
			return _screen->isOpenGLset();
		}
		else
		{
			return ( SDL_OPENGL & VideoSurface::_defaultflags ) != 0;
		}
	}
	bool Window::isNoFrame()
	{
		
		if (_screen!=NULL)
		{
			return _screen->isNoFrameset();
		}
		else
		{
			return ( SDL_NOFRAME & VideoSurface::_defaultflags ) != 0;
		}
	}
	
        Window::Window(std::string title)
                : _title(title),_background(Color(0,0,0))
        {
#ifdef DEBUG
            Log << nl << "Window::Window(" << title << ") called ..." ;
#endif

            try
            {
                _eventmanager = new EventManager();
                _videoinfo = new VideoInfo();
#ifdef HAVE_OPENGL

                _glmanager = new GLManager();

#endif

				_engine = new DefaultEngine();
                _userengine=false;

            }
            catch (std::exception &e)
            {
                Log << nl << e.what() << std::endl;
            }
            _screen=NULL;
            //setting the static videoInfo to be used by all surfaces...

            BaseSurface::_vinfo = _videoinfo;

			RWOps iconrwops( _defaultIcon, sizeof(_defaultIcon));

            setIcon(RGBSurface(iconrwops));
            setTitle(_title);

#ifdef DEBUG

            Log << nl << "Window::Window(" << title << ") done @ "<< this ;
#endif

        }

        Window::~Window()
        {
#ifdef DEBUG
            Log << nl << "Window::~Window() called ..." << std::endl;
#endif
#ifdef HAVE_OPENGL

            delete _glmanager, _glmanager = NULL;
#endif
			delete _eventmanager, _eventmanager = NULL;
            if (!_userengine) //if the user set his own engine , he is responsible for deleting it
                delete _engine, _engine = NULL;
            delete _videoinfo, _videoinfo = NULL;
            BaseSurface::_vinfo = NULL;
#ifdef DEBUG

            Log << nl << "Window::~Window() done." << std::endl;
#endif

        }


            void Window::applyBGColor() const
            {
                if (_screen != NULL)
				{
#ifdef HAVE_OPENGL
					if (_screen->isOpenGLset())
					{
						glClearColor(static_cast<float> (_background.getR() ) / 255.0f, static_cast<float> (_background.getG() ) / 255.0f,static_cast<float> (_background.getB() ) / 255.0f,0.0f);
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

					}
					else
					{
#endif
						//TODO background can be null, andthis will not be called.... ( speed improvemnt )
						_screen->fill(_background);
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
            _userengine=true;
            _engine=engine;

#ifdef DEBUG
            Log << nl << "Window::setEngine(" << engine << ") done.";

#endif

        }

        VideoSurface* Window::resetDisplay( int width, int height)
        {
#ifdef DEBUG
            Log << nl << "Window::reset(" << width << "," << height << ") called ..." << std::endl;
#endif

            int _bpp=VideoSurface::getSuggestedBPP(width, height);
            //but beware about bpp == 0...
            if (_bpp == 0 )
            {//0 as return code mean the current format is not supported
                Log << nl << "The requested video mode is not supported under any bit depth. Display reset cancelled !";
            }
            else
            {
                Log << nl << "SDL will use " << width << "x" << height << "@" <<_bpp;
                //create a new screen
                try
                {
                    //REMINDER : SDL_SetVideoMode, takes care of freeing the old surfaces (according to the doc)
                        _screen = new VideoSurface(width, height, _bpp);
						_engine->init(width, height);
                        applyBGColor();
                }
                catch(std::exception & e)
                {
                    Log << e.what();
                }
            }
#ifdef DEBUG
            Log << nl << "Window::reset(" << width << "," << height << ") done." << std::endl;
#endif

            //return res;
			return _screen;

        }

        VideoSurface* Window::resizeDisplay (int width, int height) const
        {

#ifdef DEBUG
            Log << nl << "Window::resize() called ...";
            assert (_screen);
#endif

            if (_screen != NULL )
            {
                _screen->resize(width,height);//doesnt keep content
				_engine->resize(width,height);
				//this order otherwise we lose opengl context from the engine just after the resize ( reinit )
				//because screen resize recreates the window, and lose opengl context as documented in SDL docs...
				applyBGColor();
            }

#ifdef DEBUG
            Log << nl << "Window::resize() done.";
#endif
			
			//Forcing the refresh (display the backcolor)
			_screen->refresh();

            //return res;
			return _screen;
        }

        bool Window::mainLoop(unsigned int framerate)
        {
			assert(framerate>0&&"framerate must be superior to 0 !");
            bool res = false;
#ifdef DEBUG

            assert(_eventmanager);
#endif

            if (_eventmanager != NULL)
            {

#ifdef DEBUG
                assert (_screen);
				assert (_engine);
#endif

                if (_screen !=NULL)
                {
			unsigned long lastframe = SDL_GetTicks();
			unsigned long newlastrender= SDL_GetTicks();
			unsigned long lastrender= newlastrender;
	                    while (!(_eventmanager->quitRequested()))
						{ 
							//handling all the events

							//
							//semble leak la qd touche souris utilis�e jam� del de la ram et aussi qd la souris passe la 1ere fois sur lecran ram utilis�e jam� del: leak ds la prise en charge par de fo de la souris ?
							//le clavier �tant implement� ds le test directement ya pa de perte avec lui apparement ^^
							//
							_eventmanager->handleAll();
							
							//applying the background

							//
							//Gro leak la!
							//
							applyBGColor();
	
							//calling engine for prerender and render events
							newlastrender = SDL_GetTicks();
							_engine->prerender( newlastrender - lastrender);
							lastrender = newlastrender;
							_engine->render(*_screen);
							
							
							//refresh screen
							//Log << nl << "before :" << SDL_GetTicks() - lastframe ;
							if ( SDL_GetTicks() - lastframe < 1000/framerate)//wait if needed - IMPORTANT otherwise the next value is far too high (not 0)
								SDL_Delay( 1000/framerate - ( SDL_GetTicks() - lastframe ) );
							
							//
							//petit leak la de 4k occasionnel
							//
							_screen->refresh();


							//Log << nl << "after :" << SDL_GetTicks() - lastframe ;
							
							lastframe=SDL_GetTicks();
	
							//calling engine for postrender events
							_engine ->postrender();

						}
                    delete _screen, _screen = NULL; // to delete the wrapper class (not the actual video surface in memory...)
                    res = true;
                }
                else
                {
                    Log << nl << "ERROR : DisplaySurface @ " << _screen << " can't be used !" << std::endl;
                    Log  << nl <<" Ignoring mainLoop call." << std::endl;
                }
                //Loop finished, the EventManager should be reinitialized
                //delete _eventmanager;
                //_eventmanager = new EventManager();
            }
            else
            {
                Log << nl << "ERROR : EventManager @ " << _eventmanager;
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
