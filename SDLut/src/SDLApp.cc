#include "SDLApp.hh"
#include "SDLConfig.hh"

namespace RAGE
{
    namespace SDL
    {

	    App::App(std::string logfilename) :    _manager(NULL), _window(NULL), _mixer(NULL)
        {
#ifdef DEBUG
            Log << nl << "App::App() called";
#endif

            setName();
            setIcon();
	    //try to create the log file. this is likely to work only in debug mode.
	    Log.enableFileLog(logfilename);
	    
#ifdef DEBUG
            Log << nl << "App::App() done";
#endif
        }

        App::~App()
        {
#ifdef DEBUG
            Log << nl << "App::~App() called";
#endif

	if (Optional::WasInit(Optional::TTF))
		Optional::Quit(Optional::TTF);

	if( Optional::WasInit(Optional::Net))
		Optional::Quit(Optional::Net);
				
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
			if (Optional::isLinked(Optional::TTF))
			{
				//Initialize SDL_ttf
				if( Optional::Init(Optional::TTF) )
				{
					Log << " TTF Error : " << Optional::GetError(Optional::TTF) << std::endl;
					return false;
				}
				return true;
			}
			return false;
			
		}

		bool App::initNet()
		{
			if (Optional::isLinked(Optional::Net))
			{
				//Initialize SDL_net
				if( Optional::Init(Optional::Net) )
				{
					Log << " NET Error : " << Optional::GetError(Optional::Net) << std::endl;
					return false;
				}
				return true;
			}
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

