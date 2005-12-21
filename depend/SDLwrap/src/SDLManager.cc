#include "SDLManager.hh"

///* Usefull Macro */
//#define CONSTRUCTOR_CALL_BLOCK(SDLFlag)        \
// try                \
// {                \
//  _uniqueInstance = new Manager(SDLFlag);      \
//  res=true;             \
// }                \
// catch (std::exception & e)          \
// {                \
//  error("SDLFlag"); res=false;        \
//  Config::addLog(e.what());         \
// }
///**/

namespace SDL
{

    Manager* Manager::_uniqueInstance = NULL;

    Manager::Manager(Uint32 flags) throw (std::logic_error)
    try : _screen(NULL), _vinfo(NULL)
    {
        if (SDL_Init(flags)<0)
        {
            throw std::logic_error("SDL_Init failed!");
        }
		_config = new Config();
    }
    catch (std::exception &e)
    {
        Config::addLog( "Exception catched in Manager Constructor !!!" );
        Config::addLog(e.what());
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
                Config::addLog(e.what());
            }
            if (_uniqueInstance != NULL)
                res = true;
        }
        return res;
    }

    //bool Manager::enableTimer(void)
    //{
    //
    // manager(SDL_INIT_TIMER)
    //
    //}
    //bool Manager::enableAudio(void)
    //{
    // bool res;
    // if (_uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_AUDIO)==0)))
    //  error("AUDIO");
    // else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_AUDIO) }
    // return res;
    //}
    //bool Manager::enableVideo(void)
    //{
    // bool res;
    // if (_uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_VIDEO)==0)))
    //  error("VIDEO");
    // else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_VIDEO) }
    // return res;
    //}
    //bool Manager::enableCdrom(void)
    //{
    // bool res;
    // if (_uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_CDROM)==0)))
    //  error("CDROM");
    // else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_CDROM)}
    // return res;
    //}
    //bool Manager::enableJoystick(void)
    //{
    // bool res;
    // if (_uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_JOYSTICK)==0)))
    //  error("JOYSTICK");
    // else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_JOYSTICK) }
    // return res;
    //}
    //bool Manager::enableEverything(void)
    //{
    // bool res;
    // if (_uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_EVERYTHING)==0)))
    //  error("EVERYTHING");
    // else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_EVERYTHING) }
    // return res;
    //}
    //bool Manager::enableNoParachute(void)
    //{
    // bool res;
    // if (_uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_NOPARACHUTE)==0)))
    //  error("NOPARACHUTE");
    // else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_NOPARACHUTE) }
    // return res;
    //}
    //bool Manager::enableEventThread(void)
    //{
    //  bool res;
    // if (_uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_EVENTTHREAD)==0)))
    //  error("EVENTTHREAD");
    // else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_EVENTTHREAD) }
    // return res;
    //}

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

    //getting the actual bpp value
	//maybe this is already done by SDL and this code is just a waste of time ?
	if ( bpp == DEFAULT_DISPLAY_BPP )
	{
		//getting the best video mode pixel format
		bpp=getVideoInfo()->getPixelFormat().getBitsPerPixel();
	}

	bpp=SDL_VideoModeOK(width, height, bpp, SDL_RESIZABLE | SDL_DOUBLEBUF | SDL_ANYFORMAT | SDL_HWSURFACE | SDL_HWPALETTE );
    //but beware about bpp == 0...
    if ( bpp == 0 )
    {//0 as return code mean the current format is not supported
        Config::addLog("The requested video mode is not supported under any bit depth");
        return NULL;
    }
	else
	{
	  std::stringstream ssused;
	  ssused << "SDL will use " << width << "x" << height << "@" <<bpp ;
	  Config::addLog(ssused.str());
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
		//if (SDL_OPENGL & displayFlags)
		//	screen = new GLWindow(width, height, bpp ,  );
		//else
		//{
#endif
			_screen = new Window(width, height, bpp );
#ifdef HAVE_OPENGL
		//}
#endif
std::cerr << "screen created" << std::endl;
	}
	//beware about the bpp == 0 used with rgbsurfaces !
	catch(std::exception & e)
	{
		Config::addLog(e.what());
	}
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
			Config::addLog(e.what());
			//no need to delete _vinfo, since constructor throw an exception
			//the VideoInfo Instance wasn't built
		}
	}
	return _vinfo;

}

    void Manager::debug(void)
    {
        //To prevent calls without proper Initialization...
        if (_uniqueInstance==NULL)
            enableEverything();

        std::stringstream logstr;
        logstr<< std::boolalpha << "Manager::debug()" << "\n" <<
        "- Is Timer Enabled ? " << isTimerEnabled() << "\n" <<
        "- Is Audio Enabled ? " << isAudioEnabled() << "\n" <<
        "- Is Video Enabled ? " << isVideoEnabled() << "\n" <<
        "- Is CDROM Enabled ? " << isCdromEnabled() << "\n" <<
        "- Is Joystick Enabled ? " << isJoystickEnabled() << "\n" <<
        "- Is \"NoParachute\" Enabled ? " << isNoParachuteEnabled() << "\n" <<
        "- Is \"EventThread\" Enabled ? " << isEventThreadEnabled() <<  std::endl;
        Config::addLog(logstr.str());
    }

}//namespace SDL
