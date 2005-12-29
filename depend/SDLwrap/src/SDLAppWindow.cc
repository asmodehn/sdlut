#include "SDLAppWindow.hh"
#include "SDLEventManager.hh"

namespace SDL
{
    bool AppWindow::iconify(void)
    {
        return ( SDL_WM_IconifyWindow() != 0 );
    }

//needs to be redone
    bool AppWindow::toggleFullScreen(void)
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

    void AppWindow::grabInput()
    {
        SDL_WM_GrabInput( SDL_GRAB_ON );
    }

    void AppWindow::releaseInput()
    {
        SDL_WM_GrabInput( SDL_GRAB_OFF );
    }

    bool AppWindow::isInputGrabbed()
    {
        return SDL_WM_GrabInput( SDL_GRAB_QUERY ) == SDL_GRAB_ON;
    }




    void AppWindow::setCaption(std::string title, std::string icon)
    {
        _title=title;
        _icon=icon;
        SDL_WM_SetCaption(_title.c_str(), _icon.c_str());
        //seticon needed or ?
    }

    bool AppWindow::setIcon(std::string iconfilename)
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
    void AppWindow::getCaption(std::string & title, std::string & icon)
    {
        char * t="";
        char * i="" ;
        SDL_WM_GetCaption(&t,&i);
        title=std::string(t);
        icon=std::string(i);
    }

        std::string AppWindow::getTitle()
        {
            char * t = "" ;
            SDL_WM_GetCaption(&t,NULL);
            return std::string(t);

        }
        std::string AppWindow::getIconName()
        {
        char * i  = "";
        SDL_WM_GetCaption(NULL,&i);
        return std::string(i);
        }

    bool AppWindow::setResizable(bool val)
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

    bool AppWindow::setFullscreen(bool val)
    {
#ifdef DEBUG
Log << nl << "AppWindow::setFullscreen(" << val << ") called" << std::endl;
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

        bool AppWindow::setNoFrame(bool val)
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
    bool AppWindow::setOpenGL(bool val)
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


    AppWindow::AppWindow(std::string title,std::string icon)
    : _title(title), _icon(icon)
    {
        try
         {
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

    AppWindow::~AppWindow()
    {
#ifdef DEBUG
        Log << nl << " AppWindow Destructor called !" << std::endl;
#endif
#ifdef HAVE_OPENGL
        delete _glmanager;
#endif
        delete _videoinfo; BaseSurface::_vinfo = NULL;
    }



    bool AppWindow::reset( int width, int height)
    {
#ifdef DEBUG
Log << nl << "AppWindow::reset(" << width << "," << height << ") called" << std::endl;
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
            Log << nl << "SDL will use " << width << "x" << height << "@" <<_bpp << std::endl;
            //create a new screen
            try
            {
                //REMINDER : SDL_SetVideoMode, takes care of freeing the old surfaces (according to the doc)
#ifdef HAVE_OPENGL
                if (SDL_OPENGL & VideoSurface::flags)
                {
                    if (_glmanager->getEngine() == NULL)
                        _glmanager->setEngine();
                    _screen = new GLWindow(width, height, _bpp,_glmanager );
                    res= (_screen != NULL);
                }
                else
                {
#endif
                    //_screen = new Window(width, height, _bpp );
                    _screen = new Window(width, height, _bpp );
                    res = (_screen!=NULL);
#ifdef HAVE_OPENGL

                }
#endif
                if (_screen != NULL) _screen->setBGColor(background);
            }
            catch(std::exception & e)
            {
                Log << e.what();
            }
        }


        return res;

    }

bool AppWindow::resize (int width, int height) const
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

bool AppWindow::mainLoop(EventManager & eventmanager)
{
    bool res = false;
#ifdef DEBUG
assert (_screen);
#endif
    if (_screen !=NULL)
    {
        while (!(eventmanager.quitRequested()))
        {
            eventmanager.handleAll();

            _screen->update();
        }
        delete _screen; // to delete the SDLWrap class (not the actual video surface in memory...)
        _screen = NULL;
        res = true;
    }
    else
    {
        Log << nl << "Display Surface @ " << _screen << " can't be used !" << std::endl;
        Log  << nl <<" Ignoring mainLoop call." << std::endl;
    }
    return res;
}

}
