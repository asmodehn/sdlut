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

        MxBitmap * m_bitmap;
        int m_bitmapPosX,m_bitmapPosY;

        MxMap * m_map;
        int m_mapPosX,m_mapPosY;

        std::vector<MxSprite *> m_sprite;
        std::vector<SDL::Rect> m_spritePos;

    public:

        MxScene() : m_bitmap(NULL), m_map(NULL) {}

        void update ();


        bool add (MxBitmap *, int posX = 0, int posY = 0)
        ;

        //authorise only one Map
        bool add (MxMap *, int posX =0, int posY =0)
        ;

        int add (MxSprite *, int posX =0, int posY =0)
        ;

        void clear ();

        void setBG(int red, int green, int blue);

        bool moveSprite(unsigned int index, int deltaX, int deltaY);

        bool testCollide(unsigned int index1, unsigned int index2);

        //timeout = 0 means no timeout.
        void display(int framerate, int timeout = 0);

    };

}
#endif
