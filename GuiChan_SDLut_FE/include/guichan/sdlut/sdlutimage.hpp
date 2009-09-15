/*
Made by XorfacX
*/

#ifndef GCN_SDLutIMAGE_HPP
#define GCN_SDLutIMAGE_HPP

#include <string>

#include "sdlutdepends.hpp"

#include "guichan/color.hpp"
#include "guichan/platform.hpp"
#include "guichan/image.hpp"

namespace gcn
{
    /**
     * SDLut implementation of Image.
     */
    class GCN_EXTENSION_DECLSPEC SDLutImage : public Image
    {
    public:
        /**
         * Constructor. Load an image from an SDLut BaseSurface.
         *
         * NOTE: The functions getPixel and putPixel are only guaranteed to work
         *       before an image has been converted to display format.
         *
         * @param surface the surface from which to load.
         * @param autoFree true if the surface should automatically be deleted.
         */
        static const SDLut::RGBAColor magicPink;
		SDLutImage(SDLut::RGBSurface* surface, bool autoFree);

        /**
         * Destructor.
         */
        virtual ~SDLutImage();

        /**
         * Gets the surface for the image.
         *
         * @return the RGBSurface for the image.
         */
		virtual SDLut::RGBSurface* getSurface() const;

        // Inherited from Image

        virtual void free();

        virtual int getWidth() const;

        virtual int getHeight() const;

        virtual gcn::Color getPixel(int x, int y);

        virtual void putPixel(int x, int y, const gcn::Color& color);

        virtual void convertToDisplayFormat();

    protected:
        SDLut::RGBSurface* mSurface;
        bool mAutoFree;
    };
}

#endif // end GCN_SDLutIMAGE_HPP
