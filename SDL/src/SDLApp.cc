#include "SDLApp.hh"

namespace RAGE
{
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
            if (_manager == NULL)
            {
#ifdef DEBUG
            Log << nl << "Creating Manager ...";
#endif
            _manager = new Manager(true,false,false,false,false,false,false);
#ifdef DEBUG
            Log << nl << "Manager created @ " <<  _manager ;
#endif
            }
            else
            {
                _manager->enableVideo();
            }

#ifdef DEBUG
            Log << nl << "Creating Window ..." ;
#endif
            _window = new Window(_name,_icon);
#ifdef DEBUG

            Log << nl << "Window created @ "<< _window ;
            Log << nl << " Setting up Window... ";
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
            Log << nl << "FATAL ERROR : InitVideo failed... Exiting" << std::endl;
            exit (1);
        }
        return res;
    }

bool App::initJoystick()
{
    bool res = false;
            if (_manager == NULL)
            {
#ifdef DEBUG
            Log << nl << "Creating Manager ..." << std::endl;
#endif
            try
            {
                _manager = new Manager(false,false,false,false,true,false,false);
                res = true;
            }
            catch (std::exception &e)
            {
                 Log << nl << "Exception caught : " << e.what() << std::endl;
                Log << nl << "FATAL ERROR : InitJoystick failed... Exiting" << std::endl;
                exit (1);
            }
#ifdef DEBUG
            Log << nl << "Manager created @ " <<  _manager << std::endl;
#endif
            }
            else
            {
                res = _manager->enableJoystick();
            }

            if ( res == true ) _jpool = new JoystickPool();
#ifdef DEBUG
            Log << nl << "Number of Joysticks available : " << _jpool->countAvailable();

            for ( int i=0; i<  _jpool->countAvailable(); i++ )
                Log << nl << " Joystick " << i << " : " << _jpool->getName(i) ;
#endif
            return res;
}

}
}

