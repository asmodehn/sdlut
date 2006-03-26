#include "SDLApp.hh"

namespace RAGE
{
    namespace SDL
    {

        App::App(std::string logfilename) :    _manager(NULL),
                _window(NULL)
        {
#ifdef DEBUG
            Log << nl << "App::App() called";
#endif

            setName();
            setIcon();
            if (!Log.enableFileLog(logfilename))
                throw std::logic_error("Log file creation FAILED !");
        }

        App::~App()
        {
#ifdef HAVE_SDLTTF
			if (TTF_WasInit())
				TTF_Quit();
#endif
            //MAKE SURE those destructor dont need App. They shouldnt !
            delete _window, _window = NULL;
            //this one should be last because it calls SDL_Quit
            delete _manager;
            _manager = NULL;
        }

        App& App::getInstance()
        {
            static App instance;
            return instance;
        }

		bool App::initText()
		{
#ifdef HAVE_SDLTTF
			//Initialize SDL_ttf
			if( TTF_Init() == -1 )
			{
				Log << " TTF Error : " << GetError(TTF) << std::endl;
				return false;
			}
			return true;
#endif
			return false;
			
		}

		//Initialize sdl timer
		bool App::initTimer()
		{
			if (_manager != NULL)
			{
				_manager->enableTimer();
				return true;
			}
			return false;
            
			
		}

        bool App::initVideo( bool fullscreen,bool opengl, bool resizable, bool noframe)
        {
            bool res = false;
            try
            {
                if (_manager == NULL)
                {
                    _manager = new Manager(true,false,false,false,false,false,false);
                }
                else
                {
                    _manager->enableVideo();
                }

                _window = new Window(_name);


                //setting the required flags...
#ifdef HAVE_OPENGL

				_window->setOpenGL(opengl);
#else

                if(opengl)
                    Log << nl << "Not compiled with opengl support --> Ignoring opengl window request"<< std::endl;
#endif

                    _window->setFullscreen(fullscreen);
                    _window->setResizable(resizable);
                    _window->setNoFrame(noframe);



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
            }
            else
            {
                res = _manager->enableJoystick();
            }

            if ( res == true )
                _jpool = new JoystickPool();
#ifdef DEBUG

            Log << nl << "Number of Joysticks available : " << _jpool->countAvailable();

            for ( int i=0; i<  _jpool->countAvailable(); i++ )
                Log << nl << " Joystick " << i << " : " << _jpool->getName(i) ;
#endif

            return res;
        }

    }
}

