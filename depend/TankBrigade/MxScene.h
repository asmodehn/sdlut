#if !defined(MX_SCENE_H_)
#define MX_SCENE_H_

#include "MxSDL.h"
#include "MxMap.h"
#include "MxSprite.h"

#include <vector>

namespace MxLib
{

    class MxScene
    {

    private:

				int m_borderup;
				int m_borderdown;
				int m_borderleft;
				int m_borderright;

        SDL::RGBSurface * m_bitmap;
        int m_bitmapPosX,m_bitmapPosY;

        MxMap * m_map;
        int m_mapPosX,m_mapPosY;

        std::vector<MxSprite *> m_sprite;
        std::vector<SDL::Rect> m_spritePos;

    public:

        MxScene(int borderup, int borderdown, int borderleft, int borderright) : m_bitmap(NULL), m_map(NULL)
        {
        	m_borderup = borderup;
        	m_borderdown = borderdown;
        	m_borderleft = borderleft;
        	m_borderright = borderright;
				}

        void update ();


        bool add (SDL::RGBSurface *, int posX = 0, int posY = 0)
        ;

        //authorise only one Map
        bool add (MxMap *, int posX =0, int posY =0)
        ;

        int add (MxSprite *, int posX =0, int posY =0)
        ;

        void del (int spriteIndex);

				int spawn (int index, MxSprite * sprite, int deltaX =0, int deltaY =0 );

        void clear ();

        void setBG(int red, int green, int blue);

        bool moveSprite(unsigned int index, int deltaX, int deltaY);

        //timeout = 0 means no timeout.
        void display(int framerate, int timeout = 0);

    };

}
#endif
