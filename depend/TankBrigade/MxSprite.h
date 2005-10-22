#if !defined(MX_SPRITE_H_)
#define MX_SPRITE_H_

#include "MxSDL.h"
#include <vector>

namespace MxLib {

class MxSprite
{
	protected :
	
	MxBitmap & m_BitmapOri;
	SDL::Rect m_bboxOri;
	
	public:
		MxSprite (MxBitmap & , unsigned int coordOriX, unsigned int coordOriY, unsigned int size);
		MxSprite (MxBitmap & , unsigned int coordOriX, unsigned int coordOriY, unsigned int sizeOriX, unsigned int sizeOriY);
	
	virtual void update();
	
	bool render(int pixX, int pixY) const;
	
};

class MxAnimatedSprite : public MxSprite
{
	std::vector<SDL::Rect> m_frame;
	unsigned int m_currentframe;
	
	public:
		MxAnimatedSprite (MxBitmap & , unsigned int coordOriX, unsigned int coordOriY, unsigned int size);
		MxAnimatedSprite (MxBitmap & , unsigned int coordOriX, unsigned int coordOriY, unsigned int sizeOriX, unsigned int sizeOriY);
	
	
	bool changeFrame(unsigned int newframe)  { if ( newframe < m_frame.size() ) m_currentframe = newframe; else return false; return true;}
	
	virtual void update();
	
	bool render(int pixX, int pixY) const;
	
};
	
}
#endif
