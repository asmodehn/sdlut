#ifndef Input_Management_HH
#define Input_Management_HH

#include "Character_Base.hh"
#include "Monster_Factory.hh"
#include "Base.hh"

class KeyboardInput : public Keyboard
{
	private:
		//The Character Definition
		Character_Base* Character;
		//This variable definied the global game state 1: Initial Menu (future dev), 2: Character Creation/Selection (future dev), 3: Ingame, 4: On Escape menu
		int Global_Game_State;

	public:

		//Constructor 
		KeyboardInput();

		//Inform the keyboard of the current character instance
		void Update_Character_Knowledge(Character_Base* character);

		//Manage the key pressed
		virtual bool handleKeyEvent (const Sym &s, bool pressed);
    
};

#endif
