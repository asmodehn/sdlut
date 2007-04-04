#include "SDLApp.hh"
#include "SDLConfig.hh"

namespace RAGE
{
    namespace SDL
    {

	App::App() : pvm_manager(NULL), pvm_window(NULL), pvm_mixer(NULL)
        {
#ifdef DEBUG
            Log << nl << "App::App() called";
#endif

            setName(DEFAULT_WINDOW_TITLE);
            setIcon("");
	    Log.enableFileLog(LOGFILENAME);
#ifndef DEBUG
	    Log.disableConsoleLog();
#endif
	    
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
            delete pvm_window, pvm_window = NULL;
            delete pvm_mixer, pvm_mixer=NULL;
            //this one should be last because it calls SDL_Quit
            delete pvm_manager;
            pvm_manager = NULL;
	    
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
			if (pvm_manager == NULL)
			{
				pvm_manager = new Manager(false,false,false,true,false,false,false);
				return true;
			}
			else
			{
				return pvm_manager->enableCdrom();
			}
			return false;
            
			
		}

		//Initialize sdl timer
		bool App::initTimer()
		{
			if (pvm_manager == NULL)
			{
				pvm_manager = new Manager(false,false,true,false,false,false,false);
				return true;
			}
			else
			{
				return pvm_manager->enableTimer();
			}
			return false;
            
			
		}

        bool App::initVideo( bool fullscreen,bool opengl, bool resizable, bool noframe)
        {
            bool res = false;
            try
            {
                if (pvm_manager == NULL)
                {
                    pvm_manager = new Manager(true,false,false,false,false,false,false);
					res = ( pvm_manager != NULL );
                }
                else
                {
                    res = pvm_manager->enableVideo();
                }

                pvm_window = new Window(pvm_name);


                //setting the required flags...
#ifdef HAVE_OPENGL

		pvm_window->setOpenGL(opengl);
#else

                if(opengl)
                    Log << nl << "Not compiled with opengl support --> Ignoring opengl window request"<< std::endl;
#endif

                    pvm_window->setFullscreen(fullscreen);
                    pvm_window->setResizable(resizable);
                    pvm_window->setNoFrame(noframe);

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
            if (pvm_manager == NULL)
            {
                try
                {
                    pvm_manager = new Manager(false,false,false,false,true,false,false);
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
                res = pvm_manager->enableJoystick();
            }

            if ( res == true )
                pvm_jpool = new JoystickPool();
#ifdef DEBUG

            Log << nl << "Number of Joysticks available : " << pvm_jpool->countAvailable();

            for ( int i=0; i<  pvm_jpool->countAvailable(); i++ )
                Log << nl << " Joystick " << i << " : " << pvm_jpool->getName(i) ;
#endif

            return res;
        }

	bool App::initAudio()
	{
		bool res = false;
		try
		{
		
			if (pvm_manager == NULL)
			{
				pvm_manager = new Manager(false,true,false,false,false,false,false);
				res = (pvm_manager != NULL);
			}
			else
			{
				res = pvm_manager->enableAudio();
			}
		
			if ( res == true )
				//tmp for test
				pvm_mixer = new Mixer();
		
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
			if (pvm_manager == NULL)
			{
				pvm_manager = new Manager(false,false,false,false,false,false,false);
				return (pvm_manager != NULL);
			}
			return false;
			
		}
    }
}

