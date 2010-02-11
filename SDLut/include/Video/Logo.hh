#ifndef LOGO_HH
#define LOGO_HH

/*******************************************
 * Class definnig what a logo is           *
 * It s a Base Surface with a defined size *
 * All logos have same size                *
 * The default logo is SDL                 *
 *******************************************/

#include "SDLVideoSurface.hh"

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

std::auto_ptr<RGBSurface> m_logo;


public:
//default size matching SDL logo size
Logo();
virtual ~Logo();

void setLogoImage( const RGBSurface & mylogo );

static void resizerender(int renderwidth=128, int renderheight= 64);

virtual bool render(VideoSurface & screen) const;

};







    }
}


#endif
