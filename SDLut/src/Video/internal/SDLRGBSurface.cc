#include "Video/internal/SDLRGBSurface.hh"
#include "SDLConfig.hh"

#include "SDLResources.inc"

using namespace RAGE;

namespace SDLut
{
namespace video
{
    namespace internal{

//Conversion Constructor
RGBSurface::RGBSurface(SDL_Surface * s) throw (std::logic_error)
try :
    BaseSurface(s), optimised(false)
{
}
catch (std::exception &e)
{
    Log << nl << "Exception catched in RGBSurface Constructor !!!"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

RGBSurface::RGBSurface(std::auto_ptr<SDL_Surface> s) throw (std::logic_error)
try :
    BaseSurface(s), optimised(false)
{
}
catch (std::exception &e)
{
    Log << nl << "Exception catched in RGBSurface Constructor !!!"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}


RGBSurface::RGBSurface(	int width, int height, int bpp,
                        bool alpha, bool colorkey , bool hardware ,
                        unsigned long r_mask , unsigned long g_mask , unsigned long b_mask , unsigned long a_mask
                      ) throw (std::logic_error)
try :
    BaseSurface(), optimised(false)
{
#ifdef DEBUG
    Log << nl << "RGBSurface::RGBSurface(" << width << ", " << height << ", " << bpp << ") called...";
#endif

    unsigned long flags(0);
    if ( hardware )
    {
        flags|= SDL_HWSURFACE;
        flags&= (~SDL_SWSURFACE);
    }
    else
    {
        flags&= (~SDL_HWSURFACE);
        flags|= SDL_SWSURFACE;
    }
    if ( colorkey ) flags|= SDL_SRCCOLORKEY;
    else flags&= (~SDL_SRCCOLORKEY);
    if ( alpha ) flags|= SDL_SRCALPHA;
    else flags&= (~SDL_SRCALPHA);

    bool surfok = set_SDL_Surface(SDL_CreateRGBSurface(flags, width, height, bpp, r_mask, g_mask, b_mask, a_mask));
    if (bpp == 0) throw std::logic_error("bpp should not be set to 0 for rgb surfaces !");
    //
    //if a_mask == 0 then SDL BUG !!
    //workaround :
    //if ( alpha )
    //{
    //	SDL_SetAlpha(_surf.get(),flags,0);
    //}
    //

    if (! surfok)
    {
        std::stringstream ss;
        ss << "Unable to set " <<  width<<  " x " <<  height <<  " rgb surface : ";
        Log << ss.str();
        throw std::logic_error("SDL_CreateRGBSurface returns NULL");
    }
#ifdef DEBUG
    Log << nl << "RGBSurface::RGBSurface(" << width << ", " << height << ", " << bpp << ") done.";
#endif

}
catch (std::exception &e)
{
    Log << nl << "Exception catched in RGBSurface Constructor !!!"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

RGBSurface::RGBSurface(	void* pixeldata, int depth, int pitch, int width, int height,
                        unsigned long r_mask , unsigned long g_mask, unsigned long b_mask , unsigned long a_mask
                      ) throw (std::logic_error)
try :
    BaseSurface(SDL_CreateRGBSurfaceFrom(pixeldata, width, height, depth, pitch, r_mask, g_mask, b_mask, a_mask)), optimised(false)
{
#ifdef DEBUG
    Log << nl << "RGBSurface::RGBSurface(" << pixeldata << ", " << depth << ", " << pitch << ", " << width << ", " <<height << ") called...";
#endif
    if (! initialized())
    {
        Log << "Unable to set " << width<< " x " << height<< " rgb surface : ";
        throw std::logic_error("SDL_CreateRGBSurface returns NULL");
    }
#ifdef DEBUG
    Log << nl << "RGBSurface::RGBSurface(" << pixeldata << ", " << depth << ", " << pitch << ", " << width << ", " <<height << ") done.";
#endif

}
catch (std::exception &e)
{
    Log << "Exception catched in RGBSurface Constructor !!!" << nl <<
    e.what() << nl << GetError() ;
    //TODO : much more explicit error message...
}

RGBSurface::RGBSurface(system::RWOps& rwops) throw (std::logic_error)
#ifdef WK_SDLIMAGE_FOUND
try : BaseSurface(IMG_Load_RW(const_cast<SDL_RWops*>(rwops.get_pSDL()),0)), optimised(false)
#else
try : BaseSurface(SDL_LoadBMP_RW(const_cast<SDL_RWops*>(rwops.get_pSDL()),0)), optimised(false)
#endif
{
        //We put back the RWOps read cursor at the beginning ( needed after load... )
        rwops.seek(0,system::RWOps::Set);

    }
    catch (std::exception &e)
    {
        Log << "Exception catched in RGBSurface Constructor !!!" << nl <<
        e.what() << nl << GetError() ;
        //TODO : much more explicit error message...
    }



RGBSurface::RGBSurface(const RGBSurface & s ) throw (std::logic_error)
try :
    BaseSurface(s)
{
#ifdef DEBUG
    Log << nl << "RGBSurface::RGBSurface(" << &s << ") called.";
#endif

#ifdef DEBUG

    Log << nl << "RGBSurface::RGBSurface(" << &s << ") done -> " << ptm_surf.get() << " created.";
#endif

}
catch (std::exception &e)
{
    Log << nl << "Exception catched in RGBSurface Copy Constructor !!!" << nl <<
    e.what() << nl << GetError() << std::endl;
}


RGBSurface& RGBSurface::operator=(const RGBSurface& s)
{
    if (this != &s)
    {
        this->BaseSurface::operator=(s);
    }
    return *this;
}

/*
RGBSurface::RGBSurface(const BaseSurface & s ) throw (std::logic_error)
try :
    BaseSurface(s)
{
#ifdef DEBUG
    Log << nl << "RGBSurface::RGBSurface(" << &s << ") called.";
#endif

#ifdef DEBUG

    Log << nl << "RGBSurface::RGBSurface(" << &s << ") done -> " << ptm_surf.get() << " created.";
#endif

}
catch (std::exception &e)
{
    Log << nl << "Exception catched in RGBSurface Conversion Constructor !!!" << nl <<
    e.what() << nl << GetError() << std::endl;
}
*/
/*
RGBSurface::RGBSurface(std::auto_ptr<BaseSurface> s ) throw (std::logic_error)
try :
    BaseSurface(s)
{
#ifdef DEBUG
    Log << nl << "RGBSurface::RGBSurface(" << s << ") called.";
#endif

#ifdef DEBUG

    Log << nl << "RGBSurface::RGBSurface(" << s << ") done -> " << ptm_surf.get() << " created.";
#endif

}
catch (std::exception &e)
{
    Log << nl << "Exception catched in RGBSurface Conversion Constructor !!!" << nl <<
    e.what() << nl << GetError() << std::endl;
}
*/

/*
RGBSurface& RGBSurface::operator=(const BaseSurface& s)
{
    if (this != &s)
    {
        this->BaseSurface::operator=(s);
    }
    return *this;
}
*/

bool RGBSurface::resetColorKey(bool ckey, const PixelColor & key, bool rleAccel)
{
    Uint32 flags = 0x0;
    if (ckey)
    {
        flags |= SDL_SRCCOLORKEY;

    if (rleAccel)
        {
            flags |= SDL_RLEACCEL;
        }

    }

    return SDL_SetColorKey(ptm_surf.get(), flags, key ) == 0;
}

bool RGBSurface::resetAlpha(bool alpha, unsigned int value, bool rleAccel)
{


    Uint32 flags = 0x0;
    if (alpha)
    {
        flags |= SDL_SRCALPHA;
        if (rleAccel)
        {
            flags |= SDL_RLEACCEL;
        }

    }


        return SDL_SetAlpha(ptm_surf.get(), flags, value) == 0;
}

bool RGBSurface::resize(int width, int height)
{
    bool res;

    //saveBMP("beforeresize.bmp");

    SDL_Surface * newsurf = SDL_CreateRGBSurface(ptm_surf->flags,width,height,ptm_surf->format->BitsPerPixel, ptm_surf->format->Rmask,ptm_surf->format->Gmask,ptm_surf->format->Bmask, ptm_surf->format->Amask);
    std::auto_ptr<SDL_Surface> newSurf( SDL_ConvertSurface(ptm_surf.get(),ptm_surf->format,ptm_surf->flags ) );
    //std::auto_ptr<SDL_Surface> newSurf( SDL_CreateRGBSurface(ptm_surf->flags,width,height,ptm_surf->format->BitsPerPixel, ptm_surf->format->Rmask,ptm_surf->format->Gmask,ptm_surf->format->Bmask, ptm_surf->format->Amask));

    /*if (ptm_surf->format->palette) // if we have a palette, we need to copy it as well. SDL_blit doesnt transfer palette !
    //BUT Convert now does it for us
    {
        SDL_SetColors(newSurf.get(),ptm_surf->format->palette->colors,0,ptm_surf->format->palette->ncolors);
    }
*/

    if (!newSurf.get()) //CreateRGBSurface has failed
    {
        Log << "Unable to resize to " << width << " x " << height << " 2D RGB surface " << nl << GetError();
        res = false;
    }
    else
    {
        /* OLD WAY, before Convert...
        if (keepcontent)
        {
            //Careful with colorkey and alpha for this blit...
            // we need to copy *everything*
            //resetColorKey(false,0);

            //alpha on tiff, even if no alpha present ??
     //       resetAlpha(false,0);
            //
            //SDL_Rect srcrct,dstrct;srcrct.x = srcrct.y = dstrct.x = dstrct.y = 0;
            //srcrct.w=ptm_surf->w;srcrct.h=ptm_surf->h;
            //dstrct.w=width;dstrct.h=height;

            if ( 0 != SDL_BlitSurface(ptm_surf.get(), NULL , newSurf.get(), NULL))
            {
                Log << "Error while blitting old surface on new resized surface" << GetError();
                res = false;
            }
        }
*/
        SDL_FreeSurface(ptm_surf.release());
        ptm_surf=newSurf;
        res = true;
    }

    //saveBMP("afterresize.bmp");

    return (res && ptm_surf.get() != 0 ) ;
}

bool RGBSurface::isSRCColorKeyset(void)
{
    return ( SDL_SRCCOLORKEY & ptm_surf->flags ) != 0;
}
bool RGBSurface::isSRCAlphaset(void)
{
    return ( SDL_SRCALPHA & ptm_surf->flags ) != 0;
}

bool RGBSurface::convertToDisplayFormat()
{
    assert(ptm_surf.get());
    std::auto_ptr<SDL_Surface> optsurf(0);
    if ( isSRCAlphaset() /*|| isSRCColorKeyset()*/ )
    {
        //this call will change colorkey in Alpha channel.
        //Useful for GL but SDL can work without
        optsurf.reset( SDL_DisplayFormatAlpha(ptm_surf.get()) );
    }
    else
    {
        optsurf.reset( SDL_DisplayFormat(ptm_surf.get()) );
    }

    return optimised = set_SDL_Surface(optsurf);
}

bool RGBSurface::blit(const RGBSurface& src, Rect& dest_rect, const Rect& src_rect )
{
#if (DEBUG == 2)
    Log << nl << "RGBSurface::blit (const RGBSurface& src," << dest_rect << ", " << src_rect << ") called...";
#endif




    bool res = BaseSurface::blit(src, dest_rect, src_rect);

/*
//If the blit is successful, it returns 0, otherwise it returns -1.
//If either of the surfaces were in video memory, and the blit returns -2, the video memory was lost, so it should be reloaded with artwork and re-blitted:
 while ( SDL_BlitSurface(image, imgrect, screen, dstrect) == -2 ) {
                while ( SDL_LockSurface(image)) < 0 )
                        Sleep(1);
                -- Write image pixels to image->pixels --
                SDL_UnlockSurface(image);
        }
*/



#if (DEBUG == 2)
    Log << nl << "RGBSurface::blit (const RGBSurface& src," << dest_rect << ", " << src_rect << ") done.";
#endif
    return res;
}



bool RGBSurface::flip(bool vertical, bool horizontal)
{
#pragma message("RGBSurface::flip needs to be implemented !!!")
    return false ;
}
//
//SDL_Surface *flip( SDL_Surface *in, int x, int y ) {
//	SDL_Surface *out, *tmp;
//	SDL_Rect from_rect, to_rect;
//	Uint32	flags;
//	Uint32  colorkey=0;
//
//	/* --- grab the settings for the incoming pixmap --- */
//
//	SDL_LockSurface(in);
//	flags = in->flags;
//
//	/* --- change in's flags so ignore colorkey & alpha --- */
//
//	if (flags & SDL_SRCCOLORKEY) {
//		in->flags &= ~SDL_SRCCOLORKEY;
//		colorkey = in->format->colorkey;
//	}
//	if (flags & SDL_SRCALPHA) {
//		in->flags &= ~SDL_SRCALPHA;
//	}
//
//	SDL_UnlockSurface(in);
//
//	/* --- create our new surface --- */
//
//	out = SDL_CreateRGBSurface(
//		SDL_SWSURFACE,
//		in->w, in->h, 32, rmask, gmask, bmask, amask);
//
//	/* --- flip horizontally if requested --- */
//
//	if (x) {
//		from_rect.h = to_rect.h = in->h;
//		from_rect.w = to_rect.w = 1;
//		from_rect.y = to_rect.y = 0;
//		from_rect.x = 0;
//		to_rect.x = in->w - 1;
//
//		do {
//			SDL_BlitSurface(in, &from_rect, out, &to_rect);
//			from_rect.x++;
//			to_rect.x--;
//		} while (to_rect.x >= 0);
//	}
//
//	/* --- flip vertically if requested --- */
//
//	if (y) {
//		from_rect.h = to_rect.h = 1;
//		from_rect.w = to_rect.w = in->w;
//		from_rect.x = to_rect.x = 0;
//		from_rect.y = 0;
//		to_rect.y = in->h - 1;
//
//		do {
//			SDL_BlitSurface(in, &from_rect, out, &to_rect);
//			from_rect.y++;
//			to_rect.y--;
//		} while (to_rect.y >= 0);
//	}
//
//	/* --- restore colorkey & alpha on in and setup out the same --- */
//
//	SDL_LockSurface(in);
//
//	if (flags & SDL_SRCCOLORKEY) {
//		in->flags |= SDL_SRCCOLORKEY;
//		in->format->colorkey = colorkey;
//		tmp = SDL_DisplayFormat(out);
//		SDL_FreeSurface(out);
//		out = tmp;
//		out->flags |= SDL_SRCCOLORKEY;
//		out->format->colorkey = colorkey;
//	} else if (flags & SDL_SRCALPHA) {
//		in->flags |= SDL_SRCALPHA;
//		tmp = SDL_DisplayFormatAlpha(out);
//		SDL_FreeSurface(out);
//		out = tmp;
//	} else {
//		tmp = SDL_DisplayFormat(out);
//		SDL_FreeSurface(out);
//		out = tmp;
//	}
//
//	SDL_UnlockSurface(in);
//
//	return out;
//}

PixelColor RGBSurface::getColorKey()
{
    return getPixelFormat().getColorKey();
}

/*
int RGBSurface::update(void)
{
 SDL_UpdateRects(_surf,_UpdateRectList.size(),UpdateRectList);
}
*/

RAGE::Logger & operator << (RAGE::Logger & log, const RGBSurface & surf)
{
    log << nl << "RGBSurface::" << nl
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
}
} //namespace SDLut::SDL

