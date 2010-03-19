/*
Made by XorfacX
*/
#ifndef GCN_SDLutGRAPHICS_HPP
#define GCN_SDLutGRAPHICS_HPP

#include "sdlutdepends.hpp"

#include "guichan/color.hpp"
#include "guichan/graphics.hpp"
#include "guichan/platform.hpp"

namespace gcn
{
class Image;
class Rectangle;

/**
 * SDLut implementation of the Graphics.
 */
class GCN_EXTENSION_DECLSPEC SDLutGraphics : public Graphics
{
public:

    // Needed so that drawImage(gcn::Image *, int, int) is visible.
    using Graphics::drawImage;

    /**
     * Constructor.
     */
    SDLutGraphics();

    /**
     * Sets the target BaseSurface to draw to. The target can be any
     * BaseSurface. This funtion also pushes a clip areas corresponding to
     * the dimension of the target.
     *
     * @param target the target to draw to.
     */
    virtual void setTarget(video::ScreenBuffer* target);

    /**
     * Gets the target BaseSurface.
     *
     * @return the target BaseSurface.
     */
    virtual video::ScreenBuffer* getTarget() const;

    /**
     * Draws a BaseSurface on the target surface. Normaly you'll
     * use drawImage
     *
     * NOTE: The clip areas will be taken into account.
     */
	virtual void drawSDLutSurface(video::Image& surface,
                                  video::Rect& source,
                                  video::Rect& destination);


    // Inherited from Graphics

    virtual void _beginDraw();

    virtual void _endDraw();

    virtual bool pushClipArea(Rectangle area);

    virtual void popClipArea();

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

    virtual void setColor(const Color& color);

    virtual const gcn::Color& getColor() const;

protected:
    /**
     * Draws a horizontal line.
     *
     * @param x1 the start coordinate of the line.
     * @param y the y coordinate of the line.
     * @param x2 the end coordinate of the line.
     */
    virtual void drawHLine(int x1, int y, int x2);

    /**
     * Draws a vertical line.
     *
     * @param x the x coordinate of the line.
     * @param y1 the start coordinate of the line.
     * @param y2 the end coordinate of the line.
     */
    virtual void drawVLine(int x, int y1, int y2);

    video::ScreenBuffer* mTarget;
    gcn::Color mColor;
    bool mAlpha;
};
}

#endif // end GCN_SDLutGRAPHICS_HPP
