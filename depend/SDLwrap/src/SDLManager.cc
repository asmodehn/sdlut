#include "SDLManager.hh"

/* Usefull Macro */
#define CONSTRUCTOR_CALL_BLOCK(SDLFlag)								\
	try 															\
	{																\
		_uniqueInstance = new Manager(SDLFlag);						\
		res=true;													\
	}																\
	catch (std::exception & e)										\
	{																\
		error("SDLFlag"); res=false;								\
		Config::addLog(e.what());									\
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
	Config::addLog( "Exception catched in Manager Constructor !!!" );
	Config::addLog(e.what());
}

bool Manager::enableTimer(void)
{
	bool res;
	if ( _uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_TIMER)==0)))
		error("TIMER");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_TIMER) }
	return res;
}
bool Manager::enableAudio(void)
{
	bool res;
	if (_uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_AUDIO)==0)))
		error("AUDIO");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_AUDIO) }
	return res;
}
bool Manager::enableVideo(void)
{
	bool res;
	if (_uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_VIDEO)==0)))
		error("VIDEO");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_VIDEO) }
	return res;
}
bool Manager::enableCdrom(void)
{
	bool res;
	if (_uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_CDROM)==0)))
		error("CDROM");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_CDROM)}
	return res;
}
bool Manager::enableJoystick(void)
{
	bool res;
	if (_uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_JOYSTICK)==0)))
		error("JOYSTICK");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_JOYSTICK) }
	return res;
}
bool Manager::enableEverything(void)
{
	bool res;
	if (_uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_EVERYTHING)==0)))
		error("EVERYTHING");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_EVERYTHING) }
	return res;
}
bool Manager::enableNoParachute(void)
{
	bool res;
	if (_uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_NOPARACHUTE)==0)))
		error("NOPARACHUTE");
	else { CONSTRUCTOR_CALL_BLOCK(SDL_INIT_NOPARACHUTE) }
	return res;
}
bool Manager::enableEventThread(void)
{
  bool res;
	if (_uniqueInstance!=NULL && (res=(SDL_InitSubSystem(SDL_INIT_EVENTTHREAD)==0)))
		error("EVENTTHREAD");
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

 std::stringstream logstr;
	logstr<< std::boolalpha << "Manager::debug()" << "\n" <<
	"- Is Timer Enabled ? " << isTimerEnabled() << "\n" <<
	"- Is Audio Enabled ? " << isAudioEnabled() << "\n" <<
	"- Is Video Enabled ? " << isVideoEnabled() << "\n" <<
	"- Is CDROM Enabled ? " << isCdromEnabled() << "\n" <<
	"- Is Joystick Enabled ? " << isJoystickEnabled() << "\n" <<
	"- Is \"NoParachute\" Enabled ? " << isNoParachuteEnabled() << "\n" <<
	"- Is \"EventThread\" Enabled ? " << isEventThreadEnabled() << 	std::endl;
  Config::addLog(logstr.str());
}

}//namespace SDL
