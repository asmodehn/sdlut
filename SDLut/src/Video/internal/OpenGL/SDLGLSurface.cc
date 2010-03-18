#include "Video/internal/OpenGL/SDLGLSurface.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{


////////////////private Conversion Constructor
GLSurface::GLSurface(SDL_Surface * s) throw (std::logic_error)
try :
    RGBSurface(s), modified(false), m_actualWidth(ptm_surf->h), m_actualHeight(ptm_surf->w)
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
    RGBSurface(s), modified(false), m_actualWidth(ptm_surf->w), m_actualHeight(ptm_surf->h)
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
    RGBSurface( rgbs ), modified(false), m_actualWidth(ptm_surf->w), m_actualHeight(ptm_surf->h)
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
    RGBSurface( gls ), modified(false), m_actualWidth(ptm_surf->w), m_actualHeight(ptm_surf->h)
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
    RGBSurface(width, height, bpp, alpha, colorkey, hardware, r_mask, g_mask, b_mask, a_mask), modified(false), m_actualWidth(ptm_surf->w), m_actualHeight(ptm_surf->h)
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
    RGBSurface(pixeldata, depth, pitch, width, height, r_mask, g_mask, b_mask, a_mask), modified(false),m_actualWidth(ptm_surf->w), m_actualHeight(ptm_surf->h)
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
try : RGBSurface(rwops), modified(false),m_actualWidth(ptm_surf->w), m_actualHeight(ptm_surf->h)
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

bool GLSurface::computeGLWidthHeight()
{
    if ( getTextureWidth() == 0 && getTextureHeight() == 0 ) return true;
    unsigned int properWidth = 1;
    unsigned int properHeight = 1;
    while ( properWidth < getTextureWidth() ) properWidth *= 2;
    while ( properHeight < getTextureHeight() ) properHeight *= 2;

    bool res = false;
    // we may need to resize the surface.
    if (properWidth > getTextureWidth() || properHeight > getTextureHeight() )
    {
        res = resize(properWidth,properHeight,true);
    }
    else
    {
        res = true; // no need to resize
    }

return res;
}

bool GLSurface::convertPixels()
{
    //Todo : We need to here convert the surface to proper BPP to match video surface
    //or OpenGL will not display it

    //WIP : Shouldnt be. PixelFormat of the surface will give us proper color when we do "RGBSurface::getpixel()"
    //WIP : Commenting.
    //RGBSurface::convertToDisplayFormat();
    // DANGER needs to be called after  setting up teh screen ( SetVideoMode ) otherwise SDL has problems

    //
    //NB : OpenGL texture are equivalents of SDL_HWSurfaces.
    // Therefore original RGBSurface should be SW_SURFACE for faster access here
    //

    optimised = false;
/* THE HARD WAY
    if ( texturePixels != NULL ) delete texturePixels, texturePixels=NULL;
    texturePixels = new unsigned int[ textureWidth * textureHeight ];
    PixelColor c,ckey = 0x00000000; //default pixelcolor value and colorkey is full transparent
    if ( RGBSurface::isSRCColorKeyset() )
    {
        ckey = RGBSurface::getColorKey();
    }
    for (unsigned int y = 0; y < textureHeight; y++)
    {
        for (unsigned int x = 0; x < textureWidth; x++)
        {
            if (x < getWidth() && y < getHeight())
            {
                c = RGBSurface::getpixel(x, y);

                //ColorKey to transparent
                if ( ckey == c )
                {
                    texturePixels[x + y * textureWidth] = 0x00000000;
                }

                //We need to convert the pixel color from the SDL RGBSurface format to the OpenGL format
                texturePixels[x + y * textureWidth] = getPixelFormat().convert(c,RGBSurface::getPixelFormat());
            }
            else
            {
                //filling with transparent 0s...
                texturePixels[x + y * textureWidth] = 0x00000000;
            }
        }
    }
    */

    /* The EASY WAY -> WORKING ?? */

return true;
}

GLSurface::~GLSurface()
{
}

bool GLSurface::resize(int width, int height, bool keepcontent)
{
    modified = RGBSurface::resize(width,height,keepcontent);
    ptm_pformat = new OGLPixelFormat(ptm_surf->format);
    return modified;
}

//resize the surface, doesnt scale the image at all
/*
bool GLSurface::resizegl(int glwidth, int glheight, bool keepcontent)
{
     bool res;

    //GLSurface::resize automatically set the proper pixel format for the new gl surface
    std::auto_ptr<SDL_Surface> newSurf(0);
    if ( isSRCAlphaset() || isSRCColorKeyset() ) // Alpha is set by SDL if bpp == 32, and we need Alpha in GL if we got colorkey in SDL
    {
     newSurf.reset(SDL_CreateRGBSurface(ptm_surf->flags,glwidth,glheight,ptm_surf->, r_default_mask, g_default_mask, b_default_mask, a_default_mask) );
     //need to fill with stuff ???
    }
    else
    {
        newSurf.reset(SDL_CreateRGBSurface(ptm_surf->flags,glwidth,glheight,bpp_default_noalpha, r_default_mask, g_default_mask, b_default_mask, a_default_mask) );
    }

    if (!newSurf.get()) //CreateRGBSurface has failed
    {
        Log << "Unable to resize to " << glwidth << " x " << glheight << " 2D GL surface " << nl << GetError();
        res = false;
    }
    else
    {
        if (keepcontent)
        {
            SDL_BlitSurface(ptm_surf.get(), NULL , newSurf.get(), NULL);
        }

        SDL_FreeSurface(ptm_surf.release());
        ptm_surf=newSurf;
        res = true;
    }
    modified = res;
    return (modified && ptm_surf.get() != 0 ) ;
}
*/

unsigned int GLSurface::getWidth()
{
    return m_actualWidth;
}

unsigned int GLSurface::getHeight()
{
    return m_actualHeight;
}


unsigned int GLSurface::getTextureWidth()
{
    return RGBSurface::getWidth();
}

unsigned int GLSurface::getTextureHeight()
{
    return RGBSurface::getHeight();
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


///Accessor to pixelFormat
const PixelFormat& GLSurface::getPixelFormat(void) const
{
    return *ptm_pformat;
}

bool GLSurface::convertToDisplayFormat()
{




        // get the number of channels in the SDL surface
        int numbytes = RGBSurface::getPixelFormat().getBytesPerPixel();

        if ( numbytes < 3 ) // conversion needed : we are not in a true color mode
        {
            //NB Conversion might not be needed
            // refer : http://osdl.sourceforge.net/main/documentation/rendering/SDL-openGL.html

Log << nl << "Warning: the image is not truecolor... Trying Conversion";
Log << nl << " Before Convert " << RGBSurface::getPixelFormat();

saveBMP("beforeconvert.bmp");

/*
            SDL_Surface * glsurf;

            //if transparency -> need alpha channel
            if ( isSRCColorKeyset() || isSRCAlphaset() )
            {
                glsurf = SDL_CreateRGBSurface( ptm_surf->flags, 1, 1, bpp_default_alpha ,r_default_mask, g_default_mask, b_default_mask, a_default_mask);
                //saving colorkey
                //Uint32 ck = ptm_surf->format->colorkey;
            }
            else

            {
                glsurf = SDL_CreateRGBSurface( ptm_surf->flags, 1, 1, bpp_default_noalpha ,g_default_mask, b_default_mask, a_default_mask, 0);
            }

            bool surfok = set_SDL_Surface(SDL_ConvertSurface(ptm_surf.get(),const_cast<SDL_PixelFormat *>(glsurf->format),ptm_surf->flags));

                //copying the colorkey // MAYBE NOT NEEDED ?
                //SDL_SetColorKey(ptm_surf.get(),ptm_surf->flags,ck);

*/
bool surfok = RGBSurface::convertToDisplayFormat();
// display Format dependent...

                if (! surfok)
                {
                    Log << nl << "Unable to copy the RGBsurface in GL conversion" ;
                    throw std::logic_error("SDL_ConvertToDisplayFormat returned NULL");
                }

            Log << nl << " After Convert " << RGBSurface::getPixelFormat();

            saveBMP("afterconvert.bmp");

            //resetting numbytes for further texture format setup
            numbytes = RGBSurface::getPixelFormat().getBytesPerPixel();

        }

        if (numbytes == 4) // contains an alpha channel
        {
            //WHAT ABOUT SDL_BYTEORDER == SDL_BIG_ENDIAN ???
            if (RGBSurface::getPixelFormat().getRshift() == 24 && RGBSurface::getPixelFormat().getAloss() == 0)
            {
                //for little endian
                textureFormat = GL_ABGR_EXT;
            }
            else if ( RGBSurface::getPixelFormat().getRshift() == 16 && RGBSurface::getPixelFormat().getAloss() == 8)
            {
                //for little endian
                textureFormat = GL_BGRA;
            }
            else //joker
            {
                    Log << nl << "Unable to recognise converted GLSurface Format : " << nl << getPixelFormat() ;
                    throw std::logic_error("Pixel Format not recognized for GL display");
            }

        }
        else if (numbytes == 3)     // no alpha channel
        {
            //This can be tested in SDL Logo that doesnt have any Alpha.
                if (RGBSurface::getPixelFormat().getRshift() == 16)
                {
                    textureFormat = GL_BGR;
                }
                else if ( RGBSurface::getPixelFormat().getRshift() == 0)
                {
                    textureFormat = GL_RGB;
                }

            else //joker
            {
                    Log << nl << "Unable to recognise converted GLSurface Format : " << nl << getPixelFormat() ;
                    throw std::logic_error("Pixel Format not recognized for GL display");
            }
        }

            else //joker
            {
                    Log << nl << "Unable to recognise converted GLSurface Format : " << nl << getPixelFormat() ;
                    throw std::logic_error("Pixel Format not recognized for GL display");
            }

    //TODO : handle colorkey in OGL

    ptm_pformat = new OGLPixelFormat(ptm_surf->format);


    /* Standard OpenGL texture creation code */
    //these might be use for screen capture as well
    // refer : http://osdl.sourceforge.net/main/documentation/rendering/SDL-openGL.html#blits
    //glPixelStorei( GL_PACK_ROW_LENGTH, 0 ) ;

    //glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glPixelStorei(GL_UNPACK_ALIGNMENT,ptm_surf->format->BytesPerPixel);
    //glPixelStorei(GL_UNPACK_ALIGNMENT,4);

    glGenTextures(1, &textureHandle);
    glBindTexture(GL_TEXTURE_2D, textureHandle);

    glTexImage2D(GL_TEXTURE_2D, 0, ptm_surf->format->BytesPerPixel, ptm_surf->w, ptm_surf->h, 0, textureFormat, GL_UNSIGNED_BYTE, ptm_surf->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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

bool GLSurface::setColorKey(const PixelColor & key, bool rleAccel)
{
    bool res = RGBSurface::setColorKey(key,rleAccel);
    modified = res;
    return modified;
}


bool GLSurface::setAlpha(unsigned int alpha, bool rleAccel)
{
    bool res = RGBSurface::setAlpha(alpha,rleAccel);
    modified = res;
    return modified;
}



} //SDL
}// RAGE
