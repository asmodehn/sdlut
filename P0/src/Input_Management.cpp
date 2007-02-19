#include "Input_Management.hh"

//Constructor
KeyboardInput::KeyboardInput()
{
	myPlayer = new Player_Base(0,0);
	myEsc_Menu = new Escape_Menu();
	myVictory_Screen = new Victory_Screen();
	BackGround_Sprite_Vector = new std::vector<BattleField_Sprite*>;
	Environment_Sprite_Vector = new std::vector<BattleField_Sprite*>;
	Monster_Factory_Skeleton = new Monster_Factory<Monster_Skeleton>;
	Monster_Factory_Worm = new Monster_Factory<Monster_Worm>;
	Global_Player_Vector = new std::vector< std::vector<Character_Base*> *>;
	Global_Monster_Vector= new std::vector< std::vector<Character_Base*> *>;
	myDaemons = new Daemons;

	//GLOBAL_GAME_STATE = 3; //Set the game_state to 3, ingame, by default
	P0_Logger << nl << "Input mgt CONSTRUCTED Successfully " << std::endl;
}
//Private method which will call all the method used when there is a deplacement by the character without knowing the direction of the movement
void KeyboardInput::Player_Moves_Consequences(unsigned long deltaticks)
{
	//P0_Logger << nl << "x: " << myPlayer->Get_X() << std::endl;
	//P0_Logger << nl << "y: " << myPlayer->Get_Y() << std::endl;
	//P0_Logger << nl << "xVel: " << myPlayer->Get_xVel() << std::endl;
	//P0_Logger << nl << "yVel: " << myPlayer->Get_yVel() << std::endl;
	
	//a movement has been triggered
	if ( (myPlayer->Get_xVel() != 0) || (myPlayer->Get_yVel() != 0) )
	{
		//set character sprite in function of the direction and dont move if it's only a direction change
		if( myPlayer->assign_direction_sprite() == false )
		{ 
			P0_Logger << nl << "Check character direction Failed " << std::endl;    
		}

		if ( myPlayer->Get_Moving_Status() ) //we're really moving but not simply changing the direction
		{
			//Move the character if possible
			if( myPlayer->move(deltaticks, Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector)
			 == false )
			{ 
				P0_Logger << nl << "Move player Failed " << std::endl;    
			}
			
			//Set the camera
			if( myPlayer->following_camera() == false )
			{ 
				P0_Logger << nl << "Failed to set the camera" << std::endl;    
			}

			//Intervals between animation's frames
			myPlayer_Move_Animation_Timer.setInterval( PLAYER_MOVE_ANIMATION_INTERVAL  );
			//Set the callback method which will define the character appearance on the screen and start animation
			myPlayer_Move_Animation_Timer.setCallback(myDaemons,&Daemons::Player_Move_Animation, (void*)NULL);
			//Start the animation
			myPlayer_Move_Animation_Timer.start();
		}

		//P0_Logger << nl << "Move " << std::endl;
	}
}
//Private method which will call all the method used when there is an attack by the character
void KeyboardInput::Player_Attack_Consequences()
{
	//attack is occuring
	myPlayer->Set_Attack_Status(true);

	
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

	//P0_Logger << nl << "Attack " << std::endl;
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
				//bool move_key_pressed = false;

				//Moves Keys
				if ((s.getKey() == RIGHT_1) || (s.getKey() == RIGHT_2))
				{
					//myCharacter->Set_xVel( myCharacter->Get_xVel() + CH_WIDTH);
					//myPlayer->Set_xVel( myPlayer->Get_xVel() + 1);
					if (myPlayer->Get_xVel() != CH_VEL )
						myPlayer->Set_xVel( myPlayer->Get_xVel() + CH_VEL);

					//move_key_pressed = true;
				} 
				if ((s.getKey() == DOWN_1) || (s.getKey() == DOWN_2))
				{
					//myCharacter->Set_yVel( myCharacter->Get_yVel() + CH_HEIGHT);
					//myPlayer->Set_yVel( myPlayer->Get_yVel() + 1);
					if (myPlayer->Get_yVel() != CH_VEL )
						myPlayer->Set_yVel( myPlayer->Get_yVel() + CH_VEL);
					//move_key_pressed = true;;
				}
				if ((s.getKey() == LEFT_1) || (s.getKey() == LEFT_2))
				{
					//myCharacter->Set_xVel( myCharacter->Get_xVel() - CH_WIDTH);
					//myPlayer->Set_xVel( myPlayer->Get_xVel() - 1);
					if (myPlayer->Get_xVel() != (-1*CH_VEL) )
						myPlayer->Set_xVel( myPlayer->Get_xVel() - CH_VEL);
					//move_key_pressed = true;
				}
				if ((s.getKey() == UP_1) || (s.getKey() == UP_2))
				{
					//myCharacter->Set_yVel( myCharacter->Get_yVel() - CH_HEIGHT);
					//myPlayer->Set_yVel( myPlayer->Get_yVel() - 1);
					if (myPlayer->Get_yVel() != (-1*CH_VEL) )
						myPlayer->Set_yVel( myPlayer->Get_yVel() - CH_VEL);
					//move_key_pressed = true;
					
				}

				 //a movement key has been pressed
				//if (move_key_pressed)
					//Player_Moves_Consequences();

				//Attack Keys
				if ((s.getKey() == ATTACK_1) || (s.getKey() == ATTACK_2)) //Attacks Key
				{
					//Stop moving
					myPlayer->Set_xVel(0);
					myPlayer->Set_yVel(0);
					Player_Attack_Consequences();
				}

				//Attack Mode
				if ((s.getKey() == CHANGE_ATTACK_MODE_1) || (s.getKey() == CHANGE_ATTACK_MODE_2))
				{
					//Change weapon style by looping between the available styles (2 for the moment)
					myPlayer->Set_Attack_Style( myPlayer->Get_Attack_Style() + 1 );
					if (myPlayer->Get_Attack_Style() > 2) { myPlayer->Set_Attack_Style(1); } //loop between style
					//Update the graphic style of the character
					if( myPlayer->Update_Graphic_Style() == false )
                    { 
						P0_Logger << nl << "Update Graphic Style FAILED " << std::endl;
                    }
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
					P0_Logger << nl << "Create Surface Failed : " << GetError() << std::endl;
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

				//Leave menu without validating
				case KEscape:
					//Work as if No has been selected
					myEsc_Menu->Manage_Validation( 2 );
					break;

				//Validate the selected esc menu's item id
				case KReturn:
					//Manage esc menu validation: leave the game if return is true
					Set_quitRequested( myEsc_Menu->Manage_Validation( myEsc_Menu->Get_SelectedItemId() ) );
					break;
			}
		}
	}
	//Victory: END, we'll simply draw the score than quit.
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
