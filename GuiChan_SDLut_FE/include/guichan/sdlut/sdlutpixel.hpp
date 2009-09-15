/*
Made by XorfacX
*/

#ifndef GCN_SDLutPIXEL_HPP
#define GCN_SDLutPIXEL_HPP

#include "sdlutdepends.hpp"

#include "guichan/color.hpp"

namespace gcn
{

    /**
     * Checks a pixels color of an BaseSurface.
     *
     * @param surface an BaseSurface where to check for a pixel color.
     * @param x the x coordinate on the surface.
     * @param y the y coordinate on the surface.
     * @return a gcn::Color of a pixel.
     */
	inline const SDLut::RGBAColor SDLutgetPixel(SDLut::BaseSurface*& surface, int x, int y)
    {
		//unsigned int color = mSurface->getpixel(x, y); 

		return surface->getPixelFormat().getRGBAValue( surface->getpixel(x, y) ) ;
		
		
		/*
		int bpp = surface->format->BytesPerPixel;

        SDL_LockSurface(surface);

        Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

        unsigned int color = 0;

        switch(bpp)
        {
          case 1:
              color = *p;
              break;

          case 2:
              color = *(Uint16 *)p;
              break;

          case 3:
              if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
              {
                  color = p[0] << 16 | p[1] << 8 | p[2];
              }
              else
              {
                  color = p[0] | p[1] << 8 | p[2] << 16;
              }
              break;

          case 4:
              color = *(Uint32 *)p;
              break;

        }
		
        unsigned char r,g,b,a;

        SDL_GetRGBA(color, surface->format, &r, &g, &b, &a);
        SDL_UnlockSurface(surface);

        return Color(r,g,b,a);*/
    }

    /**
     * Puts a pixel on an BaseSurface.
     *
     * @param x the x coordinate on the surface.
     * @param y the y coordinate on the surface.
     * @param color the gcn::Color the pixel should be in.
     */
	inline void SDLutputPixel(SDLut::BaseSurface* surface, int x, int y, const gcn::Color& color)
    {
		surface->setpixel( x, y, surface->getPixelFormat().getValueFromRGB(SDLut::RGBColor( (unsigned char)color.r, (unsigned char)color.g, (unsigned char)color.b ) ) );
    }

    /**
     * Puts a pixel on an BaseSurface with alpha
     *
     * @param x the x coordinate on the surface.
     * @param y the y coordinate on the surface.
     * @param gcn::RGBColor the color the pixel should be in.
     */
	inline void SDLutputPixelAlpha(SDLut::BaseSurface* surface, int x, int y, const gcn::Color& color)
    {
		surface->setpixel( x, y, surface->getPixelFormat().getValueFromRGB(SDLut::RGBAColor( (unsigned char)color.r, (unsigned char)color.g, (unsigned char)color.b ) ), (unsigned char)color.a );
    }
}

#endif // end GCN_SDLutPIXEL_HPP
