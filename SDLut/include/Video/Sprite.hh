#ifndef SDLut_Sprite_hh
#define SDLut_Sprite_hh

/**
 * \class Scene
 * \ingroup Video
 *
 * \brief This class handles the content of the displayed zone
 *
 * This class hides the details of implementation of 2D organisation of Sprites...
 *
 * \author Alex
 *
 * \date 2009\07\25
 *
 * contact : asmodehn@gna.org
 */


#include "Video/Image.hh"

namespace RAGE
{

namespace SDL
{

class Sprite
{
    //width and height by default same as image, but could be different ( used for collisions for example )
    int m_width;
    int m_height;

    int m_posx;
    int m_posy;

    //TODO : animation
    const Image* pm_img;

public:
    //TODO : Use Image loader here later
    Sprite();
    Sprite( const Sprite& );
    ~Sprite();
    bool setImage( const Image * );
    bool hasImage()
    {
        return pm_img >0;
    }
    const Image & getImage()
    {
        return *pm_img;
    }

    bool move( int deltax, int deltay );
    bool moveto( int posx, int posy);

    int posX()
    {
        return m_posx;
    }
    int posY()
    {
        return m_posy;
    }

};

} // SDL

} //RAGE

#endif


