#ifndef Daemons_HH
#define Daemons_HH

//#include "Base.hh"
#include "Monster_Factory.hh"
#include "NPCs.hh"
#include "Player.hh"


//Class that will only contains callback methods used by timers
class Daemons
{
private:
	//variables that need to be designed externally
	Player* myPlayer;
	NPC_Merchant* myNPC; //The NPC Definition
	std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector;
	std::vector<BattleField_Sprite*>* Environment_Sprite_Vector;
	Monster_Factory<Monster_Skeleton>* Monster_Factory_Skeleton;
	Monster_Factory<Monster_Worm>* Monster_Factory_Worm;
	std::vector< std::vector<Character_Base*> *>* Global_Player_Vector; //Pointer to the vector that contains pointer to all vectors of player
	std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector; //Pointer to the vector that contains pointer to all vectors of monster
		
	

public:
/***Def****/	
	Daemons(Player* &myPlayer, NPC_Merchant* &myNPC, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector,
				 Monster_Factory<Monster_Skeleton>* &Monster_Factory_Skeleton, Monster_Factory<Monster_Worm>* &Monster_Factory_Worm,
				 std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector
				 );
	~Daemons();

/****Methods****/
	//Callback method that will call monsters movement
	unsigned int Move_Monsters(unsigned int interval, void* args);
	//Callback method that will eventually generate new monster (not to near from the character!)
	unsigned int Generate_Monsters(unsigned int interval, void* args);
	//Callback method that will call npcs movement
	unsigned int Move_NPCs(unsigned int interval, void* args);
	//Callback method that will launch the character's move animation
	unsigned int Player_Move_Animation(unsigned int interval, void* args);
	//Callback method that will launch the arrow attack animation
	unsigned int Player_Arrow_Movement(unsigned int interval, void* args);
	//Callback method that will manage score
	unsigned int Score(unsigned int interval, void* args);

};

#endif
