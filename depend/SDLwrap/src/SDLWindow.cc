#include "SDLWindow.hh"
#include "SDLEventManager.hh"

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
            : _title(title), _icon(icon)
    {
        try
        {
#ifdef DEBUG

            Log << nl << "Creating EventManager ... " << std::endl;
#endif

            _eventmanager = new EventManager();
#ifdef DEBUG

            Log << nl << "EventManager created @ " << _eventmanager << std::endl;
#endif

            _videoinfo = new VideoInfo();
#ifdef HAVE_OPENGL

            _glmanager = new GLManager();
#endif

        }
        catch (std::exception &e)
        {
            Log << nl << e.what() << std::endl;
        }
        _screen=NULL;
        //setting the static videoInfo to be used by all surfaces...

        BaseSurface::_vinfo = _videoinfo;
#ifdef DEBUG

        Log << nl << "VideoInfo created @ " << _videoinfo << std::endl;
#endif

        setIcon(_icon);
        setTitle(_title);

        setBGColor( Color (0,0,0) );
    }

    Window::~Window()
    {
#ifdef DEBUG
        Log << nl << " Window Destructor called !" << std::endl;
#endif
#ifdef HAVE_OPENGL

        delete _glmanager;
#endif

        delete _videoinfo;
        BaseSurface::_vinfo = NULL;
    }



    bool Window::reset( int width, int height)
    {
#ifdef DEBUG
        Log << nl << "Window::reset(" << width << "," << height << ") called" << std::endl;
#endif

        bool res = false;
        int _bpp=VideoSurface::getSuggestedBPP(width, height);
        //but beware about bpp == 0...
        if (_bpp == 0 )
        {//0 as return code mean the current format is not supported
            Log << nl << "The requested video mode is not supported under any bit depth. Display reset cancelled !";
        }
        /*else if ( suggestedbpp != _bpp)
        {
            Log << nl << " BPP wanted = " << _bpp << nl << " Using suggested BPP instead = " << suggestedbpp << std::endl;
            _bpp=suggestedbpp;
            res=true;
        }
        else
            res=true;
        */
        //if (res)
        else
        {
            Log << nl << "SDL will use " << width << "x" << height << "@" <<_bpp;
            //create a new screen
            try
            {
                //REMINDER : SDL_SetVideoMode, takes care of freeing the old surfaces (according to the doc)
#ifdef HAVE_OPENGL
                if (SDL_OPENGL & VideoSurface::_defaultflags)
                {
                    _screen = new GLSurface(width, height, _bpp,_glmanager );
                    res= (_screen != NULL);
                }
                else
                {
#endif
                    //_screen = new Window(width, height, _bpp );
                    _screen = new VideoSurface(width, height, _bpp );
                    res = (_screen!=NULL);
#ifdef HAVE_OPENGL

                }
#endif
                if (_screen != NULL)
                    _screen->setBGColor(background);
            }
            catch(std::exception & e)
            {
                Log << e.what();
            }
        }


        return res;

    }

    bool Window::resize (int width, int height) const
    {
        bool res = false;
#ifdef DEBUG
        assert (_screen);
#endif

        if (_screen != NULL )
        {
            _screen->saveContent();
            if (_screen->resize(width,height))
            {
                _screen->setBGColor(background);
                _screen->restoreContent();
            }
        }
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
                    delete _screen; // to delete the SDLWrap class (not the actual video surface in memory...)
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
