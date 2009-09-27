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
inline const SDLut::RGBAColor SDLutgetPixel(SDLut::Image*& img, int x, int y)
{
    return img->getpixel(x, y);
}
inline const SDLut::RGBAColor SDLutgetPixel(SDLut::ScreenBuffer*& scr, int x, int y)
{
    return scr->getpixel(x, y);
}

/**
 * Puts a pixel on an BaseSurface.
 *
 * @param x the x coordinate on the surface.
 * @param y the y coordinate on the surface.
 * @param color the gcn::Color the pixel should be in.
 */
inline void SDLutputPixel(SDLut::Image* img, int x, int y, const gcn::Color& color)
{
    img->setpixel( x, y, SDLut::RGBColor( (unsigned char)color.r, (unsigned char)color.g, (unsigned char)color.b ) ) ;
}
inline void SDLutputPixel(SDLut::ScreenBuffer* scr, int x, int y, const gcn::Color& color)
{
    scr->setpixel( x, y, SDLut::RGBColor( (unsigned char)color.r, (unsigned char)color.g, (unsigned char)color.b ) ) ;
}

/**
 * Puts a pixel on an BaseSurface with alpha
 *
 * @param x the x coordinate on the surface.
 * @param y the y coordinate on the surface.
 * @param gcn::RGBColor the color the pixel should be in.
 */
inline void SDLutputPixelAlpha(SDLut::Image* img, int x, int y, const gcn::Color& color)
{
    img->setpixel( x, y, SDLut::RGBAColor( (unsigned char)color.r, (unsigned char)color.g, (unsigned char)color.b, (unsigned char)color.a ) );
}
inline void SDLutputPixelAlpha(SDLut::ScreenBuffer* scr, int x, int y, const gcn::Color& color)
{
    scr->setpixel( x, y, SDLut::RGBAColor( (unsigned char)color.r, (unsigned char)color.g, (unsigned char)color.b, (unsigned char)color.a ) );
}

}

#endif // end GCN_SDLutPIXEL_HPP
