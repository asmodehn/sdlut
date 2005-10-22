#include "SDLManager.hh"

/* Usefull Macro */
#define CONSTRUCTOR_CALL_BLOCK(SDLFlag)								\
	try 															\
	{																\
		_uniqueInstance = new Manager(SDLFlag);					\
		res=true;													\
	}																\
	catch (std::exception & e)										\
	{																\
		MANAGER_ERROR("SDLFlag"); res=false;						\
	}	
/**/

namespace SDL {

Manager* Manager::_uniqueInstance = NULL;

Manager::Manager(Uint32 flags) throw (std::logic_error)
try
{
	if (SDL_Init(flags)<0)
	{
		throw std::logic_error("SDL_Init failed!");
	}
}
catch (std::exception &e)
{
	LIB_ERROR ( "Exception catched in Manager Constructor !!!" );
	LIB_ERROR(e.what());
}

bool Manager::enableTimer(void)
{
	bool res;
	if ( _uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_TIMER))==0)
		MANAGER_ERROR("TIMER");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_TIMER) }
	return res;
}
bool Manager::enableAudio(void)
{
	int res;
	if (_uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_AUDIO))==0)
		MANAGER_ERROR("AUDIO");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_AUDIO) }
	return res;
}
bool Manager::enableVideo(void)
{
	int res;
	if (_uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_VIDEO))==0)
		MANAGER_ERROR("VIDEO");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_VIDEO) }
	return res;
}
bool Manager::enableCdrom(void)
{
	int res;
	if (_uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_CDROM))==0)
		MANAGER_ERROR("CDROM");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_CDROM)}
	return res;
}
bool Manager::enableJoystick(void)
{
	int res;
	if (_uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_JOYSTICK))==0)
		MANAGER_ERROR("JOYSTICK");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_JOYSTICK) }
	return res;	
}
bool Manager::enableEverything(void)
{
	int res;
	if (_uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_EVERYTHING))==0)
		MANAGER_ERROR("EVERYTHING");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_EVERYTHING) }
	return res;	
}
bool Manager::enableNoParachute(void)
{
	int res;
	if (_uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_NOPARACHUTE))==0)
		MANAGER_ERROR("NOPARACHUTE");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_NOPARACHUTE) }
	return res;
}
bool Manager::enableEventThread(void)
{
	int res;
	if (_uniqueInstance!=NULL && (res=SDL_InitSubSystem(SDL_INIT_EVENTTHREAD))==0)
		MANAGER_ERROR("EVENTTHREAD");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_EVENTTHREAD) }
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

void Manager::debug(void)
{
	//To prevent calls without proper Initialization...
	if (_uniqueInstance==NULL) enableEverything();
	
	std::cout << std::boolalpha << "\nManager::debug()" << "\n" <<
	"- Is Timer Enabled ? " << isTimerEnabled() << "\n" <<
	"- Is Audio Enabled ? " << isAudioEnabled() << "\n" <<
	"- Is Video Enabled ? " << isVideoEnabled() << "\n" <<
	"- Is CDROM Enabled ? " << isCdromEnabled() << "\n" <<
	"- Is Joystick Enabled ? " << isJoystickEnabled() << "\n" <<
	"- Is \"NoParachute\" Enabled ? " << isNoParachuteEnabled() << "\n" <<
	"- Is \"EventThread\" Enabled ? " << isEventThreadEnabled() << "\n" <<
	std::endl;
}

}//namespace SDL
