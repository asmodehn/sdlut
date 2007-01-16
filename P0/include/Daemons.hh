#ifndef Daemons_HH
#define Daemons_HH

#include "Monster_Factory.hh"
#include "Base.hh"
#include "Player_Base.hh"

//Class that will only contains callback methods used by timers
class Daemons
{
private:
	//variables that need to be designed externally
	Player_Base* myPlayer;
	std::vector<BattleField_Sprite*> BackGround_Sprite_Vector;
	std::vector<BattleField_Sprite*> Environment_Sprite_Vector;
	Monster_Factory<Monster_Skeleton>* Monster_Factory_Skeleton;
	Monster_Factory<Monster_Worm>* Monster_Factory_Worm;
	std::vector<Monster_Base*> Monster_Vector_Skeleton;
	std::vector<Monster_Base*> Monster_Vector_Worm;
	

public:

	//Accessor
	void Set_Player_Base(Player_Base* newPlayer_Base)
	{
		myPlayer = newPlayer_Base;
	}

	void Set_BackGround_Sprite_Vector(std::vector<BattleField_Sprite*> newBackGround_Sprite_Vector)
	{
		BackGround_Sprite_Vector = newBackGround_Sprite_Vector;
	}
	
	void Set_Environment_Sprite_Vector(std::vector<BattleField_Sprite*> newEnvironment_Sprite_Vector)
	{
		Environment_Sprite_Vector = newEnvironment_Sprite_Vector;
	}

	void Set_Monster_Factory_Skeleton(Monster_Factory<Monster_Skeleton>* newMonster_Factory_Skeleton)
	{
		Monster_Factory_Skeleton = newMonster_Factory_Skeleton;
	}
	/*Monster_Factory<Monster_Base>* Get_Monster_Factory_Skeleton() const
    {
        return Monster_Factory_Skeleton;
    }*/

	void Set_Monster_Factory_Worm(Monster_Factory<Monster_Worm>* newMonster_Factory_Worm)
	{
		Monster_Factory_Worm = newMonster_Factory_Worm;
	}
	/*Monster_Factory<Monster_Base>* Get_Monster_Factory_Worm() const
    {
        return Monster_Factory_Worm;
    }*/

	void Set_Monster_Vector_Skeleton(std::vector<Monster_Base*> newMonster_Vector_Skeleton)
	{
		Monster_Vector_Skeleton = newMonster_Vector_Skeleton;
	}
	std::vector<Monster_Base*> Get_Monster_Vector_Skeleton() const
    {
        return Monster_Vector_Skeleton;
    }

	void Set_Monster_Vector_Worm(std::vector<Monster_Base*> newMonster_Vector_Worm)
	{
		Monster_Vector_Worm = newMonster_Vector_Worm;
	}
	std::vector<Monster_Base*> Get_Monster_Vector_Worm() const
    {
        return Monster_Vector_Worm;
    }

	/****Methods****/
	Daemons();
	~Daemons();

	//Callback method that will call monsters movement
	unsigned int Move_Monsters(unsigned int interval, void* args);
	//Callback method that will eventually generate new monster (not to near from the character!)
	unsigned int Generate_Monsters(unsigned int interval, void* args);
	//Callback method that will launch the character's move animation
	unsigned int Player_Move_Animation(unsigned int interval, void* args);
	//Callback method that will launch the character's attack animation
	unsigned int Player_Attack_Animation(unsigned int interval, void* args);
	//Callback method that will launch the arrow attack animation
	unsigned int Player_Arrow_Animation(unsigned int interval, void* args);

};

#endif
