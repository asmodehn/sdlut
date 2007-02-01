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
}

//Callback method that will call monsters movement
unsigned int Daemons::Move_Monsters(unsigned int interval, void* args)
{
try {
	Monster_Factory_Skeleton->Move_Monsters( Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector );
	Monster_Factory_Worm->Move_Monsters( Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector );
	P0_Logger << " Move Monsters " << std::endl;
	return interval; // loop
} catch (...) {
	P0_Logger << " Move Monsters Daemon Failed " << std::endl;
	return interval; // loop
}
}

//Callback method that will eventually generate new monster (not to near from the character!)
unsigned int Daemons::Generate_Monsters(unsigned int interval, void* args)
{
try {
	//Skeletons
	Global_Monster_Vector->at(0) = Monster_Factory_Skeleton->Generate_New_Monster( Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector );
	//->swap( 
	//Worms
	Global_Monster_Vector->at(1) = Monster_Factory_Worm->Generate_New_Monster( Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector );

	P0_Logger << " Generate Monsters " << std::endl;
	return interval; // loop
} catch (...) {
	P0_Logger << " Generate Monsters Daemon Failed " << std::endl;
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
	P0_Logger << " Player Move Animation Timer Failed " << std::endl;
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
	P0_Logger << " Player Attack Animation Timer Failed " << std::endl;
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
	P0_Logger << " Player's Arrow Animation Timer Failed " << std::endl;
	return 0; //end of timer
}
}
