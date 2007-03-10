#ifndef Input_Management_HH
#define Input_Management_HH

#include "Monster_Factory.hh"
#include "NPCs.hh"
#include "Player.hh"
//#include "Base.hh"
#include "Menus.hh"
//#include "Render_Engine.hh"
#include "Daemons.hh"

class KeyboardInput : public Keyboard
{
	private:
		//Character attack animation timer
		Timer<Daemons>* myPlayer_Attack_Animation_Timer;
		Timer<Daemons>* myPlayer_Move_Animation_Timer;
		Timer<Daemons>* myPlayer_Arrow_Animation_Timer;

		//Variables designed to be defined externaly
		Player* myPlayer; //The Player Definition
		NPCs* myNPC; //The NPC Definition
		std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector; //Vector which will contains all BackGround type and clip
		std::vector<BattleField_Sprite*>* Environment_Sprite_Vector; //Vector which will contains all Environment items type and clip
		Monster_Factory<Monster_Skeleton>* Monster_Factory_Skeleton; //A factory of Monster Skeletons
		Monster_Factory<Monster_Worm>* Monster_Factory_Worm; //A factory of Monster Worms
		std::vector< std::vector<Character_Base*> *>* Global_Player_Vector; //Pointer to the vector that contains pointer to all vectors of player
		std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector; //Pointer to the vector that contains pointer to all vectors of monster
		Escape_Menu* myEsc_Menu; //The escape menu definition
		Victory_Screen* myVictory_Screen; //The victory screen def
		Daemons* myDaemons; //Daemons

	public:

		//Def 
		KeyboardInput(Player* &myPlayer, NPCs* &myNPC, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector,
				 Monster_Factory<Monster_Skeleton>* &Monster_Factory_Skeleton, Monster_Factory<Monster_Worm>* &Monster_Factory_Worm,
				 std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector,
				 Escape_Menu* &myEsc_Menu, Victory_Screen* &myVictory_Screen, Daemons* &myDaemons
				 );
		~KeyboardInput();

		void Set_quitRequested(bool new_quitRequested)
		{
			_quitRequested=new_quitRequested;
		}
		bool Get_quitRequested()
		{
			return _quitRequested;
		}

		//Manage the key pressed
		bool handleKeyEvent (const Sym &s, bool pressed);
    
		//Method which will call all the method used when there is a deplacement by the character without knowing the direction of the movement
		void Player_Moves_Consequences();
		//Method which will call all the method used when there is an attack by the character
		void Player_Attack_Consequences();
};

#endif
