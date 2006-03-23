#include "Input_Management.hh"

//Construtor
KeyboardInput::KeyboardInput(Character_Base* character)
{
	Character_Base* Character = character;
}
//Destructor
KeyboardInput::~KeyboardInput()
{
}
bool KeyboardInput::handleKeyEvent (const Sym &s, bool pressed)
{
	bool quit = false;
	//This variable definied the global game state 1: Initial Menu (future dev), 2: Character Creation/Selection (future dev), 3: Ingame, 4: On Escape menu
	int Global_Game_State = 3;

	//Future dev
	if (Global_Game_State == 1)
	{}
	//Future dev
	else if (Global_Game_State == 2)
	{}
	//InGame
	else if (Global_Game_State == 3)
	{
		switch( s.getKey() )
		{
			//Moves Keys
			case KKp8:
			case KUp:
				Character->Set_xVel( Character->Get_xVel() - CH_HEIGHT);
				break;
			case KKp5:
			case KDown:
				Character->Set_yVel( Character->Get_yVel() + CH_HEIGHT);
				break;
			case KKp7:
			case KLeft:
				Character->Set_xVel( Character->Get_xVel() - CH_WIDTH);
				break;
			case KKp9:
			case KRight:
				Character->Set_yVel( Character->Get_yVel() + CH_WIDTH);
				break;

			//Attacks Key
			case KKDivide:
			case KRctrl:
				Character->Set_Attack_Status(true);
				break;
			//Change weapon style by looping between the available styles (2 for the moment)
			case KKMultiply:
			case KRShift:
				Character->Set_Attack_Style( Character->Get_Attack_Style() + 1 );
				if (Character->Get_Attack_Style() > 2) { Character->Set_Attack_Style(1); }
				break;

			//Leave/appears on the Battlefield and save but do not quit
			case KKEnter:
				//To DO *******
				break;

			//Esc Key Pressed
			case KEscape:
				Global_Game_State = 4;//Escape Menu called
				break;
		}
		return quit;
	}
	//Escape menu when in game (Paused Character While The world Continu to live)
	else if (Global_Game_State == 4)
	{
		quit = true;
	}
	return quit;
    
}
