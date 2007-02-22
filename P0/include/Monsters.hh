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

		//Battlefield rules
		int Get_BG_vs_CH_Rules(int bgType);
};

#endif

