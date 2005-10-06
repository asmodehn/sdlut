#ifndef DISPLAY_HH
#define DISPLAY_HH

#include "Config.hh"
#include "Camera.hh"

class Display
{
  protected : 
	
	#ifdef USE_DEPEND_SDLwrap
	
	//only one display possible at the same time
	static SDLDisplaySurface * _display;	
	
	#else 
	
	#error "No library defined to handle 2D graphics"
	
	#endif
	
	Camera * _camera;
	
	public:
	
  Display(int width = 640, int height = 480) throw (std::logic_error) ;
  
};

#endif

