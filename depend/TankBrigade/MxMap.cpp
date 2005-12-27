#include "MxMap.h"

namespace MxLib
{

    MxMap::MxMap(int sizeOfSprite, int mapWidth, int mapHeight)
            : m_spriteSize(sizeOfSprite), m_mapWidth(mapWidth), m_mapHeight(mapHeight)
    {
        m_map.reserve(m_mapWidth*m_mapHeight);
        m_map.assign(m_mapWidth*m_mapHeight,(const MxSprite *)NULL);
    }

    int MxMap::loadSprite( const MxSprite * sprite )
    {
        m_spritelist.push_back(sprite);
        return m_spritelist.size()-1;
    }

    int MxMap::loadnewSprite( SDL::RGBSurface & bitmap,int x, int y)
    {
        MxSprite * sprite = new MxSprite(bitmap,x,y,m_spriteSize);
        m_spritelist.push_back(sprite);
        return m_spritelist.size()-1;
    }

    int MxMap::placeSprite(int index, int mapX, int mapY)
    {
        if ((mapX < m_mapWidth) && (mapY < m_mapHeight))
            m_map[mapX+mapY*m_mapWidth]=m_spritelist[index];
    }

    void MxMap::render(int pixX, int pixY)
    {
        //std::cerr << "Update called on MxMap" << std::endl;
        for ( int i=0; i < m_mapWidth; i++)
        {
            for ( int j=0; j< m_mapHeight; j++)
            {
                //std::cerr << "rendering tile from " << i << "," << j << " at " << i*32 << "," << j*32 << std::endl;
                if (m_map[i+j*m_mapWidth]!=NULL)
                {
                    //std::cerr << "Rendering " << map[i+j*m_mapWidth] << std::endl;;
                    m_map[i+j*m_mapWidth]->render( i*m_spriteSize,j*m_spriteSize);
                }
            }
        }
    }

};
