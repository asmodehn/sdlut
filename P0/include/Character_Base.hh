#ifndef Character_Base_HH
#define Character_Base_HH

#include "Base.hh"
#include "BattleField.hh"

//Character Class
class Character_Base
{
	protected:
		//The X and Y offsets of the character
		int X, Y;
		
		//The velocity of the character
		int xVel, yVel;

		//Tile & Clip
		RGBSurface Characters_Tile;
		Rect Characters_SpriteRect;
		
	public:
		

};

#endif
