#ifndef SDLut_ScreenInfo_hh
#define SDLut_ScreenInfo_hh

#include "WkPlatform_SDLut.h"

#include "Video/internal/SDLVideoInfo.hh"

#ifdef WK_SDLut_FOUND_OPENGL
#include "Video/internal/OpenGL/OGLVideoInfo.hh"
#endif //WK_SLDut_FOUND_OPENGL


namespace SDLut
{
namespace video
{


/**
 * This class handles VideoInfo the same way than ScreenBuffer handles VideoSurface
 * It is used as a structure to store parameters for the ScreenBuffer.
 */



class ScreenInfo
{
    friend class ScreenBuffer;

    //forbiddend assignment
    const ScreenInfo & operator=(const ScreenInfo& si)
    {
        return si;
    }

    //forbidden copy
    ScreenInfo( const ScreenInfo &); // copy the videoinfo structure

    ///we should have only one instance of screeninfo per screen ( or display for request if screen not created ) at any moment in time.
    ///This is to match SDL which provides only a pointer to internal read-only videoinfo structure.

protected :
#ifdef WK_SDLut_FOUND_OPENGL
    internal::OGL::OGLVideoInfo m_videoinfo;
    ScreenInfo( const internal::OGL::OGLVideoInfo &); // generate a videoinfo structure from internal structure
#else
    internal::VideoInfo m_videoinfo;
    ScreenInfo( const internal::VideoInfo &); // generate a videoinfo structure from internal structure
#endif // WK_SDLut_FOUND_OPENGL


public:
    ScreenInfo(); // generate a videoinfo structure from SDL "getVideoInfo" function
    ~ScreenInfo();

    //these modify the videoinfo structure to store requested parameters
    /// WARNING : These are non-const !
    /// When retrieving existing screen's info, instance should be read only, to forbid any request.
    /// returns true if request granted, false otherwise
    unsigned short requestSize(unsigned int width, unsigned int height );
    unsigned short requestBPP(unsigned short bpp);
    bool requestOpenGL( bool value);
    bool requestResizable (bool value);
    bool requestNoFrame (bool value);
    bool requestFullscreen (bool value);

    unsigned int getRequestedWidth() const;
    unsigned int getRequestedHeight() const;
    unsigned short getRequestedBPP() const;

    //These are useless and confusing here. Should be retrieved through ScreenBuffer directly
    //unsigned int getWidth() const;
    //unsigned int getHeight() const;
    //unsigned short getBPP() const;

    //accessor, to ask the status of screen setup
    bool isOpenGL() const;
    bool isResizable() const;
    bool isNoFrame() const;
    bool isFullscreen() const;


    //display all detected informations about graphics
    friend Core::Logger & operator << (Core::Logger & ostr, const ScreenInfo & vinfo);


};






}
}


#endif
