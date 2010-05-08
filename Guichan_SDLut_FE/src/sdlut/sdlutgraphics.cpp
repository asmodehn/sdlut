/*
Made by XorfacX
*/

/*
 * For comments regarding functions please see the header file.
 */

#include "guichan/sdlut/sdlutgraphics.hpp"

#include "guichan/exception.hpp"
#include "guichan/font.hpp"
#include "guichan/image.hpp"
#include "guichan/sdlut/sdlutimage.hpp"
#include "guichan/sdlut/sdlutpixel.hpp"
#include "guichan/sdlut/sdlutimageloader.hpp" //for magicPink

// For some reason an old version of MSVC did not like std::abs,
// so we added this macro.
#ifndef ABS
#define ABS(x) ((x)<0?-(x):(x))
#endif

namespace gcn
{

SDLutGraphics::SDLutGraphics()
{
    mAlpha = false;
}

void SDLutGraphics::setTarget(video::ScreenBuffer* target)
{
    mTarget = target;

    //if (!Image4Pixels.get())
    {
        Image4Pixels.reset( new video::Image(mTarget->getWidth(), mTarget->getHeight(), mTarget->getBPP(), false, false ) );
        //Image4Pixels->resetColorKey(true, SDLutImageLoader::magicPink);
    }

    //Image4Pixels->resize(mTarget->getWidth(), mTarget->getHeight());
    Image4PixelsDim = video::Rect(0, 0, Image4Pixels->getWidth(), Image4Pixels->getHeight());

    //Image4Pixels->fill(SDLutImageLoader::magicPink);
}

video::ScreenBuffer* SDLutGraphics::getTarget() const
{
    return mTarget;
}


// Inherited from Graphics
void SDLutGraphics::_beginDraw()
{
    Rectangle area;
    area.x = 0;
    area.y = 0;
    area.width = mTarget->getWidth();
    area.height = mTarget->getHeight();
    pushClipArea(area);
}

void SDLutGraphics::_endDraw()
{
    tempImage4PixelsDim = Image4PixelsDim;
    mTarget->blit(*Image4Pixels.get(), tempImage4PixelsDim);

    popClipArea();
}


bool SDLutGraphics::pushClipArea(Rectangle area)
{

    bool result = Graphics::pushClipArea(area);

    const ClipRectangle& carea = mClipStack.top();

    video::Rect rect( carea.x, carea.y, carea.width, carea.height );

    mTarget->resetClipRect(rect);

    //SDL_SetClipRect(mTarget, &rect);

    return result;
}

void SDLutGraphics::popClipArea()
{
    Graphics::popClipArea();

    if (mClipStack.empty())
    {
        return;
    }

    const ClipRectangle& carea = mClipStack.top();
    video::Rect rect(carea.x, carea.y, carea.width, carea.height);

    mTarget->resetClipRect(rect);
}



void SDLutGraphics::drawImage(const gcn::Image* image,
                              int srcX,
                              int srcY,
                              int dstX,
                              int dstY,
                              int width,
                              int height)
{
    if (mClipStack.empty())
    {
        throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
    }

    const ClipRectangle& top = mClipStack.top();

    video::Rect src (srcX, srcY, width, height);
    video::Rect dst (dstX + top.xOffset, dstY + top.yOffset, width, height);
    /*src.setx( srcX );
    src.sety( srcY );
    src.setw( width );
    src.seth( height );
    dst.setx( dstX + top.xOffset );
    dst.sety( dstY + top.yOffset );*/

    const SDLutImage* srcImage = dynamic_cast<const SDLutImage*>(image);

    if (srcImage == NULL)
    {
        throw GCN_EXCEPTION("Trying to draw an image of unknown format, must be an SDLutImage.");
    }

    mTarget->blit(*(srcImage->getSurface()), dst, src);
    //SDL_BlitSurface(srcImage->getSurface(), &src, mTarget, &dst);
}

void SDLutGraphics::fillRectangle(const Rectangle& rectangle)
{
    if (mClipStack.empty())
    {
        throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
    }

    const ClipRectangle& top = mClipStack.top();

    Rectangle area = rectangle;
    area.x += top.xOffset;
    area.y += top.yOffset;

    if (!area.isIntersecting(top))
    {
        return;
    }

    if (mAlpha)
    {
        int x1 = area.x > top.x ? area.x : top.x;
        int y1 = area.y > top.y ? area.y : top.y;
        int x2 = area.x + area.width < top.x + top.width ? area.x + area.width : top.x + top.width;
        int y2 = area.y + area.height < top.y + top.height ? area.y + area.height : top.y + top.height;
        int x, y;

        for (y = y1; y < y2; y++)
        {
            for (x = x1; x < x2; x++)
            {
                SDLutputPixel(Image4Pixels.get(), x, y, mColor);
            }
        }
    }
    else
    {
        video::Rect rect(area.x, area.y, area.width, area.height);
        video::Color rgbacolor( (unsigned char)mColor.r, (unsigned char)mColor.g, (unsigned char)mColor.b, (unsigned char)mColor.a );

        //mTarget->fill(rgbacolor, rect );
        //Image4Pixels->fill(rgbacolor, rect );

    }
}

void SDLutGraphics::drawPoint(int x, int y)
{
    if (mClipStack.empty())
    {
        throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
    }

    const ClipRectangle& top = mClipStack.top();

    x += top.xOffset;
    y += top.yOffset;

    if (!top.isPointInRect(x,y))
        return;

    SDLutputPixel(Image4Pixels.get(), x, y, mColor);
}

void SDLutGraphics::drawHLine(int x1, int y, int x2)
{
    drawLine(x1, y, x2, y);
}

void SDLutGraphics::drawVLine(int x, int y1, int y2)
{
    drawLine(x, y1, x, y2);
}

void SDLutGraphics::drawRectangle(const Rectangle& rectangle)
{
    int x1 = rectangle.x;
    int x2 = rectangle.x + rectangle.width - 1;
    int y1 = rectangle.y;
    int y2 = rectangle.y + rectangle.height - 1;

    drawHLine(x1, y1, x2);
    drawHLine(x1, y2, x2);

    drawVLine(x1, y1, y2);
    drawVLine(x2, y1, y2);
}

void SDLutGraphics::drawLine(int x1, int y1, int x2, int y2)
{
    if (mClipStack.empty())
    {
        throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
    }

    const ClipRectangle& top = mClipStack.top();

    x1 += top.xOffset;
    y1 += top.yOffset;
    x2 += top.xOffset;
    y2 += top.yOffset;

    // Draw a line with Bresenham

    int dx = ABS(x2 - x1);
    int dy = ABS(y2 - y1);

    if (dx > dy)
    {
        if (x1 > x2)
        {
            // swap x1, x2
            x1 ^= x2;
            x2 ^= x1;
            x1 ^= x2;

            // swap y1, y2
            y1 ^= y2;
            y2 ^= y1;
            y1 ^= y2;
        }

        if (y1 < y2)
        {
            int y = y1;
            int p = 0;

            for (int x = x1; x <= x2; x++)
            {
                if (top.isPointInRect(x, y))
                {
                    SDLutputPixel(Image4Pixels.get(), x, y, mColor);
                }

                p += dy;

                if (p * 2 >= dx)
                {
                    y++;
                    p -= dx;
                }
            }
        }
        else
        {
            int y = y1;
            int p = 0;

            for (int x = x1; x <= x2; x++)
            {
                if (top.isPointInRect(x, y))
                {
                    SDLutputPixel(Image4Pixels.get(), x, y, mColor);
                }

                p += dy;

                if (p * 2 >= dx)
                {
                    y--;
                    p -= dx;
                }
            }
        }
    }
    else
    {
        if (y1 > y2)
        {
            // swap y1, y2
            y1 ^= y2;
            y2 ^= y1;
            y1 ^= y2;

            // swap x1, x2
            x1 ^= x2;
            x2 ^= x1;
            x1 ^= x2;
        }

        if (x1 < x2)
        {
            int x = x1;
            int p = 0;

            for (int y = y1; y <= y2; y++)
            {
                if (top.isPointInRect(x, y))
                {
                    SDLutputPixel(Image4Pixels.get(), x, y, mColor);
                }

                p += dx;

                if (p * 2 >= dy)
                {
                    x++;
                    p -= dy;
                }
            }
        }
        else
        {
            int x = x1;
            int p = 0;

            for (int y = y1; y <= y2; y++)
            {
                if (top.isPointInRect(x, y))
                {
                    SDLutputPixel(Image4Pixels.get(), x, y, mColor);
                }

                p += dx;

                if (p * 2 >= dy)
                {
                    x--;
                    p -= dy;
                }
            }
        }
    }
}

void SDLutGraphics::setColor(const gcn::Color& color)
{
    mColor = color;

    mAlpha = (color.a < 255);
}

const gcn::Color& SDLutGraphics::getColor() const
{
    return mColor;
}

void SDLutGraphics::drawSDLutSurface(video::Image& surface,
                                     video::Rect& source,
                                     video::Rect& destination)
{
    if (mClipStack.empty())
    {
        throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
    }

    const ClipRectangle& top = mClipStack.top();

    destination.resetx( top.xOffset + destination.getx() );
    destination.resety( top.yOffset + destination.gety() );

    mTarget->blit( surface, destination, source);
}

} //gcn
