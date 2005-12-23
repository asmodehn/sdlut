#include "SDLManager.hh"

namespace SDL
{

    Manager* Manager::_uniqueInstance = NULL;

    Manager::Manager(Uint32 flags) throw (std::logic_error)
    try
    {
    	 _screen=NULL;
    	 _vinfo=NULL;
    	 #ifdef HAVE_OPENGL
       _gl=NULL;
			#endif
				if (!Log.enableFileLog("SDLWrap.log"))
					  throw std::logic_error("Log file creation FAILED !");
        if (SDL_Init(flags)<0)
        {
            throw std::logic_error("SDL_Init failed!");
        }

        if (isVideoEnabled())
        {
        	_vinfo=new VideoInfo();
        	#ifdef HAVE_OPENGL
					_gl=new GLManager();
					#endif
        }


    }
    catch (std::exception &e)
    {
        Log << "Exception catched in Manager Constructor !!!" << nl << e.what();
    }

    bool Manager::init(Uint32 flags)
    {
        bool res = false;
        //if already created call initsubsystem
        if ( _uniqueInstance!=NULL && ( res=SDL_InitSubSystem(flags)==0 ))
        {
            error(flags);
        }
        else //otherwise creates a new instance
        {
            try
            {
                _uniqueInstance = new Manager(flags);
            }
            catch (std::exception & e)
            {
                error(flags);
                res=false;
								Log << e.what();
            }
            if (_uniqueInstance != NULL)
                res = true;
        }
        return res;
    }

    void Manager::disableTimer(void)
    {
        if (_uniqueInstance!=NULL)
            SDL_QuitSubSystem(SDL_INIT_TIMER);
    }
    void Manager::disableAudio(void)
    {
        if (_uniqueInstance!=NULL)
            SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
    void Manager::disableVideo(void)
    {
        if (_uniqueInstance!=NULL)
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }
    void Manager::disableCdrom(void)
    {
        if (_uniqueInstance!=NULL)
            SDL_QuitSubSystem(SDL_INIT_CDROM);
    }
    void Manager::disableJoystick(void)
    {
        if (_uniqueInstance!=NULL)
            SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
    }
    void Manager::disableEverything(void)
    {
        if (_uniqueInstance!=NULL)
            SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
    }
    void Manager::disableNoParachute(void)
    {
        if (_uniqueInstance!=NULL)
            SDL_QuitSubSystem(SDL_INIT_NOPARACHUTE);
    }
    void Manager::disableEventThread(void)
    {
        if (_uniqueInstance!=NULL)
            SDL_QuitSubSystem(SDL_INIT_EVENTTHREAD);
    }

DisplaySurface * Manager::setDisplay( int width, int height, int bpp)
{
	//if (!isVideoEnabled()) { enableVideo(); std::cerr << "WARNING : shouldnt be needed !!!" << std::endl; }
	//if _screen already exists
	if (_screen!=NULL)
	{
		//resize it
		_screen->resize(width, height);
	}
    else
    {
        resetDisplay(width, height, bpp);
    }
    return _screen;
}

DisplaySurface * Manager::resetDisplay( int width, int height, int bpp)
{
		//if (!isVideoEnabled()) {enableVideo(); std::cerr << "WARNING : shouldnt be needed !!!" << std::endl; }
    //getting the actual bpp value
	//maybe this is already done by SDL and this code is just a waste of time ?
	if ( bpp == DEFAULT_DISPLAY_BPP )
	{
		//getting the best video mode pixel format
		//_vinfo has been built in the constructor
		bpp=_vinfo->getPixelFormat()->getBitsPerPixel();
	}

	bpp=SDL_VideoModeOK(width, height, bpp, DisplaySurface::flags );
    //but beware about bpp == 0...
    if ( bpp == 0 )
    {//0 as return code mean the current format is not supported
        Log << nl << "The requested video mode is not supported under any bit depth";
        return NULL;
    }
	else
	{
	  Log << nl << "SDL will use " << width << "x" << height << "@" <<bpp << std::endl;
	}


    //setting caption (default if needed) BEFORE construction the displaysurface...
    std::string titletest, icontest;
    DisplaySurface::getCaption( titletest, icontest);
    if ( titletest == "" && icontest == "" ) DisplaySurface::setCaption();

	//create a new screen
	try
	{
#ifdef HAVE_OPENGL
		if (SDL_OPENGL & DisplaySurface::flags)
		{
			_screen = new GLWindow(width, height, bpp );
		}
		else
		{
#endif
			_screen = new Window(width, height, bpp );
#ifdef HAVE_OPENGL
		}
#endif

	}
	//beware about the bpp == 0 used with rgbsurfaces !
	catch(std::exception & e)
	{
		Log << e.what();
	}
	return _screen;

}



    void Manager::debug(void)
    {

        Log << nl << std::boolalpha << "Manager::debug()" << nl <<
        "- Is Timer Enabled ? " << isTimerEnabled() << nl <<
        "- Is Audio Enabled ? " << isAudioEnabled() << nl <<
        "- Is Video Enabled ? " << isVideoEnabled() << nl <<
        "- Is CDROM Enabled ? " << isCdromEnabled() << nl <<
        "- Is Joystick Enabled ? " << isJoystickEnabled() << nl <<
        "- Is \"NoParachute\" Enabled ? " << isNoParachuteEnabled() << nl <<
        "- Is \"EventThread\" Enabled ? " << isEventThreadEnabled() << std::endl;

    }

}//namespace SDL
