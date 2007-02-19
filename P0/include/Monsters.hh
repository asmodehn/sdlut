#ifndef Monsters_HH
#define Monsters_HH

#include "Monster_Base.hh"

//Skeleton specifics
class Monster_Skeleton : public Monster_Base
{
    private:

	public:
		Monster_Skeleton(int x, int y);
		~Monster_Skeleton();

		//Check if the ground allow the Skeleton to move
		//std::vector<int> check_background_allow_monster(Rect Collision_Box, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);
		//Battlefield rules
		int Get_BG_vs_CH_Rules(int bgType);
};

//Worm specifics
class Monster_Worm : public Monster_Base
{
    private:
		
	public:
		Monster_Worm(int x, int y);
		~Monster_Worm();

		//Check if the ground allow the worm to move
		//std::vector<int> check_background_allow_monster(Rect Collision_Box, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);
		int Get_BG_vs_CH_Rules(int bgType);
};

#endif

