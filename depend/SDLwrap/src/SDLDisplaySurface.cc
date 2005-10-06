#include "SDLDisplaySurface.hh"

SDLDisplaySurface* SDLDisplaySurface::_screen = NULL;
std::string SDLDisplaySurface::_title = DEFAULT_WINDOW_TITLE;
std::string SDLDisplaySurface::_icon = DEFAULT_WINDOW_ICON;

//Constructor
SDLDisplaySurface::SDLDisplaySurface(int width, int height, int bpp, Uint32 flags) throw (std::logic_error)
try : SDLBaseSurface(SDL_SetVideoMode(width,height,bpp,flags ))
{
	if (_surf == NULL)
	{
		std::cerr << "Unable to set " << width << " x " << height << " display surface : ";
		throw std::logic_error("SDL_SetVideoMode() return NULL");
	}
			
	//If a caption has been defined
	SDL_WM_SetCaption(_title.c_str(), _icon.c_str());
	//SDL_WM_SetIcon(SDL_LoadBMP(_icon.c_str()),NULL);

}
catch (std::exception &e)
{
	LIB_ERROR( "Exception catched in SDLDisplaySurface Constructor !!!" );
	//Affichage Erreur
	LIB_ERROR(e.what());

	SDLERROR;
	//TODO : much more explicit error message...
}


void SDLDisplaySurface::setCaption(std::string title, std::string icon)
{
	_title=title; _icon=icon;
	//if already displayed, change the caption
	if (_screen!=NULL)
	{
		SDL_WM_SetCaption(_title.c_str(), _icon.c_str());
		//SDL_WM_SetIcon(SDL_LoadBMP(_icon.c_str()),NULL);
	}
}

void SDLDisplaySurface::getCaption(std::string & title, std::string & icon)
{
	char ** t,** i;
	SDL_WM_GetCaption(t,i);
	title=std::string(*t);
	icon=std::string(*i);
}

bool SDLDisplaySurface::iconify(void)
{
	return ( SDL_WM_IconifyWindow() != 0 );	
}

bool SDLDisplaySurface::toggleFullScreen(void)
{
	//This only works for X11
	#ifndef __MINGW32__
	return ( SDL_WM_ToggleFullScreen(_screen->_surf) != 0 ) ;
	#else
	//This is the workaround for Win32
	//TODO :
	// 1)	Copy the screen surface to another (backup...)
	// 2)	Free the screen surface
	// 3)	Create a new one with fullscreen set
	return false;
	#endif
}
/*enablegrabInput(void);
disableGrabInput(void);
queryGrabInput(void);
*/



bool SDLDisplaySurface::update(SDLRect r)
{
	if (locked()) return false;//to prevent calling while locked
	else SDL_UpdateRect(_surf, r.getx(), r.gety(), r.getw(), r.geth());
	return true;
}

bool SDLDisplaySurface::update(std::vector<SDLRect> rlist)
{
	if (locked()) return false;//to prevent calling while locked
	else 
	{
		SDL_Rect* list = new SDL_Rect[rlist.size()];
		for (unsigned int i=0; i<rlist.size() ; i++) list[i]=*(rlist[i]._rect);
		SDL_UpdateRects(_surf, rlist.size(), list);
	}
	return true;
}

void SDLDisplaySurface::debug(void) const
{
	SDLBaseSurface::debug();
	std::stringstream logstr;
	logstr<< std::boolalpha << "- Fullscreen ? " << isFullScreenset() << "\n"
				<< "- Resizable ? " << isResizableset() << "\n"
				<< "- NoFrame ? " << isNoFrameset() << "\n"
				<< "- AnyFormat ? " << isAnyFormatset() << "\n"
				<< "- Double Buffered ? " << isDoubleBufset();
  SDLConfig::getLog()->add(logstr.str(),verbose);
  //tmp
  SDLConfig::getLog()->flush();
}
