#ifndef Project0_HH
#define Project0_HH

//#include "Monster_Factory.hh"
//#include "Monsters.hh"
//#include "Character_Base.hh"
#include "Render_Engine.hh"
//#include "Input_Management.hh"
//#include "Menus.hh"
//#include "BattleField.hh"


//Variable Declaration
BackGround* myBackGround; 
std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector;

Environment* myEnvironment;
std::vector<BattleField_Sprite*>* Environment_Sprite_Vector;

std::vector< std::vector<Character_Base*> *>* Global_Player_Vector;
std::vector<Character_Base*>* NPCs_Vector;
NPC_Merchant* myNPC;
std::vector<Character_Base*>* Players_Vector;
Player* myPlayer;

std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector;
Monster_Factory<Monster_Skeleton>* Monster_Factory_Skeleton;
Monster_Factory<Monster_Worm>* Monster_Factory_Worm;

Escape_Menu* myEsc_Menu;
Victory_Screen* myVictory_Screen;
Messages* myMessages;

Daemons* myDaemons;
Timer<Daemons>* myMonster_Factory_Monsters_Generation_Timer;
Timer<Daemons>* myScore;

KeyboardInput* myKeyboardInput;
Render_Engine* myRender_Engine;


//Methods
	//Initialization
bool InitEverything();
	//Implementation
void ImplementEverything();
	//Run
void RunGame();
	//Clean Up
bool CleanEverything();

#endif
