#include "SDLApp.hh"

namespace SDL
{

        App::App(std::string logfilename) :    _manager(NULL),
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
            //MAKE SURE those destructor dont need App. They shouldnt !
            delete _appwindow;
            delete _eventhandler;
            //this one should be last because it calls SDL_Quit
            delete _manager;
        }

App& App::getInstance()
{
    static   App  instance;
    return   instance;
}

bool App::initWindow( bool fullscreen,bool opengl, bool resizable, bool noframe)
{
    bool res = false;
    try
    {
    _manager = new Manager(true);
    }
    catch (...)
    {
        Log << nl << "FATAL ERROR : Manager cant be created... Exiting" << std::endl;
            exit (1);
    }
    if ( _manager !=NULL )
    {
        //more try / catch to do ??
        _appwindow = new AppWindow(_name,_icon);
        //setting the required flags...
    #ifdef HAVE_OPENGL
        if (opengl) _appwindow->setOpenGL(true);
    #else
        if(opengl) Log << nl << "Not compiled with opengl support --> Ignoring opengl window request"<< std::endl;
    #endif
        if (fullscreen) _appwindow->setFullscreen(true);
        if (resizable) _appwindow->setResizable(true);
        if (noframe) _appwindow->setNoFrame(true);
        _eventhandler = new EventHandler(_appwindow);
        res = true;
    }
    return res;
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

