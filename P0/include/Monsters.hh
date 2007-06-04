#ifndef Monsters_HH
#define Monsters_HH

#include "Monster_Base.hh"

//dumb declaration to be able to define the template class as friend of the Monster_* class
template <typename Monster_Template> class Monster_Factory;

//Skeleton specifics
class Monster_Skeleton : public Monster_Base
{
	friend class Monster_Factory<Monster_Skeleton>;

    private:
		static string Description_Filename;

	public:
		Monster_Skeleton(int x, int y,
						int &Ch_Vel, int &BASE_LIFE, int &BASE_ARMOR, int &BASE_INFLICTED_DAMAGE, int &Sprite_Width, int &Sprite_Height, Character_Types &Characters_ID,
						Rect &Allowed_Area,
						int &CB_X_Modifier, int &CB_Y_Modifier, int &CB_Width, int &CB_Height,
						RGBSurface* &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect,
						Character_Animation* &Attack_Animation, Character_Animation* &Death_Animation, Character_Animation* &Run_Animation, Character_Animation* &Walk_Animation,
						Character_Animation* &Hit_Animation, Character_Animation* &Stop_Animation, Character_Animation* &Pause_Animation
						);
		~Monster_Skeleton();



		//Battlefield rules
		int Get_BG_vs_CH_Rules(const int& bgType);
};

//Worm specifics
class Monster_Worm : public Monster_Base
{
	friend class Monster_Factory<Monster_Worm>;

    private:
		static string Description_Filename;
		
	public:
		Monster_Worm(int x, int y,
					int &Ch_Vel, int &BASE_LIFE, int &BASE_ARMOR, int &BASE_INFLICTED_DAMAGE, int &Sprite_Width, int &Sprite_Height, Character_Types &Characters_ID,
					Rect &Allowed_Area,
					int &CB_X_Modifier, int &CB_Y_Modifier, int &CB_Width, int &CB_Height,
					RGBSurface* &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect,
					Character_Animation* &Attack_Animation, Character_Animation* &Death_Animation, Character_Animation* &Run_Animation, Character_Animation* &Walk_Animation,
					Character_Animation* &Hit_Animation, Character_Animation* &Stop_Animation, Character_Animation* &Pause_Animation
					);
		~Monster_Worm();

		//Battlefield rules
		int Get_BG_vs_CH_Rules(const int& bgType);
};

#endif

