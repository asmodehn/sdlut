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
	static SDLColor _bg;
	
	
	#else 
	
	#error "No library defined to handle 2D graphics"
	
	#endif
	
	Camera * _camera;
	
	public:
	
	//Config should have been called with Video turned on... CHECK TO ADD
	//this should add to the user input everything that is needed to handle
  Display(int width = 640, int height = 480) throw (std::logic_error) ;
  
  bool resize(int width = 640, int height)
  {//TODO in .cc
  }
  
  void setBGColor(const SDLColor& c = SDLColor(255,0,0));
  bool update(void);
  
  //function that implement the loop to manage the window and events.
  //void show();
};

#endif

