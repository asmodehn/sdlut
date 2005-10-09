#include "Display.hh"

SDLDisplaySurface * Display::_display=NULL;	

Display::Display(int width, int height) throw (std::logic_error)
try{
	#ifdef USE_DEPEND_SDLwrap
	
	SDLSurfaceFactory::setDisplaySize(width,height);
	//BEWARE : we HAVE TO BE SURE that the actual SDLDisplaySurface is created here...
	_display=SDLSurfaceFactory::createDisplay("AML Application","../data/SDL.ico");
	if ( NULL == _display ) //otherwise the display creation fail as well.
    throw std::logic_error("SDLDisplaySurface creation failed !");
  
  
  #else 
  #error "No library defined to handle 2D graphics"
	#endif
	
	//give the info to Config about the screen
	Config::_screen=_display;
	
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


bool Display::update(void)
{
	bool res = false;
	if (_camera!=NULL)
  {
  	_camera->render(_display->getWidth()/2,_display->getHeight()/2);
  	res=true;
  }
  return res;
}

