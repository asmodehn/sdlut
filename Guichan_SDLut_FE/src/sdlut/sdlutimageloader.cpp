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

	const video::Color SDLutImageLoader::magicPink = video::Color(255,0,255,255);

SDLutImageLoader::SDLutImageLoader()
{

}

gcn::Image* SDLutImageLoader::load(const std::string& filename, bool convertToDisplayFormat)
{
    //Inner default color key in guichan
    return load(filename, magicPink, convertToDisplayFormat);
}

gcn::Image* SDLutImageLoader::load(const std::string& filename, const video::Color& rgba_color, bool convertToDisplayFormat)
{
    std::auto_ptr<video::Image> img = sdlutimgloader.load(filename, rgba_color);
    SDLutImage* image = new SDLutImage( img.release() , true );

    if (image && convertToDisplayFormat)
    {
        image->convertToDisplayFormat();
    }

    return image;
}

}
