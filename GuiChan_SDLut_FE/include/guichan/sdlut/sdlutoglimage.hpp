

#ifndef GCN_SDLutOGLIMAGE_HPP
	#define GCN_SDLutOGLIMAGE_HPP
#if defined (_WIN32)
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#ifndef NOMINMAX
		#define NOMINMAX // windows stupidity
	#endif
	#include <windows.h>
#endif

#if defined (__amigaos4__)
	#include <mgl/gl.h>
#elif defined (__APPLE__)
	#include <OpenGL/gl.h>
#else
#include <GL/gl.h>

//TMP ( from glext.h )
#ifndef GL_EXT_abgr
#define GL_ABGR_EXT                       0x8000
#endif

#endif

#include <string>

#include "guichan/sdlut/sdlutdepends.hpp"

#include "guichan/color.hpp"
#include "guichan/platform.hpp"
#include "guichan/image.hpp"

namespace gcn
{
    /**
     * SDLutOpenGL implementation of Image.
     */
    class GCN_EXTENSION_DECLSPEC SDLutOGLImage : public Image
    {
    public:
        /**
         * Constructor. Loads an image from an array of pixels. The pixel array is
		 * is copied in the constructor and should thus be freed after the constructor
		 * has been called.
         *
         * NOTE: The functions getPixel and putPixel are only guaranteed to work
         *       before an image has been converted to display format.
         *
         * @param pixels to load from.
         * @param width the width of the image.
         * @param height the height of the image.
         * @param ColorKey the color that will become transparent (default = gcn::magicPink).
         */
        static const SDLut::RGBAColor magicPink;
		SDLutOGLImage(const unsigned int* pixels, int width, int height, const SDLut::RGBAColor& ColorKey = magicPink);

        /**
         * Constructor. Load an image from an OpenGL texture handle. The width
		 * and height specifies the size of the "interesting" part of the
		 * texture, the real width and height of the texture are assumed to
		 * be the closest higher power of two.
         *
         * @param textureHandle the texture handle from which to load.
		 * @param width the width of the image.
		 * @param height the height of the image.
         * @param autoFree true if the surface should automatically be deleted.
         */
        SDLutOGLImage(GLuint textureHandle, int width, int height, bool autoFree);

        /**
         * Destructor.
         */
        virtual ~SDLutOGLImage();

        /**
         * Gets the OpenGL texture handle for the image.
         *
         * @return the OpenGL texture handle for the image.
         */

        virtual GLuint getTextureHandle() const;

        /**
         * Gets the width of texture.
         *
         * @return the width of the texture.
         */
        virtual int getTextureWidth() const;

        /**
         * Gets the height of the texture.
         *
         * @return the height of the texture.
         */
        virtual int getTextureHeight() const;


        // Inherited from Image

        virtual void free();

        virtual int getWidth() const;

        virtual int getHeight() const;

        virtual Color getPixel(int x, int y);

        virtual void putPixel(int x, int y, const Color& color);

        virtual void convertToDisplayFormat();

    protected:
        GLuint mTextureHandle;
        unsigned int* mPixels;
        bool mAutoFree;
        int mWidth;
        int mHeight;
		int mTextureWidth;
		int mTextureHeight;

    };
}

#endif // end GCN_SDLutOGLIMAGE_HPP
