#include "SDLDisplaySurface.hh"
#include "SDLManager.hh"
//#include <sstream>

namespace SDL {


std::string DisplaySurface::_title = DEFAULT_WINDOW_TITLE;
std::string DisplaySurface::_icon = DEFAULT_WINDOW_ICON ;
std::vector<int> DisplaySurface::availableWidth;
std::vector<int> DisplaySurface::availableHeight;
Uint32 DisplaySurface::flags = SDL_RESIZABLE | SDL_DOUBLEBUF | SDL_ANYFORMAT | SDL_HWSURFACE | SDL_HWPALETTE ;

//Constructor
DisplaySurface::DisplaySurface(int width, int height, int bpp, Uint32 flags) throw (std::logic_error)
try : BaseSurface(SDL_SetVideoMode(width,height,bpp,flags ))
{
	if (_surf == NULL)
	{
	  Log << nl <<"Unable to set " << width << " x " << height << " display surface : ";
		throw std::logic_error("SDL_SetVideoMode() return NULL");
	}

	//If a caption has been defined
	//SDL_WM_SetCaption(_title.c_str(), _icon.c_str());
	//shouldnt be needed if already done before...

}
catch (std::exception &e)
{
	Log << nl << "Exception catched in DisplaySurface Constructor !!!" << nl <<
		e.what() << nl << GetError() << std::endl;
	//TODO : much more explicit error message...
};


void DisplaySurface::setCaption(std::string title, std::string icon)
{
	_title=title; _icon=icon;
	SDL_WM_SetCaption(_title.c_str(), _icon.c_str());
}

bool DisplaySurface::setIcon(std::string iconfilename)
{
    bool res=false;
    SDL_Surface * icon=SDL_LoadBMP(iconfilename.c_str());
    if ( icon != NULL )
    {
        _icon=iconfilename;
        SDL_WM_SetIcon( icon , NULL);
        res = true;
    }
    else
    {
		Log << nl << "Unable to load the icon " << iconfilename << " : " << GetError() << std::endl;
    }
    return res;
}

void DisplaySurface::getCaption(std::string & title, std::string & icon)
{
	char ** t = NULL ;
	char ** i  = NULL ;
	SDL_WM_GetCaption(t,i);
	if ( !t ) title = "";
	else title=std::string(*t); //initializer to "" needed ?
	if ( !i ) icon = "";
	else icon=std::string(*i); //initializer to "" needed ?
}

bool DisplaySurface::iconify(void)
{
	return ( SDL_WM_IconifyWindow() != 0 );
}

bool DisplaySurface::toggleFullScreen(void)
{
	//This only works for X11
	#ifndef __MINGW32__
	return ( SDL_WM_ToggleFullScreen(_surf) != 0 ) ;
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

bool DisplaySurface::setFlags( bool openGL, bool fullScreen,
						bool resizable, bool noFrame,
						bool doubleBuf, bool anyFormat,
						bool SWSurface, bool HWSurface,
						bool HWPalette, bool asyncBlit)
{
	if ( openGL ) flags|= SDL_OPENGL; else flags&= (~SDL_OPENGL) ;
	if ( fullScreen ) flags|= SDL_FULLSCREEN; else flags&= (~SDL_FULLSCREEN) ;
	if ( resizable ) flags|= SDL_RESIZABLE; else flags&= (~SDL_RESIZABLE) ;
	if ( noFrame ) flags|= SDL_NOFRAME; else flags&= (~SDL_NOFRAME) ;
	if ( doubleBuf ) flags|= SDL_DOUBLEBUF; else flags&= (~SDL_DOUBLEBUF) ;
	if ( anyFormat ) flags|= SDL_ANYFORMAT; else flags&= (~SDL_ANYFORMAT) ;
	if ( SWSurface ) flags|= SDL_SWSURFACE; else flags&= (~SDL_SWSURFACE) ;
	if ( HWSurface ) flags|= SDL_HWSURFACE; else flags&= (~SDL_HWSURFACE) ;
	if ( HWPalette ) flags|= SDL_HWPALETTE; else flags&= (~SDL_HWPALETTE) ;
	if ( asyncBlit ) flags|= SDL_ASYNCBLIT; else flags&= (~SDL_ASYNCBLIT) ;

	return checkAvailableSize();
}


bool DisplaySurface::checkAvailableSize( const PixelFormat * fmt )
{
	SDL_Rect ** modes;
	bool res;
	//we copy the pixelformat (because of const behaviour...)
	SDL_PixelFormat* test_fmt= new SDL_PixelFormat( *(fmt->_pformat));

	modes=SDL_ListModes(test_fmt, flags);
	if (modes == (SDL_Rect **)0) res=false;
	else
	{
		availableWidth.clear();
		availableHeight.clear();

		if (modes == (SDL_Rect **)-1)
		{
			availableWidth.push_back(-1);
			availableHeight.push_back(-1);
		}
		else
		{
			for(int i=0;modes[i];++i)
			{
				availableWidth.push_back(modes[i]->w);
				availableHeight.push_back(modes[i]->h);
			}
		}
		res=true;
	}

	Log << nl << "Available Modes : " ;
	if ( availableHeight[0] == -1 || availableWidth[0] == -1 ) Log << "all" << std::endl;
	else
	{
		for (unsigned int i=0; i<availableHeight.size() ; i++)
		{
			Log <<  "- " << availableHeight[i] << "x" << availableWidth[i] << nl;
		}
		Log << std::endl;
	}



	return res;
}

bool DisplaySurface::checkAvailableSize(void)
{
	return checkAvailableSize( Manager::manager()->getVideoInfo()->getPixelFormat());
}




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
	BaseSurface::debug();
	Log << nl<<std::boolalpha << "- Fullscreen ? " << isFullScreenset() << nl
				<< "- Resizable ? " << isResizableset() << nl
				<< "- NoFrame ? " << isNoFrameset() <<nl
				<< "- AnyFormat ? " << isAnyFormatset() << nl
				<< "- Double Buffered ? " << isDoubleBufset() << std::endl;
}

} //namespace SDL
