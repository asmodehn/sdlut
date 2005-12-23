#ifndef SDL_MANAGER_HH
#define SDL_MANAGER_HH

/**
 * \class Manager
 *
 * \ingroup General
 *
 * \brief Manage the global SDL state
 *
 * Singleton to manage SDL. It calls SDL_Quit when deleted
 * Provide also handy access to widely used classes
 *
 * \author Alex
 *
 * \date 2005/10/22
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLConfig.hh"

#include "SDLVideoInfo.hh"
#ifdef HAVE_OPENGL
#include "SDLGLWindow.hh"
#include "SDLGLManager.hh"
#endif //HAVE_OPENGL

#include "SDLWindow.hh"


namespace SDL
{

    //Singleton Class to manage initializations in SDL
    class Manager
    {
        static Manager * _uniqueInstance;

        //logs manager error with usefull information
        static inline void error(Uint32 flags)
        {
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
        }

        DisplaySurface * _screen;
        VideoInfo * _vinfo;
#ifdef HAVE_OPENGL
        GLManager * _gl;
#endif

    protected:
        Manager(Uint32 flags = SDL_INIT_EVERYTHING) throw (std::logic_error);
        ~Manager()
        {
            SDL_Quit();
        }
        static bool init(Uint32 flags);


    public:

        static inline Manager* manager(void) throw (std::logic_error)
        {
            if (_uniqueInstance == NULL)
						{
							enableEverything();
              throw std::logic_error("WARNING : Everything Enabled by default. You should enable subsystems manually !");
						}
            return _uniqueInstance;
        }


        //Enablers creates the singleton Instance if not present
        //If Manager is already initialized, try to enable a subSystem
        //and return the result
        static inline bool enableTimer(void)
        {
            return init(SDL_INIT_TIMER);
        }
        static inline bool enableAudio(void)
        {
            return init(SDL_INIT_AUDIO);
        }
        static inline bool enableVideo(void)
        {
            return init(SDL_INIT_VIDEO);
        }
        static inline bool enableCdrom(void)
        {
            return init(SDL_INIT_CDROM);
        }
        static inline bool enableJoystick(void)
        {
            return init(SDL_INIT_JOYSTICK);
        }
        static inline bool enableEverything(void)
        {
            return init(SDL_INIT_EVERYTHING);
        }
        static inline bool enableNoParachute(void)
        {
            return init(SDL_INIT_NOPARACHUTE);
        }
        static inline bool enableEventThread(void)
        {
            return init(SDL_INIT_EVENTTHREAD);
        }

        //Disablers
        void disableTimer(void);
        void disableAudio(void);
        void disableVideo(void);
        void disableCdrom(void);
        void disableJoystick(void);
        void disableEverything(void);
        void disableNoParachute(void);
        void disableEventThread(void);

        //Accesseurs
        inline bool isTimerEnabled(void)
        {
            return ( SDL_WasInit(SDL_INIT_TIMER) ) != 0;
        }
        inline bool isAudioEnabled(void)
        {
            return ( SDL_WasInit(SDL_INIT_AUDIO) ) != 0;
        }
        inline bool isVideoEnabled(void)
        {
            return ( SDL_WasInit(SDL_INIT_VIDEO) ) != 0;
        }
        inline bool isCdromEnabled(void)
        {
            return ( SDL_WasInit(SDL_INIT_CDROM) ) != 0;
        }
        inline bool isJoystickEnabled(void)
        {
            return ( SDL_WasInit(SDL_INIT_JOYSTICK) ) != 0;
        }
        inline bool isNoParachuteEnabled(void)
        {
            return ( SDL_WasInit(SDL_INIT_NOPARACHUTE) ) != 0;
        }
        inline bool isEventThreadEnabled(void)
        {
            return ( SDL_WasInit(SDL_INIT_EVENTTHREAD) ) != 0;
        }



        //display all Informations
        void debug(void);

        //Access other classes (instanced only once)
        DisplaySurface * setDisplay( int width = DEFAULT_DISPLAY_WIDTH, int height = DEFAULT_DISPLAY_HEIGHT, int bpp = DEFAULT_DISPLAY_BPP );
        //same than set but forces the re-creation...
        DisplaySurface * resetDisplay( int width = DEFAULT_DISPLAY_WIDTH, int height = DEFAULT_DISPLAY_HEIGHT, int bpp = DEFAULT_DISPLAY_BPP );
        DisplaySurface * getDisplay( void ) {return _screen;} //init if not?

        VideoInfo * getVideoInfo( void ) {return _vinfo;}

#ifdef HAVE_OPENGL
        GLManager * getGLManager() {return _gl;}
#endif
    };

}//namespace SDL
#endif
