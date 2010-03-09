#ifndef LOGO_HH
#define LOGO_HH

/*******************************************
 * Class definning what a logo is          *
 * It s a Surface with a defined size      *
 * All logos have same size                *
 * The default logo is SDL logo            *
 *******************************************/


#include "WkPlatform.h"
//to be able to know which renderers can be used for the logo

#ifdef WK_OPENGL_FOUND
#include "SDLVideoGLSurface.hh"
#else
#include "SDLVideoSurface.hh"
#endif

namespace RAGE
{
    namespace SDL
    {

class Logo
{

protected:
//TODO : later manage resize of all logos at once
static int m_render_width;
static int m_render_height;

#ifdef WK_OPENGL_FOUND
std::auto_ptr<GLSurface> m_logo;
#else
std::auto_ptr<RGBSurface> m_logo;
#endif

public:
//default size matching SDL logo size
Logo();
virtual ~Logo();

virtual void setLogoImage( const RGBSurface & mylogo );

static void resizerender(int renderwidth=128, int renderheight= 64);

#ifdef WK_OPENGL_FOUND
virtual bool render(VideoGLSurface & screen) const;
#else
virtual bool render(VideoSurface & screen) const;
#endif

};







    }
}


#endif
