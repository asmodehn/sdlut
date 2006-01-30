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

#include "SDLConfig.hh"

#include "SDLRect.hh"
#include "SDLVideoInfo.hh"
#include <cassert>

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
            static const VideoInfo * _vinfo; ///a usefull static pointer, set to the current VideoInfo by AppWindow

        protected:
            //TODO : improve wrapping with const SDL_Surface * // or maybe (const?) SDL_Surface &
            //... look at SDL_video.h to access correctly to SDL_Surface like as for PixelFormat and everything else

            //the adress of SDL_Surface struct should never change
            //SDL_Surface * const _surf;
            //except for resize...
            SDL_Surface * _surf; ///< the actual allocated surface
            static const VideoInfo * getVideoInfo()
            {
                return _vinfo;
            } ///access method to be used by derivated classes

            /// This method return true if the surface is initialized, false otherwise.
            bool initialized() const
            {
                return _surf != NULL;
            }
            //could be useless if exception handle is well coded in the heriting tree

            //TODO : delete this, already in SDL_Surface structure
            //To manage locks
            unsigned int locks;
            inline bool locked(void)
            {
                return locks > 0;
            }
            inline bool unlocked(void)
            {
                return !locked();
            }
            //

            ///This method return true if all is OK,or if it doesn't need being locked/unlocked.
            ///it return false only if this cannot be locked...
            bool lock(void)
            ;
            bool unlock(void);


            Uint32 getpixel(int x, int y);
            void setpixel(int x, int y, Uint32 pixel);

            ///Conversion Constructor
            explicit BaseSurface(SDL_Surface * s) : _surf(s),locks(0)
            {} ///< This one should be called only by subclasses

            /** \brief Copy constructor overload.
              */
            BaseSurface(const BaseSurface & s) throw (std::logic_error);
            BaseSurface(const BaseSurface & s , Uint32 flags, PixelFormat pfmt) throw (std::logic_error);


            /** \brief assignement operator overload.
            */
            BaseSurface& operator=(const BaseSurface& s);

            inline Uint32 getFlags(void) const
            {
                return _surf->flags;
            } ///<usefull accessor for children only

        public:

            /// Virtual Destructor
            virtual ~BaseSurface()
            {
                if (_surf!=NULL)
                    SDL_FreeSurface(_surf);
            }

            ///Accessors
            inline int getHeight(void) const
            {
                return _surf->h;
            }
            inline int getWidth(void) const
            {
                return _surf->w;
            }
            Rect getSize() const
            {
                return Rect(getWidth(),getHeight());
            }

            inline int getBPP(void) const
            {
                assert(_surf->format);
                return _surf->format->BitsPerPixel;
            }
            inline bool isSWset(void) const
            {
                return ( SDL_SWSURFACE & _surf->flags ) != 0;
            }
            inline bool isHWset(void) const
            {
                return ( SDL_HWSURFACE & _surf->flags ) != 0;
            }
            inline bool isHWAccelset(void) const
            {
                return ( SDL_HWACCEL & _surf->flags ) != 0;
            }
            inline bool isRLEAccelset(void) const
            {
                return ( SDL_RLEACCEL & _surf->flags ) != 0;
            }
            inline bool isPreAllocset(void) const
            {
                return ( SDL_PREALLOC & _surf->flags ) != 0;
            }

            ///Accessor to pixelFormat
            inline PixelFormat getPixelFormat(void) const
            {
                return PixelFormat(_surf->format);
            }

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
                return fill(PixelFormat(_surf->format).getValueFromRGB(color));
            }
            inline bool fill (const RGBAColor& color)
            {
                return fill(PixelFormat(_surf->format).getValueFromRGBA(color));
            }
            inline bool fill (const PixelColor& color)
            {
                Rect dest_rect(getWidth(), getHeight());
                return fill( color, dest_rect );
            }
            inline bool fill (const RGBColor& color, Rect dest_rect)
            {
                return fill(PixelFormat(_surf->format).getValueFromRGB(color), dest_rect);
            }
            inline bool fill (const RGBAColor& color, Rect dest_rect)
            {
                return fill(PixelFormat(_surf->format).getValueFromRGBA(color), dest_rect);
            }
            bool fill (const PixelColor& color, Rect dest_rect);

            //Blit src surface into the current surface
            inline bool blit (const BaseSurface& src, const Point& dest_pos=Point())
            {
                Rect dest_rect(dest_pos);
                return blit(src, dest_rect);
            }
            inline bool blit (const BaseSurface& src, const Point& dest_pos, const Rect& src_rect)
            {
                Rect dest_rect(dest_pos);
                return blit(src, dest_rect, src_rect);
            }
            //Beware ! The final blitting rectangle is saved in dest_rect.
            inline bool blit (const BaseSurface& src, Rect& dest_rect)
            {
                Rect src_rect(src.getWidth(), src.getHeight());
                return blit(src, dest_rect, src_rect);
            }
            //Blit src into the current surface.
            bool blit (const BaseSurface& src, Rect& dest_rect, const Rect& src_rect);

            friend Logger & operator << (Logger & ostr, const BaseSurface & surf);

        };
    }
} //namespace RAGE::SDL

#endif
