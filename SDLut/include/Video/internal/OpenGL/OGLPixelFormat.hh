
#ifndef SDL_GLMANAGER_HH
#define SDL_GLMANAGER_HH

/**
 * \class OGLPixelFormat
 *
 *
 * \brief This class is an OpenGL Pixel Format
 *
 * This class implements the opengl functions that SDL provides related to pixel format
 *
 * \author Alex
 *
 * \date 2010/03/17
 *
 * Contact: asmodehn@gna.org
 *
 */

#include "Logger.hh"
#include "Video/internal/SDLPixelFormat.hh"

#include "WkPlatform.h"

#include <string>

namespace SDLut
{
namespace video
{
namespace internal
{
namespace OGL
{


#ifdef WK_OPENGL_FOUND


class OGLPixelFormat : public PixelFormat
{
    friend class GLSurface; // to be able to access OGLPixel Format Constructor

private:

    //default Constructor
    OGLPixelFormat(void);

    //Copy Constructor from SDL_PixelFormat
    //This handle explicit casts
    explicit OGLPixelFormat(const SDL_PixelFormat* pf);
    //DEVELOPER BEWARE ! Don't free the original pixelformat.
    //The user should never be able to free the original pixelformat
    //nor to use SDL directly.

public :


    ~OGLPixelFormat();

    virtual int getBitsPerPixel() const;
    virtual int getBytesPerPixel() const;
    virtual int getRshift() const;
    virtual int getGshift() const;
    virtual int getBshift() const;
    virtual int getAshift() const;

    virtual int getRloss() const;
    virtual int getGloss() const;
    virtual int getBloss() const;
    virtual int getAloss() const;

    //BEWARE ! sometimes this has no sense, because only the palette is set...
    //TODO : Handle this...
    virtual unsigned long getRmask() const;
    virtual unsigned long getGmask() const;
    virtual unsigned long getBmask() const;
    virtual unsigned long getAmask() const;

    virtual PixelColor getColorKey() const;
    virtual int getAlpha() const;




    //OLDCOMMENT : TO CHECK
    // Q? : if GLWindow not set, can we access the GL data ??
    // ANSWER : on windows (wingdi driver) everything is == 0 when GLWindow not set
    // On Windows , after setvideo, the values are : { 8,8,8,8,32,24,8,0,0,0,0 } should be set by default...
    // or maybe 0 before means default after set video...
    int getRSize(void) const ;
    int getGSize(void) const ;
    int getBSize(void) const ;
    int getASize(void) const ;
    int getBufferSize(void) const ;
    int getDepthSize(void) const ;
    int getStencilSize(void) const ;
    int getAccumRSize(void) const ;
    int getAccumGSize(void) const ;
    int getAccumBSize(void) const ;
    int getAccumASize(void) const ;

    //OLD COMMENT : TO CHECK
    //TODO : if the video is already set, a change here should result in VIDEO RE-SET, via SDLSurfaceFactory
    //beware of the Surface Factory behavior about this for other things like doublebuf, we have to do it the same way...
    //On windows ( wingdi) all set functions returns true, but it seems they have no effects on the result after setVideoMode...
    //Tests to do on linux...
    bool setRSize(int bits);
    bool setGSize(int bits);
    bool setBSize(int bits);
    bool setASize(int bits);
    bool setBufferSize(int bits);
    bool setDepthSize(int bits);
    bool setStencilSize(int bits);
    bool setAccumRSize(int bits);
    bool setAccumGSize(int bits);
    bool setAccumBSize(int bits);
    bool setAccumASize(int bits);

    friend RAGE::Logger & operator << (RAGE::Logger & ostr, const OGLPixelFormat & glman);
};

#endif // WK_OPENGL_FOUND

} // namespace OGL
} // namespace internal
} // namespace video
} // namespace SDLut

#endif
