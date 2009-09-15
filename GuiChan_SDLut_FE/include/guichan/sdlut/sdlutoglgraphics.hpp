#ifndef GCN_SDLutOGLGRAPHICS_HPP
#define GCN_SDLutOGLGRAPHICS_HPP

#include "guichan/sdlut/sdlutdepends.hpp"

#include "guichan/color.hpp"
#include "guichan/graphics.hpp"
#include "guichan/platform.hpp"

namespace gcn
{
    /**
     * OpenGL implementation of the Graphics.
     */
    class GCN_EXTENSION_DECLSPEC SDLutOGLGraphics : public Graphics
    {
    public:

        /**
         * Constructor.
         */
        SDLutOGLGraphics();

        /**
         * Constructor.
		 *
		 * @param width the width of the logical drawing surface. Should be the
         *              same as the screen resolution.
		 *
		 * @param height the height ot the logical drawing surface. Should be
		 *               the same as the screen resolution.
		 */
        SDLutOGLGraphics(int width, int height);

		/**
		 * Destructor.
		 */
        virtual ~SDLutOGLGraphics();

        /**
         * Sets the target plane on where to draw.
		 *
		 * @param width the width of the logical drawing surface. Should be the
		 *              same as the screen resolution.
		 * @param height the height ot the logical drawing surface. Should be
		 *               the same as the screen resolution.
         */
        virtual void setTargetPlane(int width, int height);


		// Inherited from Graphics

        virtual void _beginDraw();

        virtual void _endDraw();

        virtual bool pushClipArea(Rectangle area);

        virtual void popClipArea();

		///**
		// * Only call Graphics::drawImage(gcn::Image *, int, int)
		// */
        //virtual void drawImage(const Image* image, int dstX, int dstY);

        virtual void drawImage(const Image* image,
                               int srcX,
                               int srcY,
                               int dstX,
                               int dstY,
                               int width,
                               int height);

        virtual void drawPoint(int x, int y);

        virtual void drawLine(int x1, int y1, int x2, int y2);

        virtual void drawRectangle(const Rectangle& rectangle);

        virtual void fillRectangle(const Rectangle& rectangle);

        virtual void setColor(const gcn::Color& color);

		virtual const gcn::Color& getColor() const;

    protected:
        int mWidth, mHeight;
		bool mAlpha;
        Color mColor;
    };
}

#endif // end GCN_SDLutOGLGRAPHICS_HPP
