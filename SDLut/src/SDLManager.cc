#include "SDLManager.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

Manager::Manager(bool video, bool audio, bool timer, bool cdrom, bool joystick, bool noparachute, bool eventthread) throw (std::logic_error)
try
{
#ifdef DEBUG
    Log << nl << "Manager::Manager() called ...";
#endif

    Uint32 flags = 0;

    if (video)
        flags |= SDL_INIT_VIDEO;
    if (audio)
        flags |= SDL_INIT_AUDIO;
    if (timer)
        flags |= SDL_INIT_TIMER;
    if (cdrom)
        flags |= SDL_INIT_CDROM;
    if (joystick)
        flags |= SDL_INIT_JOYSTICK;
    if (noparachute)
        flags |= SDL_INIT_NOPARACHUTE;
// Win32 doesn't allow a separate event threadw
#ifndef WIN32
    if (eventthread)
        flags |= SDL_INIT_EVENTTHREAD;
//not sure what to do with mingw but probably nothing...
#endif

    if (SDL_Init(flags)<0)
    {
        //logs manager error with usefull information
        std::string errormsg("Unable to initialize SDL subsystems ");
        if ( (flags & SDL_INIT_TIMER) !=0 )
            errormsg+= "TIMER " ;
        if ( (flags & SDL_INIT_AUDIO) != 0)
            errormsg+= "AUDIO " ;
        if ( (flags & SDL_INIT_VIDEO) != 0)
            errormsg+= "VIDEO " ;
        if ( (flags & SDL_INIT_CDROM) != 0)
            errormsg+= "CDROM " ;
        if ( (flags & SDL_INIT_JOYSTICK) != 0)
            errormsg+= "JOYSTICK " ;
        if ( (flags & SDL_INIT_NOPARACHUTE) != 0)
            errormsg+= "NOPARACHUTE " ;
        if ( (flags & SDL_INIT_EVENTTHREAD) != 0)
            errormsg+= "EVENTTHREAD " ;

        Log << errormsg << ": " << GetError() ;
        throw std::logic_error("SDL_Init failed!");
    }
#ifdef DEBUG
    Log << nl << "Manager::Manager() done.";
#endif

}
catch (std::exception &e)
{
    Log << nl << "Exception catched in Manager Constructor" << nl << e.what();
}

Manager::~Manager()
{
#ifdef DEBUG
    Log << nl << "Manager::~Manager() called ...";
#endif

    SDL_Quit();
#ifdef DEBUG
    Log << nl << "Manager::~Manager() done.";
#endif
}

bool Manager::enableTimer(void)
{
    return SDL_InitSubSystem(SDL_INIT_TIMER) == 0;
}
bool Manager::enableAudio(void)
{
    return SDL_InitSubSystem(SDL_INIT_AUDIO)== 0;
}
bool Manager::enableVideo(void)
{
    return SDL_InitSubSystem(SDL_INIT_VIDEO)== 0;
}
bool Manager::enableCdrom(void)
{
    return SDL_InitSubSystem(SDL_INIT_CDROM)== 0;
}
bool Manager::enableJoystick(void)
{
    return SDL_InitSubSystem(SDL_INIT_JOYSTICK)== 0;
}
bool Manager::enableEverything(void)
{
    return SDL_InitSubSystem(SDL_INIT_EVERYTHING)== 0;
}
bool Manager::enableNoParachute(void)
{
    return SDL_InitSubSystem(SDL_INIT_NOPARACHUTE)== 0;
}
bool Manager::enableEventThread(void)
{
    return SDL_InitSubSystem(SDL_INIT_EVENTTHREAD)== 0;
}


void Manager::disableTimer(void)
{
    SDL_QuitSubSystem(SDL_INIT_TIMER);
}
void Manager::disableAudio(void)
{
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}
void Manager::disableVideo(void)
{
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
void Manager::disableCdrom(void)
{

    SDL_QuitSubSystem(SDL_INIT_CDROM);
}
void Manager::disableJoystick(void)
{

    SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
}
void Manager::disableEverything(void)
{

    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
}
void Manager::disableNoParachute(void)
{

    SDL_QuitSubSystem(SDL_INIT_NOPARACHUTE);
}
void Manager::disableEventThread(void)
{

    SDL_QuitSubSystem(SDL_INIT_EVENTTHREAD);
}


bool Manager::isTimerEnabled(void) const
{
    return ( SDL_WasInit(SDL_INIT_TIMER) ) != 0;
}
bool Manager::isAudioEnabled(void) const
{
    return ( SDL_WasInit(SDL_INIT_AUDIO) ) != 0;
}
bool Manager::isVideoEnabled(void) const
{
    return ( SDL_WasInit(SDL_INIT_VIDEO) ) != 0;
}
bool Manager::isCdromEnabled(void) const
{
    return ( SDL_WasInit(SDL_INIT_CDROM) ) != 0;
}
bool Manager::isJoystickEnabled(void) const
{
    return ( SDL_WasInit(SDL_INIT_JOYSTICK) ) != 0;
}
bool Manager::isNoParachuteEnabled(void) const
{
    return ( SDL_WasInit(SDL_INIT_NOPARACHUTE) ) != 0;
}
bool Manager::isEventThreadEnabled(void) const
{
    return ( SDL_WasInit(SDL_INIT_EVENTTHREAD) ) != 0;
}


bool Manager::enableOpenGL(void) const
{
    VideoSurface::setOpenGL(true);
    return isOpenGLEnabled();
}

bool Manager::disableOpenGL(void) const
{
    VideoSurface::setOpenGL(false);
    return ! isOpenGLEnabled();
}

bool Manager::isOpenGLEnabled(void) const
{
    //TODO : carefully check consistency with opengl setting on existing videosurface...
    //If needed check opengl set or not on creation and reset the default flags on Video Surface...
    return ( SDL_OPENGL & VideoSurface::ptm_defaultflags ) != 0;
}


Logger & operator << (Logger & log, const Manager & man)
{
    log << nl << std::boolalpha << "Manager :" << nl <<
    "- Is Timer Enabled ? " << man.isTimerEnabled() << nl <<
    "- Is Audio Enabled ? " << man.isAudioEnabled() << nl <<
    "- Is Video Enabled ? " << man.isVideoEnabled() << nl <<
    "- Is CDROM Enabled ? " << man.isCdromEnabled() << nl <<
    "- Is Joystick Enabled ? " << man.isJoystickEnabled() << nl <<
    "- Is \"NoParachute\" Enabled ? " << man.isNoParachuteEnabled() << nl <<
    "- Is \"EventThread\" Enabled ? " << man.isEventThreadEnabled() ;
    return log;

}
}
}//namespace RAGE::SDL
