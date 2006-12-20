#include "Character_Base.hh"

//Initialization construtor
Character_Base::Character_Base(int X, int Y)
{
    //Initial position
	x = X;
	y = Y;
    
    //Initial velocity
    xVel = 0;
    yVel = 0;

	//Initial arrow position
	arrow_x = x;
	arrow_y = y;

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

	//Assign the right sprite to character by default
	Character_SpriteRect = _character_right_attack[0];

	//Initialize animation variables
    frame = 0;  // for animation
	arrow_frame = 0; //for arrow animation
    move_status = CH_RIGHT;

	//Attack variable
	attack_status = false; //false = 0
	attack_style = 1; //0: nothing (future dev), 1: Melee attack (default), 2: Distant attack, 3: magic attack (future dev)
	attack_successfull = 0; //Tells if a monster has been hit, by default no
	hit_monster_distance = 0; //distance to the hitted monster

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

	Arrow_SpriteRect = Arrow_Right[0]; //default arrow sprite rect


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
	attack_msg = *AttackMsg_Font.render(" ", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0)); // Empty msg until the attack key is pressed once (when using empty msg the creator crash so until this bug is solved we will use " " insted of "")
	attack_melee_msg_hit = *AttackMsg_Font.render("Melee Hit", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
	attack_distant_msg_hit = *AttackMsg_Font.render("Distant Hit", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
	attack_melee_msg_miss = *AttackMsg_Font.render("Melee Miss", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
	attack_distant_msg_miss = *AttackMsg_Font.render("Distant Miss", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
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
void Character_Base::move(std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector, std::vector<Monster_Skeleton*> Monster_Vector_Skeleton, std::vector<Monster_Worm*> Monster_Vector_Worm)
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
	//If the Character went too far up or down (minus the status bar)
	if((collision_box.gety() < 0) || (collision_box.gety() + CH_HEIGHT > LEVEL_HEIGHT - STATUS_BAR_H) )
    {
        //move back
        collision_box.sety(y);    
    }

	//Collision with skeletons
	for(unsigned int i=0; i < Monster_Vector_Skeleton.size(); i++)
	{
		if (check_collision( collision_box, Monster_Vector_Skeleton[i]->Get_Collision_Box() ))
		{
			//move back
			collision_box.setx(x);
			collision_box.sety(y); 

			//we have found a collision inside the vector, no need to work more
			return;
		}
	}
	//Collision with worms
	for(unsigned int i=0; i < Monster_Vector_Worm.size(); i++)
	{
		if (check_collision( collision_box, Monster_Vector_Worm[i]->Get_Collision_Box() ))
		{
			//move back
			collision_box.setx(x);
			collision_box.sety(y); 

			//we have found a collision inside the vector, no need to work more
			return;
		}
	}
    
	//Now that all collision has been checked, we must check if the battlefield allow the move
	if(! check_battlefield_allow_character(collision_box.getx(), collision_box.gety(), Environment_Sprite_Vector, BackGround_Sprite_Vector) )
	{
		//move back
		collision_box.setx(x);
		collision_box.sety(y); 
	}

	//Finally move the character in the same place of his collision box...
	x = collision_box.getx();
	y = collision_box.gety();
	
	//...and the arrow with his owner^^
	arrow_x = x;
	arrow_y = y;

}
//Check if the battlefield allow the character presence
bool Character_Base::check_battlefield_allow_character(int x, int y, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
	//1st, we must check if the environment allow the move
	if( check_environment_allow_character(x, y, Environment_Sprite_Vector) == -1)
	{
		//No environement item present, the ground have priority
		if(! check_background_allow_character(x, y, BackGround_Sprite_Vector) )
		{
			return false;
		}
	}
	 //environment item present and dont allow presence
	else if( check_environment_allow_character(x, y, Environment_Sprite_Vector) == 0)
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
	for(unsigned int i=0; i < BackGround_Sprite_Vector.size(); i++)
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
			else if( newGround_Type == LAKE_GROUND ) //Allow move
			{
				return false;
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
	for(unsigned int i=0; i < Environment_Sprite_Vector.size(); i++)
	{
		//when we have located the good destination inside the vector,...
		if (( x == Environment_Sprite_Vector[i]->Get_X() ) && ( y == Environment_Sprite_Vector[i]->Get_Y() ))
		{
			//...get the destination environment...
			int newEnv_Type = Environment_Sprite_Vector[i]->Get_BattleField_Type();
			
			//...then check if the environment allow the character presence
			if( newEnv_Type == NOTHING_ENV_ITEM )  //indicate no environement is present
			{
				return -1; 
			}
			else if( newEnv_Type == TREE_ENV_ITEM ) //Don't allow presence
			{
				return 0;
			}
			else if( newEnv_Type == ROCK_ENV_ITEM ) //Don't allow presence
			{
				return 0;
			}
			else if( newEnv_Type == WALL_ENV_ITEM ) //Don't allow presence
			{
				return 0;
			}
			else if( newEnv_Type == HOUSE_ENV_ITEM ) //Allow presence
			{
				return 1;
			}
			else // not listed type (impossible!!??). Allow presence
			{
				return 1;  
			}
		}
	}
	//we can't locate the position inside the vector (impossible!!??)
	return -1;
}
//check the move direction and assign the good sprite
void Character_Base::check_character_direction()
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
  
	if (attack_status == false) //no attack is occuring
	{
		//assign the good sprite to the character sprite and the good arrow to the character arrow
		if( move_status == CH_RIGHT )
		{
			Character_SpriteRect = _character_right_attack[0];
			Arrow_SpriteRect = Arrow_Right[0];
		}
		else if( move_status == CH_LEFT )
		{
			Character_SpriteRect = _character_left_attack[0];
			Arrow_SpriteRect = Arrow_Left[0];
		}
		else if( move_status == CH_DOWN )
		{
			Character_SpriteRect = _character_down_attack[0];
			Arrow_SpriteRect = Arrow_Down[0];
		}
		else if( move_status == CH_UP )
		{
			Character_SpriteRect = _character_up_attack[0];
			Arrow_SpriteRect = Arrow_Up[0];
		}
	}
}
//define character sprite which appear on the screen during moves
bool Character_Base::Set_Move_Animation_Sprite()
{
		//P0_Logger << " Set_Move_Animation_Sprite called" << std::endl;

		//end of the timer for the moment (until moved animation developped (future dev))
		return false; //no animation

}
//Handle character attack on monsters for all attack style and return the distance where the attack took place (in case of a distant attack for example)
int Character_Base::attack(std::vector<Monster_Skeleton*> Monster_Vector_Skeleton, std::vector<Monster_Worm*> Monster_Vector_Worm)
{
	int Hit_Distance = 0; //The Hit distance is the distance between the character and the monster by default the Melee Hit Distance (aka 0)

	//If the player has pushed the attack key => check if attack was seccessfull or not and act accordingly
	if (attack_status == true)
	{
		//By default consider that no attack was successfull
		attack_successfull = 0;

		//First Check attack style
		if (attack_style == 1) //Melee attack: Only hit at one square distant
		{
			Hit_Distance = 0;
			//if one of the monster have been it The_Attack_Successfull become true
			attack_successfull = attack_check_status(1, Monster_Vector_Skeleton, Monster_Vector_Worm);
		}
		else if (attack_style == 2) //distant attack: 3 square hit distance max
		{
			Hit_Distance = 3;
			//loop for all the arrow traject
			for (int i=1; i<=3; i++)
			{
				//if one of the monster is on the arrow traject it has been it so The_Attack_Successfull become true
				attack_successfull = attack_check_status(i, Monster_Vector_Skeleton, Monster_Vector_Worm) ;
				if (attack_successfull != 0) { //One monster has been hit
					Hit_Distance = i-1; //update the hit distance
					break;
				}
			}
		}
	}

	return Hit_Distance;
}
//Check if collision between the attack and one of the monsters on the battlefield regarding the number of movements that the attack collision is currently doing
int Character_Base::attack_check_status(int collision_box_movement, std::vector<Monster_Skeleton*> Monster_Vector_Skeleton, std::vector<Monster_Worm*> Monster_Vector_Worm)
{
	int _attack_successfull = 0;
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
	

	//Check attack with all skeletons inside the vector and return true if one of the skeleton was hit also update the monster Alive_Status
	for(unsigned int i=0; i < Monster_Vector_Skeleton.size(); i++)
	{
		//check if collision between monster and attack now that the attack_collision_box has been moved
		if (check_collision( attack_collision_box, Monster_Vector_Skeleton[i]->Get_Collision_Box() ))
		{
			//One monster has been hit so modify the The_Attack_Successfull status...
			_attack_successfull = 1;
			//...Change the monster status to false aka monster dead...
			Monster_Vector_Skeleton[i]->Set_Alive_Status(false);
			//...Than leave the check in order to touch only one monster at a time.
			return _attack_successfull;
		}			
	}
	//Check attack with all worms inside the vector and return true if one of the worm was hit also update the monster Alive_Status
	for(unsigned int i=0; i < Monster_Vector_Worm.size(); i++)
	{
		//check if collision between monster and attack now that the attack_collision_box has been moved
		if (check_collision( attack_collision_box, Monster_Vector_Worm[i]->Get_Collision_Box() ))
		{
			//One monster has been hit so modify the The_Attack_Successfull status...
			_attack_successfull = 2;
			//...Change the monster status to false aka monster dead...
			Monster_Vector_Worm[i]->Set_Alive_Status(false);
			//...Than leave the check in order to touch only one monster at a time.
			return _attack_successfull;
		}			
	}

	return _attack_successfull;
}
//Set Character Sprite Which change when attack occured
bool Character_Base::Set_Attack_Animation_Sprite()
{
	//increase frame each time the timer is run (from 0 to 2)
	frame++;

	//make the timer loop until end of animation (2 frames)
	if (frame > 2) //end of anim
	{
		frame = 0; //reset frame anim
		attack_status = false; //end of attack
	}

	P0_Logger << " Set_Attack_Animation_Sprite called FRAME:" << frame << std::endl;

	// Melee Style
	if (attack_style == 1)
	{
		//assign the good sprite rect to the character sprite rect depending of the frame and the direction
		if( move_status == CH_RIGHT )
		{
			//right sprite
			Character_SpriteRect = _character_right_attack[frame];
		}
		else if( move_status == CH_LEFT )
		{
			//left sprite
			Character_SpriteRect = _character_left_attack[frame];
		}
		else if( move_status == CH_DOWN )
		{
			//down sprite
			Character_SpriteRect = _character_down_attack[frame];

		}
		else if( move_status == CH_UP )
		{
			//up sprite
			Character_SpriteRect = _character_up_attack[frame];
		}

	}
	// Distant Style
	else if (attack_style == 2)
	{
		//define the good character sprite (future devs: depending of the frame and the direction)
		//frame = 0;
	}

	if ( frame == 0 )
	{ return false; } //end of anim

	//anim is still looping
	return true;

}
//arrow animation (callback method)
bool Character_Base::Set_Arrow_Sprite_Coordinate()
{
	//increase arrow frame
	arrow_frame++;

	P0_Logger << " Set_Arrow_Sprite_Infos called FRAME:" << arrow_frame << std::endl;

	if (arrow_frame <= hit_monster_distance) //Move the arrow until hit_monster_distance reached. Equal, monster hit!
	{
		//set coordinate in fonction of the character direction
		if( move_status == CH_RIGHT )
		{
			arrow_x = x + (arrow_frame * CH_WIDTH);
			arrow_y = y;
		}
		else if( move_status == CH_LEFT )
		{
			arrow_x = x - (arrow_frame * CH_WIDTH);
			arrow_y = y;
		}
		else if( move_status == CH_DOWN )
		{
			arrow_x = x;
			arrow_y = y + (arrow_frame * CH_HEIGHT);
		}
		else if( move_status == CH_UP )
		{
			arrow_x = x;
			arrow_y = y - (arrow_frame * CH_HEIGHT);
		}
		return true;
	} else { //end of animation
		arrow_frame = 0; //end anim
		hit_monster_distance = 0; //reset the distance
		arrow_x = x; //reset coordinate (no need to reset rect coz it dont change)
		arrow_y = y;
		return false;
	}	
}
//blit the character on the screen
void Character_Base::Show_Character(VideoSurface& Screen)
{
	Screen.blit(Characters_Tile, Point::Point(x - Camera.getx(), y - Camera.gety()), Character_SpriteRect);
}
//blit the arrow on the screen
void Character_Base::Show_Arrow(VideoSurface& Screen)
{
	if ( (x != arrow_x) || (y != arrow_y) ) //dont display the arrow when it's at the same place than the character
	{
		Screen.blit(Arrow_Tile, Point::Point(arrow_x - Camera.getx(), arrow_y - Camera.gety()), Arrow_SpriteRect);

	}
}
//Display attack msg on the status bar (hit or miss)
void Character_Base::Display_Attack_Msg(VideoSurface& Screen)
{
	//Clean the status Bar
	Screen.fill( Color(0x00, 0x00, 0x00), Rect(0, CURRENT_SCREEN_HEIGHT - STATUS_BAR_H, CURRENT_SCREEN_WIDTH, STATUS_BAR_H) );

	//If the player has pushed the attack key => display the good msg in the status bar
	if (attack_status == true)
	{
		//If a monster has been hit displayed the hit msg, if no display miss msg
		if (attack_successfull != 0)
		{
			attack_msg = attack_msg_hit;

			if (attack_successfull == 1)
				P0_Logger << " >>> Skeleton Hit <<< " << std::endl;
			if (attack_successfull == 2)
				P0_Logger << " >>> Worm Hit <<< " << std::endl;
		}
		else
		{
			attack_msg = attack_msg_miss;
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
