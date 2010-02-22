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

const SDLut::Color SDLutImageLoader::magicPink = SDLut::Color(255,0,255,255);


Image* SDLutImageLoader::load(const std::string& filename, bool convertToDisplayFormat)
{
    //Inner default color key in guichan
    return load(filename, magicPink, convertToDisplayFormat);
}

Image* SDLutImageLoader::load(const std::string& filename, const SDLut::Color& rgba_color, bool convertToDisplayFormat)
{
    std::auto_ptr<SDLut::Image> img=sdlutimgloader.load(filename, rgba_color);
    SDLutImage* image = new SDLutImage( img.release() , true );

    if (image && convertToDisplayFormat)
    {
        image->convertToDisplayFormat();
    }

    return image;
}

}
