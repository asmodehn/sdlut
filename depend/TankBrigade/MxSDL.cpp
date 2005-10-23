#include "MxSDL.h"

namespace MxLib {
	
MxInit * MxInit::_instance = NULL;

MxInit::MxInit(int width, int height) throw (std::logic_error)
try
{
	if (!SDL::Manager::enableEverything())
	throw std::logic_error("SDL init failed");
	
	SDL::SurfaceFactory::setDisplayFlags(false,false,false,false,true,true,false ,true,true,false);
	
	SDL::SurfaceFactory::setDisplaySize(width, height);
	
	SDL::SurfaceFactory::createDisplay("Tank Brigade");
	
}
catch (std::exception &e)
{
	std::cout << e.what() << std::endl;
}

MxInit * MxInit::init(int width, int height)
{
	if ( _instance == NULL )
	{
		_instance= new MxInit(width, height);
	}
	return _instance;
}

SDL::DisplaySurface * MxInit::getDisplay(void)
{
	return SDL::SurfaceFactory::getScreen();
}

SDL::SurfaceFactory * MxBitmap::sm_factory = NULL;

MxBitmap::MxBitmap(std::string filename)
	{
		if ( sm_factory == NULL )
		{
      sm_factory = new SDL::SurfaceFactory;
      sm_factory->setRGBFlags(false, true, true);
		}
    m_surfindex=sm_factory->createRGBSurface(filename);
	}

MxBitmap::MxBitmap(std::string filename, const SDL::Color & colorKey)
	{
		if ( sm_factory == NULL )
		{
      sm_factory = new SDL::SurfaceFactory;
      sm_factory->setRGBFlags(false, true, true);
		}
    m_surfindex=sm_factory->createRGBSurface(filename,colorKey);
	}
	
void MxBitmap::optimize()
{
	m_surfindex = sm_factory->cloneToDisplay(m_surfindex);
}

SDL::RGBSurface * MxBitmap::getRawSurface()
{
	return sm_factory->getSurface(m_surfindex);
}

bool MxBitmap::render (int pixX , int pixY )
{
	return MxInit::getDisplay()->blit(*getRawSurface(),SDL::Point(pixX,pixY));
}

}
