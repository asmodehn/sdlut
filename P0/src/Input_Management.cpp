#include "Input_Management.hh"

//Constructor
KeyboardInput::KeyboardInput()
{
	GLOBAL_GAME_STATE = 3; //Set the game_state to 3, ingame, by default
}
//Private method which will call all the method used when there is a deplacement by the character without knowing the direction of the movement
void KeyboardInput::Player_Moves_Consequences()
{
	//Get Monster's vectors
	//Monster_Vector_Skeleton = myDaemons->Get_Monster_Vector_Skeleton();
	//Monster_Vector_Worm = myDaemons->Get_Monster_Vector_Worm();

	//set character sprite in function of the direction and dont move if it's only a direction change
	if( myPlayer->assign_direction_sprite() == false )
	{ 
      P0_Logger << " Check character direction Failed " << std::endl;    
    }

	if ( myPlayer->Get_Moving_Status() ) //we're really moving but not simply changing the direction
	{
		//Move the character if possible
		if( myPlayer->move(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector)
		 == false )
		{ 
		  P0_Logger << " Move player Failed " << std::endl;    
		}
		
		//Set the camera
		if( myPlayer->following_camera() == false )
		{ 
		  P0_Logger << " Failed to set the camera" << std::endl;    
		}

		//Intervals between animation's frames
		myPlayer_Move_Animation_Timer.setInterval( PLAYER_MOVE_ANIMATION_INTERVAL  );
		//Set the callback method which will define the character appearance on the screen and start animation
		myPlayer_Move_Animation_Timer.setCallback(myDaemons,&Daemons::Player_Move_Animation, (void*)NULL);
		//Start the animation
		myPlayer_Move_Animation_Timer.start();

		//Send the modified character's collision box to daemons
		//myDaemons->Set_Player_Base(myPlayer);
	}
	
	//Send the modified character to the render engine 
	//myRender_Engine->Set_Player_Base(myPlayer);

	//P0_Logger << " Move " << std::endl;
}
//Private method which will call all the method used when there is an attack by the character
void KeyboardInput::Player_Attack_Consequences()
{
	//attack is occuring
	myPlayer->Set_Attack_Status(true);

	//Get Monster's vectors
	/*Monster_Vector_Skeleton = myDaemons->Get_Monster_Vector_Skeleton();
	Monster_Vector_Worm = myDaemons->Get_Monster_Vector_Worm();*/
	
	//Handle attacks & set the distance of the attack
	/***WARNING !! IN CASE OF DISTANT ATTACK THE MONSTER IS CONSIDERED AS DEAD WHEN THE KEY IS PRESSED AND NOT WHEN THE ARROW REACHED THE TARGET => TODO: FIND A WAY TO SOLVE THAT (SEPARATE THE ATTACK METHOD IN TWO DISTINCT METHOD PERHAPS CAN HELP)***/
	myPlayer->Set_Hit_Monster_Distance( myPlayer->attack(Global_Monster_Vector) );
	
	//Set the callback method which will define the character appearance on the screen and start animation
	myPlayer_Attack_Animation_Timer.setCallback(myDaemons,&Daemons::Player_Attack_Animation, (void*)NULL);
	
	//difference between attack styles
	if ( myPlayer->Get_Attack_Style() == 1 ) 
	{
		//Intervals between animation's frames
		myPlayer_Attack_Animation_Timer.setInterval( PLAYER_SWORD_ATTACK_ANIMATION_INTERVAL );
	}
	else if ( myPlayer->Get_Attack_Style() == 2 )
	{
		//Intervals between animation's frames
		myPlayer_Attack_Animation_Timer.setInterval( PLAYER_BOW_ATTACK_ANIMATION_INTERVAL );
		//Arrow management
		myPlayer_Arrow_Animation_Timer.setInterval( PLAYER_ARROW_MOVE_ANIMATION_INTERVAL );
		myPlayer_Arrow_Animation_Timer.setCallback(myDaemons,&Daemons::Player_Arrow_Animation, (void*)NULL);
	}
	
	//Start the attack animation
	myPlayer_Attack_Animation_Timer.start();
	
	//In case of distant attack only
	if ( myPlayer->Get_Attack_Style() == 2 )
	{
		//Start arrow animation
		myPlayer_Arrow_Animation_Timer.start();
	}


	//Send the modified character to the render engine 
	//myRender_Engine->Set_Player_Base(myPlayer);

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
			//switch( s.getKey() )
			//{
			if ( !myPlayer->Get_Attack_Status() ) //If attack is occuring then no keys are available except escape/options keys
			/************SEEMS TO BUG HERE WHEN CHANGING WEAPON DURING ATTACK ?****************/
			{
				bool move_key_pressed = false;

				//Moves Keys
				if ((s.getKey() == UP_1) || (s.getKey() == UP_2))
				{
					//myCharacter->Set_yVel( myCharacter->Get_yVel() - CH_HEIGHT);
					myPlayer->Set_yVel( myPlayer->Get_yVel() - 1);
					move_key_pressed = true;
					
				}
				if ((s.getKey() == DOWN_1) || (s.getKey() == DOWN_2))
				{
					//myCharacter->Set_yVel( myCharacter->Get_yVel() + CH_HEIGHT);
					myPlayer->Set_yVel( myPlayer->Get_yVel() + 1);
					move_key_pressed = true;;
				}
				if ((s.getKey() == LEFT_1) || (s.getKey() == LEFT_2))
				{
					//myCharacter->Set_xVel( myCharacter->Get_xVel() - CH_WIDTH);
					myPlayer->Set_xVel( myPlayer->Get_xVel() - 1);
					move_key_pressed = true;
				}
				if ((s.getKey() == RIGHT_1) || (s.getKey() == RIGHT_2))
				{
					//myCharacter->Set_xVel( myCharacter->Get_xVel() + CH_WIDTH);
					myPlayer->Set_xVel( myPlayer->Get_xVel() + 1);
					move_key_pressed = true;
				} 
				 //a movement key has been pressed
				if (move_key_pressed)
					Player_Moves_Consequences();

				if ((s.getKey() == ATTACK_1) || (s.getKey() == ATTACK_2)) //Attacks Key
				{
					//Stop moving
					myPlayer->Set_xVel(0);
					myPlayer->Set_yVel(0);
					Player_Attack_Consequences();
				}
				if ((s.getKey() == CHANGE_ATTACK_MODE_1) || (s.getKey() == CHANGE_ATTACK_MODE_2))
				{
					//Change weapon style by looping between the available styles (2 for the moment)
					myPlayer->Set_Attack_Style( myPlayer->Get_Attack_Style() + 1 );
					if (myPlayer->Get_Attack_Style() > 2) { myPlayer->Set_Attack_Style(1); } //loop between style
					//Update the graphic style of the character
					if( myPlayer->Update_Graphic_Style() == false )
                    { 
						P0_Logger << " Update Graphic Style FAILED " << std::endl;
                    }
					//Send the modified character to the render engine 
					//myRender_Engine->Set_Player_Base(myPlayer);
				}
				if ((s.getKey() == KKEnter) || (s.getKey() == KKEnter))
				{
					//Leave/appears on the Battlefield and save but do not quit
					//case KKEnter:
					//To DO *******
					
				}
			}
			
			//Windows <--> Fullscreen
			if ((s.getKey() == WINDOW_MODE_1) || (s.getKey() == WINDOW_MODE_2))
			{
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
			}
			

			//Menu call
			if ((s.getKey() == MENU_CALL_1) || (s.getKey() == MENU_CALL_2))
			{

				GLOBAL_GAME_STATE = 4;//Escape Menu called
			}
		}
		else // Key released
		{
				//Moves Keys released => no velocity
				if ( (s.getKey() == UP_1) || (s.getKey() == UP_2) || (s.getKey() == DOWN_1) || (s.getKey() == DOWN_2) )
					myPlayer->Set_yVel(0);
				if ( (s.getKey() == LEFT_1) || (s.getKey() == LEFT_2) || (s.getKey() == RIGHT_1) || (s.getKey() == RIGHT_2) )
					myPlayer->Set_xVel(0);
		}
	}
	//Escape menu when ingame (Paused Character While The world Continue To Live)
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
					App::getInstance().getMixer()->playChannel(EscMenuButtonFx_Chan);
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
					//myRender_Engine->Set_Esc_Menu(myEsc_Menu);
					break;
				
				//Increment esc menu's selected item id until it reach the bottom than go back to the top
				case KDown:
					//play menu Fx
					//App::getInstance().getMixer()->toggleChannel(App::getInstance().getMixer()->mixSound(EscMenuButtonFx, true));
					//App::getInstance().getMixer()->Play();
					App::getInstance().getMixer()->playChannel(EscMenuButtonFx_Chan);
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
					//myRender_Engine->Set_Esc_Menu(myEsc_Menu);
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
	//Victory: Nothing work anymore we'll simply draw the score than quit.
	else if (GLOBAL_GAME_STATE == 5)
	{
		if (pressed) //Key pressed
		{
			switch( s.getKey() )
			{
				case KReturn:
				case KKEnter:
				case KEscape:
					//Save time in file
					myVictory_Screen->Save_Time();
					//Quit
					Set_quitRequested(true);
					break;
			}
		}
	}

	return true; //the return is not usefull for now
    
}
