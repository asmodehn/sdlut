#ifndef GCN_SDLutOGLIMAGELOADER_HPP
#define GCN_SDLutOGLIMAGELOADER_HPP

#include "guichan/sdlut/sdlutimageloader.hpp"

namespace gcn
{
class Image;

/**
 * SDLut implementation of ImageLoader.
 */
class GCN_EXTENSION_DECLSPEC SDLutOGLImageLoader : public SDLutImageLoader
{
public:

    // Inherited from ImageLoader
    virtual Image* load(const std::string& filename, bool convertToDisplayFormat = true);

    virtual Image* load(const std::string& filename, const RAGE::SDL::RGBAColor& rgba_color, bool convertToDisplayFormat = true);

};
}

#endif // end GCN_SDLutOGLIMAGELOADER_HPP
