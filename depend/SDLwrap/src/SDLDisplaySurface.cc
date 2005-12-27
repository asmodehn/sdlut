#include "SDLDisplaySurface.hh"

//#include <sstream>

namespace SDL {

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
	return checkAvailableSize( getVideoInfo()->getPixelFormat());
}

int DisplaySurface::getSuggestedBPP(int width, int height)
{
#ifdef DEBUG
    assert( getVideoInfo());
    Log << nl << "VideoInfo Accessible @ " << getVideoInfo << std::endl;
    assert( getVideoInfo()->getPixelFormat());
    Log << nl << "PixelFormat Accessible @ " << getVideoInfo()->getPixelFormat() << std::endl;
#endif
    return SDL_VideoModeOK(width,height,getVideoInfo()->getPixelFormat()->getBitsPerPixel(),flags);
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

Logger & operator << (Logger & log, const DisplaySurface & surf)
{
	//log << static_cast<BaseSurface>(surf);
	log << nl<<std::boolalpha << "- Fullscreen ? " << surf.isFullScreenset() << nl
				<< "- Resizable ? " << surf.isResizableset() << nl
				<< "- NoFrame ? " << surf.isNoFrameset() <<nl
				<< "- AnyFormat ? " << surf.isAnyFormatset() << nl
				<< "- Double Buffered ? " << surf.isDoubleBufset();
    return log;
}

} //namespace SDL
