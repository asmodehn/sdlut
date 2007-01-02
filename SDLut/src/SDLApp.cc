#include "SDLApp.hh"

namespace RAGE
{
    namespace SDL
    {

	    App::App(std::string logfilename) :    _manager(NULL), _window(NULL), _mixer(NULL), _netInitialized(false)
        {
#ifdef DEBUG
            Log << nl << "App::App() called";
#endif

            setName();
            setIcon();
            if (!Log.enableFileLog(logfilename))
                throw std::logic_error("Log file creation FAILED !");
	    
#ifdef DEBUG
            Log << nl << "App::App() done";
#endif
        }

        App::~App()
        {
#ifdef DEBUG
            Log << nl << "App::~App() called";
#endif
#ifdef HAVE_SDLTTF
			if (TTF_WasInit())
				TTF_Quit();
#endif
#ifdef HAVE_SDLNET
			if( _netInitialized)
				SDLNet_Quit();
#endif
            //MAKE SURE those destructor dont need App. They shouldnt !
            delete _window, _window = NULL;
            delete _mixer, _mixer=NULL;
            //this one should be last because it calls SDL_Quit
            delete _manager;
            _manager = NULL;
	    
#ifdef DEBUG
            Log << nl << "App::~App() done";
#endif
        }

        App& App::getInstance()
        {
            static App instance;
            return instance;
        }

		bool App::initText()
		{
#ifdef HAVE_SDLTTF
			if (TTF::isLinked())
			{
				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					Log << " TTF Error : " << TTF::GetError() << std::endl;
					return false;
				}
				return true;
			}
#endif
			return false;
			
		}

		bool App::initNet()
		{
#ifdef HAVE_SDLNET
			_netInitialized = true;
			//Initialize SDL_net
			if( SDLNet_Init() == -1 )
			{
				Log << " NET Error : " << GetError(Net) << std::endl;
				return false;
			}
			return true;
#endif
			return false;
			
		}


		//Initialize sdl cdrom
		bool App::initCDRom()
		{
			if (_manager == NULL)
			{
				_manager = new Manager(false,false,false,true,false,false,false);
				return true;
			}
			else
			{
				return _manager->enableCdrom();
			}
			return false;
            
			
		}

		//Initialize sdl timer
		bool App::initTimer()
		{
			if (_manager == NULL)
			{
				_manager = new Manager(false,false,true,false,false,false,false);
				return true;
			}
			else
			{
				return _manager->enableTimer();
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
					res = ( _manager != NULL );
                }
                else
                {
                    res = _manager->enableVideo();
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

	bool App::initAudio()
	{
		bool res = false;
		try
		{
		
			if (_manager == NULL)
			{
				_manager = new Manager(false,true,false,false,false,false,false);
				res = (_manager != NULL);
			}
			else
			{
				res = _manager->enableAudio();
			}
		
			if ( res == true )
				//tmp for test
				_mixer = new Mixer();
		
		}
		catch (std::exception &e)
		{
			Log << nl << "Exception caught : " << e.what() << std::endl;
			Log << nl << "FATAL ERROR : InitAudio failed... Exiting" << std::endl;
			exit(1);
		}

		
		return res;
	}
			
	
		bool App::init()
		{
			if (_manager == NULL)
			{
				_manager = new Manager(false,false,false,false,false,false,false);
				return (_manager != NULL);
			}
			return false;
			
		}

    }
}

