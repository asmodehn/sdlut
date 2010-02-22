/*
Made by XorfacX
*/

/*
 * For comments regarding functions please see the header file.
 */

#include "guichan/sdlut/sdlutimage.hpp"

#include "guichan/exception.hpp"
#include "guichan/sdlut/sdlutpixel.hpp"

namespace gcn
{
//moved into loader
//const SDLut::RGBAColor SDLutImage::magicPink = SDLut::RGBAColor(255,0,255,255);

SDLutImage::SDLutImage(SDLut::Image* surface, bool autoFree)
{
    mAutoFree = autoFree;
    mSurface = surface;
}

SDLutImage::~SDLutImage()
{
    if (mAutoFree)
    {
        free();
    }
}

SDLut::Image* SDLutImage::getSurface() const
{
    return mSurface;
}

int SDLutImage::getWidth() const
{
    if (mSurface == NULL)
    {
        throw GCN_EXCEPTION("Trying to get the width of a non loaded image.");
    }

    return mSurface->getWidth();
}

int SDLutImage::getHeight() const
{
    if (mSurface == NULL)
    {
        throw GCN_EXCEPTION("Trying to get the height of a non loaded image.");
    }

    return mSurface->getHeight();
}

gcn::Color SDLutImage::getPixel(int x, int y)
{
    if (mSurface == NULL)
    {
        throw GCN_EXCEPTION("Trying to get a pixel from a non loaded image.");
    }
    SDLut::Color color = SDLutgetPixel((SDLut::Image*&)mSurface, x, y);
    return gcn::Color( color.getR(), color.getG(), color.getB(), color.getA() );
}

void SDLutImage::putPixel(int x, int y, const gcn::Color& color)
{
    if (mSurface == NULL)
    {
        throw GCN_EXCEPTION("Trying to put a pixel in a non loaded image.");
    }

    SDLutputPixel((SDLut::Image*&)mSurface, x, y, color);
}

void SDLutImage::convertToDisplayFormat()
{
    if (mSurface == NULL)
    {
        throw GCN_EXCEPTION("Trying to convert a non loaded image to display format.");
    }

    mSurface->convertToDisplayFormat();

    //NOT SURE if part of the old algorithms is still needed...
    /*
    SDLut::Color pink = magicPink;

    bool hasPink = false;
    bool hasAlpha = false;

    for (signed int x = 0; x < mSurface->getWidth(); x++)
    {
        for (signed int y = 0; y < mSurface->getHeight(); y++)
        {
            SDLut::Color Current_pxColor = SDLutgetPixel((SDLut::Image*&)mSurface, x, y);

            //Looking for pink color as it's the default ColorKey for image in GuiChan
            if (!hasPink)
                if (Current_pxColor == pink )
                    hasPink = true;

            //looking for an alpha
            if (!hasAlpha)
                if ( Current_pxColor.getA() != 255 )
                {
                    hasAlpha = true;
                    pink.setA( Current_pxColor.getA() );
                }


            //leave loop when both has been found
            if ( hasPink && hasAlpha )
                break;
        }
        //leave loop when both has been found
        if ( hasPink && hasAlpha )
            break;

    }

    mSurface->optimise(hasAlpha);

    //Enable alpha-blending with SDL_SRCALPHA
    if (hasAlpha)
    {
        mSurface->resetFlags(true,false,false,true);
    }

    if (hasPink)
    {
        mSurface->setColorKeyAndAlpha( pink, true );
    }

    */

}

void SDLutImage::free()
{
    delete mSurface, mSurface = NULL;
}
}
