#include "Config.hh"

Config::Config(void)
{
	#ifdef USE_DEPEND_SDLwrap

	SDL::Manager::enableEverything();

  #else
  #error "No library defined to handle 2D graphics"
	#endif

}

Config::Config(bool video, bool audio, bool cdrom, bool joystick, bool timer)
{
	#ifdef USE_DEPEND_SDLwrap

	//TODO
	SDL::Manager::enableEverything();

  #else
  #error "No library defined to handle 2D graphics"
	#endif
}