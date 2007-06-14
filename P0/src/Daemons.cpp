#include "Daemons.hh"

//Constructor
Daemons::Daemons(Player* &myPlayer, NPC_Merchant* &myNPC, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector,
				 Monster_Factory<Monster_Skeleton>* &Monster_Factory_Skeleton, Monster_Factory<Monster_Worm>* &Monster_Factory_Worm,
				 std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector
				 )
{
	//Allocations
	/*myPlayer = new Player();
	myNPC = new NPC_Merchant();
	BackGround_Sprite_Vector = new std::vector<BattleField_Sprite*>;
	Environment_Sprite_Vector = new std::vector<BattleField_Sprite*>;
	Monster_Factory_Skeleton = new Monster_Factory<Monster_Skeleton>;
	Monster_Factory_Worm = new Monster_Factory<Monster_Worm>;
	Global_Player_Vector = new std::vector< std::vector<Character_Base*> *>;
	Global_Monster_Vector = new std::vector< std::vector<Character_Base*> *>;*/
	this->myPlayer = myPlayer;
	this->myNPC = myNPC;
	this->BackGround_Sprite_Vector = BackGround_Sprite_Vector;
	this->Environment_Sprite_Vector = Environment_Sprite_Vector;
	this->Monster_Factory_Skeleton = Monster_Factory_Skeleton;
	this->Monster_Factory_Worm = Monster_Factory_Worm;
	this->Global_Player_Vector = Global_Player_Vector;
	this->Global_Monster_Vector = Global_Monster_Vector;

	P0_Logger << nl << "Deamons CONSTRUCTED Successfully " << std::endl;
}
//Destructor
Daemons::~Daemons()
{
	P0_Logger << nl << "Deamons DESTRUCTED Successfully " << std::endl;
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

} catch (std::exception &exc) {
	P0_Logger << nl << "From Monster_Factory::Move_Monsters(), " << (string)exc.what() << std::endl;
	return interval; //loop
} catch (...) {
	P0_Logger << nl << "Unhandled Error In Monster_Factory::Move_Monsters()" << std::endl;
	return interval; //loop
}
}

//Callback method that will eventually generate new monster (not to near from the character!)
unsigned int Daemons::Generate_Monsters(unsigned int interval, void* args)
{
try {
	if (GLOBAL_GAME_STATE != 5 )//victory 
	{
		//Skeletons
		Monster_Factory_Skeleton->Generate_New_Monster( Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector );
		//Worms
		Monster_Factory_Worm->Generate_New_Monster( Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector );

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

//Callback method that will call npcs movement
unsigned int Daemons::Move_NPCs(unsigned int interval, void* args)
{
try {
	if (GLOBAL_GAME_STATE != 5 )//victory 
	{
		myNPC->Move(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector);
		P0_Logger << nl << "Move NPC_Merchant " << std::endl;
		return interval; // loop
	} else { //Victory: end of timer
		return 0;
	}
} catch (std::exception &exc) {
	P0_Logger << nl << "Move NPC_Merchant Daemon Failed " << (string)exc.what() << std::endl;
	return interval; // loop
} catch (...) {
	P0_Logger << nl << "Move NPC_Merchant Daemon Failed " << std::endl;
	return interval; // loop
}
}

//Callback method that will launch the arrow attack animation
unsigned int Daemons::Player_Arrow_Movement(unsigned int interval, void* args)
{
try {
	//
	//TODO (future): only "launch" the arrow at the good distant attack animation frame until that w8
	//TODO (future): use real arrow speed depending on character's characteristics
	//

	int xc = myPlayer->Get_Attack_CB().getx() - myPlayer->Get_Attack_Initial_X() ;
	xc *= xc;
	int yc = myPlayer->Get_Attack_CB().gety() - myPlayer->Get_Attack_Initial_Y() ;
	yc *= yc;
	int Distance_2_CH = (int)( sqrt ( (float)( xc + yc ) ) );

	int Arrow_Current_Damage = myPlayer->Get_Real_Inflicted_Damage() - ( Distance_2_CH*myPlayer->Get_Real_Inflicted_Damage()/myPlayer->Get_Real_Range() );

	myPlayer->Set_Attack_Successfull( myPlayer->Attack_Check_Status(myPlayer->Get_Arrow_Vel(), Arrow_Current_Damage, Global_Monster_Vector) );
	
	myPlayer->Set_Arrow_Sprite_Coordinate();

	//if the attack was succesfull
	if (myPlayer->Get_Attack_Successfull() != 0 ) //&& ( myPlayer->Get_Attack_Style() == 2 ) )
	{
		//play hit Fx
		if ( (ENABLE_SFXS_SOUNDS) && (ENABLE_ALL_SOUNDS) )
			App::getInstance().getMixer().playChannel(*HitFx.get(), SFXS_VOLUME);

		////Remove Dead Monsters
		//Monster_Factory_Skeleton->Remove_Dead_Monsters();
		//Monster_Factory_Worm->Remove_Dead_Monsters();
	} 
	else
	{ 
		if ( Distance_2_CH <= myPlayer->Get_Real_Range() ) //arrow anim is still occuring than loop
			return interval;

		//play miss Fx	
		if ( (ENABLE_SFXS_SOUNDS) && (ENABLE_ALL_SOUNDS) )
			App::getInstance().getMixer().playChannel(*MissFx.get(), SFXS_VOLUME);
	} 
	
	//set attack msg, reset & end timer
	myPlayer->Set_Attack_Msg();
	myPlayer->Set_Arrow_X(myPlayer->Get_X());
	myPlayer->Set_Arrow_Y(myPlayer->Get_Y());
	myPlayer->Set_Attack_Initial_X(-1);
	myPlayer->Set_Attack_Initial_Y(-1);
	myPlayer->Set_Attack_Direction(-1);
	return 0; 
	
} catch (...) {
	P0_Logger << nl << "Player's Arrow Animation Timer Failed " << std::endl;
	return 0; //end of timer
}
}

//Callback method that will manage score
unsigned int Daemons::Score(unsigned int interval, void* args)
{
//try {

	if (ALiVE_MONSTERS > 0)
		return interval;

	FiNiSH_TiME = (unsigned)time( NULL ) - FiNiSH_TiME;

	GLOBAL_GAME_STATE = 5;

	return 0; //end of timer
	
//} catch (...) {
//	P0_Logger << nl << "Score manager Failed " << std::endl;
//	return 0; //end of timer
//}
}
