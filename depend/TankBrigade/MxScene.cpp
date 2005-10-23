#include "MxScene.h"
#include "MxInput.h"

namespace MxLib {

MxScene::MxScene(int red , int green, int blue)
: m_bitmap(NULL), m_map(NULL)
{
	setBG(red,green,blue);
}


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

void MxScene::add (MxSprite * sprite, int posX, int posY)
{
	m_sprite.push_back(sprite);
	m_spritePosX.push_back(posX);
	m_spritePosY.push_back(posY);
}

void MxScene::clear ()
{
	m_bitmap = NULL;
	m_map = NULL;
	m_sprite.clear();
}

void MxScene::setBG(int red, int green, int blue)
{
	m_bgColor.setR(red);
	m_bgColor.setG(green);
	m_bgColor.setB(blue);
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
    m_sprite[i]->render(m_spritePosX[i],m_spritePosY[i]);
  
  if (m_bitmap!=NULL)
    m_bitmap->render(m_bitmapPosX, m_bitmapPosY);
    
    MxInit::getDisplay()->update();
	//TODO
}

}
