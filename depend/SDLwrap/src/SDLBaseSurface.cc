#include "SDLBaseSurface.hh"

namespace SDL {

bool BaseSurface::lock(void)
{
	if (SDL_MUSTLOCK(_surf))
	{
		locks++;
		return SDL_LockSurface(_surf) == 0;
	}
	else return true;
}

bool BaseSurface::unlock(void)
{
	if (SDL_MUSTLOCK(_surf))
	{
		if ( locks > 0 ) locks--;
		SDL_UnlockSurface(_surf);
	}
	return true;
}


BaseSurface::BaseSurface(const BaseSurface & s , bool cloning, bool toDisplay, bool alpha) throw (std::logic_error)
try : locks(0)
{
	if (cloning)
	{
		if (toDisplay)
		{
			if (alpha)
			{
				_surf=SDL_DisplayFormatAlpha(s._surf);
			}
			else
			{
				_surf=SDL_DisplayFormat(s._surf);
			}
		}
		else
		{
			_surf=SDL_ConvertSurface(s._surf,new SDL_PixelFormat(*(s._surf->format)),s._surf->flags); // copy to deal with const... maybe a const cast should be ok...
		}
	}
	else
	{
		_surf=SDL_CreateRGBSurface(s._surf->flags, s.getWidth(), s.getHeight(), s._surf->format->BitsPerPixel, s._surf->format->Rmask, s._surf->format->Gmask, s._surf->format->Bmask, s._surf->format->Amask);
	}

	std::cerr << "SDL::BaseSurface Copy Called" << std::endl;
	const std::string errstr = cloning ? toDisplay ? alpha ? "SDL_DisplayFormatAlpha" : "SDLDisplayFormat" : "SDL_ConvertSurface" : "SDL_CreateRGBSurface";
  if(_surf == NULL)
	{
    std::cerr << "Unable to copy the RGBsurface @ " << &s << std::endl ;
    throw std::logic_error(errstr + " returns NULL");
  }
  else
	  std::cerr << "SDL_Surface created @ "<< _surf<< std::endl;
}
catch (std::exception &e)
{
	Config::addLog( "Exception catched in SDLBaseSurface Copy Constructor !!!" );
	Config::addLog(e.what());
	Config::addLog(GetError());
}


Uint32 BaseSurface::getpixel(int x, int y)
{
    lock();
	/* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)_surf->pixels + y * _surf->pitch + x * _surf->format->BytesPerPixel;
	Uint32 pixel;
    switch(_surf->format->BytesPerPixel) {
    case 1:
        pixel=*p;

    case 2:
        pixel=*(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            pixel= p[0] << 16 | p[1] << 8 | p[2];
        else
            pixel= p[0] | p[1] << 8 | p[2] << 16;
    case 4:
        pixel= *(Uint32 *)p;

    default:
        pixel= 0;       /* shouldn't happen, but avoids warnings */
    }
	unlock();
	return pixel;
}

void BaseSurface::setpixel(int x, int y, Uint32 pixel)
{
	lock();
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)_surf->pixels + y * _surf->pitch + x * _surf->format->BytesPerPixel;

    switch(_surf->format->BytesPerPixel) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
	unlock();
}

//instance methods

bool BaseSurface::saveBMP(std::string filename) const
{
	if (_surf!=NULL)
	{
		return SDL_SaveBMP(_surf,filename.c_str()) == 0;
	}
	return false;
}

bool BaseSurface::fill (const PixelColor& color, Rect dest_rect)
{
	int res=SDL_FillRect(_surf, dest_rect._rect, color);
	//std::cerr << "SDLBaseSurface::Fill(" << _surf << ", " << dest_rect << ", " << color << ")" << std::endl;
	//std::cerr << "returned " << res << std::endl;
	return res == 0;
}

bool BaseSurface::blit(const BaseSurface& src, Rect& dest_rect, const Rect& src_rect )
{
	/*if (src._surf==NULL) LIB_ERROR("! src._surf NULL !");
	if (src._surf->pixels==NULL) LIB_ERROR("! src._surf->pixels NULL !");
	std::cout << "src.debug() " << std::endl;
	src.debug();
	if (_surf==NULL) LIB_ERROR("! _surf NULL !");
	if (_surf->pixels==NULL) LIB_ERROR("! _surf->pixels NULL !");
	std::cout << "debug() " << std::endl;
	debug();
	*/
	bool res=false;
	switch (SDL_BlitSurface(src._surf, src_rect._rect , _surf, dest_rect._rect))
	{
		case 0 : res=true; break;
		case -1 : res=false; break;
		default : Config::addLog(GetError()); break; // beware the -2 returns... see the SDL doc
	}
	return res;
}


//Set the clip rect
void BaseSurface::setClipRect(const Rect& rect)
{
	SDL_SetClipRect(_surf,rect._rect);
}

//get the clip rect
Rect BaseSurface::getClipRect(void) const
{
	Rect r;
	SDL_GetClipRect(_surf, r._rect);
	return r;
}

void BaseSurface::debug(void) const
{
	std::stringstream logstr;
	logstr<< "SDL*Surfaces::debug()" << "\n"
				<< "- Height = " << getHeight() << "\n"
				<< "- Width = " << getWidth() << "\n"
				<< "- bpp = " << getBPP() << "\n"
				<< std::boolalpha
				<< "- SW ? " << isSWset() << "\n"
				<< "- HW ? " << isHWset() << "\n"
				<< "- HWAccel ? " << isHWAccelset() << "\n"
				<< "- RLEAccel ? " << isRLEAccelset() << "\n"
				<< "- PreAlloc ? " << isPreAllocset() << std::endl;
  Config::getLog()->add(logstr.str());
}

} //namespace SDL
