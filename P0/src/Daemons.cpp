#include "Daemons.hh"

//Constructor
Daemons::Daemons()
{
	//Allocations
	myPlayer = new Player_Base(0,0);
	BackGround_Sprite_Vector = new std::vector<BattleField_Sprite*>;
	Environment_Sprite_Vector = new std::vector<BattleField_Sprite*>;
	Monster_Factory_Skeleton = new Monster_Factory<Monster_Skeleton>;
	Monster_Factory_Worm = new Monster_Factory<Monster_Worm>;
	Global_Player_Vector = new std::vector< std::vector<Character_Base*> *>;
	Global_Monster_Vector = new std::vector< std::vector<Character_Base*> *>;

	P0_Logger << nl << "Deamons CONSTRUCTED Successfully " << std::endl;
}
//Destructor
Daemons::~Daemons()
{
	//Allocations
	delete myPlayer, myPlayer = NULL;
	delete BackGround_Sprite_Vector, BackGround_Sprite_Vector = NULL;
	delete Environment_Sprite_Vector, Environment_Sprite_Vector = NULL;
	delete Monster_Factory_Skeleton, Monster_Factory_Skeleton = NULL;
	delete Monster_Factory_Worm, Monster_Factory_Worm = NULL;
	delete Global_Player_Vector, Global_Player_Vector = NULL;
	delete Global_Monster_Vector, Global_Monster_Vector = NULL;
}

//Callback method that will call monsters movement
unsigned int Daemons::Move_Monsters(unsigned int interval, void* args)
{
try {
	if (GLOBAL_GAME_STATE != 5 )//victory 
	{
		Monster_Factory_Skeleton->Move_Monsters( Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector );
		Monster_Factory_Worm->Move_Monsters( Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector );
		P0_Logger << nl << "Move Monsters " << std::endl;
		return interval; // loop
	} else { //Victory: end of timer
		return 0;
	}
} catch (...) {
	P0_Logger << nl << "Move Monsters Daemon Failed " << std::endl;
	return interval; // loop
}
}

//Callback method that will eventually generate new monster (not to near from the character!)
unsigned int Daemons::Generate_Monsters(unsigned int interval, void* args)
{
try {
	if (GLOBAL_GAME_STATE != 5 )//victory 
	{
		//Skeletons
		Global_Monster_Vector->at(0) = Monster_Factory_Skeleton->Generate_New_Monster( Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector );
		//->swap( 
		//Worms
		Global_Monster_Vector->at(1) = Monster_Factory_Worm->Generate_New_Monster( Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector );

		P0_Logger << nl << "Generate Monsters " << std::endl;
		return interval; // loop
	} else { //Victory: end of timer
		return 0;
	}
} catch (...) {
	P0_Logger << nl << "Generate Monsters Daemon Failed " << std::endl;
	return interval; // loop
}
}

//Callback method that will launch the character's move animation
unsigned int Daemons::Player_Move_Animation(unsigned int interval, void* args)
{
try {
	
	if ( myPlayer->Set_Move_Animation_Sprite() )
	{ return interval; } //move anim is still ocuring than loop
	return 0; //end of timer
	
} catch (...) {
	P0_Logger << nl << "Player Move Animation Timer Failed " << std::endl;
	return 0; //end of timer
}
}

//Callback method that will launch the character's attack animation
unsigned int Daemons::Player_Attack_Animation(unsigned int interval, void* args)
{
try {
	
	if ( myPlayer->Set_Attack_Animation_Sprite() ) //attack anim is still ocuring than loop
	{ 
		myPlayer->Set_Attack_Status(true); //attack occuring
		return interval;
	} 
	
	//if the attack was succesfull
	if ( (myPlayer->Get_Attack_Successfull() != 0 ) && ( myPlayer->Get_Attack_Style() == 1 ) )
	{//Now that attack anim is finished, remove Dead monsters from theirs respective vector
			//Skeletons
		Global_Monster_Vector->at(0) = Monster_Factory_Skeleton->Remove_Dead_Monsters();
			//Worms
		Global_Monster_Vector->at(1) = Monster_Factory_Worm->Remove_Dead_Monsters();
	}
	myPlayer->Set_Attack_Status(false); //end of attack
	return 0; //end of timer

} catch (...) {
	P0_Logger << nl << "Player Attack Animation Timer Failed " << std::endl;
	return 0; //end of timer
}
}

//Callback method that will launch the arrow attack animation
unsigned int Daemons::Player_Arrow_Animation(unsigned int interval, void* args)
{
try {
	
	if ( myPlayer->Set_Arrow_Sprite_Coordinate() ) //arrow anim is still ocuring than loop
	{ 
		myPlayer->Set_Attack_Status(true); //attack occuring
		return interval;
	} 
	
	//if the attack was succesfull
	if ( (myPlayer->Get_Attack_Successfull() != 0 ) && ( myPlayer->Get_Attack_Style() == 2 ) )
	{//Now that arrow anim is finished, remove Dead monsters from theirs respective vector
			//Skeletons
		Global_Monster_Vector->at(0) = Monster_Factory_Skeleton->Remove_Dead_Monsters();
			//Worms
		Global_Monster_Vector->at(1) = Monster_Factory_Worm->Remove_Dead_Monsters();
	}
	myPlayer->Set_Attack_Status(false); //end of attack
	return 0; //end of timer
	
} catch (...) {
	P0_Logger << nl << "Player's Arrow Animation Timer Failed " << std::endl;
	return 0; //end of timer
}
}

//Callback method that will manage score
unsigned int Daemons::Score(unsigned int interval, void* args)
{
try {
	if (ALiVE_MONSTERS > 0)
		return interval;

	FiNiSH_TiME = (unsigned)time( NULL ) - FiNiSH_TiME;

	GLOBAL_GAME_STATE = 5;

	return 0; //end of timer
	
} catch (...) {
	P0_Logger << nl << "Score manager Failed " << std::endl;
	return 0; //end of timer
}
}
