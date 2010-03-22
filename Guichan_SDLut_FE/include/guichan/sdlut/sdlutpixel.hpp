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
 * Checks a pixels color of an video::Image.
 *
 * @param img the video::Image where to check for a pixel color.
 * @param x the x coordinate on the surface.
 * @param y the y coordinate on the surface.
 * @return a video::Color of a pixel.
 */
inline const video::Color SDLutgetPixel(video::Image*& img, int x, int y)
{
    return img->getpixel(x, y);
}

/**
 * Checks a pixels color of a video::ScreenBuffer.
 *
 * @param scr the video::ScreenBuffer where to check for a pixel color.
 * @param x the x coordinate on the surface.
 * @param y the y coordinate on the surface.
 * @return a video::Color of a pixel.
 */
inline const video::Color SDLutgetPixel(video::ScreenBuffer*& scr, int x, int y)
{
    return scr->getpixel(x, y);
}

/**
 * Puts a pixel on a video::Image (with or wo alpha)
 *
 * @param img the video::Image where to put the color.
 * @param x the x coordinate on the surface.
 * @param y the y coordinate on the surface.
 * @param gcn::Color the color the pixel should be in.
 */
inline void SDLutputPixel(video::Image* img, int x, int y, const gcn::Color& color)
{
    img->setpixel( x, y, video::Color( (unsigned char)color.r, (unsigned char)color.g, (unsigned char)color.b, (unsigned char)color.a ) );
}

/**
 * Puts a pixel on a video::ScreenBuffer (with or wo alpha)
 *
 * @param scr the video::ScreenBuffer where to put the color.
 * @param x the x coordinate on the surface.
 * @param y the y coordinate on the surface.
 * @param gcn::Color the color the pixel should be in.
 */
inline void SDLutputPixel(video::ScreenBuffer* scr, int x, int y, const gcn::Color& color)
{
    scr->setpixel( x, y, video::Color( (unsigned char)color.r, (unsigned char)color.g, (unsigned char)color.b, (unsigned char)color.a ) );
}

}

#endif // end GCN_SDLutPIXEL_HPP
