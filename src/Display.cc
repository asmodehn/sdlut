#include "Display.hh"

SDLDisplaySurface * Display::_display=NULL;	
SDLColor Display::_bg=SDLColor(255,0,0);

Display::Display(int width, int height) throw (std::logic_error)
try{
	#ifdef USE_DEPEND_SDLwrap
	
	if(!SDLSurfaceFactory::setDisplayFlags())
    throw std::logic_error("The required mode is not available !");
	
	if (!SDLSurfaceFactory::setDisplaySize(width,height))
		throw std::logic_error("This Size is not available in the current mode !");
	
	//BEWARE : we HAVE TO BE SURE that the actual SDLDisplaySurface is created here...
	_display=SDLSurfaceFactory::createDisplay("AML Application");//"../data/SDL.ico"
	if ( NULL == _display ) //otherwise the display creation fail as well.
    throw std::logic_error("SDLDisplaySurface creation failed !");
  
  
  std::cout << "SDL will use " << SDLSurfaceFactory::getScreen()->getWidth()
            << "x" << SDLSurfaceFactory::getScreen()->getHeight()
            << "@" << SDLSurfaceFactory::getScreen()->getBPP()
            << std::endl;
  
  #else 
  #error "No library defined to handle 2D graphics"
	#endif
	_display->fill(_bg);
	
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

bool Display::resize(int width, int height)
{
	return _display->resize(width,height);
}

void Display::setBGColor(const SDLColor& c )
{
	//_bg=c; //TO FIX
	_display->fill(c);
}

bool Display::update(void)
{
	bool res = false;
	_display->fill(_bg);
	if (_camera!=NULL)
  {
  	std::cerr<< "Calling _camera->render (" <<_display->getWidth()/2 << "," << _display->getHeight()/2<< ")"<<std::endl;
  	_camera->render(_display->getWidth()/2,_display->getHeight()/2);
  	_display->debug();
  	res=true;
  }
  return res;
}

