#include "Video/SDLBaseSurface.hh"
#include "SDLConfig.hh"

namespace RAGE
{
    namespace SDL
    {

        const VideoInfo * BaseSurface::_vinfo = 0;

        bool BaseSurface::lock(void)
        {
            if (SDL_MUSTLOCK(_surf))
            {
                locks++;
                return SDL_LockSurface(_surf.get()) == 0;
            }
            else
                return true;
        }

        bool BaseSurface::unlock(void)
        {
            if (SDL_MUSTLOCK(_surf))
            {
                if ( locks > 0 )
                    locks--;
                SDL_UnlockSurface(_surf.get());
            }
            return true;
        }

	///Conversion Constructor
	BaseSurface::BaseSurface(SDL_Surface * s) : _surf(s),locks(0)
	{}
	    
	//Conversion Constructor with explicit ownership transfer as it s using an auto_ptr
	BaseSurface::BaseSurface(std::auto_ptr<SDL_Surface> s) : _surf(s),locks(0)
	{}

        BaseSurface::BaseSurface(const BaseSurface & s) throw (std::logic_error)
        try : _surf(0), locks(0)
        {
#ifdef DEBUG
            Log << nl << "BaseSurface::BaseSurface(" << &s << ") called...";
#endif

            _surf.reset(SDL_ConvertSurface(s._surf.get(),s._surf->format,s._surf->flags));
	    const std::string errstr = "SDL_ConvertSurface";
            if(_surf.get() == 0)
            {
                Log << nl << "Unable to copy the RGBsurface" ;
                throw std::logic_error(errstr + " returns NULL");
            }
#ifdef DEBUG
            Log << nl << "BaseSurface::BaseSurface(" << &s << ") done.";
#endif

        }
        catch (std::exception &e)
        {
            Log << nl << "Exception catched in SDLBaseSurface Copy Constructor !!!" << nl <<
            e.what() << nl << GetError();
        }

BaseSurface& BaseSurface::operator=(const BaseSurface& s)
{
    if (this != &s) // make sure not same object
    {
	    SDL_FreeSurface(_surf.release());
            _surf.reset(SDL_ConvertSurface(s._surf.get(),s._surf->format,s._surf->flags)); //deep copy...
            if (_surf.get() == 0)
	    {
                Log << nl << "Unable to copy the BaseSurface : error in SDL_ConvertSurface -> " << GetError() ;
	    }
    }
    return *this;
}

 unsigned long BaseSurface::getFlags(void) const
{
	return _surf->flags;
}

BaseSurface::~BaseSurface()
{
	SDL_FreeSurface(_surf.release());
}

        BaseSurface::BaseSurface(const BaseSurface & s ,unsigned long flags, PixelFormat pfmt) throw (std::logic_error)
        try : _surf(0), locks(0)
        {
#ifdef DEBUG
            Log << nl << "BaseSurface::BaseSurface(const BaseSurface & s,unsigned long flags, PixelFormat pfmt) called...";
#endif

            _surf.reset(SDL_ConvertSurface(s._surf.get(),const_cast<SDL_PixelFormat *>(pfmt._pformat),flags)); //SDL shouldnt modify the pixel format at all

            const std::string errstr = "SDL_ConvertSurface";
            if(_surf.get() == 0)
            {
                Log << nl << "Unable to copy the RGBsurface" ;
                throw std::logic_error(errstr + " returns NULL");
            }
#ifdef DEBUG
            Log << nl << "BaseSurface::BaseSurface(const BaseSurface & s,unsigned long flags, PixelFormat pfmt)  done.";
#endif

        }
        catch (std::exception &e)
        {
            Log << nl << "Exception catched in SDLBaseSurface Copy Constructor !!!" << nl <<
            e.what() << nl << GetError();
        }

	//usefull to get the SDL structure without no risk of modifying it
	SDL_Surface BaseSurface::get_SDL() const
	{
		return *_surf;
	}
	
	int BaseSurface::getHeight(void) const
	{
		return _surf->h;
	}
	int BaseSurface::getWidth(void) const
	{
		return _surf->w;
	}

	int BaseSurface::getBPP(void) const
	{
		assert(_surf->format);
		return _surf->format->BitsPerPixel;
	}
	bool BaseSurface::isSWset(void) const
	{
		return ( SDL_SWSURFACE & _surf->flags ) != 0;
	}
	bool BaseSurface::isHWset(void) const
	{
		return ( SDL_HWSURFACE & _surf->flags ) != 0;
	}
	bool BaseSurface::isHWAccelset(void) const
	{
		return ( SDL_HWACCEL & _surf->flags ) != 0;
	}
	bool BaseSurface::isRLEAccelset(void) const
	{
		return ( SDL_RLEACCEL & _surf->flags ) != 0;
	}
	bool BaseSurface::isPreAllocset(void) const
	{
		return ( SDL_PREALLOC & _surf->flags ) != 0;
	}

            ///Accessor to pixelFormat
	PixelFormat BaseSurface::getPixelFormat(void) const
	{
		return PixelFormat(_surf->format);
	}

        PixelColor BaseSurface::getpixel(int x, int y)
        {
            lock();
            /* Here p is the address to the pixel we want to retrieve */
            Uint8 *p = (Uint8 *)_surf->pixels + y * _surf->pitch + x * _surf->format->BytesPerPixel;
            Uint32 pixel;
            switch(_surf->format->BytesPerPixel)
            {
                case 1:
                pixel=*p;
				break;

                case 2:
                pixel=*(Uint16 *)p;
				break;

                case 3:
#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                    pixel= p[0] << 16 | p[1] << 8 | p[2];
#else
                    pixel= p[0] | p[1] << 8 | p[2] << 16;
#endif
					break;
                case 4:
                pixel= *(Uint32 *)p;
				break;

                default:
                pixel= 0;       /* shouldn't happen, but avoids warnings */
				break;
            }
            unlock();
            return pixel;
        }

        void BaseSurface::setpixel(int x, int y, PixelColor pixel, unsigned char alpha)
        {
            lock();
            /* Here p is the address to the pixel we want to set */
            Uint8 *p = (Uint8 *)_surf->pixels + y * _surf->pitch + x * _surf->format->BytesPerPixel;

			if ( alpha == 255 )
			{
				switch(_surf->format->BytesPerPixel)
				{
					case 1:
						*p = (Uint8) pixel;
						break;

					case 2:
						*(Uint16 *)p = (Uint16) pixel;
						break;

					case 3:
						#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
							p[0] = (Uint8) (pixel >> 16) & 0xff;
							p[1] = (Uint8) (pixel >> 8) & 0xff;
							p[2] = (Uint8) pixel & 0xff;
						#else
							p[0] = (Uint8) pixel & 0xff;
							p[1] = (Uint8) (pixel >> 8) & 0xff;
							p[2] = (Uint8) (pixel >> 16) & 0xff;
						#endif
						break;

					case 4:
						*(Uint32 *)p = (Uint32) pixel;
						break;
				}
			}
			else //If We Want To Set A Pixel With Alpha !
			{
				unsigned int r, g, b;
				RGBColor color;
				switch(_surf->format->BytesPerPixel)
				{
					case 1:
						*p = (Uint8) pixel;
						break;

					case 2:
						r = ((pixel & _surf->format->Rmask) * alpha + (*(Uint32 *)p & _surf->format->Rmask) * (255 - alpha)) >> 8;
						g = ((pixel & _surf->format->Gmask) * alpha + (*(Uint32 *)p & _surf->format->Gmask) * (255 - alpha)) >> 8;
						b = ((pixel & _surf->format->Bmask) * alpha + (*(Uint32 *)p & _surf->format->Bmask) * (255 - alpha)) >> 8;

						*(Uint16 *)p = ( (unsigned short)( (r & _surf->format->Rmask) | (g & _surf->format->Gmask) | (b & _surf->format->Bmask) ) );
						break;

					case 3:
						color = ((PixelFormat*)(_surf->format))->getRGBValue(pixel);
						#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
							r = (p[0] * (255 - alpha) + color.getR() * alpha) >> 8;
							g = (p[1] * (255 - alpha) + color.getG() * alpha) >> 8;
							b = (p[2] * (255 - alpha) + color.getB() * alpha) >> 8;

							p[2] = b;
							p[1] = g;
							p[0] = r;
						#else
							r = (p[2] * (255 - alpha) + color.getR() * alpha) >> 8;
							g = (p[1] * (255 - alpha) + color.getG() * alpha) >> 8;
							b = (p[0] * (255 - alpha) + color.getB() * alpha) >> 8;

							p[0] = b;
							p[1] = g;
							p[2] = r;
						#endif
						break;

					case 4:
						r = ((pixel & 0xff) * alpha + (*(Uint32 *)p & 0xff) * (255 - alpha)) >> 8;
						g = ((pixel & 0xff00) * alpha + (*(Uint32 *)p & 0xff00) * (255 - alpha)) >> 8;
						b = ((pixel & 0xff0000) * alpha + (*(Uint32 *)p & 0xff0000) * (255 - alpha)) >> 8;

						*(Uint32 *)p = ( (r & 0xff) | (g & 0xff00) | (b & 0xff0000) );
						break;
				}
			}
            unlock();
        }

        //instance methods

        bool BaseSurface::saveBMP(std::string filename) const
        {
            if (initialized())
            {
                return SDL_SaveBMP(_surf.get(),filename.c_str()) == 0;
            }
            return false;
        }

        bool BaseSurface::fill (const PixelColor& color, Rect dest_rect)
        {
#if (DEBUG == 2)
Log << nl << "BaseSurface::fill (const PixelColor& color," << dest_rect << ") called...";
#endif
            int res=SDL_FillRect(_surf.get(), dest_rect._rect, color);
            //std::cerr << "SDLBaseSurface::Fill(" << _surf << ", " << dest_rect << ", " << color << ")" << std::endl;
            //std::cerr << "returned " << res << std::endl;

#if (DEBUG == 2)
Log << nl << "BaseSurface::fill (const PixelColor& color," << dest_rect << ") done.";
#endif
            return res == 0;
        }

        bool BaseSurface::blit(const BaseSurface& src, Rect& dest_rect, const Rect& src_rect )
        {
#if (DEBUG == 2)
Log << nl << "BaseSurface::blit (const BaseSurface& src," << dest_rect << ", " << src_rect << ") called...";
#endif
            bool res=false;
#ifdef DEBUG
            //to make sure the SDL surface is completely usable
            assert(_surf->format);
            assert(src._surf->format);
#endif

            switch (SDL_BlitSurface(src._surf.get(), src_rect._rect , _surf.get(), dest_rect._rect))
            {
                case 0 :
                res=true;
                break;
                case -1 :
                res=false;
                default :
                Log << GetError() << std::endl;
                break; // beware the -2 returns... see the SDL doc
            }
#if (DEBUG == 2)
Log << nl << "BaseSurface::blit (const BaseSurface& src," << dest_rect << ", " << src_rect << ") done.";
#endif
            return res;
        }


        //Set the clip rect
        void BaseSurface::setClipRect(const Rect& rect)
        {
            SDL_SetClipRect(_surf.get(),rect._rect);
        }

        //get the clip rect
        Rect BaseSurface::getClipRect(void) const
        {
            Rect r;
            SDL_GetClipRect(_surf.get(), r._rect);
            return r;
        }

        Logger & operator << (Logger & log, const BaseSurface & surf)
        {
            log << nl << "SDLBaseSurface::" << nl
            << " - Height = " << surf.getHeight() << nl
            << " - Width = " << surf.getWidth() << nl
            << " - bpp = " << surf.getBPP() << nl
            << std::boolalpha
            << " - SW ? " << surf.isSWset() << nl
            << " - HW ? " << surf.isHWset() << nl
            << " - HWAccel ? " << surf.isHWAccelset() << nl
            << " - RLEAccel ? " << surf.isRLEAccelset() << nl
            << " - PreAlloc ? " << surf.isPreAllocset();
            return log;
        }
    }
} //namespace RAGE::SDL
