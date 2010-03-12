/*
Made by XorfacX
*/

#ifndef GCN_SDLutIMAGELOADER_HPP
#define GCN_SDLutIMAGELOADER_HPP

#include "sdlutdepends.hpp"

#include "guichan/imageloader.hpp"
#include "guichan/platform.hpp"

namespace gcn
{
class Image;

/**
 * SDLut implementation of ImageLoader.
 */
class GCN_EXTENSION_DECLSPEC SDLutImageLoader : public ImageLoader
{
public:
    static const SDLut::Color magicPink;

	SDLutImageLoader();

    // Inherited from ImageLoader
    //loadgin with default Guichan magicPink colorkey
    virtual Image* load(const std::string& filename, bool convertToDisplayFormat = true);
    //loading with custom colorkey. We need two different functions, to make sure hte interface base class function is overloaded
    virtual Image* load(const std::string& filename, const SDLut::Color& rgba_color, bool convertToDisplayFormat = true);

protected:

    SDLut::ImageLoader sdlutimgloader;

};
}

#endif // end GCN_SDLutIMAGELOADER_HPP
