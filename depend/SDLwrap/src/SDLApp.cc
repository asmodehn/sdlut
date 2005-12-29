#include "SDLApp.hh"

namespace SDL
{

    App::App(std::string logfilename) :    _manager(NULL),
            _eventmanager(NULL),
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
        delete _eventmanager;
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
#ifdef DEBUG
            Log << nl << "Creating Manager ..." << std::endl;
#endif

            _manager = new Manager(true);
#ifdef DEBUG

            Log << nl << "Manager created @ " <<  _manager << std::endl;
            Log << nl << "Creating AppWindow ..." << std::endl;
#endif

            _appwindow = new AppWindow(_name,_icon);
#ifdef DEBUG

            Log << nl << "AppWindow created @ "<< _appwindow << std::endl;
            Log << nl << " Setting up AppWindow... " << std::endl;
#endif


            //setting the required flags...
#ifdef HAVE_OPENGL

            if (opengl)
                _appwindow->setOpenGL(true);
#else

            if(opengl)
                Log << nl << "Not compiled with opengl support --> Ignoring opengl window request"<< std::endl;
#endif

            if (fullscreen)
                _appwindow->setFullscreen(true);
            if (resizable)
                _appwindow->setResizable(true);
            if (noframe)
                _appwindow->setNoFrame(true);


#ifdef DEBUG

            Log << nl << "Creating EventManager ... " << std::endl;
#endif

            _eventmanager = new EventManager(*_appwindow);
#ifdef DEBUG

            Log << nl << "EventManager created @ " << _eventmanager << std::endl;
#endif

            res=true;
        }
        catch (std::exception &e)
        {
            Log << nl << "Exception caught : " << e.what() << std::endl;
            Log << nl << "FATAL ERROR : InitWindow failed... Exiting" << std::endl;
            exit (1);
        }
        return res;
    }

    bool App::mainLoop()
    {
        bool res = false;
#ifdef DEBUG
        assert(_eventmanager);
#endif

        if (_eventmanager != NULL)
        {
#ifdef DEBUG
            assert(_appwindow);
#endif

            if ( _appwindow != NULL)
            {
                res=_appwindow->mainLoop(*_eventmanager);
            }
            else
            {
                Log << nl << "ERROR : AppWindow @ " << _appwindow;
            }
            //Loop finished, the EventManager should be reinitialized
            delete _eventmanager;
            _eventmanager = new EventManager(*_appwindow);
        }
        else
        {
            Log << nl << "ERROR : EventManager @ " << _eventmanager;
        }
        if (!res)
        {
        Log  << nl << "An error occured when trying to laucnh the main loop, make sure you have initialized everything." << std::endl;
        Log  << nl <<" Ignoring mainLoop call." << std::endl;
        }
        return res;
    }

}

