#include "SDLAppWindow.hh"
#include "SDLEvent.hh"

namespace SDL
{
    bool AppWindow::iconify(void)
    {
        return ( SDL_WM_IconifyWindow() != 0 );
    }

    bool AppWindow::toggleFullScreen(void)
    {
        //This only works for X11
#ifndef __MINGW32__ //check for WIN32 instead ??
        return ( SDL_WM_ToggleFullScreen(_surf) != 0 ) ;
#else
        setFullscreen(true);
        //This is the workaround for Win32
        //TODO :
        // 1)	Copy the screen surface to another (backup...)
        // 2)	Free the screen surface
        // 3)	Create a new one with fullscreen set
        return false;
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
            DisplaySurface::setResizable(val);
        else if (_screen->isResizableset() !=val )
        {
            if (! reset(_screen->getWidth(),_screen->getHeight()))
                res=false;
        }
        return res;
    }

    bool AppWindow::setFullscreen(bool val)
    {
        bool res = true;
        if (_screen == NULL )
            DisplaySurface::setFullscreen(val);
        else if (_screen->isFullScreenset() !=val )
        {
            if (! reset(_screen->getWidth(),_screen->getHeight()))
                res=false;
        }
        return res;
    }

        bool AppWindow::setNoFrame(bool val)
    {
        bool res = true;
        if (_screen == NULL )
            DisplaySurface::setNoFrame(val);
        else if (_screen->isNoFrameset() !=val )
        {
            if (! reset(_screen->getWidth(),_screen->getHeight()))
                res=false;
        }
        return res;
    }

    bool AppWindow::setOpenGL(bool val)
    {
        bool res = true;
        if (_screen == NULL )
            DisplaySurface::setOpenGL(val);
        else
        {
            std::cout << _screen->isOpenGLset() << "!=" << val << std::endl;
            //    if ( _screen->isOpenGLset() !=val )
            //    {
            DisplaySurface::setOpenGL(val);
            if (! reset(_screen->getWidth(),_screen->getHeight()))
                res=false;
        }
        return res;
    }


    AppWindow::AppWindow(std::string title,std::string icon,int bpp): _title(title), _icon(icon),_bpp(bpp)
    {
        _screen=NULL;

        setIcon(_icon);
        setTitle(_title);
    }

    bool AppWindow::reset( int width, int height)
    {
        bool res = false;
        int suggestedbpp=DisplaySurface::checkBPP(width, height, _bpp);
        //but beware about bpp == 0...
        if ( suggestedbpp == 0 )
        {//0 as return code mean the current format is not supported
            Log << nl << "The requested video mode is not supported under any bit depth. Display reset cancelled !";
        }
        else if ( suggestedbpp != _bpp)
        {
            Log << nl << " BPP wanted = " << _bpp << nl << " Using suggested BPP instead = " << suggestedbpp << std::endl;
            _bpp=suggestedbpp;
            res=true;
        }
        else
            res=true;

        if (res)
        {
            Log << nl << "SDL will use " << width << "x" << height << "@" <<_bpp << std::endl;
            //create a new screen
            try
            {
                //REMINDER : SDL_SetVideoMode, takes care of freeing the old surfaces (according to the doc)
#ifdef HAVE_OPENGL
                if (SDL_OPENGL & DisplaySurface::flags)
                {
                    _screen = new GLWindow(width, height, _bpp );
                }
                else
                {
#endif
                    _screen = new Window(width, height, _bpp );
#ifdef HAVE_OPENGL

                }
#endif

            }
            catch(std::exception & e)
            {
                Log << e.what();
            }
        }
        return res && ( _screen != NULL);

    }

bool AppWindow::resize (int width, int height)
{
    if (_screen !=NULL ) return _screen->resize(width,height);
    else return false;
}

bool AppWindow::mainLoop(EventHandler & handler)
{
    bool res = false;
    if (_screen !=NULL)
    {
        while (!(handler.shouldQuit()))
        {
            Event::handleEvents(handler);

            _screen->update();
        }
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
