#if !defined(MX_MAP_H_)
#define MX_MAP_H_

#include "MxSDL.h"
#include "MxSprite.h"

namespace MxLib
{

    class MxMap
    {

        int m_spriteSize;
        int m_mapWidth;
        int m_mapHeight;

        std::vector<const MxSprite*>m_spritelist;
        std::vector<const MxSprite*>m_map;

    public:
        MxMap(int sizeOfSprite = 32, int mapWidth = 20, int mapHeight = 15);

        int loadSprite( const MxSprite* sprite );
        int loadnewSprite(SDL::RGBSurface & bitmap,int x, int y);
        int placeSprite(int index, int mapX, int mapY);


        void render (int pixX = 0, int pixY = 0);

    };


}



#endif
