#include "SDLSurfaceFactory.hh"

namespace SDL  {

int SurfaceFactory::displayWidth = DEFAULT_DISPLAY_WIDTH;
int SurfaceFactory::displayHeight = DEFAULT_DISPLAY_HEIGHT;
int SurfaceFactory::displayBPP = DEFAULT_DISPLAY_BPP;
std::vector<int> SurfaceFactory::availableDisplayWidth;
std::vector<int> SurfaceFactory::availableDisplayHeight;
Uint32 SurfaceFactory::displayFlags = SDL_RESIZABLE | SDL_DOUBLEBUF | SDL_ANYFORMAT | SDL_HWSURFACE | SDL_HWPALETTE ;

DisplaySurface* SurfaceFactory::screen = NULL;

bool SurfaceFactory::setDisplayFlags( bool openGL, bool fullScreen,
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

bool SurfaceFactory::setDisplaySize( int width, int height)
{
	displayWidth = width; displayHeight = height;
	int new_bpp=checkVideoMode();
	if (new_bpp)
    setDisplayBPP ( new_bpp );
	else 
		return false;
	return true;
}
	
bool SurfaceFactory::checkAvailableDisplaySize(void)
{
	return checkAvailableDisplaySize( VideoInfo::Info()->getPixelFormat());
}

bool SurfaceFactory::checkAvailableDisplaySize( const PixelFormat& fmt )
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

int SurfaceFactory::checkVideoMode(void)
{
	VideoInfo * vi = VideoInfo::Info();

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

DisplaySurface* SurfaceFactory::createDisplay(std::string title, std::string icon)
{
	//if _screen already exists
	if (screen!=NULL)
	{
		//delete the object
		delete screen;			
	}

	//set the title and the icon of the window
	DisplaySurface::setCaption(title,icon);

	//create a new screen
	try
	{
#ifdef OPENGL
		if (SDL_OPENGL & displayFlags)
			screen = new GLWindow(displayWidth, displayHeight, displayBPP , displayFlags );
		else
		{
#endif
			screen = new Window(displayWidth, displayHeight, displayBPP , displayFlags );
#ifdef OPENGL
		}
#endif
	}
	//beware about the bpp == 0 used with rgbsurfaces !
	catch(std::exception & e)
	{
		LIB_ERROR(e.what());
	}
	
	
	
	return screen;
}

bool SurfaceFactory::setRGBFlags( bool SWSURFACE, bool HWSURFACE, bool SRCCOLORKEY, bool SRCALPHA)
{
	if ( SWSURFACE ) RGBFlags|= SDL_SWSURFACE;
	if ( HWSURFACE ) RGBFlags|= SDL_HWSURFACE;
	if ( SRCCOLORKEY ) RGBFlags|= SDL_SRCCOLORKEY;
	if ( SRCALPHA ) RGBFlags|= SDL_SRCALPHA;

	//must create a kind of prototype to clone ??

	return true;
}

unsigned int SurfaceFactory::createRGBSurface(void)
{
	RGBSurface* surf = NULL;
	try
	{
		surf = new RGBSurface(RGBWidth, RGBHeight, RGBBPP, RGBFlags);
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

unsigned int SurfaceFactory::createRGBSurface(int width , int height , Color color )
{
	RGBSurface* surf = NULL;
	try
	{
		surf = new RGBSurface(width, height, RGBBPP, RGBFlags);
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

unsigned int SurfaceFactory::createRGBSurface(void* pixeldata, int depth, int pitch)
{
	RGBSurface* surf = NULL;
	try
	{
		surf = new RGBSurface(pixeldata, RGBWidth, RGBHeight, depth, pitch);
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

unsigned int SurfaceFactory::createRGBSurface( std::string filename )
{
	RGBSurface* surf = NULL;
	try
	{
		surf = new RGBSurface(filename);
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
unsigned int SurfaceFactory::createRGBSurface( std::string filename, RGBColor bgcolor )
{
	RGBSurface* fsurf = getSurface(createRGBSurface(filename));
	RGBSurface* csurf = getSurface(createRGBSurface(fsurf->getWidth(),fsurf->getHeight(), bgcolor));
	
	csurf->blit(*fsurf);
  if (csurf!=NULL)
		surfaceList.push_back(csurf);
	return surfaceList.size()-1;
}

//clone an RGBSurface.
unsigned int SurfaceFactory::clone(int index,int times) // clone the one on index
{
	RGBSurface* toClone = surfaceList.at(index);
	try //before the loop, because if one fail, the others should fail also...
	{
		for(int i=0; i<times ; i++)
		{
			RGBSurface* s = new RGBSurface(*toClone,true,false,toClone->isSRCAlphaset());
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

unsigned int SurfaceFactory::cloneToDisplay(int index,int times, bool alpha) // clone the one on index, optimized for display
{
	RGBSurface* toClone = surfaceList.at(index);
	try //before the loop, because if one fail, the others should fail also...
	{
		for(int i=0; i<times ; i++)
		{
			RGBSurface* s = new RGBSurface(*toClone,true,true,alpha);
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

}
