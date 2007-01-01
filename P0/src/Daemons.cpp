#include "Daemons.hh"

//Constructor
Daemons::Daemons()
{}

//Destructor
Daemons::~Daemons()
{}

//Callback method that will call monsters movement
unsigned int Daemons::Move_Monsters(unsigned int interval, void* args)
{
try {
	Monster_Factory_Skeleton->Move_Monsters( myCharacter->collision_box, Environment_Sprite_Vector, BackGround_Sprite_Vector, 2, Monster_Vector_Skeleton, Monster_Vector_Worm );
	Monster_Factory_Worm->Move_Monsters( myCharacter->collision_box, Environment_Sprite_Vector, BackGround_Sprite_Vector, 2, Monster_Vector_Skeleton, Monster_Vector_Worm );
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
	Monster_Vector_Skeleton = Monster_Factory_Skeleton->Generate_New_Monster( myCharacter->collision_box, Environment_Sprite_Vector, BackGround_Sprite_Vector );
	Monster_Vector_Worm = Monster_Factory_Worm->Generate_New_Monster( myCharacter->collision_box, Environment_Sprite_Vector, BackGround_Sprite_Vector );

	P0_Logger << " Generate Monsters " << std::endl;
	return interval; // loop
} catch (...) {
	P0_Logger << " Generate Monsters Daemon Failed " << std::endl;
	return interval; // loop
}
}

//Callback method that will launch the character's move animation
unsigned int Daemons::Character_Move_Animation(unsigned int interval, void* args)
{
try {
	
	if ( myCharacter->Set_Move_Animation_Sprite() )
	{ return interval; } //move anim is still ocuring than loop
	return 0; //end of timer
	
} catch (...) {
	P0_Logger << " Character Move Animation Timer Failed " << std::endl;
	return 0; //end of timer
}
}

//Callback method that will launch the character's attack animation
unsigned int Daemons::Character_Attack_Animation(unsigned int interval, void* args)
{
try {
	
	if ( myCharacter->Set_Attack_Animation_Sprite() ) //attack anim is still ocuring than loop
	{ return interval; } 
	
	//if the attack was succesfull
	if ( (myCharacter->Get_Attack_Successfull() != 0 ) && ( myCharacter->Get_Attack_Style() == 1 ) )
	{//Now that attack anim is finished, remove Dead monsters from theirs respective vector
		Monster_Vector_Skeleton = Monster_Factory_Skeleton->Remove_Dead_Monsters();
		Monster_Vector_Worm = Monster_Factory_Worm->Remove_Dead_Monsters();
	}
	return 0; //end of timer

} catch (...) {
	P0_Logger << " Character Attack Animation Timer Failed " << std::endl;
	return 0; //end of timer
}
}

//Callback method that will launch the arrow attack animation
unsigned int Daemons::Character_Arrow_Animation(unsigned int interval, void* args)
{
try {
	
	if ( myCharacter->Set_Arrow_Sprite_Coordinate() ) //arrow anim is still ocuring than loop
	{ return interval; } 
	
	//if the attack was succesfull
	if ( (myCharacter->Get_Attack_Successfull() != 0 ) && ( myCharacter->Get_Attack_Style() == 2 ) )
	{//Now that arrow anim is finished, remove Dead monsters from theirs respective vector
		Monster_Vector_Skeleton = Monster_Factory_Skeleton->Remove_Dead_Monsters();
		Monster_Vector_Worm = Monster_Factory_Worm->Remove_Dead_Monsters();
	}
	return 0; //end of timer
	
} catch (...) {
	P0_Logger << " Character's Arrow Animation Timer Failed " << std::endl;
	return 0; //end of timer
}
}
