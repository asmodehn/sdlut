/*
Made by XorfacX
*/

/*
 * For comments regarding functions please see the header file.
 */

#include "guichan/sdlut/sdlutoglimage.hpp"

#include "guichan/exception.hpp"
#include "guichan/sdlut/sdlutoglimageloader.hpp"

namespace gcn
{
Image* SDLutOGLImageLoader::load(const std::string& filename, bool convertToDisplayFormat)
{
    SDLut::RGBSurface loaded(filename);
    SDLutOGLImage* image = NULL;
    if ( convertToStandardFormat(&loaded) )
    {
        loaded.lock();
        image = new SDLutOGLImage( static_cast<const unsigned int*> (loaded.getpixels()), loaded.getWidth(), loaded.getHeight() );
        loaded.unlock();
    }
    else
    {
        throw GCN_EXCEPTION( "Unable to convert to Standard Format " );
    }

    if ( image && convertToDisplayFormat)
    {
        image->convertToDisplayFormat();
    }

    return image;
}


Image* SDLutOGLImageLoader::load(const std::string& filename, const RAGE::SDL::RGBAColor& rgba_color,bool convertToDisplayFormat)
{
    SDLut::RGBSurface loaded(filename);
    SDLutOGLImage* image = NULL;
    if ( convertToStandardFormat(&loaded) )
    {
        loaded.lock();
        image = new SDLutOGLImage( static_cast<const unsigned int*> (loaded.getpixels()), loaded.getWidth(), loaded.getHeight(), rgba_color );
        loaded.unlock();
    }
    else
    {
        throw GCN_EXCEPTION( "Unable to convert to Standard Format " );
    }

    if (image && convertToDisplayFormat)
    {
        image->convertToDisplayFormat();
    }

    return image;
}

}
