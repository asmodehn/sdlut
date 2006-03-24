#include "Input_Management.hh"

KeyboardInput::KeyboardInput()
{
	Global_Game_State = 3; //Set the game_state to 3, ingame, by default
}

//Inform the keyboard of the current character
void KeyboardInput::Update_Character_Knowledge(Character_Base* character)
{
	Character = character;
}
//Managed actions associated to key in function of the context (defined by Global_Game_State)
bool KeyboardInput::handleKeyEvent (const Sym &s, bool pressed)
{
	bool quit = false;

	//Future dev
	if (Global_Game_State == 1)
	{}
	//Future dev
	else if (Global_Game_State == 2)
	{}
	//InGame
	else if (Global_Game_State == 3)
	{
		if (pressed) //Key pressed
		{
			switch( s.getKey() )
			{
				//Moves Keys
				case KKp8:
				case KUp:
					Character->Set_yVel( Character->Get_yVel() - CH_HEIGHT);
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
					Character->Set_xVel( Character->Get_xVel() + CH_WIDTH);
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
		}
		else // Key released
		{
			switch( s.getKey() )
			{
				//Moves Keys
				case KKp8:
				case KUp:
					Character->Set_yVel( Character->Get_yVel() + CH_HEIGHT);
					break;
				case KKp5:
				case KDown:
					Character->Set_yVel( Character->Get_yVel() - CH_HEIGHT);
					break;
				case KKp7:
				case KLeft:
					Character->Set_xVel( Character->Get_xVel() + CH_WIDTH);
					break;
				case KKp9:
				case KRight:
					Character->Set_xVel( Character->Get_xVel() - CH_WIDTH);
					break;
			}
		}
	}
	//Escape menu when in game (Paused Character While The world Continue to live)
	else if (Global_Game_State == 4)
	{
		quit = true;
		_quitRequested = true; //Will generate the mainloop to close
	}
	return quit;
    
}
