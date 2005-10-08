#include "SDLSurfaceFactory.hh"

int SDLSurfaceFactory::displayWidth = DEFAULT_DISPLAY_WIDTH;
int SDLSurfaceFactory::displayHeight = DEFAULT_DISPLAY_HEIGHT;
int SDLSurfaceFactory::displayBPP = DEFAULT_DISPLAY_BPP;
std::vector<int> SDLSurfaceFactory::availableDisplayWidth;
std::vector<int> SDLSurfaceFactory::availableDisplayHeight;
Uint32 SDLSurfaceFactory::displayFlags = SDL_RESIZABLE | SDL_DOUBLEBUF | SDL_ANYFORMAT | SDL_HWSURFACE | SDL_HWPALETTE ;

SDLDisplaySurface* SDLSurfaceFactory::screen = NULL;

bool SDLSurfaceFactory::setDisplayFlags( bool openGL, bool fullScreen,
						bool resizable, bool noFrame,
						bool doubleBuf, bool anyFormat,
						bool SWSurface, bool HWSurface,
						bool HWPalette, bool asyncBlit)
{
	if ( openGL ) displayFlags|= SDL_OPENGL;
	if ( fullScreen ) displayFlags|= SDL_FULLSCREEN;
	if ( resizable ) displayFlags|= SDL_RESIZABLE;
	if ( noFrame ) displayFlags|= SDL_NOFRAME;
	if ( doubleBuf ) displayFlags|= SDL_DOUBLEBUF;
	if ( anyFormat ) displayFlags|= SDL_ANYFORMAT;
	if ( SWSurface ) displayFlags|= SDL_SWSURFACE;
	if ( HWSurface ) displayFlags|= SDL_HWSURFACE;
	if ( HWPalette ) displayFlags|= SDL_HWPALETTE;
	if ( asyncBlit ) displayFlags|= SDL_ASYNCBLIT;
	
	return checkAvailableDisplaySize();
}

bool SDLSurfaceFactory::setDisplaySize( int width, int height)
{
	displayWidth = width; displayHeight = height;
	int new_bpp=checkVideoMode();
	if ( new_bpp==0)  return false;
	else 
	{
		setDisplayBPP ( new_bpp );
	}
	return true;
}
	
bool SDLSurfaceFactory::checkAvailableDisplaySize(void)
{
	return checkAvailableDisplaySize( SDLVideoInfo::Info()->getPixelFormat());
}

bool SDLSurfaceFactory::checkAvailableDisplaySize( const SDLPixelFormat& fmt )
{
	SDL_Rect ** modes;
	bool res;
	//we copy the pixelformat (because of const behaviour...)
	SDL_PixelFormat* test_fmt= new SDL_PixelFormat(*(fmt._pformat));
	
	modes=SDL_ListModes(test_fmt, displayFlags);
	if (modes == (SDL_Rect **)0) res=false;
	else
	{
		availableDisplayWidth.clear();
		availableDisplayHeight.clear();
		
		if (modes == (SDL_Rect **)-1)
		{
			availableDisplayWidth.push_back(-1);
			availableDisplayHeight.push_back(-1);
		}
		else
		{
			for(int i=0;modes[i];++i)
			{
				availableDisplayWidth.push_back(modes[i]->w);
				availableDisplayHeight.push_back(modes[i]->h);
			}
		}
		res=true;
	}
	return res;
}

int SDLSurfaceFactory::checkVideoMode(void)
{
	SDLVideoInfo * vi = SDLVideoInfo::Info();

	//If bpp is 0 and VideoInfo is reachable
	//maybe this is already done by SDL and this code is just a waste of time ?
	if ( displayBPP == DEFAULT_DISPLAY_BPP && vi != NULL )
	{
		//getting the best video mode pixel format
		displayBPP=vi->getPixelFormat().getBitsPerPixel();
	}
	//but beware about bpp == 0... (especially when used with rgb)
	return SDL_VideoModeOK(displayWidth, displayHeight, displayBPP, displayFlags);
}

SDLDisplaySurface* SDLSurfaceFactory::createDisplay(std::string title, std::string icon)
{
	//if _screen already exists
	if (screen!=NULL)
	{
		//delete the object
		delete screen;			
	}

	//set the title and the icon of the window
	SDLDisplaySurface::setCaption(title,icon);

	//create a new screen
	try
	{
		if (SDL_OPENGL & displayFlags)
			screen = new SDLGLWindow(displayWidth, displayHeight, displayBPP , displayFlags );
		else
			screen = new SDLWindow(displayWidth, displayHeight, displayBPP , displayFlags );
	}
	//beware about the bpp == 0 used with rgbsurfaces !
	catch(std::exception & e)
	{
		LIB_ERROR(e.what());
	}
	
	
	
	return screen;
}

bool SDLSurfaceFactory::setRGBFlags( bool SWSURFACE, bool HWSURFACE, bool SRCCOLORKEY, bool SRCALPHA)
{
	if ( SWSURFACE ) RGBFlags|= SDL_SWSURFACE;
	if ( HWSURFACE ) RGBFlags|= SDL_HWSURFACE;
	if ( SRCCOLORKEY ) RGBFlags|= SDL_SRCCOLORKEY;
	if ( SRCALPHA ) RGBFlags|= SDL_SRCALPHA;

	//must create a kind of prototype to clone ??

	return true;
}

unsigned int SDLSurfaceFactory::createRGBSurface(void)
{
	SDLRGBSurface* surf = NULL;
	try
	{
		surf = new SDLRGBSurface(RGBWidth, RGBHeight, RGBBPP, RGBFlags);
	}
	catch ( std::exception& e )
	{
		LIB_ERROR("RGB Surface cannot be created !");
		LIB_ERROR(e.what());
	}
	if (surf!=NULL)
		surfaceList.insert(surfaceList.end(),surf);
	return surfaceList.size()-1;
}

unsigned int SDLSurfaceFactory::createRGBSurface(int width , int height , SDLColor color )
{
	SDLRGBSurface* surf = NULL;
	try
	{
		surf = new SDLRGBSurface(width, height, RGBBPP, RGBFlags);
		surf->fill(color);
	}
	catch ( std::exception& e )
	{
		LIB_ERROR("RGB Surface cannot be created !");
		LIB_ERROR(e.what());
	}
	if (surf!=NULL)
		surfaceList.insert(surfaceList.end(),surf);
	return surfaceList.size()-1;
}

unsigned int SDLSurfaceFactory::createRGBSurface(void* pixeldata, int depth, int pitch)
{
	SDLRGBSurface* surf = NULL;
	try
	{
		surf = new SDLRGBSurface(pixeldata, RGBWidth, RGBHeight, depth, pitch);
	}
	catch ( std::exception &e )
	{
		LIB_ERROR("RGB Surface cannot be created !");
		LIB_ERROR(e.what());
	}
	if (surf!=NULL)
		surfaceList.push_back(surf);
	return surfaceList.size()-1;
}

unsigned int SDLSurfaceFactory::createRGBSurface( std::string filename )
{
	SDLRGBSurface* surf = NULL;
	try
	{
		surf = new SDLRGBSurface(filename);
	}
	catch ( std::exception &e )
	{
		LIB_ERROR("RGB Surface cannot be created !");
		LIB_ERROR(e.what());
	}
	if (surf!=NULL)
		surfaceList.push_back(surf);
	return surfaceList.size()-1;
}

//recent add to enable background on file load if needed... 18/08/2005 - Alex
//TO TEST !
unsigned int SDLSurfaceFactory::createRGBSurface( std::string filename, SDLRGBColor bgcolor )
{
	SDLRGBSurface* fsurf = getSurface(createRGBSurface(filename));
	SDLRGBSurface* csurf = getSurface(createRGBSurface(fsurf->getWidth(),fsurf->getHeight(), bgcolor));
	
	csurf->blit(*fsurf);
  if (csurf!=NULL)
		surfaceList.push_back(csurf);
	return surfaceList.size()-1;
}

//clone an RGBSurface.
unsigned int SDLSurfaceFactory::clone(int index,int times) // clone the one on index
{
	SDLRGBSurface* toClone = surfaceList.at(index);
	try //before the loop, because if one fail, the others should fail also...
	{
		for(int i=0; i<times ; i++)
		{
			SDLRGBSurface* s = new SDLRGBSurface(*toClone,true,false,toClone->isSRCAlphaset());
			if (s != NULL)
        surfaceList.push_back(s);
		}
	}
	catch (std::exception & e)
	{
		LIB_ERROR(e.what());
	}
  return surfaceList.size()-1;;
}

unsigned int SDLSurfaceFactory::cloneToDisplay(int index,int times, bool alpha) // clone the one on index, optimized for display
{
	SDLRGBSurface* toClone = surfaceList.at(index);
	try //before the loop, because if one fail, the others should fail also...
	{
		for(int i=0; i<times ; i++)
		{
			SDLRGBSurface* s = new SDLRGBSurface(*toClone,true,true,alpha);
			if (s != NULL)
			  surfaceList.push_back(s);
		}
	}
	catch (std::exception & e)
	{
		LIB_ERROR(e.what());
	}
	return surfaceList.size()-1;
}

