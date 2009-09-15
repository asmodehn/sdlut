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

void SDLutGraphics::setTarget(SDLut::BaseSurface* target)
{
    mTarget = target;
}

SDLut::BaseSurface* SDLutGraphics::getTarget() const
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
    popClipArea();
}


bool SDLutGraphics::pushClipArea(Rectangle area)
{
    SDLut::Rect rect;
    bool result = Graphics::pushClipArea(area);

    const ClipRectangle& carea = mClipStack.top();
    rect.setx( carea.x );
    rect.sety( carea.y );
    rect.setw( carea.width );
    rect.seth( carea.height );

    mTarget->setClipRect(rect);

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
    SDLut::Rect rect;
    rect.setx( carea.x );
    rect.sety( carea.y );
    rect.setw( carea.width );
    rect.seth( carea.height );

    mTarget->setClipRect(rect);
    //SDL_SetClipRect(mTarget, &rect);
}



void SDLutGraphics::drawImage(const Image* image,
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

    SDLut::Rect src;
    SDLut::Rect dst;
    src.setx( srcX );
    src.sety( srcY );
    src.setw( width );
    src.seth( height );
    dst.setx( dstX + top.xOffset );
    dst.sety( dstY + top.yOffset );

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

        mTarget->lock();
        for (y = y1; y < y2; y++)
        {
            for (x = x1; x < x2; x++)
            {
                SDLutputPixelAlpha(mTarget, x, y, mColor);
            }
        }
        mTarget->unlock();
        //SDL_UnlockSurface(mTarget);

    }
    else
    {
        SDLut::Rect rect;
        rect.setx( area.x );
        rect.sety( area.y );
        rect.setw( area.width );
        rect.seth( area.height );


        mTarget->fill(
            SDLut::RGBAColor( (unsigned char)mColor.r, (unsigned char)mColor.g, (unsigned char)mColor.b, (unsigned char)mColor.a )
            , rect );

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

    if (mAlpha)
    {
        SDLutputPixelAlpha(mTarget, x, y, mColor);
    }
    else
    {
        SDLutputPixel(mTarget, x, y, mColor);
    }
}

void SDLutGraphics::drawHLine(int x1, int y, int x2)
{
    drawLine(x1, y, x2, y);

    /* if (mClipStack.empty())
     {
         throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
     }

     const ClipRectangle& top = mClipStack.top();

     x1 += top.xOffset;
     y += top.yOffset;
     x2 += top.xOffset;

     if (y < top.y || y >= top.y + top.height)
     {
         return;
     }

     if (x1 > x2)
     {
         x1 ^= x2;
         x2 ^= x1;
         x1 ^= x2;
     }

     if (top.x > x1)
     {
         if (top.x > x2)
         {
             return;
         }

         x1 = top.x;
     }

     if (top.x + top.width <= x2)
     {
         if (top.x + top.width <= x1)
         {
             return;
         }

         x2 = top.x + top.width -1;
     }

     int bpp = mTarget->getBPP();

     SDL_LockSurface(mTarget);

     Uint8 *p = (Uint8 *)mTarget->pixels + y * mTarget->pitch + x1 * bpp;

     Uint32 pixel = SDL_MapRGB(mTarget->format,
                               mColor.r,
                               mColor.g,
                               mColor.b);
     switch(bpp)
     {
         case 1:
             for (;x1 <= x2; ++x1)
             {
                 *(p++) = pixel;
             }
             break;

         case 2:
         {
             Uint16* q = (Uint16*)p;
             for (;x1 <= x2; ++x1)
             {
                 *(q++) = pixel;
             }
             break;
         }
         case 3:
             if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
             {
                 for (;x1 <= x2; ++x1)
                 {
                     p[0] = (pixel >> 16) & 0xff;
                     p[1] = (pixel >> 8) & 0xff;
                     p[2] = pixel & 0xff;
                     p += 3;
                 }
             }
             else
             {
                 for (;x1 <= x2; ++x1)
                 {
                     p[0] = pixel & 0xff;
                     p[1] = (pixel >> 8) & 0xff;
                     p[2] = (pixel >> 16) & 0xff;
                     p += 3;
                 }
             }
             break;

         case 4:
         {
             Uint32* q = (Uint32*)p;
             for (;x1 <= x2; ++x1)
             {
                 if (mAlpha)
                 {
                     *q = SDLutAlpha32(pixel,*q,mColor.a);
                     q++;
                 }
                 else
                 {
                     *(q++) = pixel;
                 }
             }
             break;
         }

     } // end switch

     SDL_UnlockSurface(mTarget);*/
}

void SDLutGraphics::drawVLine(int x, int y1, int y2)
{
    drawLine(x, y1, x, y2);

    /*if (mClipStack.empty())
    {
        throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
    }

    const ClipRectangle& top = mClipStack.top();

    x += top.xOffset;
    y1 += top.yOffset;
    y2 += top.yOffset;

    if (x < top.x || x >= top.x + top.width)
    {
        return;
    }

    if (y1 > y2)
    {
        y1 ^= y2;
        y2 ^= y1;
        y1 ^= y2;
    }

    if (top.y > y1)
    {
        if (top.y > y2)
        {
            return;
        }

        y1 = top.y;
    }

    if (top.y + top.height <= y2)
    {
        if (top.y + top.height <= y1)
        {
            return;
        }

        y2 = top.y + top.height - 1;
    }

    int bpp = mTarget->format->BytesPerPixel;

    SDL_LockSurface(mTarget);

    Uint8 *p = (Uint8 *)mTarget->pixels + y1 * mTarget->pitch + x * bpp;

    Uint32 pixel = SDL_MapRGB(mTarget->format, mColor.r, mColor.g, mColor.b);

    switch(bpp)
    {
      case 1:
          for (;y1 <= y2; ++y1)
          {
              *p = pixel;
              p += mTarget->pitch;
          }
          break;

      case 2:
          for (;y1 <= y2; ++y1)
          {
              *(Uint16*)p = pixel;
              p += mTarget->pitch;
          }
          break;

      case 3:
          if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
          {
              for (;y1 <= y2; ++y1)
              {
                  p[0] = (pixel >> 16) & 0xff;
                  p[1] = (pixel >> 8) & 0xff;
                  p[2] = pixel & 0xff;
                  p += mTarget->pitch;
              }
          }
          else
          {
              for (;y1 <= y2; ++y1)
              {
                  p[0] = pixel & 0xff;
                  p[1] = (pixel >> 8) & 0xff;
                  p[2] = (pixel >> 16) & 0xff;
                  p += mTarget->pitch;
              }
          }
          break;

      case 4:
          for (;y1 <= y2; ++y1)
          {
              if (mAlpha)
              {
                  *(Uint32*)p = SDLutAlpha32(pixel,*(Uint32*)p,mColor.a);
              }
              else
              {
                  *(Uint32*)p = pixel;
              }
              p += mTarget->pitch;
          }
          break;

    } // end switch

    SDL_UnlockSurface(mTarget);*/
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
                    if (mAlpha)
                    {
                        SDLutputPixelAlpha(mTarget, x, y, mColor);
                    }
                    else
                    {
                        SDLutputPixel(mTarget, x, y, mColor);
                    }
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
                    if (mAlpha)
                    {
                        SDLutputPixelAlpha(mTarget, x, y, mColor);
                    }
                    else
                    {
                        SDLutputPixel(mTarget, x, y, mColor);
                    }
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
                    if (mAlpha)
                    {
                        SDLutputPixelAlpha(mTarget, x, y, mColor);
                    }
                    else
                    {
                        SDLutputPixel(mTarget, x, y, mColor);
                    }
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
                    if (mAlpha)
                    {
                        SDLutputPixelAlpha(mTarget, x, y, mColor);
                    }
                    else
                    {
                        SDLutputPixel(mTarget, x, y, mColor);
                    }
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

    mAlpha = color.a != 255;
}

const gcn::Color& SDLutGraphics::getColor() const
{
    return mColor;
}

void SDLutGraphics::drawSDLutSurface(SDLut::BaseSurface& surface,
                                     SDLut::Rect& source,
                                     SDLut::Rect& destination)
{
    if (mClipStack.empty())
    {
        throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
    }

    const ClipRectangle& top = mClipStack.top();

    destination.setx( top.xOffset + destination.getx() );
    destination.sety( top.yOffset + destination.gety() );

    mTarget->blit( surface, destination, source);
}
}
