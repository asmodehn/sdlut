#ifndef SDLMANAGER_HH
#define SDLMANAGER_HH

/**
 * \class SDLManager
 *
 * \ingroup General
 *
 * \brief Manage the global SDL state
 *
 * Singleton to manage SDL
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "SDLConfig.hh"

//#include "SDLDisplaySurface.hh"

//Error Messages
#define MANAGER_ERROR(system) LIB_ERROR("Unable to initialize SDL " << system << " : " << SDL_GetError() )

//Singleton Class to manage initializations in SDL
//TODO : Make a separate SGEconfig
class SDLManager
{
	static SDLManager * _uniqueInstance;
  static Logger * _SDLlog;

protected:
	SDLManager(Uint32 flags = SDL_INIT_EVERYTHING) throw (std::logic_error);
	~SDLManager(){SDL_Quit();}
	
public:
	
	static inline SDLManager* manager(void) throw (std::logic_error)
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
	inline bool isTimerEnabled(void) {return SDL_WasInit(SDL_INIT_TIMER);}
	inline bool isAudioEnabled(void) {return SDL_WasInit(SDL_INIT_AUDIO);}
	inline bool isVideoEnabled(void) {return SDL_WasInit(SDL_INIT_VIDEO);}
	inline bool isCdromEnabled(void) {return SDL_WasInit(SDL_INIT_CDROM);}
	inline bool isJoystickEnabled(void) {return SDL_WasInit(SDL_INIT_JOYSTICK);}
	inline bool isNoParachuteEnabled(void) {return SDL_WasInit(SDL_INIT_NOPARACHUTE);}
	inline bool isEventThreadEnabled(void) {return SDL_WasInit(SDL_INIT_EVENTTHREAD);}

  //Get the pointer to the Log
  inline Logger* getLog(void) {return _SDLlog;}

	//display all Informations
	void debug(void);
};
#endif
