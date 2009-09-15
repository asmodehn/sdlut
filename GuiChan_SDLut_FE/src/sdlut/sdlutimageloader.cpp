/*
Made by XorfacX
*/

/*
 * For comments regarding functions please see the header file.
 */

#include "guichan/sdlut/sdlutimage.hpp"

#include "guichan/exception.hpp"
#include "guichan/sdlut/sdlutimageloader.hpp"

namespace gcn
{
    Image* SDLutImageLoader::load(const std::string& filename, bool convertToDisplayFormat)
    {
		SDLut::RGBSurface* surface = new SDLut::RGBSurface(filename);
		SDLutImage* image = NULL;
		if ( true /*convertToStandardFormat(surface)*/ )
		{
			image = new SDLutImage( surface , true );
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

	Image* SDLutImageLoader::load(const std::string& filename, const SDLut::RGBAColor& rgba_color, bool convertToDisplayFormat)
	{
		SDLut::RGBSurface* surface = new SDLut::RGBSurface(filename, rgba_color);
		SDLutImage* image = NULL;
		if ( true /*convertToStandardFormat(surface)*/ )
		{
			image = new SDLutImage( surface , true );
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

	bool SDLutImageLoader::convertToStandardFormat(SDLut::RGBSurface* surface)
    {
		SDLut::RGBSurface::resetFlags(true,false,false,false);
		SDLut::RGBSurface colorSurface(SDLut::RGBColor(),0,0,32);
		SDLut::RGBSurface::resetFlags();
		
		return surface->convert(colorSurface.getPixelFormat(),true,false,false,false);
    }

}
