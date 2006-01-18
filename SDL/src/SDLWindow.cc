#include "SDLWindow.hh"
#include "SDLEventManager.hh"

namespace RAGE
{
    namespace SDL
    {
        bool Window::iconify(void)
        {
            return ( SDL_WM_IconifyWindow() != 0 );
        }

        //needs to be redone
        bool Window::toggleFullScreen(void)
        {
            //This only works for X11
#if defined ( __MINGW32__) || defined ( __WIN32__) || defined( WIN32 ) ||  defined( _WINDOWS ) //check for WIN32
            //workaround for win32 ??
#ifdef DEBUG
            Log << nl << "Ignoring ToggleFullScreen() on Windows platform..." << std::endl;
#endif
            //return setFullscreen(true);
            //looks like it doesnt work...
            return false;
#else
#ifdef DEBUG

            Log << nl << "Calling SDL_WM_ToggleFullScreen(" << _screen->_surf << ")" << std::endl;
#endif

            return ( SDL_WM_ToggleFullScreen(_screen->_surf) != 0 ) ;
#endif

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




        void Window::setCaption(std::string title, std::string icon)
        {
            _title=title;
            _icon=icon;
            SDL_WM_SetCaption(_title.c_str(), _icon.c_str());
            //seticon needed or ?
        }

        bool Window::setIcon(std::string iconfilename)
        {
            bool res=false;
            SDL_Surface * icon=SDL_LoadBMP(iconfilename.c_str());
            if ( icon != NULL )
            {
                _icon=iconfilename;
                SDL_WM_SetIcon( icon , NULL);
                res = true;
            }
            else
            {
                Log << nl << "Unable to load the icon " << iconfilename << " : " << GetError() << std::endl;
            }
            return res;
        }

        //old version
        void Window::getCaption(std::string & title, std::string & icon)
        {
            char * t="";
            char * i="" ;
            SDL_WM_GetCaption(&t,&i);
            title=std::string(t);
            icon=std::string(i);
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
                if (! reset(_screen->getWidth(),_screen->getHeight()))
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
                    if (! reset(_screen->getWidth(),_screen->getHeight()))
                        res=false;
                }
            }
            return res;
        }

        bool Window::setNoFrame(bool val)
        {
            bool res = true;
            if (_screen == NULL )
                VideoSurface::setNoFrame(val);
            else if (_screen->isNoFrameset() !=val )  //if called inside mainLoop while screen is active
            {
                if (! reset(_screen->getWidth(),_screen->getHeight()))
                    res=false;
            }
            return res;
        }
#ifdef HAVE_OPENGL
        bool Window::setOpenGL(bool val)
        {
            bool res = true;
            if (_screen == NULL )
                VideoSurface::setOpenGL(val);
            else if ( _screen->isOpenGLset() !=val ) //if called inside mainLoop while screen is active
            {
                VideoSurface::setOpenGL(val);
                if (! reset(_screen->getWidth(),_screen->getHeight()))
                    res=false;
            }
            return res;
        }
#endif


        Window::Window(std::string title,std::string icon)
                : _title(title), _icon(icon),_background(Color(0,0,0)),_engine(NULL)
#ifdef HAVE_OPENGL
                ,_glengine(NULL)
#endif
        {
#ifdef DEBUG
            Log << nl << "Window::Window(" << title << ", " << icon << ") called ..." ;
#endif

            try
            {
                _eventmanager = new EventManager();
                _videoinfo = new VideoInfo();
#ifdef HAVE_OPENGL

                _userglengine=false;
                _glmanager = new GLManager();

#endif

                _userengine=false;

            }
            catch (std::exception &e)
            {
                Log << nl << e.what() << std::endl;
            }
            _screen=NULL;
            //setting the static videoInfo to be used by all surfaces...

            BaseSurface::_vinfo = _videoinfo;

            setIcon(_icon);
            setTitle(_title);

#ifdef DEBUG

            Log << nl << "Window::Window(" << title << ", " << icon << ") done @ "<< this ;
#endif

        }

        Window::~Window()
        {
#ifdef DEBUG
            Log << nl << "Window::~Window() called ..." << std::endl;
#endif
#ifdef HAVE_OPENGL

            if (!_userglengine)
                delete _glengine, _glengine = NULL;
            delete _glmanager, _glmanager = NULL;
#endif

            if (!_userengine)
                delete _engine, _engine = NULL;
            delete _videoinfo, _videoinfo = NULL;
            BaseSurface::_vinfo = NULL;
#ifdef DEBUG

            Log << nl << "Window::~Window() done." << std::endl;
#endif

        }

        void Window::setEngine (Engine *engine)
        {
#ifdef DEBUG
            Log << nl << "Window::setEngine(" << engine << ") called ...";
            assert(engine);
#endif

            _userengine=true;
            _engine=engine;
            if (_screen != NULL)
            {
                _screen->setEngine(_engine);
                _engine->init(_screen->getWidth(),_screen->getHeight());
            }

#ifdef DEBUG
            Log << nl << "Window::setEngine(" << engine << ") done.";

#endif

        }

#ifdef HAVE_OPENGL
        void Window::setGLEngine (GLEngine* glengine)
        {
#ifdef DEBUG
            Log << nl << "Window::setGLEngine(" << glengine << ") called ...";
            assert(glengine);
#endif

            _userglengine = true;
            _glengine=glengine;
            if (_screen != NULL)
                if  (_screen->isOpenGLset())
                {
                    _screen->setEngine(_glengine);
                    _glengine->init(_screen->getWidth(),_screen->getHeight());
                }
#ifdef DEBUG
            Log << nl << "Window::setGLEngine(" << glengine << ") done.";
#endif

        }
#endif

        bool Window::reset( int width, int height)
        {
#ifdef DEBUG
            Log << nl << "Window::reset(" << width << "," << height << ") called ..." << std::endl;
#endif

            bool res = false;
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
#ifdef HAVE_OPENGL
                    //if opengl support compiled and opengl enable on screen then initialise it
                    if ( (SDL_OPENGL & VideoSurface::_defaultflags) !=0 )
                    {
                        if (_glengine == NULL)
                        {
                            _userglengine=false;
                            _glengine = new GLEngine();
                        }


                        _screen = new GLSurface(width, height, _bpp,_glmanager, _glengine);
                        res= (_screen != NULL);
                        if (res && _glengine !=NULL)
                            _glengine->init(_screen->getWidth(),_screen->getHeight());
                    }
                    else
                    {
#endif
                        if (_engine == NULL)
                        {
                            _userengine=false;
                            _engine = new Engine();
                        }
                        _screen = new VideoSurface(width, height, _bpp, _engine);
                        res = (_screen!=NULL);
                        if (res && _engine !=NULL)
                            _engine->init(_screen->getWidth(),_screen->getHeight());
#ifdef HAVE_OPENGL

                    }
#endif

                    if (_screen != NULL)
                        _screen->setBGColor(_background);
                }
                catch(std::exception & e)
                {
                    Log << e.what();
                }
            }
#ifdef DEBUG
            Log << nl << "Window::reset(" << width << "," << height << ") done." << std::endl;
#endif

            return res;

        }

        bool Window::resize (int width, int height) const
        {

#ifdef DEBUG
            Log << nl << "Window::resize() called ...";
            assert (_screen);
#endif

            bool res = false;
            if (_screen != NULL )
            {
                Log << nl << "Savecontent";
                _screen->saveContent();
                Log << nl << "resize _screen";
                if (_screen->resize(width,height))
                {
                    Log << nl << "setBGColor";
                    _screen->setBGColor(_background);
                    Log << nl << "restoreContent";
                    _screen->restoreContent();
                }
            }

#ifdef DEBUG
            Log << nl << "Window::resize() done.";
#endif

            return res;
        }

        bool Window::mainLoop()
        {
            bool res = false;
#ifdef DEBUG

            assert(_eventmanager);
#endif

            if (_eventmanager != NULL)
            {

#ifdef DEBUG
                assert (_screen);
#endif

                if (_screen !=NULL)
                {
                    while (!(_eventmanager->quitRequested()))
                    {
                        _eventmanager->handleAll();

                        _screen->update();
                    }
                    delete _screen; // to delete the wrapper class (not the actual video surface in memory...)
                    _screen = NULL;
                    res = true;
                }
                else
                {
                    Log << nl << "ERROR : DisplaySurface @ " << _screen << " can't be used !" << std::endl;
                    Log  << nl <<" Ignoring mainLoop call." << std::endl;
                }
                //Loop finished, the EventManager should be reinitialized
                delete _eventmanager;
                _eventmanager = new EventManager();
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
