
#include "guichan/sdlut/sdlutoglimage.hpp"

#include "guichan/exception.hpp"

namespace gcn
{
const SDLut::RGBAColor SDLutOGLImage::magicPink = SDLut::RGBAColor(255,0,255,255);

SDLutOGLImage::SDLutOGLImage(const unsigned int* pixels, int width, int height, const SDLut::RGBAColor& ColorKey)
{
    mAutoFree = true;

    mWidth = width;
    mHeight = height;
    mTextureWidth = 1, mTextureHeight = 1;

    while (mTextureWidth < mWidth)
    {
        mTextureWidth *= 2;
    }

    while (mTextureHeight < mHeight)
    {
        mTextureHeight *= 2;
    }

    // Create a new pixel array and copy the pixels into it
    mPixels = new unsigned int[mTextureWidth * mTextureHeight];

    //Color key to unsigned int
#if (SDL_BYTE_ORDER == SDL_BIG_ENDIAN)
//		std::cout << "Big endian" << std::endl;
    unsigned int iColorKey = ColorKey.getA() | ColorKey.getB() << 8 | ColorKey.getG() << 16 | ColorKey.getR() << 24;
#else
//		std::cout << "Little endian" << std::endl;
    unsigned int iColorKey = ColorKey.getR() | ColorKey.getG() << 8 | ColorKey.getB() << 16 | ColorKey.getA() << 24;
#endif

#ifdef _DEBUG
    std::cout << " ColorKey = " << std::hex << iColorKey << std::endl;
#endif

    unsigned int c = 0x00000000;

#ifdef _DEBUG
    std::cout << " Pixel (1,1) " << std::hex << pixels[1 + 1 * mWidth] << std::endl;
#endif

    for (int y = 0; y < mTextureHeight; y++)
    {
        for (int x = 0; x < mTextureWidth; x++)
        {
            if (x < mWidth && y < mHeight)
            {
                c = pixels[x + y * mWidth];

                //ColorKey to transparent
                if (c == iColorKey)
                {
                    c = 0x00000000; //0xff000000; //WE WANT THE CK TO BE TRANSPARENT !
                    //on linux opengl :
                    //0xXX000000 -> alpha -> 0 transparent, ff opaque
                    //0x00XX0000 -> blue
                    //0x0000XX00 -> green
                    //0x000000XX -> red

                }

                mPixels[x + y * mTextureWidth] = c;
            }
            else
            {
                mPixels[x + y * mTextureWidth] = 0x00000000;
            }
        }
    }
}

SDLutOGLImage::SDLutOGLImage(GLuint textureHandle, int width, int height, bool autoFree)
{
    mTextureHandle = textureHandle;
    mAutoFree = autoFree;
    mPixels = NULL;

    mWidth = width;
    mHeight = height;
    mTextureWidth = 1, mTextureHeight = 1;

    while (mTextureWidth < mWidth)
    {
        mTextureWidth *= 2;
    }

    while (mTextureHeight < mHeight)
    {
        mTextureHeight *= 2;
    }
}

SDLutOGLImage::~SDLutOGLImage()
{
    if (mAutoFree)
    {
        free();
    }
}

GLuint SDLutOGLImage::getTextureHandle() const
{
    return mTextureHandle;
}

int SDLutOGLImage::getTextureWidth() const
{
    return mTextureWidth;
}

int SDLutOGLImage::getTextureHeight() const
{
    return mTextureHeight;
}

void SDLutOGLImage::free()
{
    if (mPixels == NULL)
    {
        glDeleteTextures(1, &mTextureHandle);
    }
    else
    {
        delete[] mPixels, mPixels = NULL;
    }
}

int SDLutOGLImage::getWidth() const
{
    return mWidth;
}

int SDLutOGLImage::getHeight() const
{
    return mHeight;
}

Color SDLutOGLImage::getPixel(int x, int y)
{
    if (mPixels == NULL)
    {
        throw GCN_EXCEPTION("Image has been converted to display format");
    }

    if (x < 0 || x >= mWidth || y < 0 || y >= mHeight)
    {
        throw GCN_EXCEPTION("Coordinates outside of the image");
    }

    unsigned int c = mPixels[x + y * mTextureWidth];

#if (SDL_BYTE_ORDER == SDL_BIG_ENDIAN)
    unsigned char r = (c >> 24) & 0xff;
    unsigned char g = (c >> 16) & 0xff;
    unsigned char b = (c >> 8) & 0xff;
    unsigned char a = c & 0xff;
#else
    unsigned char a = (c >> 24) & 0xff;
    unsigned char b = (c >> 16) & 0xff;
    unsigned char g = (c >> 8) & 0xff;
    unsigned char r = c & 0xff;
#endif

    return Color(r, g, b, a);
}

void SDLutOGLImage::putPixel(int x, int y, const Color& color)
{
    std::cout << " putpixels " ;
    if (mPixels == NULL)
    {
        throw GCN_EXCEPTION("Image has been converted to display format");
    }

    if (x < 0 || x >= mWidth || y < 0 || y >= mHeight)
    {
        throw GCN_EXCEPTION("Coordinates outside of the image");
    }

#if ( SDL_BYTE_ORDER == SDL_BIG_ENDIAN )
    unsigned int c = color.a | color.b << 8 | color.g << 16 | color.r << 24;
#else
    unsigned int c = color.r | color.g << 8 | color.b << 16 | color.a << 24;
#endif

    mPixels[x + y * mTextureWidth] = c;
}

void SDLutOGLImage::convertToDisplayFormat()
{
    if (mPixels == NULL)
    {
        throw GCN_EXCEPTION("Image has already been converted to display format");
    }

    glGenTextures(1, &mTextureHandle);
    glBindTexture(GL_TEXTURE_2D, mTextureHandle);

    //TO FIX : Order of pixel color opposite of what it should be... need to investigate
    glTexImage2D(GL_TEXTURE_2D, 0, 4, mTextureWidth, mTextureHeight, 0, GL_ABGR_EXT, GL_UNSIGNED_BYTE, mPixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    delete[] mPixels, mPixels = NULL;

    GLenum error = glGetError();
    if (error)
    {
        std::string errmsg;
        switch (error)
        {
        case GL_INVALID_ENUM:
            errmsg = "GL_INVALID_ENUM";
            break;

        case GL_INVALID_VALUE:
            errmsg = "GL_INVALID_VALUE";
            break;

        case GL_INVALID_OPERATION:
            errmsg = "GL_INVALID_OPERATION";
            break;

        case GL_STACK_OVERFLOW:
            errmsg = "GL_STACK_OVERFLOW";
            break;

        case GL_STACK_UNDERFLOW:
            errmsg = "GL_STACK_UNDERFLOW";
            break;

        case GL_OUT_OF_MEMORY:
            errmsg = "GL_OUT_OF_MEMORY";
            break;
        }

        throw GCN_EXCEPTION(std::string("Unable to convert to OpenGL display format, glGetError said: ") + errmsg);
    }
}
}

