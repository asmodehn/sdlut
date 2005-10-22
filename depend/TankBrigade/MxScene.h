#if !defined(MX_SCENE_H_)
#define MX_SCENE_H_

#include "MxSDL.h"
#include "MxMap.h"
#include "MxSprite.h"
#include "MxInput.h"

#include <vector>

namespace MxLib {

	
		
    class MxScene
    {
    	SDL::Color m_bgColor;
    	
    	MxBitmap * m_bitmap;
    	int m_bitmapPosX,m_bitmapPosY;
    	
    	MxMap * m_map;
    	int m_mapPosX,m_mapPosY;
    	
    	std::vector<MxSprite *> m_sprite;
    	std::vector<int> m_spritePosX;
    	std::vector<int> m_spritePosY;
    	
    	protected :
    	MxInput * m_input;
    	void update (MxInput&);
    	
    		public:
    		MxScene(int red = 0, int green = 0, int blue = 0);
    		
    		bool add (MxBitmap *, int posX = 0, int posY = 0);
    		
    		//authorise only one Map
    		bool add (MxMap *, int posX =0, int posY =0);
    		
    		void add (MxSprite *, int posX =0, int posY =0);
    		
    		void clear ();
    		
    		void setBG(int red, int green, int blue);
    		
    		//timeout = 0 means no timeout.
    		void display(int framerate, int timeout = 0);
    		
    };
								
}
#endif
