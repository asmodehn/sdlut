#ifndef Input_Management_HH
#define Input_Management_HH

#include "Character_Base.hh"
#include "Monster_Factory.hh"
#include "Base.hh"
#include "Menus.hh"

class KeyboardInput : public Keyboard
{
	private:
		//The Character Definition
		Character_Base* Character;
		//The escape menu definition
		Escape_Menu* Esc_Menu;

	public:

		//Constructor 
		KeyboardInput();

		void Set_quitRequested(int new_quitRequested)
		{
			_quitRequested=new_quitRequested;
		}
		int Get_quitRequested()
		{
			return _quitRequested;
		}

		//Inform the keyboard of the current character instance and of the escape menu instance
		void Update_Character_Knowledge(Character_Base* character, Escape_Menu* esc_menu);

		//Manage the key pressed
		virtual bool handleKeyEvent (const Sym &s, bool pressed);
    
};

#endif
