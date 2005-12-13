#include "SDLDisplaySurface.hh"
//#include <sstream>

namespace SDL {

DisplaySurface* DisplaySurface::_screen = NULL;
std::string DisplaySurface::_title = DEFAULT_WINDOW_TITLE;
std::string DisplaySurface::_icon = DEFAULT_WINDOW_ICON;

//Constructor
DisplaySurface::DisplaySurface(int width, int height, int bpp, Uint32 flags) throw (std::logic_error)
try : BaseSurface(SDL_SetVideoMode(width,height,bpp,flags ))
{
	if (_surf == NULL)
	{
	  std::stringstream ss;
	  ss<<"Unable to set " << width << " x " << height << " display surface : ";
		Config::addLog(ss.str() );
		throw std::logic_error("SDL_SetVideoMode() return NULL");
	}

	//If a caption has been defined
	SDL_WM_SetCaption(_title.c_str(), _icon.c_str());
	//SDL_WM_SetIcon(SDL_LoadBMP(_icon.c_str()),NULL);

}
catch (std::exception &e)
{
	Config::addLog( "Exception catched in DisplaySurface Constructor !!!" );
	//Affichage Erreur
	Config::addLog(e.what());

	Config::addLog(GetError());
	//TODO : much more explicit error message...
};


void DisplaySurface::setCaption(std::string title, std::string icon)
{
	_title=title; _icon=icon;
	//if already displayed, change the caption
	if (_screen!=NULL)
	{
		SDL_WM_SetCaption(_title.c_str(), _icon.c_str());
		//SDL_WM_SetIcon(SDL_LoadBMP(_icon.c_str()),NULL);
	}
}

void DisplaySurface::getCaption(std::string & title, std::string & icon)
{
	char ** t,** i;
	SDL_WM_GetCaption(t,i);
	title=std::string(*t);
	icon=std::string(*i);
}

bool DisplaySurface::iconify(void)
{
	return ( SDL_WM_IconifyWindow() != 0 );
}

bool DisplaySurface::toggleFullScreen(void)
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



bool DisplaySurface::update(Rect r)
{
	if (locked()) return false;//to prevent calling while locked
	else SDL_UpdateRect(_surf, r.getx(), r.gety(), r.getw(), r.geth());
	return true;
}

bool DisplaySurface::update(std::vector<Rect> rlist)
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

void DisplaySurface::debug(void) const
{
  std::stringstream logstr;
	BaseSurface::debug();
	logstr<< std::boolalpha << "- Fullscreen ? " << isFullScreenset() << "\n"
				<< "- Resizable ? " << isResizableset() << "\n"
				<< "- NoFrame ? " << isNoFrameset() << "\n"
				<< "- AnyFormat ? " << isAnyFormatset() << "\n"
				<< "- Double Buffered ? " << isDoubleBufset() << std::endl;
  Config::addLog(logstr.str());
}

} //namespace SDL
