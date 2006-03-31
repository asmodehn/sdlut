#ifndef Monsters_HH
#define Monsters_HH

#include "Base.hh"
#include "Monster_Base.hh"
#include "BattleField.hh"

//Skeleton specifics
class Monster_Skeleton : public Monster_Base
{
    private:

	public:
		Monster_Skeleton(int X, int Y);

		//Check if the ground allow the Skeleton to move
		bool check_ground_allow_move(std::vector<BattleField_Sprite*> BattleField_Sprite_Vector);
		
};

//Worm specifics
class Monster_Worm : public Monster_Base
{
    private:
		
	public:
		Monster_Worm(int X, int Y);

		//Check if the ground allow the worm to move
		bool check_ground_allow_move(std::vector<BattleField_Sprite*> BattleField_Sprite_Vector);
		
};

#endif

