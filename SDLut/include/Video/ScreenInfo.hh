#ifndef SDLut_ScreenInfo_hh
#define SDLut_ScreenInfo_hh

#include "WkPlatform.h"

#include "Video/internal/SDLVideoInfo.hh"

#ifdef WK_OPENGL_FOUND
#include "Video/internal/OpenGL/OGLVideoInfo.hh"
#endif //WK_OPENGL_FOUND


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
    const ScreenInfo & operator=(const ScreenInfo& si) { return si;}


protected :
#ifdef WK_OPENGL_FOUND
    internal::OGL::OGLVideoInfo m_videoinfo;
    ScreenInfo( const internal::OGL::OGLVideoInfo &); // generate a videoinfo structure from internal structure
#else
    internal::VideoInfo m_videoinfo;
    ScreenInfo( const internal::VideoInfo &); // generate a videoinfo structure from internal structure
#endif // WK_OPENGL_FOUND


public:
    ScreenInfo(); // generate a videoinfo structure from SDL "getVideoInfo" function
    ScreenInfo( const ScreenInfo &); // copy the videoinfo structure
    ~ScreenInfo();


    //these modify the videoinfo structure to store requested parameters
    /// WARNING : These are non-const !
    /// When retrieving existing screen's info, instance should be read only, to forbid any request.
    /// returns true if request granted, false otherwise
    bool requestSize(unsigned int width, unsigned int height );
    bool requestBPP(unsigned short bpp);
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
    friend RAGE::Logger & operator << (RAGE::Logger & ostr, const ScreenInfo & vinfo);


 };






}
}


#endif
