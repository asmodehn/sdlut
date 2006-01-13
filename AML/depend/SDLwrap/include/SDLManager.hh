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


namespace SDL
{

    //Singleton Class to manage initializations in SDL
    class Manager
    {

    friend class App;

    protected:
        Manager(bool video = false, bool audio = false, bool timer = false, bool cdrom = false, bool joystick = false, bool noparachute = false, bool eventthread = false) throw (std::logic_error);
        ~Manager()
        {
            SDL_Quit();
        }
        //bool init(Uint32 flags);

    public:
    //Enablers
        bool enableTimer(void);
        bool enableAudio(void);
        bool enableVideo(void);
        bool enableCdrom(void);
        bool enableJoystick(void);
        bool enableEverything(void);
        bool enableNoParachute(void);
        bool enableEventThread(void);

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
        inline bool isTimerEnabled(void) const
        {
            return ( SDL_WasInit(SDL_INIT_TIMER) ) != 0;
        }
        inline bool isAudioEnabled(void) const
        {
            return ( SDL_WasInit(SDL_INIT_AUDIO) ) != 0;
        }
        inline bool isVideoEnabled(void) const
        {
            return ( SDL_WasInit(SDL_INIT_VIDEO) ) != 0;
        }
        inline bool isCdromEnabled(void) const
        {
            return ( SDL_WasInit(SDL_INIT_CDROM) ) != 0;
        }
        inline bool isJoystickEnabled(void) const
        {
            return ( SDL_WasInit(SDL_INIT_JOYSTICK) ) != 0;
        }
        inline bool isNoParachuteEnabled(void) const
        {
            return ( SDL_WasInit(SDL_INIT_NOPARACHUTE) ) != 0;
        }
        inline bool isEventThreadEnabled(void) const
        {
            return ( SDL_WasInit(SDL_INIT_EVENTTHREAD) ) != 0;
        }



        //display all Informations
	friend Logger & operator << (Logger & log, const Manager & man);

    };

}//namespace SDL
#endif

