#include "Video/internal/OpenGL/SDLGLSurface.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{


////////////////private Conversion Constructor
GLSurface::GLSurface(SDL_Surface * s) throw (std::logic_error)
try :
    RGBSurface(s), modified(false), textureWidth(0), textureHeight(0), texturePixels(NULL)
{

#ifdef DEBUG
    Log << nl << "GLSurface::GLSurface(" << s << ") called.";
#endif


    computeGLWidthHeight();
    convertPixels();

#ifdef DEBUG

    Log << nl << "GLSurface::GLSurface(" << s << ") done -> " << ptm_surf.get() << " created.";
#endif

}
catch (std::exception &e)
{
    Log << nl << "Exception catched in GLSurface Constructor !!!"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

GLSurface::GLSurface(std::auto_ptr<SDL_Surface> s) throw (std::logic_error)
try :
    RGBSurface(s), modified(false), textureWidth(0), textureHeight(0), texturePixels(NULL)
{

#ifdef DEBUG
    Log << nl << "GLSurface::GLSurface(" << s.get() << ") called.";
#endif

    computeGLWidthHeight();
    convertPixels();

#ifdef DEBUG

    Log << nl << "GLSurface::GLSurface(" << s.get() << ") done -> " << ptm_surf.get() << " created.";
#endif

}
catch (std::exception &e)
{
    Log << nl << "Exception catched in GLSurface Constructor !!!"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}


////////////public Conversion constructor
GLSurface::GLSurface( const RGBSurface & rgbs) throw (std::logic_error)
try :
    RGBSurface( rgbs ), modified(false), textureWidth(0), textureHeight(0), texturePixels(NULL)
{

#ifdef DEBUG
    Log << nl << "GLSurface::GLSurface(" << &rgbs << ") called.";
#endif


    computeGLWidthHeight();
    convertPixels();

#ifdef DEBUG

    Log << nl << "GLSurface::GLSurface(" << &rgbs << ") done -> " << ptm_surf.get() << " created.";
#endif

}
catch (std::exception &e)
{
    Log << nl << "Exception catched in GLSurface Constructor !!!"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

////////////Coopy Constructor
GLSurface::GLSurface( const GLSurface & gls) throw (std::logic_error)
try :
    RGBSurface( gls ), modified(false), textureWidth(0), textureHeight(0), texturePixels(NULL)
{

#ifdef DEBUG
    Log << nl << "GLSurface::GLSurface(" << &gls << ") called.";
#endif


    computeGLWidthHeight();
    convertPixels();

#ifdef DEBUG

    Log << nl << "GLSurface::GLSurface(" << &gls << ") done -> " << ptm_surf.get() << " created.";
#endif

}
catch (std::exception &e)
{
    Log << nl << "Exception catched in GLSurface Constructor !!!"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}


GLSurface::GLSurface( int width, int height, int bpp, bool alpha , bool colorkey , bool hardware,
                      unsigned long r_mask ,
                      unsigned long g_mask ,
                      unsigned long b_mask ,
                      unsigned long a_mask
                    ) throw (std::logic_error)
try :
    RGBSurface(width, height, bpp, alpha, colorkey, hardware, r_mask, g_mask, b_mask, a_mask), modified(false), textureWidth(0), textureHeight(0), texturePixels(NULL)
{

#ifdef DEBUG
    Log << nl << "GLSurface::GLSurface(" << width <<", " << height << ", " << bpp << ", "<< alpha << ", " << colorkey << ", " << hardware << "... ) called.";
#endif

    computeGLWidthHeight();
    convertPixels();

#ifdef DEBUG
    Log << nl << "GLSurface::GLSurface(" << width <<", " << height << ", " << bpp << ", "<< alpha << ", " << colorkey << ", " << hardware << "...) done -> " << ptm_surf.get() << " created.";
#endif

}
catch (std::exception &e)
{
    Log << nl << "Exception catched in GLSurface Constructor !!!"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

GLSurface::GLSurface( void * pixeldata, int depth, int pitch, int width, int height,
                      unsigned long r_mask ,
                      unsigned long g_mask ,
                      unsigned long b_mask ,
                      unsigned long a_mask
                    ) throw (std::logic_error)
try	:
    RGBSurface(pixeldata, depth, pitch, width, height, r_mask, g_mask, b_mask, a_mask), modified(false),textureWidth(0), textureHeight(0), texturePixels(NULL)
{
#ifdef DEBUG
    Log << nl << "GLSurface::GLSurface(" << pixeldata << ", " << depth << ", " << pitch << ", " << width <<", " << height << "... ) called.";
#endif

    computeGLWidthHeight();
    convertPixels();
#ifdef DEBUG
    Log << nl << "GLSurface::GLSurface(" << pixeldata << ", " << depth << ", " << pitch << ", " << width <<", " << height << "...) done -> " << ptm_surf.get() << " created.";
#endif

}
catch (std::exception &e)
{
    Log << nl << "Exception catched in GLSurface Constructor !!!"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

GLSurface::GLSurface(RWOps & rwops) throw (std::logic_error)
try : RGBSurface(rwops), modified(false),textureWidth(0), textureHeight(0), texturePixels(NULL)
{
#ifdef DEBUG
    Log << nl << "GLSurface::GLSurface(" << rwops << "... ) called.";
#endif

    computeGLWidthHeight();
    convertPixels();
#ifdef DEBUG
    Log << nl << "GLSurface::GLSurface(" << rwops << "...) done -> " << ptm_surf.get() << " created.";
#endif

}
catch (std::exception &e)
{
    Log << nl << "Exception catched in GLSurface Constructor !!!"  << nl <<
    e.what() << nl << GetError() << std::endl;
    //TODO : much more explicit error message...
}

void GLSurface::computeGLWidthHeight()
{
    if ( getWidth() == 0 && getHeight() == 0 ) return;
    textureWidth = 1;
    textureHeight = 1;
    while ( textureWidth < getWidth() ) textureWidth *= 2;
    while ( textureHeight < getHeight() ) textureHeight *= 2;
}

void GLSurface::convertPixels()
{
    //Todo : We need to here convert the surface to proper BPP to match video surface
    //or OpenGL will not display it
    RGBSurface::convertToDisplayFormat();
    //but we re not completely ready yet
    optimised = false;

    if ( texturePixels != NULL ) delete texturePixels, texturePixels=NULL;
    texturePixels = new unsigned int[ textureWidth * textureHeight ];
    PixelColor c,ckey = 0x00000000;
    if ( isSRCColorKeyset() )
    {
        ckey = getColorKey();
    }
    for (unsigned int y = 0; y < textureHeight; y++)
    {
        for (unsigned int x = 0; x < textureWidth; x++)
        {
            if (x < getWidth() && y < getHeight())
            {
                c = getpixel(x, y);

                //ColorKey to transparent
                if ( ckey == c )
                {
                    texturePixels[x + y * textureWidth] = 0x00000000;
                }

                //BUG here : TOFIX
                texturePixels[x + y * textureWidth] = c;
            }
            else
            {
                //filling with transparent 0s...
                texturePixels[x + y * textureWidth] = 0x00000000;
            }
        }
    }
}

GLSurface::~GLSurface()
{
    if ( texturePixels != NULL )
        delete[] texturePixels, texturePixels = NULL;
}

bool GLSurface::resize(int width, int height, bool keepcontent)
{
    //TODO : test and fix
    bool res = RGBSurface::resize(width, height, keepcontent);
    modified = true;
    return res;
}


unsigned int GLSurface::getTextureWidth()
{
    return textureWidth;
}

unsigned int GLSurface::getTextureHeight()
{
    return textureHeight;
}

bool GLSurface::fill (const PixelColor& color, Rect dest_rect)
{
    //easy way, but not really optimised.
    //we could do it here as well, using the opengl color format...
    modified = true;
    return RGBSurface::fill(color, dest_rect);
}

bool GLSurface::blit (const RGBSurface& src, Rect& dest_rect, const Rect& src_rect)
{
    modified = true;
    return RGBSurface::blit(src, dest_rect, src_rect);
}

bool GLSurface::convertToDisplayFormat()
{
    if (texturePixels == NULL)
    {
        //No data to convert
        // Problem, convert Pixels should have been called before if there was any modification...
        // Or no conversion is actually needed...
        return false;
    }

    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);

    glTexImage2D(GL_TEXTURE_2D, 0, 4, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturePixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    delete[] texturePixels, texturePixels = NULL;
    //TODO : set SDLut Error string to GLerror value...
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
        return false;
    }
    modified = false;//resseting modified flag to false. in memory texture is now updated.
    optimised = true;
    return true;
}


} //SDL
}// RAGE
