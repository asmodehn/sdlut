#include "Video/internal/SDLBaseSurface.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

const VideoInfo * BaseSurface::pvm_vinfo = 0;

bool BaseSurface::lock(void)
{
    if (SDL_MUSTLOCK(ptm_surf))
    {
        return SDL_LockSurface(ptm_surf.get()) == 0;
    }
    return true;
}

bool BaseSurface::unlock(void)
{
    if (SDL_MUSTLOCK(ptm_surf))
    {
        SDL_UnlockSurface(ptm_surf.get());
    }
    return true;
}

BaseSurface::BaseSurface() throw (std::logic_error)
{
}

bool BaseSurface::set_SDL_Surface(SDL_Surface * s)
{
    bool res = (s != NULL);
    if ( res )
    {
        SDL_FreeSurface(ptm_surf.release());
        ptm_surf.reset(s);
    }
    return res;
}

bool BaseSurface::set_SDL_Surface(std::auto_ptr<SDL_Surface> s)
{
    bool res = (s.get() != NULL);
    if ( res )
    {
        SDL_FreeSurface(ptm_surf.release());
        ptm_surf = s;
    }
    return res;
}

///Conversion Constructor
BaseSurface::BaseSurface(SDL_Surface * s) throw (std::logic_error) : ptm_surf(s)
{
    if (ptm_surf.get() == 0 ) throw std::logic_error("Surface not initialised properly : SDL_Surface NULL pointer.");
}

//Conversion Constructor with explicit ownership transfer as it s using an auto_ptr
BaseSurface::BaseSurface(std::auto_ptr<SDL_Surface> s) throw (std::logic_error) : ptm_surf(s)
{
    if (ptm_surf.get() == 0 ) throw std::logic_error("Surface not initialised properly : SDL_Surface NULL pointer.");
}

//deep copy
BaseSurface::BaseSurface(const BaseSurface & s) throw (std::logic_error)
try :
    ptm_surf(0)
{
#ifdef DEBUG
    Log << nl << "BaseSurface::BaseSurface(" << &s << ") called...";
#endif

    const std::string errstr = "SDL_ConvertSurface";
    bool surfok = set_SDL_Surface(SDL_ConvertSurface(s.ptm_surf.get(),s.ptm_surf->format,s.ptm_surf->flags));
    if ( ! surfok)
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
        bool surfok = set_SDL_Surface(SDL_ConvertSurface(s.ptm_surf.get(),s.ptm_surf->format,s.ptm_surf->flags)); //deep copy...
        if (! surfok)
        {
            Log << nl << "Unable to copy the BaseSurface : error in SDL_ConvertSurface -> " << GetError() ;
        }
    }
    return *this;
}

unsigned long BaseSurface::getFlags(void) const
{
    return ptm_surf->flags;
}

BaseSurface::~BaseSurface()
{
    SDL_FreeSurface(ptm_surf.release());
}

BaseSurface::BaseSurface(const BaseSurface & s ,unsigned long flags, PixelFormat pfmt) throw (std::logic_error)
try :
    ptm_surf(0)
{
#ifdef DEBUG
    Log << nl << "BaseSurface::BaseSurface(const BaseSurface & s,unsigned long flags, PixelFormat pfmt) called...";
#endif

    const std::string errstr = "SDL_ConvertSurface";
    bool surfok = set_SDL_Surface(SDL_ConvertSurface(s.ptm_surf.get(),const_cast<SDL_PixelFormat *>(pfmt.ptm_sdl_pformat),flags)); //SDL shouldnt modify the pixel format at all
    if (! surfok)
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
    return *ptm_surf;
}

unsigned int BaseSurface::getHeight(void) const
{
    return static_cast<unsigned int>(ptm_surf->h);
}
unsigned int BaseSurface::getWidth(void) const
{
    return static_cast<unsigned int>(ptm_surf->w);
}

int BaseSurface::getBPP(void) const
{
    assert(ptm_surf->format);
    return ptm_surf->format->BitsPerPixel;
}
bool BaseSurface::isSWset(void) const
{
    return ( SDL_SWSURFACE & ptm_surf->flags ) != 0;
}
bool BaseSurface::isHWset(void) const
{
    return ( SDL_HWSURFACE & ptm_surf->flags ) != 0;
}
bool BaseSurface::isHWAccelset(void) const
{
    return ( SDL_HWACCEL & ptm_surf->flags ) != 0;
}
bool BaseSurface::isRLEAccelset(void) const
{
    return ( SDL_RLEACCEL & ptm_surf->flags ) != 0;
}
bool BaseSurface::isPreAllocset(void) const
{
    return ( SDL_PREALLOC & ptm_surf->flags ) != 0;
}

void * BaseSurface::getpixels(void) const
{
    return ptm_surf->pixels;
}

///Accessor to pixelFormat
PixelFormat BaseSurface::getPixelFormat(void) const
{
    return PixelFormat(ptm_surf->format);
}

PixelColor BaseSurface::getpixel(int x, int y)
{
    lock();
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)ptm_surf->pixels + y * ptm_surf->pitch + x * ptm_surf->format->BytesPerPixel;
    Uint32 pixel;
    switch (ptm_surf->format->BytesPerPixel)
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
        //pixel= *(Uint32 *)p;
#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        pixel= p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3];
#else
        pixel= p[0] | p[1] << 8 | p[2] << 16 | p[3] << 24;
#endif
        break;

    default:
        pixel= 0;       /* shouldn't happen, but avoids warnings */
        break;
    }
    unlock();
    return pixel;
}

void BaseSurface::setpixel(int x, int y, PixelColor pixel)
{
    lock();
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)ptm_surf->pixels + y * ptm_surf->pitch + x * ptm_surf->format->BytesPerPixel;
#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
    Uint8 alpha= (Uint8) pixel & 0xff;
#else
    Uint8 alpha= (Uint8) (pixel >> 24) & 0xff;
#endif
    if ( alpha == 255 )
    {
        switch (ptm_surf->format->BytesPerPixel)
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
            /*
            #if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                    p[0] = (Uint8) (pixel >> 24) & 0xff;
                    p[1] = (Uint8) (pixel >> 16) & 0xff;
                    p[2] = (Uint8) (pixel >> 8) & 0xff;
                    p[3] = (Uint8) pixel & 0xff;
            #else
                    p[0] = (Uint8) pixel & 0xff;
                    p[1] = (Uint8) (pixel >> 8) & 0xff;
                    p[2] = (Uint8) (pixel >> 16) & 0xff;
                    p[3] = (Uint8) (pixel >> 24) & 0xff;
            #endif
            */
            break;

        }
    }
    else //If We Want To Set A Pixel With Alpha !
    {
        unsigned int r, g, b;

        switch (ptm_surf->format->BytesPerPixel)
        {
        case 1:
            *p = (Uint8) pixel;
            break;

        case 2:
            r = ((pixel & ptm_surf->format->Rmask) * alpha + (*(Uint32 *)p & ptm_surf->format->Rmask) * (256 - alpha)) >> 8;
            g = ((pixel & ptm_surf->format->Gmask) * alpha + (*(Uint32 *)p & ptm_surf->format->Gmask) * (256 - alpha)) >> 8;
            b = ((pixel & ptm_surf->format->Bmask) * alpha + (*(Uint32 *)p & ptm_surf->format->Bmask) * (256 - alpha)) >> 8;

            *(Uint16 *)p = ( (unsigned short)( (r & ptm_surf->format->Rmask) | (g & ptm_surf->format->Gmask) | (b & ptm_surf->format->Bmask) ) );
            break;

        case 3:

            r = ((pixel & 0xff) * alpha + (*(Uint32 *)p & 0xff) * (256 - alpha)) >> 8;
            g = ((pixel & 0xff00) * alpha + (*(Uint32 *)p & 0xff00) * (256 - alpha)) >> 8;
            b = ((pixel & 0xff0000) * alpha + (*(Uint32 *)p & 0xff0000) * (256 - alpha)) >> 8;

            *(Uint16 *)p = ( (r & 0xff) | (g & 0xff00) );
            *(Uint8 *)(p+2) = (b & 0xff0000) ;

            break;

        case 4:
            r = ((pixel & 0xff) * alpha + (*(Uint32 *)p & 0xff) * (256 - alpha)) >> 8;
            g = ((pixel & 0xff00) * alpha + (*(Uint32 *)p & 0xff00) * (256 - alpha)) >> 8;
            b = ((pixel & 0xff0000) * alpha + (*(Uint32 *)p & 0xff0000) * (256 - alpha)) >> 8;

            *(Uint32 *)p = ( (r & 0xff) | (g & 0xff00) | (b & 0xff0000) );
            break;
        }
    }
    unlock();
}

//instance methods

bool BaseSurface::saveBMP(std::string filename) const
{
    bool res = false;
    if (initialized())
    {
        if ( SDL_SaveBMP(ptm_surf.get(),filename.c_str()) != 0 )
        { //TODO : handle erros such as disk full, etc. )

        }
        else
        {
            res = true;
        }

    }
    return res;
}

//Fill

bool BaseSurface::fill (const PixelColor& color)
{
    Rect dest_rect(0,0,getWidth(), getHeight());
    return fill( color, dest_rect );
}

bool BaseSurface::fill (const PixelColor& color, Rect dest_rect)
{
#if (DEBUG == 2)
    Log << nl << "BaseSurface::fill (const PixelColor& color," << dest_rect << ") called...";
#endif
    lock();
    int res=SDL_FillRect(ptm_surf.get(), dest_rect.get_pSDL(), color);
    //std::cerr << "SDLBaseSurface::Fill(" << _surf << ", " << dest_rect << ", " << color << ")" << std::endl;
    //std::cerr << "returned " << res << std::endl;
    unlock();
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

    //to make sure the SDL surface is completely usable
    assert(ptm_surf->format);
    assert(src.ptm_surf->format);

    switch (SDL_BlitSurface(src.ptm_surf.get(), src_rect.get_pSDL() , ptm_surf.get(), dest_rect.get_pSDL()))
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
    SDL_SetClipRect(ptm_surf.get(),rect.get_pSDL());
}

//get the clip rect
Rect BaseSurface::getClipRect(void) const
{
    Rect r;
    SDL_GetClipRect(ptm_surf.get(), r.get_pSDL());
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
