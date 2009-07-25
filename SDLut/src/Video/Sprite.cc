#include "Video/Sprite.hh"
#include "SDLConfig.hh"

namespace RAGE
{
	namespace SDL
	{

    Sprite::Sprite()
    : m_width(0), m_height(0), m_posx(0), m_posy(0), pm_img(NULL)
    {

    }

    Sprite::Sprite( const Sprite& s )
    : m_width(s.m_width), m_height(s.m_height), m_posx(s.m_posx), m_posy(s.m_posy), pm_img(s.pm_img)
    {
    }

    Sprite::~Sprite()
    {
    }

    bool Sprite::setImage( const Image * img)
    {
        //default useful values
        m_width = img->getWidth();
        m_height = img->getHeight();


        pm_img = img;
        return true;
    }

    bool Sprite::move( int deltax, int deltay )
    {
        m_posx += deltax;
        m_posy += deltay;
    }

    bool Sprite::moveto( int posx, int posy)
    {
        m_posx = posx;
        m_posy = posy;
    }


	} // SDL

} // RAGE

