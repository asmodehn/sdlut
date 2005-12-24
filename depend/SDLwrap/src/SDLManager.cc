#include "SDLManager.hh"

namespace SDL
{

    Manager::Manager(bool video, bool audio, bool timer, bool cdrom, bool joystick, bool noparachute, bool eventthread) throw (std::logic_error)
    try
    {
        Uint32 flags;

        if (video) flags |= SDL_INIT_VIDEO;
        if (audio) flags |= SDL_INIT_AUDIO;
        if (timer) flags |= SDL_INIT_TIMER;
        if (cdrom) flags |= SDL_INIT_CDROM;
        if (joystick) flags |= SDL_INIT_JOYSTICK;
        if (noparachute) flags |= SDL_INIT_NOPARACHUTE;
        if (eventthread) flags |= SDL_INIT_EVENTTHREAD;

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
    }
    catch (std::exception &e)
    {
        Log << nl << "Exception catched in Manager Constructor" << nl << e.what();
    }

        bool enableTimer(void)
        {
            return SDL_InitSubSystem(SDL_INIT_TIMER) == 0;
        }
         bool enableAudio(void)
        {
            return SDL_InitSubSystem(SDL_INIT_AUDIO)== 0;
        }
         bool enableVideo(void)
        {
            return SDL_InitSubSystem(SDL_INIT_VIDEO)== 0;
        }
         bool enableCdrom(void)
        {
            return SDL_InitSubSystem(SDL_INIT_CDROM)== 0;
        }
         bool enableJoystick(void)
        {
            return SDL_InitSubSystem(SDL_INIT_JOYSTICK)== 0;
        }
         bool enableEverything(void)
        {
            return SDL_InitSubSystem(SDL_INIT_EVERYTHING)== 0;
        }
         bool enableNoParachute(void)
        {
            return SDL_InitSubSystem(SDL_INIT_NOPARACHUTE)== 0;
        }
         bool enableEventThread(void)
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
