#ifndef SDLut_Scene_hh
#define SDLut_Scene_hh

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

#include "Video/Sprite.hh"

#include <vector>

 namespace RAGE{

     namespace SDL{

//NB : For now size of world = size of display in pixel. Later we ll make a distinction, with camera and other stuff...
class Scene
{
    int m_width;
    int m_height;

    std::vector<Sprite*> m_spritelist;

public:

    Scene(int width, int height);
    Scene( const Scene & );
    ~Scene();

    bool setWidth(int width);
    bool setHeight(int height);

    bool add( Sprite*);

    //This return the list of sprite that need to be displayed, with the correct screen coordinates and dimensions
    std::vector<Sprite*> getRenderList() const;

    //this methods sets in which order the sprites should be rendered.
    void setRenderPriorityPolicy();

};

     } // SDL

 } //RAGE

#endif

