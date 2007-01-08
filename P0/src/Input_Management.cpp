#include "Input_Management.hh"

//Constructor
KeyboardInput::KeyboardInput()
{
	GLOBAL_GAME_STATE = 3; //Set the game_state to 3, ingame, by default
}
//Private method which will call all the method used when there is a deplacement by the character without knowing the direction of the movement
void KeyboardInput::Character_Moves_Consequences()
{
	//Get Monster's vectors
	Monster_Vector_Skeleton = myDaemons->Get_Monster_Vector_Skeleton();
	Monster_Vector_Worm = myDaemons->Get_Monster_Vector_Worm();

	//Move the character if possible
	if( myCharacter->move(Environment_Sprite_Vector, BackGround_Sprite_Vector, Monster_Vector_Skeleton, Monster_Vector_Worm)
	 == false )
	{ 
      P0_Logger << " Move character Failed " << std::endl;    
    }
	
	//Set the camera
	if( myCharacter->following_camera() == false )
	{ 
      P0_Logger << " Failed to set the camera" << std::endl;    
    }
	
	//check character looking direction
	if( myCharacter->check_character_direction() == false )
	{ 
      P0_Logger << " Check character direction Failed " << std::endl;    
    }

	//Send the modified character to the render engine 
	myRender_Engine->Set_Character_Base(myCharacter);

	//Send the modified character's collision box to daemons
	myDaemons->Set_Character_Base(myCharacter);

	//Intervals between animation's frames
	myCharacter_Move_Animation_Timer.setInterval( CHARACTER_MOVE_ANIMATION_INTERVAL  );
	//Set the callback method which will define the character appearance on the screen and start animation
	myCharacter_Move_Animation_Timer.setCallback(myDaemons,&Daemons::Character_Move_Animation, (void*)NULL);
	//Start the animation
	myCharacter_Move_Animation_Timer.start();

	//P0_Logger << " Move " << std::endl;
}
//Private method which will call all the method used when there is an attack by the character
void KeyboardInput::Character_Attack_Consequences()
{
	//attack is occuring
	myCharacter->Set_Attack_Status(true);

	//Get Monster's vectors
	Monster_Vector_Skeleton = myDaemons->Get_Monster_Vector_Skeleton();
	Monster_Vector_Worm = myDaemons->Get_Monster_Vector_Worm();
	
	//Handle attacks & set the distance of the attack
	/***WARNING !! IN CASE OF DISTANT ATTACK THE MONSTER IS CONSIDERED AS DEAD WHEN THE KEY IS PRESSED AND NOT WHEN THE ARROW REACHED THE TARGET => TODO: FIND A WAY TO SOLVE THAT (SEPARATE THE ATTACK METHOD IN TWO DISTINCT METHOD EPRHAPS CAN HELP)***/
	myCharacter->Set_Hit_Monster_Distance( myCharacter->attack(Monster_Vector_Skeleton, Monster_Vector_Worm) );
	
	//Intervals between animation's frames
	myCharacter_Attack_Animation_Timer.setInterval( CHARACTER_MELEE_ATTACK_ANIMATION_INTERVAL );
	//Set the callback method which will define the character appearance on the screen and start animation
	myCharacter_Attack_Animation_Timer.setCallback(myDaemons,&Daemons::Character_Attack_Animation, (void*)NULL);
	
	//In case of distant attack only
	if ( myCharacter->Get_Attack_Style() == 2 )
	{
		myCharacter_Arrow_Animation_Timer.setInterval( CHARACTER_ARROW_MOVE_ANIMATION_INTERVAL );
		//Set the callback method which will define the character appearance on the screen and start animation
		myCharacter_Arrow_Animation_Timer.setCallback(myDaemons,&Daemons::Character_Arrow_Animation, (void*)NULL);
	}
	
	//Start the attack animation
	myCharacter_Attack_Animation_Timer.start();
	
	//In case of distant attack only
	if ( myCharacter->Get_Attack_Style() == 2 )
	{
		//Start arrow animation
		myCharacter_Arrow_Animation_Timer.start();
	}


	//Send the modified character to the render engine 
	myRender_Engine->Set_Character_Base(myCharacter);

	//P0_Logger << " Attack " << std::endl;
}

//Managed actions associated to key in function of the player interface context (defined by GLOBAL_GAME_STATE)
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
				if ( !myCharacter->Get_Attack_Status() ) //no attack is occuring if attack not key is available except escape
				{
					//Moves Keys
					case KKp8:
					case KUp:
						myCharacter->Set_yVel( myCharacter->Get_yVel() - CH_HEIGHT);
						Character_Moves_Consequences();
						break;
					case KKp5:
					case KDown:
						myCharacter->Set_yVel( myCharacter->Get_yVel() + CH_HEIGHT);
						Character_Moves_Consequences();
						break;
					case KKp7:
					case KLeft:
						myCharacter->Set_xVel( myCharacter->Get_xVel() - CH_WIDTH);
						Character_Moves_Consequences();
						break;
					case KKp9:
					case KRight:
						myCharacter->Set_xVel( myCharacter->Get_xVel() + CH_WIDTH);
						Character_Moves_Consequences();
						break;

					//Attacks Key
					case KKDivide:
					case KRctrl:
						Character_Attack_Consequences();
						break;

					//Change weapon style by looping between the available styles (2 for the moment)
					case KKMultiply:
					case KRShift:
						myCharacter->Set_Attack_Style( myCharacter->Get_Attack_Style() + 1 );
						if (myCharacter->Get_Attack_Style() > 2) { myCharacter->Set_Attack_Style(1); } //loop between style
						//Update the graphic style of the character
						if( myCharacter->Update_Graphic_Style() == false )
                    	{ 
                            P0_Logger << " Update Graphic Style FAILED " << std::endl;
                        }
						//Send the modified character to the render engine 
						myRender_Engine->Set_Character_Base(myCharacter);
						break;

					//Leave/appears on the Battlefield and save but do not quit
					case KKEnter:
						//To DO *******
						break;

						//Windows <--> Fullscreen
					case KF11:
						//reset the display
						CURRENT_SCREEN_WIDTH = SCREEN_WIDTH;
						CURRENT_SCREEN_HEIGHT = SCREEN_HEIGHT;
						/*if (App::getInstance().getWindow()->resetDisplay(SCREEN_WIDTH, SCREEN_HEIGHT) == NULL  )
						{
							P0_Logger << " Create Surface Failed : " << GetError() << std::endl;
							return false;
						}*/
						//Go to fullscreen
						//App::getInstance().getWindow()->setFullscreen(true);
						//App::getInstance().getWindow()->setFullscreen(!App::getInstance().getWindow()->isFullscreen()); not working dont know why ...
						App::getInstance().getWindow()->setFullscreen(!App::getInstance().getWindow()->resizeDisplay(SCREEN_WIDTH,SCREEN_HEIGHT)->isFullScreenset());
						break;
				}

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
					myCharacter->Set_yVel( myCharacter->Get_yVel() + CH_HEIGHT);
					//Character_Moves_Consequences();
					break;
				case KKp5:
				case KDown:
					myCharacter->Set_yVel( myCharacter->Get_yVel() - CH_HEIGHT);
					//Character_Moves_Consequences();
					break;
				case KKp7:
				case KLeft:
					myCharacter->Set_xVel( myCharacter->Get_xVel() + CH_WIDTH);
					//Character_Moves_Consequences();
					break;
				case KKp9:
				case KRight:
					myCharacter->Set_xVel( myCharacter->Get_xVel() - CH_WIDTH);
					//Character_Moves_Consequences();
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
					//play menu Fx	
					//App::getInstance().getMixer()->toggleChannel(App::getInstance().getMixer()->mixSound(EscMenuButtonFx, true));
					//App::getInstance().getMixer()->Play();
					App::getInstance().getMixer()->toggleChannel(EscMenuButtonFx_Chan);
					//loop between Y/N 
					if ( myEsc_Menu->Get_SelectedItemId() > 1 )
					{
						myEsc_Menu->Set_SelectedItemId(myEsc_Menu->Get_SelectedItemId() - 1);
					}
					else
					{
						myEsc_Menu->Set_SelectedItemId(2); //The bottom SelectItem id is 2 at this time
					}
					//Send the modified Esc_Menu to the render engine 
					myRender_Engine->Set_Esc_Menu(myEsc_Menu);
					break;
				
				//Increment esc menu's selected item id until it reach the bottom than go back to the top
				case KDown:
					//play menu Fx
					//App::getInstance().getMixer()->toggleChannel(App::getInstance().getMixer()->mixSound(EscMenuButtonFx, true));
					//App::getInstance().getMixer()->Play();
					App::getInstance().getMixer()->toggleChannel(EscMenuButtonFx_Chan);
					//loop between Y/N 
					if ( myEsc_Menu->Get_SelectedItemId() < 2 )
					{
						myEsc_Menu->Set_SelectedItemId(myEsc_Menu->Get_SelectedItemId() + 1);
					}
					else
					{
						myEsc_Menu->Set_SelectedItemId(1); //The top SelectItem id is 1 at this time
					}
					//Send the modified Esc_Menu to the render engine 
					myRender_Engine->Set_Esc_Menu(myEsc_Menu);
					break;

				//Validate the selected esc menu's item id
				case KReturn:
					//Esc Menu Validation
					myEsc_Menu->Set_ValidatedItemId( myEsc_Menu->Get_SelectedItemId() );
					//Manage esc menu validation: leave the game if return is true
					Set_quitRequested( myEsc_Menu->Manage_Validation() );
					break;
			}
		}
	}

	return true; //the return is not usefull for now
    
}
