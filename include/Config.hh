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

//further reference
//for friend access
class Display;
class Sprite;

class Config
{
	private:
	
  #ifdef USE_DEPEND_SDLwrap
	
	//only one display possible at the same time
	static SDLDisplaySurface * _screen;	
	
	#else 
	
	#error "No library defined to handle 2D graphics"
	
	#endif	
	
	friend class Display;
	friend class Sprite;
	
	static Config * _uniqueInstance;
	
	protected:
	
	Config(void);
	Config(bool video, bool audio, bool cdrom, bool joystick, bool timer);
		
	public:
	
	static Config * getConfig(void);
	static Config * setConfig(bool video, bool audio, bool cdrom, bool joystick, bool timer);
	
	
	bool isScreenSet() { return _screen!=NULL; }
	

};








#endif

