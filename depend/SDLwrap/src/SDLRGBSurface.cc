#include "SDLRGBSurface.hh"

namespace SDL {

static Uint32 RGBFlags=SDL_SWSURFACE;

RGBSurface::RGBSurface(int width, int height, int bpp, bool SWSURFACE , bool HWSURFACE , bool SRCCOLORKEY , bool SRCALPHA , Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask) throw (std::logic_error)
try : BaseSurface(SDL_CreateRGBSurface(RGBFlags, width, height, bpp, rmask, gmask, bmask, amask))
{
	if ( SWSURFACE ) RGBFlags|= SDL_SWSURFACE; else RGBFlags&= (~SDL_SWSURFACE);
	if ( HWSURFACE ) RGBFlags|= SDL_HWSURFACE; else RGBFlags&= (~SDL_HWSURFACE);
	if ( SRCCOLORKEY ) RGBFlags|= SDL_SRCCOLORKEY; else RGBFlags&= (~SDL_SRCCOLORKEY);
	if ( SRCALPHA ) RGBFlags|= SDL_SRCALPHA; else RGBFlags&= (~SDL_SRCALPHA);


	//std::cerr << "RGBSurface Constructor Called" << std::endl;
	if (bpp == 0)
		throw std::logic_error("bpp should not be set to 0 for rgb surfaces !");
    if(_surf == NULL)
	{
	  std::stringstream ss;
	  ss << "Unable to set " <<  width<<  " x " <<  height <<  " rgb surface : ";
        Config::addLog( ss.str());
        throw std::logic_error("SDL_CreateRGBSurface returns NULL");
    }
}
catch (std::exception &e)
{
	Config::addLog( "Exception catched in RGBSurface Constructor !!!" );
	//Error Display
	Config::addLog(e.what());
	Config::addLog(GetError());
	//TODO : much more explicit error message...
};

RGBSurface::RGBSurface(void* pixeldata, int depth, int pitch, int width, int height, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask) throw (std::logic_error)
try : BaseSurface(SDL_CreateRGBSurfaceFrom(pixeldata, width, height, depth, pitch, rmask, gmask, bmask, amask))
{
	//std::cerr << "RGBSurface Constructor Called" << std::endl;
    if(_surf == NULL)
	{
	  std::stringstream ss;
	  ss << "Unable to set " << width<< " x " << height<< " rgb surface : ";
        Config::addLog (ss.str() );
        throw std::logic_error("SDL_CreateRGBSurface returns NULL");
    }
}
catch (std::exception &e)
{
	Config::addLog( "Exception catched in RGBSurface Constructor !!!" );
	//Error Display
	Config::addLog(e.what());
	Config::addLog(GetError());
	//TODO : much more explicit error message...
};

RGBSurface::RGBSurface( std::string filename )throw (std::logic_error)
try : BaseSurface(SDL_LoadBMP(filename.c_str()))
{
	//std::cerr << "RGBSurface Constructor Called" << std::endl;
	//TODO : support for other format than BMP with SDL_image
    if(_surf == NULL)
	{
        Config::addLog( "Unable to set rgb surface from " + filename );
        throw std::logic_error("SDL_LoadBMP returns NULL");
    }
}
catch (std::exception &e)
{
	Config::addLog( "Exception catched in RGBSurface Constructor !!!" );
	//Error Display
	Config::addLog(e.what());
	Config::addLog(GetError());
	//TODO : much more explicit error message...
};

//Copy Constructor ( doesn't copy the content of the surface)
//and Clone (also copy the content of the surface)
RGBSurface::RGBSurface(const RGBSurface & s , const PixelFormat& fmt, Uint32 flags, bool cloning) throw (std::logic_error)
try : BaseSurface ( 	cloning ?
				SDL_ConvertSurface(s._surf,new SDL_PixelFormat(*fmt._pformat),flags) // copy to deal with const... maybe a const cast should be ok...
				: SDL_CreateRGBSurface(flags, s.getWidth(), s.getHeight(), fmt.getBitsPerPixel(), fmt.getRmask(), fmt.getGmask(), fmt.getBmask(), fmt.getAmask())
		)
{
	//std::cerr << "RGBSurface Copy Called" << std::endl;
	const std::string errstr = cloning ? "SDL_ConvertSurface" : "SDL_CreateRGBSurface";
    if(_surf == NULL)
	{
        Config::addLog( "Unable to copy the RGBsurface @ " + (int) &s) ;
        throw std::logic_error(errstr + " returns NULL");
    }
    else
	    Config::addLog( "SDL_Surface created @ " + (int) _surf);
}
catch (std::exception &e)
{
	Config::addLog( "Exception catched in RGBSurface Copy Constructor !!!" );
	Config::addLog(e.what());
	Config::addLog(GetError());
};


RGBSurface::RGBSurface(const RGBSurface & s , Uint32 flags, bool cloning) throw (std::logic_error)
try : BaseSurface ( 	cloning ?
				SDL_ConvertSurface(s._surf,new SDL_PixelFormat(*(s._surf->format)),flags) // copy to deal with const... maybe a const cast should be ok...
				: SDL_CreateRGBSurface(flags, s.getWidth(), s.getHeight(), s._surf->format->BitsPerPixel, s._surf->format->Rmask, s._surf->format->Gmask, s._surf->format->Bmask, s._surf->format->Amask)
		)
{
	//std::cerr << "RGBSurface Copy Called" << std::endl;
	const std::string errstr = cloning ? "SDL_ConvertSurface" : "SDL_CreateRGBSurface";
    if(_surf == NULL)
	{
        Config::addLog( "Unable to copy the RGBsurface @ " +  (int)&s );
        throw std::logic_error(errstr + " returns NULL");
    }
    else
	    Config::addLog( "SDL_Surface created @ " + (int) _surf );
}
catch (std::exception &e)
{
	Config::addLog("Exception catched in RGBSurface Copy Constructor !!!" );
	Config::addLog(e.what());
	Config::addLog(GetError());
};

RGBSurface::RGBSurface(const BaseSurface & s , bool cloning, bool toDisplay, bool alpha) throw (std::logic_error)
try : BaseSurface(s,cloning,toDisplay,alpha)
{
  //std::cerr << "RGBSurface Copy Called" << std::endl;
	Config::addLog( "SDL_Surface created @ " + (int) _surf );
}
catch (std::exception &e)
{
	Config::addLog("Exception catched in RGBSurface Copy Constructor !!!" );
	Config::addLog(e.what());
	Config::addLog(GetError());
};

/*
RGBSurface::RGBSurface(const RGBSurface & s , bool cloning, bool toDisplay, bool alpha) throw (std::logic_error)
try : SDLBaseSurface(s,cloning,toDisplay,alpha)
{
  std::cerr << "RGBSurface Copy Called" << std::endl;
	std::cerr << "SDL_Surface created @ "<< _surf<< std::endl;
}
catch (std::exception &e)
{
	LIB_ERROR( "Exception catched in RGBSurface Copy Constructor !!!" );
	LIB_ERROR(e.what());
	SDLERROR;
}
*/

/*
void RGBSurface::setUpdateRect(int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x=x;rect.y=y;rect.w=w;rect.h=h;
	_UpdateRectList.push_back(rect);
}
*/

bool RGBSurface::setColorKey(const RGBColor & key, const PixelFormat & pformat, bool rleAccel)
{
	Uint32 flags;
	if (rleAccel)
	flags=SDL_SRCCOLORKEY | SDL_RLEACCEL;
	else
	flags=SDL_SRCCOLORKEY;

	return SDL_SetColorKey(_surf, flags, pformat.getValueFromRGB(key) ) == 0;
}

/*
int RGBSurface::update(void)
{
	SDL_UpdateRects(_surf,_UpdateRectList.size(),UpdateRectList);
}
*/


} //namespace SDL

