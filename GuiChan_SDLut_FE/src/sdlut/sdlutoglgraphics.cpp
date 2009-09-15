#include "guichan/sdlut/sdlutoglgraphics.hpp"

#if defined (_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#if defined (__amigaos4__)
#include <mgl/gl.h>
#define glVertex3i glVertex3f
#elif defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "guichan/exception.hpp"
#include "guichan/image.hpp"
#include "guichan/sdlut/sdlutoglimage.hpp"

namespace gcn
{
    SDLutOGLGraphics::SDLutOGLGraphics()
    {
        setTargetPlane(640, 480);
        mAlpha = false;
    }

    SDLutOGLGraphics::SDLutOGLGraphics(int width, int height)
    {
        setTargetPlane(width, height);
		mAlpha = false;
    }

    SDLutOGLGraphics::~SDLutOGLGraphics()
    {

    }

    void SDLutOGLGraphics::_beginDraw()
    {
        glPushAttrib(
            GL_COLOR_BUFFER_BIT |
            GL_CURRENT_BIT |
            GL_DEPTH_BUFFER_BIT |
            GL_ENABLE_BIT |
            GL_FOG_BIT |
            GL_LIGHTING_BIT |
            GL_LINE_BIT |
            GL_POINT_BIT |
            GL_POLYGON_BIT |
            GL_SCISSOR_BIT |
            GL_STENCIL_BUFFER_BIT |
            GL_TEXTURE_BIT |
            GL_TRANSFORM_BIT |
            GL_POINT_BIT |
            GL_LINE_BIT
            );

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glMatrixMode(GL_TEXTURE);
        glPushMatrix();
        glLoadIdentity();

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        
        glOrtho(0.0, (double)mWidth, (double)mHeight, 0.0, -1.0, 1.0);

        glDisable(GL_LIGHTING);
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_TEXTURE_2D);

        glEnable(GL_SCISSOR_TEST);
        glPointSize(1.0);
        glLineWidth(1.0);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        pushClipArea(Rectangle(0, 0, mWidth, mHeight));
    }

    void SDLutOGLGraphics::_endDraw()
    {
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glMatrixMode(GL_TEXTURE);
        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        glPopAttrib();

        popClipArea();
    }

    bool SDLutOGLGraphics::pushClipArea(Rectangle area)
    {
        bool result = Graphics::pushClipArea(area);

        glScissor(mClipStack.top().x,
                  mHeight - mClipStack.top().y - mClipStack.top().height,
                  mClipStack.top().width,
                  mClipStack.top().height);

        return result;
    }

    void SDLutOGLGraphics::popClipArea()
    {
        Graphics::popClipArea();

        if (mClipStack.empty())
        {
            return;
        }

        glScissor(mClipStack.top().x,
                  mHeight - mClipStack.top().y - mClipStack.top().height,
                  mClipStack.top().width,
                  mClipStack.top().height);
    }

    void SDLutOGLGraphics::setTargetPlane(int width, int height)
    {
        mWidth = width;
        mHeight = height;
    }

	//void SDLutOGLGraphics::drawImage(const Image* image, int dstX, int dstY)
    //{
	//	Graphics::drawImage(image, dstX, dstY);
	//}

    void SDLutOGLGraphics::drawImage(const Image* image, int srcX, int srcY, int dstX, int dstY, int width, int height)
    {
		const SDLutOGLImage* srcImage = dynamic_cast<const SDLutOGLImage*>(image);

        if (srcImage == NULL)
        {
            throw GCN_EXCEPTION("Trying to draw an image of unknown format, must be an OpenGLImage.");
        }

        if (mClipStack.empty())
        {
            throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
        }

        const ClipRectangle& top = mClipStack.top();

        dstX += top.xOffset;
        dstY += top.yOffset;

        // Find OpenGL texture coordinates
        float texX1 = srcX / (float)srcImage->getTextureWidth();
        float texY1 = srcY / (float)srcImage->getTextureHeight();
        float texX2 = (srcX+width) / (float)srcImage->getTextureWidth();
        float texY2 = (srcY+height) / (float)srcImage->getTextureHeight();

        glBindTexture(GL_TEXTURE_2D, srcImage->getTextureHandle());

        glEnable(GL_TEXTURE_2D);

        // Check if blending already is enabled
        if (!mAlpha)
        {
            glEnable(GL_BLEND);
        }

        // Draw a textured quad -- the image
        glBegin(GL_QUADS);
        glTexCoord2f(texX1, texY1);
        glVertex3i(dstX, dstY, 0);

        glTexCoord2f(texX1, texY2);
        glVertex3i(dstX, dstY + height, 0);

        glTexCoord2f(texX2, texY2);
        glVertex3i(dstX + width, dstY + height, 0);

        glTexCoord2f(texX2, texY1);
        glVertex3i(dstX + width, dstY, 0);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        // Don't disable blending if the color has alpha
        if (!mAlpha)
        {
            glDisable(GL_BLEND);
        }
    }

    void SDLutOGLGraphics::drawPoint(int x, int y)
    {
        if (mClipStack.empty())
        {
            throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
        }

        const ClipRectangle& top = mClipStack.top();

        x += top.xOffset;
        y += top.yOffset;

        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }

    void SDLutOGLGraphics::drawLine(int x1, int y1, int x2, int y2)
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

        glBegin(GL_LINES);
        glVertex2f(x1 + 0.375f,
                   y1 + 0.375f);
        glVertex2f(x2 + 1.0f - 0.375f,
                   y2 + 1.0f - 0.375f);
        glEnd();

        glBegin(GL_POINTS);
        glVertex2f(x2 + 1.0f - 0.375f,
                   y2 + 1.0f - 0.375f);
        glEnd();

        glBegin(GL_POINTS);
        glVertex2f(x1 + 0.375f,
                   y1 + 0.375f);
        glEnd();

        
    }

    void SDLutOGLGraphics::drawRectangle(const Rectangle& rectangle)
    {
        if (mClipStack.empty())
        {
            throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
        }

        const ClipRectangle& top = mClipStack.top();
        
        glBegin(GL_LINE_LOOP);
        glVertex2f( static_cast<GLfloat>(rectangle.x + top.xOffset + 1.0f), static_cast<GLfloat>(rectangle.y + top.yOffset) );
        glVertex2f( static_cast<GLfloat>(rectangle.x + rectangle.width + top.xOffset),  static_cast<GLfloat>(rectangle.y + top.yOffset + 0.375f) );
        glVertex2f( static_cast<GLfloat>(rectangle.x + rectangle.width + top.xOffset),  static_cast<GLfloat>(rectangle.y + rectangle.height + top.yOffset  - 1.0f) );
        glVertex2f( static_cast<GLfloat>(rectangle.x + top.xOffset),  static_cast<GLfloat>(rectangle.y + rectangle.height + top.yOffset - 1.0f) );
        glEnd();
    }

    void SDLutOGLGraphics::fillRectangle(const Rectangle& rectangle)
    {
        if (mClipStack.empty())
        {
            throw GCN_EXCEPTION("Clip stack is empty, perhaps you called a draw funtion outside of _beginDraw() and _endDraw()?");
        }

        const ClipRectangle& top = mClipStack.top();

        glBegin(GL_QUADS);
        glVertex2i(rectangle.x + top.xOffset, rectangle.y + top.yOffset);
        glVertex2i(rectangle.x + rectangle.width + top.xOffset, rectangle.y + top.yOffset);
        glVertex2i(rectangle.x + rectangle.width + top.xOffset, rectangle.y + rectangle.height + top.yOffset);
        glVertex2i(rectangle.x + top.xOffset, rectangle.y + rectangle.height + top.yOffset);
        glEnd();
    }

    void SDLutOGLGraphics::setColor(const gcn::Color& color)
    {
        mColor = color;
        glColor4ub(color.r, color.g, color.b, color.a);

        mAlpha = color.a != 255;

        if (mAlpha)
        {
            glEnable(GL_BLEND);
        }
    }

	const gcn::Color& SDLutOGLGraphics::getColor() const
    {
        return mColor;
    }
}
