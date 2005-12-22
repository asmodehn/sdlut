#include "SDLManager.hh"

namespace SDL
{

    Manager* Manager::_uniqueInstance = NULL;

    Manager::Manager(Uint32 flags) throw (std::logic_error)
    try : _screen(NULL), _vinfo(NULL)
#ifdef HAVE_OPENGL
        ,_gl(NULL)
#endif
    {
		Log.setLogfile("SDLWrap.log");
        if (SDL_Init(flags)<0)
        {
            throw std::logic_error("SDL_Init failed!");
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
    //getting the actual bpp value
	//maybe this is already done by SDL and this code is just a waste of time ?
	if ( bpp == DEFAULT_DISPLAY_BPP )
	{
		//getting the best video mode pixel format
		bpp=getVideoInfo()->getPixelFormat().getBitsPerPixel();
	}

	bpp=SDL_VideoModeOK(width, height, bpp, DisplaySurface::flags );
    //but beware about bpp == 0...
    if ( bpp == 0 )
    {//0 as return code mean the current format is not supported
        Log << "The requested video mode is not supported under any bit depth";
        return NULL;
    }
	else
	{
	  Log << "SDL will use " << width << "x" << height << "@" <<bpp ;
	}


    //setting caption (default if needed)
    std::string titletest, icontest;
    DisplaySurface::getCaption( titletest, icontest);
    if ( titletest == "" && icontest == "" ) DisplaySurface::setCaption();

std::cerr << "caption done" << std::endl;

	//create a new screen
	try
	{
#ifdef HAVE_OPENGL
		if (SDL_OPENGL & DisplaySurface::flags)
			_screen = new GLWindow(width, height, bpp );
		else
		{
#endif
			_screen = new Window(width, height, bpp );
#ifdef HAVE_OPENGL
		}
#endif
std::cerr << "screen created" << std::endl;
	}
	//beware about the bpp == 0 used with rgbsurfaces !
	catch(std::exception & e)
	{
		Log << e.what();
	}
	return _screen;

}

VideoInfo * Manager::getVideoInfo( void )
{
	if (_vinfo == NULL)
	{
		try
		{
			_vinfo=new VideoInfo();
		}
		catch (std::exception& e)
		{
			//Keep this catch to prevent program terminate...
			Log << e.what();
			//no need to delete _vinfo, since constructor throw an exception
			//the VideoInfo Instance wasn't built
		}
	}
	return _vinfo;

}

#ifdef HAVE_OPENGL
GLManager * Manager::getGLManager( void )
{
	if (_gl == NULL)
	{
		try
		{
			_gl=new GLManager();
		}
		catch (std::exception& e)
		{
			//Keep this catch to prevent program terminate...
			Log << e.what();
			//no need to delete _vinfo, since constructor throw an exception
			//the VideoInfo Instance wasn't built
		}
	}
	return _gl;

}
#endif

    void Manager::debug(void)
    {

        Log << nl << std::boolalpha << "Manager::debug()" << nl <<
        "- Is Timer Enabled ? " << isTimerEnabled() << nl <<
        "- Is Audio Enabled ? " << isAudioEnabled() << nl <<
        "- Is Video Enabled ? " << isVideoEnabled() << nl <<
        "- Is CDROM Enabled ? " << isCdromEnabled() << nl <<
        "- Is Joystick Enabled ? " << isJoystickEnabled() << nl <<
        "- Is \"NoParachute\" Enabled ? " << isNoParachuteEnabled() << nl <<
        "- Is \"EventThread\" Enabled ? " << isEventThreadEnabled() <<  std::endl;

    }

}//namespace SDL
