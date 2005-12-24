#include "SDLApp.hh"

namespace SDL
{

        App::App(std::string logfilename) :    _manager(NULL),
#ifdef HAVE_OPENGL
                                _glmanager(NULL),
#endif
                                _videoinfo(NULL),
                                 _eventhandler(NULL),
                                 _appwindow(NULL)
        {
            setName();
            setIcon();
            if (!Log.enableFileLog(logfilename))
                throw std::logic_error("Log file creation FAILED !");
        }
        App::~App()
        {
            delete _appwindow;
            delete _eventhandler;
            delete _videoinfo;
#ifdef HAVE_OPENGL
            delete _glmanager;
    #endif
            delete _manager;
        }

bool App::initWindow(bool opengl, bool fullscreen, bool resizable, bool noframe)
{
    try
    {
    _manager = new Manager(true);
    }
    catch (...)
    {
        Log << nl << "FATAL ERROR : Video cant be initialized... Exiting" << std::endl;
            exit (1);
    }
    if ( _manager !=NULL )
    {
#ifdef HAVE_OPENGL
        _glmanager = new GLManager();
#endif
        _videoinfo = new VideoInfo();
        _appwindow = new AppWindow(_name,_icon,_videoinfo->getPixelFormat()->getBitsPerPixel());
        //setting the required flags...
        if (opengl) _appwindow->setOpenGL(true);
        if (fullscreen) _appwindow->setFullscreen(true);
        if (resizable) _appwindow->setResizable(true);
        if (noframe) _appwindow->setNoFrame(true);
        _eventhandler = new EventHandler(_appwindow);
    }
}

bool App::mainLoop()
 {
     if (_eventhandler != NULL)
     {
         if ( _appwindow != NULL)
        {
            if (_eventhandler->_focusedwindow == _appwindow)
            {
                return _appwindow->mainLoop(*_eventhandler);
            }
            Log << nl << "EventHandler not created against the current AppWindow !";
        }
        else
        {
            Log << nl << "ERROR : AppWindow @ " << _appwindow;
        }
     }
    else
    {
        Log << nl << "ERROR : EventHandler @ " << _eventhandler;
    }

    Log  << nl <<" Ignoring mainLoop call." << std::endl;
     return false;
}

}

