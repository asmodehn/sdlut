#include "Display.hh"

Display::Display(int width, int height) throw (std::logic_error)
try{
	#ifdef USE_DEPEND_SDLwrap
	
	SDLSurfaceFactory::setDisplaySize(width,height);
	//BEWARE : we HAVE TO BE SURE that the screen is created here...
	if ( NULL == SDLSurfaceFactory::createDisplay("AML Application","../data/SDL.ico") )
    throw std::logic_error("SDLDisplaySurface creation failed !");
  //otherwise the display creation fail as well.
  
  #else 
  #error "No library defined to handle 2D graphics"
	#endif
	
	//if there is already a Camera created, we attach the first of the list.
	_camera=Camera::getCamera(0);
	//if there is no Camera created, we create one.
	if ( _camera==NULL )
	{
		_camera = new Camera();
	}
	
}
catch (std::exception& e)
{
    //TODO : use the logger for that
    std::cerr << e.what() << std::endl;
}

