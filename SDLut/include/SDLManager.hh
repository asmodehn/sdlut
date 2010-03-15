#ifndef SDL_MANAGER_HH
#define SDL_MANAGER_HH

/**
 * \class Manager
 *
 * \ingroup General
 *
 * \brief Manage the global SDL state
 *
 * Class to manage SDL. It calls SDL_Quit when deleted
 * Provide also handy access to widely used classes
 *
 * \author Alex
 *
 * \date 2005/10/22
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "Logger.hh"


//we can include here the class that we manage...
//Themselves should refer to the SDLManager through a singleton in SDLConfig.hh ( if ever.. probably no point to access their own settings through here... )
#include "Video/internal/SDLVideoSurface.hh"

#include <stdexcept>

namespace RAGE
{
namespace SDL
{

//Class to manage initializations in SDL
class Manager
{

    friend class App;

protected:

    Manager(bool video = false, bool audio = false, bool timer = false, bool cdrom = false, bool joystick = false, bool noparachute = false, bool eventthread = false) throw (std::logic_error);

public:

    ~Manager();

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
    bool isTimerEnabled(void) const;
    bool isAudioEnabled(void) const;
    bool isVideoEnabled(void) const;
    bool isCdromEnabled(void) const;
    bool isJoystickEnabled(void) const;
    bool isNoParachuteEnabled(void) const;
    bool isEventThreadEnabled(void) const;

    //display all Informations
    friend Logger & operator << (Logger & log, const Manager & man);

};

}
}//namespace RAGE::SDL
#endif

