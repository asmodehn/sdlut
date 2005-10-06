#ifndef AML_CONFIG_HH
#define AML_CONFIG_HH
//Common include for every AML header



//defining the use of SDLwrap by default
#ifndef USE_DEPEND_SDLwrap
#define USE_DEPEND_SDLwrap
//if using SDL (mandatory for now)
#include "SDLwrap.hh"
#endif








/**
  * This class manages the global configuration of AML
  */

class Config
{
	private:
	
	static Config * _uniqueInstance;
	
	public:
	
	Config(void);
	Config(bool video, bool audio, bool cdrom, bool joystick, bool timer);
	
	Config * getConfig();
	
};








#endif

