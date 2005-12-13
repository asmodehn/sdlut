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
 *
 * \author Alex
 *
 * \date 2005/10/22
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLConfig.hh"

//Error Messages
//#define MANAGER_ERROR(system) Config::addLog("Unable to initialize SDL " + system + " : " + GetError() )


namespace SDL {
//Singleton Class to manage initializations in SDL
//TODO : Make a separate SGEconfig
class Manager
{
	static Manager * _uniqueInstance;

protected:
	Manager(Uint32 flags = SDL_INIT_EVERYTHING) throw (std::logic_error);
	~Manager(){SDL_Quit();}

public:

	static inline Manager* manager(void) throw (std::logic_error)
	{
		if (_uniqueInstance == NULL)
			if (!enableEverything())
				throw std::logic_error("enableEverything failed !!!");
		return _uniqueInstance;
	}

	//Enablers creates the singleton Instance if not present
	//If Manager is already initialized, try to enable a subSystem
	//and return the result
	static bool enableTimer(void);
	static bool enableAudio(void);
	static bool enableVideo(void);
	static bool enableCdrom(void);
	static bool enableJoystick(void);
	static bool enableEverything(void);
	static bool enableNoParachute(void);
	static bool enableEventThread(void);

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
	inline bool isTimerEnabled(void) {return ( SDL_WasInit(SDL_INIT_TIMER) ) != 0;}
	inline bool isAudioEnabled(void) {return ( SDL_WasInit(SDL_INIT_AUDIO) ) != 0;}
	inline bool isVideoEnabled(void) {return ( SDL_WasInit(SDL_INIT_VIDEO) ) != 0;}
	inline bool isCdromEnabled(void) {return ( SDL_WasInit(SDL_INIT_CDROM) ) != 0;}
	inline bool isJoystickEnabled(void) {return ( SDL_WasInit(SDL_INIT_JOYSTICK) ) != 0;}
	inline bool isNoParachuteEnabled(void) {return ( SDL_WasInit(SDL_INIT_NOPARACHUTE) ) != 0;}
	inline bool isEventThreadEnabled(void) {return ( SDL_WasInit(SDL_INIT_EVENTTHREAD) ) != 0;}

	//logs manager error with usefull information
	static inline void error(std::string system)
	{
		Config::addLog("Unable to initialize SDL " + system + " : " + GetError() );
	}

	//display all Informations
	void debug(void);
};

}//namespace SDL
#endif
