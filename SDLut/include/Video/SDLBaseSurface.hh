#ifndef SDL_BASESURFACE_HH
#define SDL_BASESURFACE_HH

/**
 * \class BaseSurface
 *
 * \ingroup Video
 *
 * \brief Abstract Class to manage Surfaces
 *
 * Abstract Class to handle common behaviour between display surface
 * and other surface types...
 *
 * \author Alex
 *
 * \date 2005/10/02
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "Logger.hh"
#include "Math/SDLRect.hh"
#include "Video/SDLVideoInfo.hh"

#include <iostream>
#include <cassert>
#include <memory>

//declaring SDL_type for late binding
struct SDL_Surface;


namespace RAGE
{
    namespace SDL
    {

        //TODO : make this class pure virtual one (how then?)... and manage creation of _surf with exception
        //in the derivating tree
        //The goal is to have _surf and this really tied.
        class BaseSurface
        {
            friend class Window;

        private:
            static const VideoInfo * _vinfo; ///a usefull static pointer, set to the current VideoInfo by AppWindow and reset to 0 on Window destruction

        protected:

			//Moved out of RGBSurface, because VideoSurface might need those sometime...
			//SDL interprets each pixel as a 32-bit number, so our masks must depend
			//on the endianness (byte order) of the machine */
			#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				static const unsigned long r_default_mask = 0xff000000;
				static const unsigned long g_default_mask = 0x00ff0000;
				static const unsigned long b_default_mask = 0x0000ff00;
				static const unsigned long a_default_mask = 0x000000ff;
			#else // SDL_BYTEORDER == SDL_LIL_ENDIAN
				static const unsigned long r_default_mask = 0x000000ff;
				static const unsigned long g_default_mask = 0x0000ff00;
				static const unsigned long b_default_mask = 0x00ff0000;
				static const unsigned long a_default_mask = 0xff000000;
			#endif

            //TODO : improve wrapping with const SDL_Surface * // or maybe (const?) SDL_Surface &
            //... look at SDL_video.h to access correctly to SDL_Surface like as for PixelFormat and everything else

            //the adress of SDL_Surface struct should never change
            //SDL_Surface * const _surf;
            //except for resize...
            std::auto_ptr<SDL_Surface> _surf; ///< the actual allocated surface
            static const VideoInfo * getVideoInfo()
            {
                return _vinfo;
            } ///access method to be used by derivated classes

            /// This method return true if the surface is initialized, false otherwise.
            bool initialized() const
            {
                return _surf.get() != 0;
            }
            //could be useless if exception handle is well coded in the heriting tree

        public: //useful else we can't access those functions outside of friend class (for example in GuiChan)

            ///This method return true if all is OK,or if it doesn't need being locked/unlocked.
            ///it return false only if this cannot be locked...
            bool lock(void);
            bool unlock(void);

            RGBAColor getpixel(int x, int y);
            void setpixel(int x, int y, RGBAColor pixel);

		protected:
			//Default Constructor overload
			BaseSurface() throw (std::logic_error) ;
			///< should be called only by subclasses

            ///RAII Conversion Constructor
			explicit BaseSurface(SDL_Surface * s) throw (std::logic_error) ;
			///< should be called only by subclasses
	    
			///RAII Conversion Constructor with explicit ownership transfer as it s using an auto_ptr
			explicit BaseSurface(std::auto_ptr<SDL_Surface> s) throw (std::logic_error) ;
			///< should be called only by subclasses
			
			///to assign a surface to a BaseSurface
			bool set_SDL_Surface(SDL_Surface * s);
			///< should be called only by subclasses

			///to assign a surface to a BaseSurface
			bool set_SDL_Surface(std::auto_ptr<SDL_Surface> s);
			///< should be called only by subclasses

            /** \brief Copy constructor overload.
              */
            BaseSurface(const BaseSurface & s) throw (std::logic_error);
            BaseSurface(const BaseSurface & s , unsigned long flags, PixelFormat pfmt) throw (std::logic_error);


            /** \brief assignement operator overload.
            */
            BaseSurface& operator=(const BaseSurface& s);

	    ///<usefull accessor for children only
	    unsigned long getFlags(void) const;

		///<protected because parameter const differs between derivates
		bool blit(const BaseSurface& src, Rect& dest_rect, const Rect& src_rect );

        public:

            /// Virtual Destructor
		virtual ~BaseSurface();

            ///Accessors

		protected:
			//usefull to get the SDL structure without no risk of modifying it
			SDL_Surface get_SDL() const;
		
			//usefull to get the SDL structure
			const SDL_Surface * get_pSDL() const
			{
				return _surf.get();
			}

		const SDL_Surface & get_rSDL() const
		{
			return *_surf; // Indirection of auto_ptr ???? -> TO INVESTIGATE....
		}

		public:
			int getHeight(void) const;
			int getWidth(void) const;

			Rect getSize() const
			{
				return Rect(getWidth(),getHeight());
			}

			int getBPP(void) const;
			bool isSWset(void) const;
			bool isHWset(void) const;
			bool isHWAccelset(void) const;
			bool isRLEAccelset(void) const;
			bool isPreAllocset(void) const;

			//if not NULL, contains the raw pixel data for the surface
			//shouldnt be public -> format problems, managed by pixel format
			//TO FIX
			void * getpixels(void) const;
			
            ///Accessor to pixelFormat
			PixelFormat getPixelFormat(void) const;
			
            //Set the clip rect
            //Default Reset the clip rect to the full size of the surface
            inline void setClipRect(void)
            {
                return setClipRect(Rect(getWidth(),getHeight()));
            }
            void setClipRect(const Rect& rect);
            //get the clip rect
            Rect getClipRect(void) const;

            //save the surface to a BMP file.
            bool saveBMP(std::string filename) const;
            //TODO : the same with other formats

            //Fill
            inline bool fill (const RGBColor& color)
            {
                return fill(getPixelFormat().getValueFromRGB(color));
            }
            inline bool fill (const RGBAColor& color)
            {
                return fill(getPixelFormat().getValueFromRGBA(color));
            }
            inline bool fill (const PixelColor& color)
            {
                Rect dest_rect(getWidth(), getHeight());
                return fill( color, dest_rect );
            }
            inline bool fill (const RGBColor& color, Rect dest_rect)
            {
                return fill(getPixelFormat().getValueFromRGB(color), dest_rect);
            }
            inline bool fill (const RGBAColor& color, Rect dest_rect)
            {
                return fill(getPixelFormat().getValueFromRGBA(color), dest_rect);
            }
            virtual bool fill (const PixelColor& color, Rect dest_rect);



	bool resize(const Rect & r)
	{
		return resize(r.getw(),r.geth());
	}

			virtual bool resize(int width, int height, bool keepcontent = false) = 0;

            friend Logger & operator << (Logger & ostr, const BaseSurface & surf);

        };
    }
} //namespace RAGE::SDL

#endif
