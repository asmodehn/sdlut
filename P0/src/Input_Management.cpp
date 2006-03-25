#include "Input_Management.hh"

KeyboardInput::KeyboardInput()
{
	GLOBAL_GAME_STATE = 3; //Set the game_state to 3, ingame, by default
}

//Inform the keyboard of the current character and of the esc menu
void KeyboardInput::Update_Character_Knowledge(Character_Base* character, Escape_Menu* esc_menu)
{
	Character = character;
	Esc_Menu = esc_menu;
}
//Managed actions associated to key in function of the context (defined by Global_Game_State)
bool KeyboardInput::handleKeyEvent (const Sym &s, bool pressed)
{
	//Future dev
	if (GLOBAL_GAME_STATE == 1)
	{}
	//Future dev
	else if (GLOBAL_GAME_STATE == 2)
	{}
	//InGame
	else if (GLOBAL_GAME_STATE == 3)
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
					GLOBAL_GAME_STATE = 4;//Escape Menu called
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
	//Escape menu when ingame (Paused Character While The world Continue to live)
	else if (GLOBAL_GAME_STATE == 4)
	{
		if (pressed) //Key pressed
		{
			switch( s.getKey() )
			{
				//Decrement esc menu's selected item id until it reach the top than go back to the bottom
				case KUp:
					if ( Esc_Menu->Get_SelectedItemId() > 1 )
					{
						Esc_Menu->Set_SelectedItemId(Esc_Menu->Get_SelectedItemId() - 1);
					}
					else
					{
						Esc_Menu->Set_SelectedItemId(2); //The bottom SelectItem id is 2 at this time
					}
					break;
				
				//Increment esc menu's selected item id until it reach the bottom than go back to the top
				case KDown:
					if ( Esc_Menu->Get_SelectedItemId() < 2 )
					{
						Esc_Menu->Set_SelectedItemId(Esc_Menu->Get_SelectedItemId() + 1);
					}
					else
					{
						Esc_Menu->Set_SelectedItemId(1); //The top SelectItem id is 1 at this time
					}
					break;

				//Validate the selected esc menu's item id
				case KReturn:
					Esc_Menu->Set_ValidatedItemId( Esc_Menu->Get_SelectedItemId() );
					break;
			}
		}
	}

	return true; //the return is not usefull for now
    
}
