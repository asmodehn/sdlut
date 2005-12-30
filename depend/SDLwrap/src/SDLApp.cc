#include "SDLApp.hh"

namespace SDL
{

    App::App(std::string logfilename) :    _manager(NULL),
            _window(NULL)
    {
        setName();
        setIcon();
        if (!Log.enableFileLog(logfilename))
            throw std::logic_error("Log file creation FAILED !");
    }
    App::~App()
    {
        //MAKE SURE those destructor dont need App. They shouldnt !
        delete _window;
        //this one should be last because it calls SDL_Quit
        delete _manager;
    }

    App& App::getInstance()
    {
        static   App  instance;
        return   instance;
    }

    bool App::initVideo( bool fullscreen,bool opengl, bool resizable, bool noframe)
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

            _window = new Window(_name,_icon);
#ifdef DEBUG

            Log << nl << "AppWindow created @ "<< _window << std::endl;
            Log << nl << " Setting up AppWindow... " << std::endl;
#endif


            //setting the required flags...
#ifdef HAVE_OPENGL

            if (opengl)
                _window->setOpenGL(true);
#else

            if(opengl)
                Log << nl << "Not compiled with opengl support --> Ignoring opengl window request"<< std::endl;
#endif

            if (fullscreen)
                _window->setFullscreen(true);
            if (resizable)
                _window->setResizable(true);
            if (noframe)
                _window->setNoFrame(true);



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

}

