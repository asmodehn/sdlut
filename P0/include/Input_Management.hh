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
		Timer<Daemons> myCharacter_Attack_Animation_Timer;
		Timer<Daemons> myCharacter_Move_Animation_Timer;
		Timer<Daemons> myCharacter_Arrow_Animation_Timer;

		//Variables designed to be defined externaly
		Character_Base* myCharacter; //The Character Definition
		Escape_Menu* myEsc_Menu; //The escape menu definition
		std::vector<BattleField_Sprite*> BackGround_Sprite_Vector; //Vector which will contains all BackGround type and clip
		std::vector<BattleField_Sprite*> Environment_Sprite_Vector; //Vector which will contains all Environment items type and clip
		Monster_Factory<Monster_Skeleton>* Monster_Factory_Skeleton; //A factory of Monster Skeletons
		std::vector<Monster_Base*> Monster_Vector_Skeleton; //Vector which will contains all skeletons
		Monster_Factory<Monster_Worm>* Monster_Factory_Worm; //A factory of Monster Worms
		std::vector<Monster_Base*> Monster_Vector_Worm; //Vector which will contains all skeletons
		Render_Engine* myRender_Engine; //Engine
		Daemons* myDaemons; //Daemons

		//Method which will call all the method used when there is a deplacement by the character without knowing the direction of the movement
		void Character_Moves_Consequences();
		//Method which will call all the method used when there is an attack by the character
		void Character_Attack_Consequences();

	public:

		//Accessor
		void Set_Character_Base(Character_Base* newCharacterBase)
		{
			myCharacter = newCharacterBase;
		}
		void Set_Esc_Menu(Escape_Menu* newEsc_Menu)
		{
			myEsc_Menu = newEsc_Menu;
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
		void Set_Monster_Vector_Skeleton(std::vector<Monster_Base*> newMonster_Vector_Skeleton)
		{
			Monster_Vector_Skeleton = newMonster_Vector_Skeleton;
		}
		void Set_Monster_Factory_Worm(Monster_Factory<Monster_Worm>* newMonster_Factory_Worm)
		{
			Monster_Factory_Worm = newMonster_Factory_Worm;
		}
		void Set_Monster_Vector_Worm(std::vector<Monster_Base*> newMonster_Vector_Worm)
		{
			Monster_Vector_Worm = newMonster_Vector_Worm;
		}
		void Set_Render_Engine(Render_Engine* newRender_Engine)
		{
			myRender_Engine = newRender_Engine;
		}
		void Set_Daemons(Daemons* newDaemons)
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
		virtual bool handleKeyEvent (const Sym &s, bool pressed);
    
};

#endif
