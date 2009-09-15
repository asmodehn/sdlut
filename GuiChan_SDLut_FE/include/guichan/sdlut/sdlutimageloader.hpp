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

        // Inherited from ImageLoader

        virtual Image* load(const std::string& filename, bool convertToDisplayFormat = true);
		virtual Image* load(const std::string& filename, const SDLut::RGBAColor& rgba_color, bool convertToDisplayFormat = true);

    protected:
		/* ALREADY DEFINED IN SDLUT
        virtual RGBSurface* loadSDLutSurface(const std::string& filename);
		*/
		virtual bool convertToStandardFormat(SDLut::RGBSurface* surface);
		
    };
}

#endif // end GCN_SDLutIMAGELOADER_HPP
