#include "Config.hh"

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
