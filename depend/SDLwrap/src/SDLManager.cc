#include "SDLManager.hh"

/* Usefull Macros */
#define CONSTRUCTOR_CALL_BLOCK(SDLFlag)								\
	try 															\
	{																\
		_uniqueInstance = new SDLManager(SDLFlag);					\
		res=true;													\
	}																\
	catch (std::exception & e)										\
	{																\
		MANAGER_ERROR("SDLFlag"); res=false;						\
	}	
/**/

SDLManager* SDLManager::_uniqueInstance = NULL;

SDLManager::SDLManager(Uint32 flags) throw (std::logic_error)
try
{
	if (SDL_Init(flags)<0)
	{
		throw std::logic_error("SDL_Init failed!");
	}
}
catch (std::exception &e)
{
	LIB_ERROR ( "Exception catched in SDLManager Constructor !!!" );
	LIB_ERROR(e.what());
}

bool SDLManager::enableTimer(void)
{
	bool res;
	if ( _uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_TIMER))==0)
		MANAGER_ERROR("TIMER");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_TIMER) }
	return res;
}
bool SDLManager::enableAudio(void)
{
	int res;
	if (_uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_AUDIO))==0)
		MANAGER_ERROR("AUDIO");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_AUDIO) }
	return res;
}
bool SDLManager::enableVideo(void)
{
	int res;
	if (_uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_VIDEO))==0)
		MANAGER_ERROR("VIDEO");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_VIDEO) }
	return res;
}
bool SDLManager::enableCdrom(void)
{
	int res;
	if (_uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_CDROM))==0)
		MANAGER_ERROR("CDROM");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_CDROM)}
	return res;
}
bool SDLManager::enableJoystick(void)
{
	int res;
	if (_uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_JOYSTICK))==0)
		MANAGER_ERROR("JOYSTICK");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_JOYSTICK) }
	return res;	
}
bool SDLManager::enableEverything(void)
{
	int res;
	if (_uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_EVERYTHING))==0)
		MANAGER_ERROR("EVERYTHING");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_EVERYTHING) }
	return res;	
}
bool SDLManager::enableNoParachute(void)
{
	int res;
	if (_uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_NOPARACHUTE))==0)
		MANAGER_ERROR("NOPARACHUTE");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_NOPARACHUTE) }
	return res;
}
bool SDLManager::enableEventThread(void)
{
	int res;
	if (_uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_EVENTTHREAD))==0)
		MANAGER_ERROR("EVENTTHREAD");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_EVENTTHREAD) }
	return res;
}

void SDLManager::disableTimer(void)
{
	if (_uniqueInstance!=NULL)
		SDL_QuitSubSystem(SDL_INIT_TIMER); 
}
void SDLManager::disableAudio(void)
{
	if (_uniqueInstance!=NULL)
		SDL_QuitSubSystem(SDL_INIT_AUDIO);
}
void SDLManager::disableVideo(void)
{
	if (_uniqueInstance!=NULL)
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
void SDLManager::disableCdrom(void)
{
	if (_uniqueInstance!=NULL)
		SDL_QuitSubSystem(SDL_INIT_CDROM);
}
void SDLManager::disableJoystick(void)
{
	if (_uniqueInstance!=NULL)
		SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
}
void SDLManager::disableEverything(void)
{
	if (_uniqueInstance!=NULL)
		SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
}
void SDLManager::disableNoParachute(void)
{
	if (_uniqueInstance!=NULL)
		SDL_QuitSubSystem(SDL_INIT_NOPARACHUTE);
}
void SDLManager::disableEventThread(void)
{
	if (_uniqueInstance!=NULL)
		SDL_QuitSubSystem(SDL_INIT_EVENTTHREAD);
}

void SDLManager::debug(void)
{
	//To prevent calls without proper Initialization...
	if (_uniqueInstance==NULL) enableEverything();
	
	std::cout << std::boolalpha << "\nSDLManager::debug()" << "\n" <<
	"- Is Timer Enabled ? " << isTimerEnabled() << "\n" <<
	"- Is Audio Enabled ? " << isAudioEnabled() << "\n" <<
	"- Is Video Enabled ? " << isVideoEnabled() << "\n" <<
	"- Is CDROM Enabled ? " << isCdromEnabled() << "\n" <<
	"- Is Joystick Enabled ? " << isJoystickEnabled() << "\n" <<
	"- Is \"NoParachute\" Enabled ? " << isNoParachuteEnabled() << "\n" <<
	"- Is \"EventThread\" Enabled ? " << isEventThreadEnabled() << "\n" <<
	std::endl;
}
