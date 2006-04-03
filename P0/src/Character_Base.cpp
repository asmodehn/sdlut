#include "Character_Base.hh"

//Initialization construtor
Character_Base::Character_Base(int X, int Y, std::vector<Monster_Skeleton*> monster_vector)
{
    //Initial position
	x = X;
	y = Y;
    
    //Initial velocity
    xVel = 0;
    yVel = 0;

	//Character Clips definition
	_character_left_attack[0].setx(0);
	_character_left_attack[0].sety(0);
	_character_left_attack[0].setw(CH_WIDTH);
	_character_left_attack[0].seth(CH_HEIGHT);

	_character_left_attack[1].setx(CH_WIDTH);
    _character_left_attack[1].sety(0);
    _character_left_attack[1].setw(CH_WIDTH);
    _character_left_attack[1].seth(CH_HEIGHT);

	_character_left_attack[2].setx(CH_WIDTH * 2);
    _character_left_attack[2].sety(0);
    _character_left_attack[2].setw(CH_WIDTH);
    _character_left_attack[2].seth(CH_HEIGHT);


    _character_right_attack[0].setx(0);
    _character_right_attack[0].sety(CH_HEIGHT);
    _character_right_attack[0].setw(CH_WIDTH);
    _character_right_attack[0].seth(CH_HEIGHT);
    
    _character_right_attack[1].setx(CH_WIDTH);
    _character_right_attack[1].sety(CH_HEIGHT);
    _character_right_attack[1].setw(CH_WIDTH);
    _character_right_attack[1].seth(CH_HEIGHT);
    
    _character_right_attack[2].setx(CH_WIDTH * 2);
    _character_right_attack[2].sety(CH_HEIGHT);
    _character_right_attack[2].setw(CH_WIDTH);
    _character_right_attack[2].seth(CH_HEIGHT);


	_character_down_attack[0].setx(0);
    _character_down_attack[0].sety(CH_HEIGHT*2);
    _character_down_attack[0].setw(CH_WIDTH);
    _character_down_attack[0].seth(CH_HEIGHT);
    
    _character_down_attack[1].setx(CH_WIDTH);
    _character_down_attack[1].sety(CH_HEIGHT*2);
    _character_down_attack[1].setw(CH_WIDTH);
    _character_down_attack[1].seth(CH_HEIGHT);
    
    _character_down_attack[2].setx(CH_WIDTH * 2);
    _character_down_attack[2].sety(CH_HEIGHT*2);
    _character_down_attack[2].setw(CH_WIDTH);
    _character_down_attack[2].seth(CH_HEIGHT);
    

    _character_up_attack[0].setx(0);
    _character_up_attack[0].sety(CH_HEIGHT*3);
    _character_up_attack[0].setw(CH_WIDTH);
    _character_up_attack[0].seth(CH_HEIGHT);
    
    _character_up_attack[1].setx(CH_WIDTH);
    _character_up_attack[1].sety(CH_HEIGHT*3);
    _character_up_attack[1].setw(CH_WIDTH);
    _character_up_attack[1].seth(CH_HEIGHT);
    
    _character_up_attack[2].setx(CH_WIDTH * 2);
    _character_up_attack[2].sety(CH_HEIGHT*3);
    _character_up_attack[2].setw(CH_WIDTH);
    _character_up_attack[2].seth(CH_HEIGHT);

	//Assign the right sprite to character by deffault
	Character_SpriteRect = _character_right_attack[0];

	//Initialize animation variables
    frame = 0;  // for future moves animation
    move_status = CH_RIGHT;

	//Attack variable
	attack_status = false; //false = 0
	attack_style = 1; //0: nothing (future dev), 1: Melee attack (default), 2: Distant attack, 3: magic attack (future dev)
	attack_successfull = false; //Tells if a monster has been hit, by default no

	//Camera: at the begining it's in the top left corner of the level
	//Camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	Camera.setx(0);
	Camera.sety(0);
	Camera.setw(CURRENT_SCREEN_WIDTH);
	Camera.seth(CURRENT_SCREEN_HEIGHT);

	//Collision Box Definition: The collision box has the size of the character
	collision_box.setx(X);
    collision_box.sety(Y);
    collision_box.setw(CH_WIDTH);
    collision_box.seth(CH_HEIGHT);

	//Attack collsion box: currently in the same place of the character
	attack_collision_box.setx(X);
    attack_collision_box.sety(Y);
    attack_collision_box.setw(CH_WIDTH);
    attack_collision_box.seth(CH_HEIGHT);

	//Msgs displayed in the status bar


	//The monster vector that containt all monsters
	Monster_Vector = monster_vector; 

	/****Arrow***/
	Arrow_Left[0].setx(0);
    Arrow_Left[0].sety(0);
    Arrow_Left[0].setw(CH_WIDTH);
    Arrow_Left[0].seth(CH_HEIGHT);

	Arrow_Right[0].setx(0);
    Arrow_Right[0].sety(CH_HEIGHT);
    Arrow_Right[0].setw(CH_WIDTH);
    Arrow_Right[0].seth(CH_HEIGHT);

	Arrow_Down[0].setx(0);
    Arrow_Down[0].sety(CH_HEIGHT*2);
    Arrow_Down[0].setw(CH_WIDTH);
    Arrow_Down[0].seth(CH_HEIGHT);

	Arrow_Up[0].setx(0);
    Arrow_Up[0].sety(CH_HEIGHT*3);
    Arrow_Up[0].setw(CH_WIDTH);
    Arrow_Up[0].seth(CH_HEIGHT);


	/****Surfaces****/
	//Characters Surfaces
	Characters_Tile_Melee = RGBSurface("data/Character_Fighter.bmp", Color(0xFF, 0xFF, 0xFF));
	Characters_Tile_Distant = RGBSurface("data/Character_Archer.bmp", Color(0xFF, 0xFF, 0xFF));
	Characters_Tile = Characters_Tile_Melee; //Default tile: the melee tile
	//Arrow surface
	Arrow_Tile = RGBSurface("data/Arrow.bmp", Color(0xFF, 0xFF, 0xFF));

	//Fight Msgs Style
	//Font AttackMsg_Font("data/ECHELON.TTF", 28);
	Font AttackMsg_Font("data/SlimSansSerif.ttf", 28);

	//Msgs displayed in the status bar
	attack_msg = RGBSurface(AttackMsg_Font, " ", Color(0xFF, 0xFF, 0xFF), Color(0, 0, 0)); // Empty msg until the attack key is pressed once (when using empty msg the creator crash so until this bug is solved we will use " " insted of "")
	attack_melee_msg_hit = RGBSurface(AttackMsg_Font, "Melee Hit", Color(0xFF, 0xFF, 0xFF), Color(0, 0, 0));
	attack_distant_msg_hit = RGBSurface(AttackMsg_Font, "Distant Hit", Color(0xFF, 0xFF, 0xFF), Color(0, 0, 0));
	attack_melee_msg_miss = RGBSurface(AttackMsg_Font, "Melee Miss", Color(0xFF, 0xFF, 0xFF), Color(0, 0, 0));
	attack_distant_msg_miss = RGBSurface(AttackMsg_Font, "Distant Miss", Color(0xFF, 0xFF, 0xFF), Color(0, 0, 0));
}
//Destructor
Character_Base::~Character_Base()
{
	////Free the msgs
	//attack_msg_hit.~RGBSurface();
	//attack_msg_miss.~RGBSurface();
	//attack_melee_msg_hit.~RGBSurface();
	//attack_melee_msg_miss.~RGBSurface();
	//attack_distant_msg_hit.~RGBSurface();
	//attack_distant_msg_miss.~RGBSurface();

	////Free the surface
	//Characters_Tile.~RGBSurface();
	//Characters_Tile_Melee.~RGBSurface();
	//Characters_Tile_Distant.~RGBSurface();
	//Arrow_Tile.~RGBSurface();
}
//Character Graphic Style Initialiation regarding the attack style
void Character_Base::Update_Graphic_Style()
{
	// Melee Style
	if (attack_style == 1)
	{
		Characters_Tile = Characters_Tile_Melee;
		attack_msg_hit = attack_melee_msg_hit;
		attack_msg_miss = attack_melee_msg_miss;
		//P0_Logger << " Graphic Style Updated To Melee Style : OK " << std::endl;
	}
	// Distant Style
	else if (attack_style == 2)
	{
		Characters_Tile = Characters_Tile_Distant;
		attack_msg_hit = attack_distant_msg_hit;
		attack_msg_miss = attack_distant_msg_miss;
		//P0_Logger << " Graphic Style Updated To Distant Style : OK " << std::endl;
	}
}
//Show the Character on the screen
void Character_Base::move(std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
    //Move the Character collision box to were we want to move
    collision_box.setx(x + xVel);
	collision_box.sety(y + yVel);
    
    //If the Character went too far to the left or right
	if( (collision_box.getx() < 0) || (collision_box.getx() + CH_WIDTH > LEVEL_WIDTH) )
	{
        //move back
        collision_box.setx(x);    
    }
	//If the Character went too far up or down (the -32 is here for the status bar)
	if((collision_box.gety() < 0) || (collision_box.gety() + CH_HEIGHT > LEVEL_HEIGHT-32) )
    {
        //move back
        collision_box.sety(y);    
    }

	//Collision with monster when moving on the x axis
	for(int i=0; i < Monster_Vector.size(); i++)
	{
		if (check_collision(collision_box, Monster_Vector[i]->collision_box))
		{
			//move back
			collision_box.setx(x);
			collision_box.sety(y); 

			//we have found the good item inside the vector, no need to work more
			break;
		}
	}
    
	//Now that all collision has been checked, we must check if the battlefield allow the move
	if(! check_battlefield_allow_character(collision_box.getx(), collision_box.gety(), Environment_Sprite_Vector, BackGround_Sprite_Vector) )
	{
		//move back
		collision_box.setx(x);
		collision_box.sety(y); 
	}

	//Finally move the character in the same place of his collision box
	x = collision_box.getx();
	y = collision_box.gety();

}
//Check if the battlefield allow the character presence
bool Character_Base::check_battlefield_allow_character(int x, int y, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
	//1st, we must check if the environment allow the move
	if( check_environment_allow_character(collision_box.getx(), collision_box.gety(), Environment_Sprite_Vector) == -1)
	{
		//No environement item present, the ground have priority
		if(! check_background_allow_character(collision_box.getx(), collision_box.gety(), BackGround_Sprite_Vector) )
		{
			return false;
		}
	}
	 //environment item present and dont allow presence
	else if( check_environment_allow_character(collision_box.getx(), collision_box.gety(), Environment_Sprite_Vector) == 0)
	{
		return false;
	}
	else //environment item present and allow presence
	{
		return true;
	}

	//allow presence
	return true;
}
//Check if the ground allow the move
bool Character_Base::check_background_allow_character(int x, int y, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
	//loop on all the vector
	for(int i=0; i < BackGround_Sprite_Vector.size(); i++)
	{
		//when we have located the good destination inside the vector,...
		if (( x == BackGround_Sprite_Vector[i]->Get_X() ) && ( y == BackGround_Sprite_Vector[i]->Get_Y() ))
		{
			//...get the destination ground...
			int newGround_Type = BackGround_Sprite_Vector[i]->Get_BattleField_Type();
			
			//...then check if the ground allow the character move
			if( newGround_Type == EMPTY_GROUND ) //Don't allow move
			{
				return false; 
			}
			else if( newGround_Type == GRASS_GROUND ) //Allow move
			{
				return true;
			}
			else if( newGround_Type == SAND_GROUND ) //Don't allow move
			{
				return false;  
			}
			else if( newGround_Type == RIVER_GROUND ) //Allow move
			{
				return true;
			}
			else // not listed type (impossible!!??). Don't allow move
			{
				return false;  
			}
		}
	}
	//we can't locate the position inside the vector (impossible!!??)
	return false;
}
//Check if the environment allow the move
int Character_Base::check_environment_allow_character(int x, int y, std::vector<BattleField_Sprite*> Environment_Sprite_Vector)
{
	//loop on all the vector
	for(int i=0; i < Environment_Sprite_Vector.size(); i++)
	{
		//when we have located the good destination inside the vector,...
		if (( x == Environment_Sprite_Vector[i]->Get_X() ) && ( y == Environment_Sprite_Vector[i]->Get_Y() ))
		{
			//...get the destination environment...
			int newEnv_Type = Environment_Sprite_Vector[i]->Get_BattleField_Type();
			
			//...then check if the environment allow the character move
			if( newEnv_Type == NOTHING_ENV_ITEM )  //indicate no environement is present
			{
				return -1; 
			}
			else if( newEnv_Type == TREE_ENV_ITEM ) //Don't allow move
			{
				return 0;
			}
			else // not listed type (impossible!!??). Allow move
			{
				return 1;  
			}
		}
	}
	//we can't locate the position inside the vector (impossible!!??)
	return -1;
}
//Show the Character on the screen
void Character_Base::move_animation(VideoSurface& Screen)
{
	//If CH is moving left
    if( xVel < 0 )
    {
        move_status = CH_LEFT;
    }
    //If CH is moving right
    else if( xVel > 0 )
    {
        move_status = CH_RIGHT;
    }
    //If CH is moving down
    else if ( yVel > 0 )
    {
        move_status = CH_DOWN;  
    }
	//If CH is moving up
	else if( yVel < 0 )
	{
	    move_status = CH_UP;
	}
  
    //assign the good sprite to the character sprite
    if( move_status == CH_RIGHT )
    {
		Character_SpriteRect = _character_right_attack[0];
	}
    else if( move_status == CH_LEFT )
    {
		Character_SpriteRect = _character_left_attack[0];
	}
	else if( move_status == CH_DOWN )
    {
		Character_SpriteRect = _character_down_attack[0];
	}
	else if( move_status == CH_UP )
    {
		Character_SpriteRect = _character_up_attack[0];
    }
	//Show the character in his good position
	Screen.blit(Characters_Tile, Point::Point(x - Camera.getx(), y - Camera.gety()), Character_SpriteRect);
}
//Handle character attack on monsters for all attack style and return the distance where the attack took place (in case of a distant attack for example)
int Character_Base::attack()
{
	int Hit_Distance = 0; //The Hit distance is the distance between the character and the monster by default the Melee Hit Distance

	//If the player has pushed the attack key => check if attack was seccessfull or not and act accordingly
	if (attack_status == true)
	{
		//By default consider that no attack was successfull
		attack_successfull = false;

		//First Check attack style
		if (attack_style == 1) //Melee attack: Only hit at one square distant
		{
			Hit_Distance = 0;
			//if one of the monster have been it attack_successfull become true
			attack_successfull = attack_check_status(1);
		}
		else if (attack_style == 2) //distant attack: 3 square hit distance max
		{
			Hit_Distance = 3;
			//loop for all the arrow traject
			for (int i=1; i<=3; i++)
			{
				//if one of the monster is on the arrow traject it has been it so attack_successfull become true
				attack_successfull = attack_check_status(i);
				if (attack_successfull) { //One monster has been hit
					Hit_Distance = i-1; //update the hit distance
					break;
				}
			}
		}
	}

	return Hit_Distance;
}
//Check if collision between the attack and one of the monsters on the battlefield regarding the number of movements that the attack collision is currently doing
bool Character_Base::attack_check_status(int collision_box_movement)
{
	bool _attack_successfull = false;
	//Check attack direction
	if( move_status == CH_RIGHT )
	{
		//move the collision box right of the character
		attack_collision_box.setx ( collision_box.getx() + (CH_WIDTH * collision_box_movement) );
		attack_collision_box.sety ( collision_box.gety());
	}
	else if( move_status == CH_LEFT )
	{
		//move the collision box left of the character
		attack_collision_box.setx( collision_box.getx() - (CH_WIDTH * collision_box_movement) );
		attack_collision_box.sety( collision_box.gety() );
	}
	else if( move_status == CH_DOWN )
	{
		//move the collision box down of the character
		attack_collision_box.setx( collision_box.getx() );
		attack_collision_box.sety( collision_box.gety() + (CH_HEIGHT * collision_box_movement) );
	}
	else if( move_status == CH_UP )
	{
		//move the collision box up of the character
		attack_collision_box.setx( collision_box.getx() );
		attack_collision_box.sety( collision_box.gety() - (CH_WIDTH * collision_box_movement) );
	}
	

	//Check attack with all monsters inside the vector and return true if one of the monster was hit also update the monster Alive_Status
	for(int i=0; i < Monster_Vector.size(); i++)
	{
		//check if collision between monster and attack now that the attack_collision_box has been moved
		if (check_collision(attack_collision_box, Monster_Vector[i]->collision_box))
		{
			//One monster has been hit so modify the attack_successfull status...
			_attack_successfull = true;
			//...Change the monster status to false aka monster dead...
			Monster_Vector[i]->Alive_Status = false;
			//...Than leave the check in order to touch only one monster at a time.
			break;
		}			
	}

	return _attack_successfull;
}
//Attack animation regarding of the style
void Character_Base::attack_animation(int character_hit_distance, VideoSurface& Screen)
{
	//If the player has pushed the attack key => launch animation attack
	if (attack_status == true)
	{
		// Melee Style (character_hit_distance = 1 so do not care)
		if (attack_style == 1)
		{
			//assign the good sprite to the character sprite depending of the frame and the direction
			if( move_status == CH_RIGHT )
			{
				//Screen->blit(Characters_Tile, Point::Point(x - Camera.getx(), y - Camera.gety()), _character_right_attack[0]);
				//Timer not started then start it
				if ( attack_regulator.get_ticks() == 0 )
				{
					attack_regulator.start();
				}
				//First frame of the attack anim until the timer reach 350ms
				if ( attack_regulator.get_ticks() <= 350 )
				{
					Character_SpriteRect = _character_right_attack[1];
				}
				//2nd frame of the attack animation between 350ms & 700ms
				if ( (attack_regulator.get_ticks() > 350) && (attack_regulator.get_ticks() <= 700) )
				{	
					Character_SpriteRect = _character_right_attack[2];
				}
				//The timer is now over the 700ms, we have finished the attack animation so we get back to the initial frame that is the normal display 
				if ( attack_regulator.get_ticks() > 700 )
				{
					Character_SpriteRect = _character_right_attack[0];
					attack_regulator.stop();
				}

				/*SDL_AddTimer( 0, CallBackFrame, 1);
				SDL_AddTimer( (350/10)*10, CallBackFrame, 2);
				SDL_AddTimer( (700/10)*10, CallBackFrame, 0);

				Uint32 CallBackFrame(Uint32 interval, void *param)
				{
					Screen->blit(Characters_Tile, Point::Point(x - Camera.getx(), y - Camera.gety()), _character_right_attack[param]);
				}*/

			}
			else if( move_status == CH_LEFT )
			{
				//Screen->blit(Characters_Tile, Point::Point(x - Camera.getx(), y - Camera.gety()), _character_left_attack[0]);
				if ( attack_regulator.get_ticks() == 0 )
				{
					attack_regulator.start();
				}
				if ( attack_regulator.get_ticks() <= 350 )
				{
					Character_SpriteRect = _character_left_attack[1];
				}
				if ( (attack_regulator.get_ticks() > 350) && (attack_regulator.get_ticks() <= 700) )
				{	
					Character_SpriteRect = _character_left_attack[2];
				}
				if ( attack_regulator.get_ticks() > 700 )
				{
					Character_SpriteRect = _character_left_attack[0];
					attack_regulator.stop();
				}
			}
			else if( move_status == CH_DOWN )
			{
				//Screen->blit(Characters_Tile, Point::Point(x - Camera.getx(), y - Camera.gety()), _character_down_attack[0]);
				if ( attack_regulator.get_ticks() == 0 )
				{
					attack_regulator.start();
				}
				if ( attack_regulator.get_ticks() <= 350 )
				{
					Character_SpriteRect = _character_down_attack[1];
				}
				if ( (attack_regulator.get_ticks() > 350) && (attack_regulator.get_ticks() <= 700) )
				{	
					Character_SpriteRect = _character_down_attack[2];
				}
				if ( attack_regulator.get_ticks() > 700 )
				{
					Character_SpriteRect = _character_down_attack[0];
					attack_regulator.stop();
				}
			}
			else if( move_status == CH_UP )
			{
				//Screen->blit(Characters_Tile, Point::Point(x - Camera.getx(), y - Camera.gety()), _character_up_attack[0]);
				if ( attack_regulator.get_ticks() == 0 )
				{
					attack_regulator.start();
				}
				if ( attack_regulator.get_ticks() <= 350 )
				{
					Character_SpriteRect = _character_up_attack[1];
				}
				if ( (attack_regulator.get_ticks() > 350) && (attack_regulator.get_ticks() <= 700) )
				{	
					Character_SpriteRect = _character_up_attack[2];
				}
				if ( attack_regulator.get_ticks() > 700 )
				{
					Character_SpriteRect = _character_up_attack[0];
					attack_regulator.stop();
				}
			}
			//Show the good character sprite
			Screen.blit(Characters_Tile, Point::Point(x - Camera.getx(), y - Camera.gety()), Character_SpriteRect);
		}
		// Distant Style
		if (attack_style == 2)
		{
			/****Character****/
			//Show the good character sprite (future devs: depending of the frame and the direction)
			Screen.blit(Characters_Tile, Point::Point(x - Camera.getx(), y - Camera.gety()), Character_SpriteRect);

			/****Arrow****/
			//Start the timer
			attack_regulator.start();

			//In case of distant attack character_hit_distance may vary if we have to take care of it
			for (int i=1; i <= character_hit_distance; i++) //Move the arrow until character_hit_distance reached that represents monster hit
			{
				//Show the good arrow in function of the position
				if( move_status == CH_RIGHT )
				{
					Screen.blit(Arrow_Tile, Point::Point(x - Camera.getx() + (i * CH_WIDTH), y - Camera.gety()), Arrow_Right[0]);
					//apply_surface(x - camera.x + (i * CH_WIDTH), y - camera.y, Arrow_Tile, screen, &Arrow_Right[0]);
					attack_regulator.start();
					while( attack_regulator.get_ticks() < 200 )
					{
						//wait    
					}
				}
				else if( move_status == CH_LEFT )
				{
					Screen.blit(Arrow_Tile, Point::Point(x - Camera.getx() - (i * CH_WIDTH), y - Camera.gety()), Arrow_Left[0]);
					//apply_surface(x - camera.x - (i * CH_WIDTH), y - camera.y, Arrow_Tile, screen, &Arrow_Left[0]);
					attack_regulator.start();
					while( attack_regulator.get_ticks() < 200 )
					{
						//wait    
					}
				}
				else if( move_status == CH_DOWN )
				{
					Screen.blit(Arrow_Tile, Point::Point(x - Camera.getx(), y - Camera.gety() + (i * CH_HEIGHT)), Arrow_Down[0]);
					//apply_surface(x - camera.x, y - camera.y + (i * CH_HEIGHT), Arrow_Tile, screen, &Arrow_Down[0]);
					attack_regulator.start();
					while( attack_regulator.get_ticks() < 200 )
					{
						//wait    
					}
				}
				else if( move_status == CH_UP )
				{
					Screen.blit(Arrow_Tile, Point::Point(x - Camera.getx(), y - Camera.gety() - (i * CH_HEIGHT)), Arrow_Up[0]);
					//apply_surface(x - camera.x, y - camera.y - (i * CH_HEIGHT), Arrow_Tile, screen, &Arrow_Up[0]);
					attack_regulator.start();
					while( attack_regulator.get_ticks() < 200 )
					{
						//wait    
					}
				}
			}

			//attack animation has been done => stop the timer
			attack_regulator.stop();
		}
	}
}
//Display attack msg on the status bar (hit or miss)
void Character_Base::Display_Attack_Msg(VideoSurface& Screen)
{
	//Clean the status Bar (last line of the screen)
	Screen.fill( Color(0x00, 0x00, 0x00), Rect(0, CURRENT_SCREEN_HEIGHT - 32, CURRENT_SCREEN_WIDTH, 32) );

	//If the player has pushed the attack key => display the good msg in the status bar
	if (attack_status == true)
	{
		//If a monster was been hit displayed the hit msg, if no display miss msg
		if (attack_successfull)
		{
			attack_msg = attack_msg_hit;
			//Screen.blit( attack_msg_hit, Point::Point(5, SCREEN_HEIGHT - 30) );
			P0_Logger << " >>> Monster Hit <<< " << std::endl;
		}
		else
		{
			attack_msg = attack_msg_miss;
			//Screen.blit( attack_msg_miss, Point::Point(5, SCREEN_HEIGHT - 30) );
			P0_Logger << " >>> Monster Miss <<< " << std::endl;
		}

		//Display attack msg is done, so now everything relative to the character attack is done, we can reset the status
		attack_status = false;
	}
	Screen.blit( attack_msg, Point::Point(5, CURRENT_SCREEN_HEIGHT - 30) );
}
//Managed the camera
void Character_Base::following_camera()
{
    //Center the camera over the Character
    Camera.setx( (x + CH_WIDTH / 2) - CURRENT_SCREEN_WIDTH / 2 );
    Camera.sety( (y + CH_HEIGHT / 2) - CURRENT_SCREEN_HEIGHT / 2 );
    //Keep the camera in bounds.
    if(Camera.getx() < 0)
    {
        Camera.setx(0);    
    }
    if(Camera.gety() < 0)
    {
        Camera.sety(0);    
    }
    if( Camera.getx() > (LEVEL_WIDTH - Camera.getw()) )
    {
        Camera.setx(LEVEL_WIDTH - Camera.getw());    
    }
    if(Camera.gety() > (LEVEL_HEIGHT - Camera.geth()) )
    {
        Camera.sety(LEVEL_HEIGHT - Camera.geth());    
    }    
}

//Update charaster's monster knowledge of monster presents on the battlefield
void Character_Base::Update_Monster_Knowledge(std::vector<Monster_Skeleton*> monster_vector)
{
	//Update only if the two vector have not the same size (only here to gain execution speed when vector will have an important size)
	if (monster_vector.size() != Monster_Vector.size())
	{
		Monster_Vector = monster_vector;
	}
}
