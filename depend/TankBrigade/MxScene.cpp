#include "MxScene.h"
#include "MxInput.h"

namespace MxLib
{

    bool MxScene::add (MxBitmap * bitmap, int posX, int posY)
    {
        bool res = (m_bitmap==NULL);
        if (res)
        {
            m_bitmap=bitmap;
            m_bitmapPosX=posX;
            m_bitmapPosY=posY;
        }

        return res;
    }

    bool MxScene::add (MxMap * map, int posX, int posY)
    {
        bool res = (m_map==NULL);
        if (res)
        {
            m_map=map;
            m_mapPosX=posX;
            m_mapPosY=posY;
        }

        return res;
    }

    int MxScene::add (MxSprite * sprite, int posX, int posY)
    {
        m_sprite.push_back(sprite);

        SDL::Rect newpos;
        newpos.setx(posX);
        newpos.sety(posY);
        newpos.setw(sprite->m_bboxOri.getw());
        newpos.seth(sprite->m_bboxOri.geth());

        m_spritePos.push_back(newpos);

        sprite->setScene(this);
        sprite->setSceneIndex(m_sprite.size() -1);
    }

    void MxScene::clear ()
    {
        m_bitmap = NULL;
        m_map = NULL;
        m_sprite.clear();
    }


    void MxScene::update ()
    {
        //if (m_map!=NULL)
        //m_map->update();

        for (unsigned int i=0;i<m_sprite.size() ;i++ )
            m_sprite[i]->update();

    }

    void MxScene::display(int framerate, int timeout)
    {

        if (m_map!=NULL)
            m_map->render(m_mapPosX,m_mapPosY);

        for (unsigned int i=0;i<m_sprite.size() ;i++ )
            m_sprite[i]->render(m_spritePos[i].getx(),m_spritePos[i].gety());

        if (m_bitmap!=NULL)
            m_bitmap->render(m_bitmapPosX, m_bitmapPosY);

        MxInit::getDisplay()->update();
        //TODO
    }

    bool MxScene::moveSprite(unsigned int index, int deltaX, int deltaY)
    {
        bool res = true;
        if (index < m_sprite.size())
        {
          m_spritePos[index] += SDL::Point (deltaX, deltaY);
        }
        for (unsigned int i=0; i<m_sprite.size(); i++ )
        {
          if (i != index )
            {
                SDL::Rect intersection=m_spritePos[index].inf(m_spritePos[i]);
                if ( intersection.getw()!=0 && intersection.geth()!=0)
                {
                  std::cout << "collide" << std::endl;
                    // move back as needed
                    if ( intersection.getw() < intersection.geth() )
                    {
                        if  ( m_spritePos[index].getx() < m_spritePos[i].getx() )
                        {
                            m_spritePos [index] += SDL::Point( - intersection.getw(), 0 );
                        }
                        else
                        {
                            m_spritePos [index] += SDL::Point( intersection.getw(), 0 );
                        }
                    }
                    else
                    {
                        if  ( m_spritePos[index].gety() < m_spritePos[i].gety() )
                        {
                            m_spritePos [index] += SDL::Point( 0, - intersection.geth() );
                        }
                        else
                        {
                            m_spritePos [index] += SDL::Point(  0, intersection.geth() );
                        }
                    }
                    m_sprite[index]->collide(intersection);
                    m_sprite[i]->collide(intersection);
                    res=false;
                }
            }
            return res;
        }
    }

}
