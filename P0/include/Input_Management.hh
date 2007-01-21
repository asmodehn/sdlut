#ifndef Input_Management_HH
#define Input_Management_HH

//#include "Character_Base.hh"
//#include "Monster_Factory.hh"
#include "Base.hh"
//#include "Menus.hh"
#include "Render_Engine.hh"
#include "Daemons.hh"

class KeyboardInput : public Keyboard
{
	private:
		//Character attack animation timer
		Timer<Daemons> myPlayer_Attack_Animation_Timer;
		Timer<Daemons> myPlayer_Move_Animation_Timer;
		Timer<Daemons> myPlayer_Arrow_Animation_Timer;

		//Variables designed to be defined externaly
		Player_Base* myPlayer; //The Character Definition
		Escape_Menu* myEsc_Menu; //The escape menu definition
		std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector; //Vector which will contains all BackGround type and clip
		std::vector<BattleField_Sprite*>* Environment_Sprite_Vector; //Vector which will contains all Environment items type and clip
		Monster_Factory<Monster_Skeleton>* Monster_Factory_Skeleton; //A factory of Monster Skeletons
		//std::vector<Character_Base*> Monster_Vector_Skeleton; //Vector which will contains all skeletons
		Monster_Factory<Monster_Worm>* Monster_Factory_Worm; //A factory of Monster Worms
		//std::vector<Character_Base*> Monster_Vector_Worm; //Vector which will contains all skeletons
		std::vector< std::vector<Character_Base*> *>* Global_Player_Vector; //Pointer to the vector that contains pointer to all vectors of player
		std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector; //Pointer to the vector that contains pointer to all vectors of monster
		Render_Engine* myRender_Engine; //Engine
		Daemons* myDaemons; //Daemons

		//Method which will call all the method used when there is a deplacement by the character without knowing the direction of the movement
		void Player_Moves_Consequences();
		//Method which will call all the method used when there is an attack by the character
		void Player_Attack_Consequences();

	public:

		//Accessor
		inline void Set_Player_Base(Player_Base* newPlayerBase)
		{
			myPlayer = newPlayerBase;
		}
		inline void Set_Esc_Menu(Escape_Menu* newEsc_Menu)
		{
			myEsc_Menu = newEsc_Menu;
		}
		inline void Set_BackGround_Sprite_Vector(std::vector<BattleField_Sprite*>* newBackGround_Sprite_Vector)
		{
			BackGround_Sprite_Vector = newBackGround_Sprite_Vector;
		}
		inline void Set_Environment_Sprite_Vector(std::vector<BattleField_Sprite*>* newEnvironment_Sprite_Vector)
		{
			Environment_Sprite_Vector = newEnvironment_Sprite_Vector;
		}
		inline void Set_Monster_Factory_Skeleton(Monster_Factory<Monster_Skeleton>* newMonster_Factory_Skeleton)
		{
			Monster_Factory_Skeleton = newMonster_Factory_Skeleton;
		}
		/*void Set_Monster_Vector_Skeleton(std::vector<Character_Base*> newMonster_Vector_Skeleton)
		{
			Monster_Vector_Skeleton = newMonster_Vector_Skeleton;
		}*/
		inline void Set_Monster_Factory_Worm(Monster_Factory<Monster_Worm>* newMonster_Factory_Worm)
		{
			Monster_Factory_Worm = newMonster_Factory_Worm;
		}
		/*void Set_Monster_Vector_Worm(std::vector<Character_Base*> newMonster_Vector_Worm)
		{
			Monster_Vector_Worm = newMonster_Vector_Worm;
		}*/
		inline void Set_Global_Player_Vector(std::vector< std::vector<Character_Base*> *>* newGlobal_Player_Vector)
		{
			Global_Player_Vector = newGlobal_Player_Vector;
		}
		inline void Set_Global_Monster_Vector(std::vector< std::vector<Character_Base*> *>* newGlobal_Monster_Vector)
		{
			Global_Monster_Vector = newGlobal_Monster_Vector;
		}
		inline void Set_Render_Engine(Render_Engine* newRender_Engine)
		{
			myRender_Engine = newRender_Engine;
		}
		inline void Set_Daemons(Daemons* newDaemons)
		{
			myDaemons = newDaemons;
		}

		//Constructor 
		KeyboardInput();

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
    
};

#endif
