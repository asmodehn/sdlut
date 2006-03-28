#include "SDLRGBSurface.hh"

#include "SDLResources.inc"

namespace RAGE
{
    namespace SDL
    {



        Uint32 RGBSurface::RGBFlags=SDL_SWSURFACE;

        RGBSurface::RGBSurface(int width, int height, int bpp) throw (std::logic_error)
        try
:
            BaseSurface(SDL_CreateRGBSurface(RGBFlags, width, height, bpp, r_default_mask, g_default_mask, b_default_mask, a_default_mask))
        {
#ifdef DEBUG
            Log << nl << "RGBSurface::RGBSurface(" << width << ", " << height << ", " << bpp << ") called...";
#endif

            //std::cerr << "RGBSurface Constructor Called" << std::endl;
            if (bpp == 0)
                throw std::logic_error("bpp should not be set to 0 for rgb surfaces !");
            if(_surf == NULL)
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
        };

        RGBSurface::RGBSurface(void* pixeldata, int depth, int pitch, int width, int height) throw (std::logic_error)
        try
:
            BaseSurface(SDL_CreateRGBSurfaceFrom(pixeldata, width, height, depth, pitch, r_default_mask, g_default_mask, b_default_mask, a_default_mask))
        {
#ifdef DEBUG
            Log << nl << "RGBSurface::RGBSurface(" << pixeldata << ", " << depth << ", " << pitch << ", " << width << ", " <<height << ") called...";
#endif
            //std::cerr << "RGBSurface Constructor Called" << std::endl;
            if(_surf == NULL)
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
        };

        RGBSurface::RGBSurface(const Color & color, int width, int height, int bpp )throw (std::logic_error)
        try
:
            BaseSurface(SDL_CreateRGBSurface(RGBFlags, width, height, bpp, r_default_mask, g_default_mask, b_default_mask, a_default_mask))
        {
#ifdef DEBUG
            Log << nl << "RGBSurface::RGBSurface(" << color << ", " << width << ", " <<height << ", " << bpp << ") called...";
#endif
            //std::cerr << "RGBSurface Constructor Called" << std::endl;
            if (bpp == 0)
                throw std::logic_error("bpp should not be set to 0 for rgb surfaces !");
            if(_surf == NULL)
            {
                Log << "Unable to set " <<  width<<  " x " <<  height <<  " rgb surface : " ;
                throw std::logic_error("SDL_CreateRGBSurface returns NULL");
            }
            else
                fill(color);
#ifdef DEBUG

            Log << nl << "RGBSurface::RGBSurface(" << color << ", " << width << ", " <<height << ", " << bpp << ") done.";
#endif

        }
        catch (std::exception &e)
        {
            Log << nl << "Exception catched in RGBSurface Constructor !!!"  << nl <<
            e.what() << nl << GetError() << std::endl ;
            //TODO : much more explicit error message...
        };

        RGBSurface::RGBSurface( std::string filename )throw (std::logic_error)
			try :
#ifdef HAVE_SDLIMAGE
			BaseSurface(IMG_Load(filename.c_str()))
#else
			BaseSurface(SDL_LoadBMP(filename.c_str()))
#endif
        {

#ifdef DEBUG
            Log << nl << "RGBSurface::RGBSurface(" << filename<< ") called...";
#endif

            //std::cerr << "RGBSurface Constructor Called" << std::endl;
            //TODO : support for other format than BMP with SDL_image
            if(_surf == NULL)
            {
                Log << nl << "Unable to set rgb surface from " << filename << std::endl;
                throw std::logic_error(
#ifdef HAVE_SDLIMAGE
					"IMG_Load returns NULL");
#else
					"SDL_LoadBMP returns NULL");
#endif
            }

#ifdef DEBUG
            Log << nl << "RGBSurface::RGBSurface(" << filename<< ") done.";
#endif

        }
        catch (std::exception &e)
        {
            Log << nl << "Exception catched in RGBSurface Constructor !!!"  << nl <<
            e.what() << nl << GetError();
            //TODO : much more explicit error message...
        };

        RGBSurface::RGBSurface( std::string filename, const Color & colorKey )throw (std::logic_error)
        try
:
#ifdef HAVE_SDLIMAGE
			BaseSurface(IMG_Load(filename.c_str()))
#else
			BaseSurface(SDL_LoadBMP(filename.c_str()))
#endif
        {
#ifdef DEBUG
            Log << nl << "RGBSurface::RGBSurface(" << filename << ", " << colorKey << ") called...";
#endif
            //std::cerr << "RGBSurface Constructor Called" << std::endl;
            //TODO : support for other format than BMP with SDL_image
            if(_surf == NULL)
            {
                Log << nl << "Unable to set rgb surface from " << filename << std::endl;
                throw std::logic_error("SDL_LoadBMP returns NULL");
            }
            else
                setColorKey(colorKey);
#ifdef DEBUG

            Log << nl << "RGBSurface::RGBSurface(" << filename << ", " << colorKey << ") done.";
#endif

        }
        catch (std::exception &e)
        {
            Log << nl << "Exception catched in RGBSurface Constructor !!!" << nl <<
            e.what() << nl << GetError();
            //TODO : much more explicit error message...
        };


		RGBSurface::RGBSurface (const RWOps & rwops) throw (std::logic_error)
        try
:
#ifdef HAVE_SDLIMAGE
			BaseSurface(IMG_Load_RW(const_cast<SDL_RWops*>(rwops.get_pSDL()),0))
#else
			BaseSurface(SDL_LoadBMP_RW(const_cast<SDL_RWops*>(rwops.get_pSDL()),0))
#endif
        {
#ifdef DEBUG
            Log << nl << "RGBSurface::RGBSurface(RWOps) called...";
#endif
            //std::cerr << "RGBSurface Constructor Called" << std::endl;
            //TODO : support for other format than BMP with SDL_image
            if(_surf == NULL)
            {
				Log << nl << "Error : Unable to set rgb surface from RWOps ";
				
#ifdef HAVE_SDLIMAGE
			    throw std::logic_error("IMG_Load_RW returns NULL");
#else
	          throw std::logic_error("SDL_LoadBMP_RW returns NULL");
#endif
      
            }
#ifdef DEBUG

            Log << nl << "RGBSurface::RGBSurface(RWOps) done.";
#endif

        }
        catch (std::exception &e)
        {
            Log << nl << "Exception catched in RGBSurface Constructor !!!" << nl <<
            e.what() << nl << GetError();
            //TODO : much more explicit error message...
        };

		//default constructor
		RGBSurface::RGBSurface () throw (std::logic_error)
        try
:
#ifdef HAVE_SDLIMAGE
			BaseSurface(IMG_Load_RW(const_cast<SDL_RWops*>(RWOps(_defaultImage,sizeof(_defaultImage)).get_pSDL()),0))
#else
			BaseSurface(SDL_LoadBMP_RW(const_cast<SDL_RWops*>(RWOps(_defaultImage,sizeof(_defaultImage)).get_pSDL()),0))
#endif
        {
#ifdef DEBUG
            Log << nl << "RGBSurface::RGBSurface(RWOps) called...";
#endif
            //std::cerr << "RGBSurface Constructor Called" << std::endl;
            //TODO : support for other format than BMP with SDL_image
            if(_surf == NULL)
            {
				Log << nl << "Error : Unable to set rgb surface from RWOps ";
				
#ifdef HAVE_SDLIMAGE
			    throw std::logic_error("IMG_Load_RW returns NULL");
#else
	          throw std::logic_error("SDL_LoadBMP_RW returns NULL");
#endif
      
            }
#ifdef DEBUG

            Log << nl << "RGBSurface::RGBSurface(RWOps) done.";
#endif

        }
        catch (std::exception &e)
        {
            Log << nl << "Exception catched in RGBSurface Constructor !!!" << nl <<
            e.what() << nl << GetError();
            //TODO : much more explicit error message...
        };



	//creates a surface from a text (solid or blended mode).
		RGBSurface::RGBSurface ( const Font & font, std::string text, RGBColor color, bool blended)
			try : BaseSurface(font.render(text, color, blended? Font::Blended : Font::Solid ))
		{
			
#ifdef DEBUG
            Log << nl << "RGBSurface::RGBSurface(Font," << text << ", " << color << ") called...";
#endif
            if(_surf == NULL)
            {
                throw std::logic_error("Unable to set rgb surface from " + text);
            }
#ifdef DEBUG

            Log << nl << "RGBSurface::RGBSurface(Font," << text << ", " << color << ") done.";
#endif

        }
        catch (std::exception &e)
        {
            Log << nl << "Exception catched in RGBSurface Constructor !!!" << nl <<
            e.what() << nl << GetError();
            //TODO : much more explicit error message...
        };


	//creates a surface from a text (shaded mode).
		RGBSurface::RGBSurface ( const Font & font, std::string text, RGBColor color, RGBColor bgcolor)
		try : BaseSurface(font.render(text, color, Font::Shaded, bgcolor ))
		{
			
#ifdef DEBUG
            Log << nl << "RGBSurface::RGBSurface(Font," << text << ", " << color << ") called...";
#endif
            if(_surf == NULL)
            {
                throw std::logic_error("Unable to set rgb surface from " + text);
            }
#ifdef DEBUG

            Log << nl << "RGBSurface::RGBSurface(Font," << text << ", " << color << ") done.";
#endif

        }
        catch (std::exception &e)
        {
            Log << nl << "Exception catched in RGBSurface Constructor !!!" << nl <<
            e.what() << nl << GetError();
            //TODO : much more explicit error message...
        };



        ////Copy Constructor ( doesn't copy the content of the surface)
        ////and Clone (also copy the content of the surface)
        //RGBSurface::RGBSurface(const RGBSurface & s , const PixelFormat& fmt, Uint32 flags, bool cloning) throw (std::logic_error)
        //try : BaseSurface (  cloning ?
        //    SDL_ConvertSurface(s._surf,new SDL_PixelFormat(*fmt._pformat),flags) // copy to deal with const... maybe a const cast should be ok...
        //    : SDL_CreateRGBSurface(flags, s.getWidth(), s.getHeight(), fmt.getBitsPerPixel(), fmt.getRmask(), fmt.getGmask(), fmt.getBmask(), fmt.getAmask())
        //  )
        //{
        // //std::cerr << "RGBSurface Copy Called" << std::endl;
        // const std::string errstr = cloning ? "SDL_ConvertSurface" : "SDL_CreateRGBSurface";
        //    if(_surf == NULL)
        // {
        //  Log << nl << "Unable to copy the RGBsurface @ " << &s << std::endl;
        //        throw std::logic_error(errstr + " returns NULL");
        //    }
        //    else
        //  Log << nl << "SDL_Surface created @ " <<  _surf << std::endl;
        //}
        //catch (std::exception &e)
        //{
        // Log << nl<< "Exception catched in RGBSurface Copy Constructor !!!"<< nl <<
        //  e.what() << nl << GetError() << std::endl;
        //};
        //
        //
        //RGBSurface::RGBSurface(const RGBSurface & s , Uint32 flags, bool cloning) throw (std::logic_error)
        //try : BaseSurface (  cloning ?
        //    SDL_ConvertSurface(s._surf,new SDL_PixelFormat(*(s._surf->format)),flags) // copy to deal with const... maybe a const cast should be ok...
        //    : SDL_CreateRGBSurface(flags, s.getWidth(), s.getHeight(), s._surf->format->BitsPerPixel, s._surf->format->Rmask, s._surf->format->Gmask, s._surf->format->Bmask, s._surf->format->Amask)
        //  )
        //{
        // //std::cerr << "RGBSurface Copy Called" << std::endl;
        // const std::string errstr = cloning ? "SDL_ConvertSurface" : "SDL_CreateRGBSurface";
        //    if(_surf == NULL)
        // {
        //  Log << nl << "Unable to copy the RGBsurface @ "  << &s << std::endl;
        //        throw std::logic_error(errstr + " returns NULL");
        //    }
        //    else
        //  Log << nl << "SDL_Surface created @ " << _surf << std::endl;
        //}
        //catch (std::exception &e)
        //{
        // Log << nl << "Exception catched in RGBSurface Copy Constructor !!!" << nl <<
        //  e.what() << nl << GetError() << std::endl;
        //};

        RGBSurface::RGBSurface(const RGBSurface & s ) throw (std::logic_error)
        try
:
            BaseSurface(s)
        {
#ifdef DEBUG
            Log << nl << "RGBSurface::RGBSurface(" << &s << ") called.";
#endif

#ifdef DEBUG

            Log << nl << "RGBSurface::RGBSurface(" << &s << ") done -> " << _surf << " created.";
#endif

        }
        catch (std::exception &e)
        {
            Log << nl << "Exception catched in RGBSurface Copy Constructor !!!" << nl <<
            e.what() << nl << GetError() << std::endl;
        };

        RGBSurface& RGBSurface::operator=(const RGBSurface& s)
        {
            if (this != &s)
            {
                this->BaseSurface::operator=(s);
            }
            return *this;
        }

        RGBSurface::RGBSurface(const BaseSurface & s ) throw (std::logic_error)
        try
:
            BaseSurface(s)
        {
#ifdef DEBUG
            Log << nl << "RGBSurface::RGBSurface(" << &s << ") called.";
#endif

#ifdef DEBUG

            Log << nl << "RGBSurface::RGBSurface(" << &s << ") done -> " << _surf << " created.";
#endif

        }
        catch (std::exception &e)
        {
            Log << nl << "Exception catched in RGBSurface Conversion Constructor !!!" << nl <<
            e.what() << nl << GetError() << std::endl;
        };

        RGBSurface& RGBSurface::operator=(const BaseSurface& s)
        {
            if (this != &s)
            {
                this->BaseSurface::operator=(s);
            }
            return *this;
        }
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

        void RGBSurface::setFlags(bool SWSURFACE, bool HWSURFACE, bool SRCCOLORKEY, bool SRCALPHA)
        {
            if ( SWSURFACE )
                RGBFlags|= SDL_SWSURFACE;
            else
                RGBFlags&= (~SDL_SWSURFACE);
            if ( HWSURFACE )
                RGBFlags|= SDL_HWSURFACE;
            else
                RGBFlags&= (~SDL_HWSURFACE);
            if ( SRCCOLORKEY )
                RGBFlags|= SDL_SRCCOLORKEY;
            else
                RGBFlags&= (~SDL_SRCCOLORKEY);
            if ( SRCALPHA )
                RGBFlags|= SDL_SRCALPHA;
            else
                RGBFlags&= (~SDL_SRCALPHA);
        }

        bool RGBSurface::setColorKey(const RGBColor & key, bool rleAccel)
        {
            Uint32 flags;
            if (rleAccel)
                flags=SDL_SRCCOLORKEY | SDL_RLEACCEL;
            else
                flags=SDL_SRCCOLORKEY;

            return SDL_SetColorKey(_surf, flags, getPixelFormat().getValueFromRGB(key) ) == 0;
        }

		bool RGBSurface::resize(int width, int height, bool keepcontent)
		{
			
			SDL_Surface * newSurf = SDL_CreateRGBSurface(_surf->flags,width,height,_surf->format->BitsPerPixel, r_default_mask, g_default_mask, b_default_mask, a_default_mask);

            if (newSurf==NULL) //SetVideoMode has failed
            {
                Log << "Unable to resize to " << width << " x " << height << " 2D RGB surface " << nl << GetError();
				
               return false;
            }

			if (keepcontent)
			{
				SDL_BlitSurface(_surf, NULL , newSurf, NULL);
			}

			assert(newSurf); // should be always OK
			SDL_FreeSurface(_surf);
            _surf=newSurf;

			return true;
		}

        bool RGBSurface::optimise(bool alpha)
        {
            assert(_surf);
            bool res;
            SDL_Surface * optsurf;
            if ( alpha )
            {
                optsurf=SDL_DisplayFormatAlpha(_surf);
            }
            else
            {
                optsurf=SDL_DisplayFormat(_surf);
            }

            if (optsurf == NULL )
                res = false;
            else
            {
                SDL_FreeSurface(_surf);
                _surf=optsurf;
                res = true;
            }

            return res;
        }



#ifdef HAVE_OPENGL
		//bool RGBSurface::isGLvalid()
		//{
		//		//Not the good test - TO CORRECT
		//		if (getWidth() >= 1 && getWidth() % 2 == 0 && getHeight() % 2 == 0 )
		//		{
		//			return true;
		//		}
		//		return false;
		//}

	//return a GL texture that you have to bind
		GLuint RGBSurface::generateTexture()
		{
			GLuint texture; //maybe keep that not to reload the texture each and everytime ??
			//Create the texture
			glGenTextures(1, &texture);
			//Load the texture
			glBindTexture(GL_TEXTURE_2D, texture);
			//Generate the texture
			glTexImage2D(GL_TEXTURE_2D, 0, 3, getWidth(),getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, _surf->pixels);
			return texture;
		}
#endif

        /*
        int RGBSurface::update(void)
        {
         SDL_UpdateRects(_surf,_UpdateRectList.size(),UpdateRectList);
        }
        */

        Logger & operator << (Logger & log, const RGBSurface & surf)
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
} //namespace RAGE::SDL

