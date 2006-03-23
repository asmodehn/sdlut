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

	public:

		KeyboardInput(Character_Base* character);
		~KeyboardInput();
		virtual bool handleKeyEvent (const Sym &s, bool pressed);
    
};

#endif
