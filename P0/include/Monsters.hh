#ifndef Monsters_HH
#define Monsters_HH

#include "Monster_Base.hh"

//Skeleton specifics
class Monster_Skeleton : public Monster_Base
{
    private:

	public:
		Monster_Skeleton(int x, int y,
						int &Ch_Vel, int &BASE_LIFE, int &Real_Life, int &BASE_ARMOR, int &Real_Armor, int &Sprite_Width, int &Sprite_Height,
						RGBSurface &Characters_Tile, RGBSurface &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect
						);
		~Monster_Skeleton();

		//Intialize Monster
		static void Initialize(int &Ch_Vel, int &BASE_LIFE, int &Real_Life, int &BASE_ARMOR, int &Real_Armor, int &Sprite_Width, int &Sprite_Height, RGBSurface &Characters_Tile,
						RGBSurface &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect);

		//Battlefield rules
		int Get_BG_vs_CH_Rules(int bgType);
};

//Worm specifics
class Monster_Worm : public Monster_Base
{
    private:
		
	public:
		Monster_Worm(int x, int y,
					int &Ch_Vel, int &BASE_LIFE, int &Real_Life, int &BASE_ARMOR, int &Real_Armor, int &Sprite_Width, int &Sprite_Height,
					RGBSurface &Characters_Tile, RGBSurface &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect
					);
		~Monster_Worm();

		//Intialize Monster
		static void Initialize(int &Ch_Vel, int &BASE_LIFE, int &Real_Life, int &BASE_ARMOR, int &Real_Armor, int &Sprite_Width, int &Sprite_Height, RGBSurface &Characters_Tile,
						RGBSurface &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect);

		//Battlefield rules
		int Get_BG_vs_CH_Rules(int bgType);
};

#endif

