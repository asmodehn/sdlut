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
class GCN_EXTENSION_DECLSPEC SDLutImageLoader : public gcn::ImageLoader
{
public:
    static const video::Color magicPink;

    SDLutImageLoader();

    // Inherited from ImageLoader
    //loadgin with default Guichan magicPink colorkey
    virtual gcn::Image* load(const std::string& filename, bool ignored_param = true);
    //loading with custom colorkey. We need two different functions, to make sure hte interface base class function is overloaded
    virtual gcn::Image* load(const std::string& filename, const video::Color& rgba_color, bool ignored_param = true);

protected:

    video::ImageLoader sdlutimgloader;

};
}

#endif // end GCN_SDLutIMAGELOADER_HPP
