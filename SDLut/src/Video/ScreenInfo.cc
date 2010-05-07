#include "Video/ScreenInfo.hh"
#include "SDLConfig.hh"

using namespace Core;

namespace SDLut
{
namespace video
{


#ifdef WK_OPENGL_FOUND
ScreenInfo::ScreenInfo( const internal::OGL::OGLVideoInfo & vi) // generate a videoinfo structure from internal structure
        : m_videoinfo(vi)
{

}
#else
ScreenInfo::ScreenInfo( const internal::VideoInfo & vi); // generate a videoinfo structure from internal structure
:
m_videoinfo(vi)
{
}
#endif // WK_OPENGL_FOUND


ScreenInfo::ScreenInfo() // generate a videoinfo structure from SDL "getVideoInfo" function
        : m_videoinfo()
{
}

ScreenInfo::ScreenInfo( const ScreenInfo & si) // copy the videoinfo structure
        :m_videoinfo(si.m_videoinfo)
{
}

ScreenInfo::~ScreenInfo()
{
}

//these modify the videoinfo structure to store requested parameters
/// WARNING : These are non-const !
/// When retrieving existing screen's info, instance should be read only, to forbid any request.
/// returns true if request granted, false otherwise
unsigned short  ScreenInfo::requestSize(unsigned int width, unsigned int height )
{
    return m_videoinfo.requestSize(width,height);
}

unsigned short ScreenInfo::requestBPP(unsigned short bpp)
{
    return m_videoinfo.requestBPP(bpp);
}

bool ScreenInfo::requestOpenGL( bool value)
{
    return m_videoinfo.requestOpenGL(value);
}

bool ScreenInfo::requestResizable (bool value)
{
    return m_videoinfo.requestResizable(value);
}

bool ScreenInfo::requestNoFrame (bool value)
{
    return m_videoinfo.requestNoFrame(value);
}

bool ScreenInfo::requestFullscreen (bool value)
{
    return m_videoinfo.requestFullscreen(value);
}

//accessor, to ask the status of screen setup
unsigned int ScreenInfo::getRequestedWidth() const
{
    return m_videoinfo.getRequestedWidth();
}

unsigned int ScreenInfo::getRequestedHeight() const
{
    return m_videoinfo.getRequestedHeight();
}

unsigned short ScreenInfo::getRequestedBPP() const
{
    return m_videoinfo.getRequestedBPP();
}

bool ScreenInfo::isOpenGL() const
{
    return m_videoinfo.isOpenGL();
}

bool ScreenInfo::isResizable() const
{
    return m_videoinfo.isResizable();
}

bool ScreenInfo::isNoFrame() const
{
    return m_videoinfo.isNoFrame();
}

bool ScreenInfo::isFullscreen() const
{
    return m_videoinfo.isFullscreen();
}


//display all detected informations about graphics
Core::Logger & operator << (Core::Logger & ostr, const ScreenInfo & vinfo)
{
    ostr << vinfo.m_videoinfo;
    return ostr;
}



}//video
}//SDLut
