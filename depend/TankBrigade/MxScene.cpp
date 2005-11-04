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

        if (index < m_sprite.size())
        {
          SDL::Point move;
          move.setx(deltaX);
          move.sety(deltaY);

            m_spritePos[index] += move;
        }
        for (unsigned int i=0; i<m_sprite.size(); i++ )
          if (i != index ) testCollide(index,i);
    }

    bool MxScene::testCollide(unsigned int index1, unsigned int index2)
    {
      //might be better done like that, although
      //this function should be completely symmetric
      //
      //return m_spritePos[index1].collide(m_spritePos[index2])

      SDL::Rect intersection=m_spritePos[index1].inf(m_spritePos[index2]);

        if ( intersection.getw()!=0 && intersection.geth()!=0)
        {
          m_sprite[index1]->collide(intersection);
          m_sprite[index2]->collide(intersection);
        }
      return true;


    }

}
