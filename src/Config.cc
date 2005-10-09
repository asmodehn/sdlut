#include "Config.hh"

SDLDisplaySurface * Config::_screen=NULL;	

Config * Config::_uniqueInstance=NULL;

Config::Config(void)
{
	#ifdef USE_DEPEND_SDLwrap
	
	SDLManager::enableEverything();
  
  #else 
  #error "No library defined to handle 2D graphics"
	#endif

}

Config::Config(bool video, bool audio, bool cdrom, bool joystick, bool timer)
{
	#ifdef USE_DEPEND_SDLwrap
	
	//TODO
	SDLManager::enableEverything();
  
  #else 
  #error "No library defined to handle 2D graphics"
	#endif
}
	
Config * Config::getConfig()
{
	if (_uniqueInstance == NULL)
		_uniqueInstance=new Config();
	return _uniqueInstance;

}

Config * Config::setConfig(bool video, bool audio, bool cdrom, bool joystick, bool timer)
{
	if (_uniqueInstance == NULL)
		_uniqueInstance=new Config( video, audio, cdrom, joystick, timer);
	return _uniqueInstance;

}
