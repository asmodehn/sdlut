#include "Player_Base.hh"

//Initialization construtor
Player_Base::Player_Base(int x, int y)
{
    //Initial position
	X = x;
	Y = y;
    
    //Initial velocity
    xVel = 0;
    yVel = 0;

	//Initial arrow position
	arrow_x = X;
	arrow_y = Y;

	//Initial moving status
	moving_status = false;

	//Character Clips definition
	_player_left_attack[0].setx(0);
	_player_left_attack[0].sety(0);
	_player_left_attack[0].setw(CH_WIDTH);
	_player_left_attack[0].seth(CH_HEIGHT);

	_player_left_attack[1].setx(CH_WIDTH);
    _player_left_attack[1].sety(0);
    _player_left_attack[1].setw(CH_WIDTH);
    _player_left_attack[1].seth(CH_HEIGHT);

	_player_left_attack[2].setx(CH_WIDTH * 2);
    _player_left_attack[2].sety(0);
    _player_left_attack[2].setw(CH_WIDTH);
    _player_left_attack[2].seth(CH_HEIGHT);


    _player_right_attack[0].setx(0);
    _player_right_attack[0].sety(CH_HEIGHT);
    _player_right_attack[0].setw(CH_WIDTH);
    _player_right_attack[0].seth(CH_HEIGHT);
    
    _player_right_attack[1].setx(CH_WIDTH);
    _player_right_attack[1].sety(CH_HEIGHT);
    _player_right_attack[1].setw(CH_WIDTH);
    _player_right_attack[1].seth(CH_HEIGHT);
    
    _player_right_attack[2].setx(CH_WIDTH * 2);
    _player_right_attack[2].sety(CH_HEIGHT);
    _player_right_attack[2].setw(CH_WIDTH);
    _player_right_attack[2].seth(CH_HEIGHT);


	_player_down_attack[0].setx(0);
    _player_down_attack[0].sety(CH_HEIGHT*2);
    _player_down_attack[0].setw(CH_WIDTH);
    _player_down_attack[0].seth(CH_HEIGHT);
    
    _player_down_attack[1].setx(CH_WIDTH);
    _player_down_attack[1].sety(CH_HEIGHT*2);
    _player_down_attack[1].setw(CH_WIDTH);
    _player_down_attack[1].seth(CH_HEIGHT);
    
    _player_down_attack[2].setx(CH_WIDTH * 2);
    _player_down_attack[2].sety(CH_HEIGHT*2);
    _player_down_attack[2].setw(CH_WIDTH);
    _player_down_attack[2].seth(CH_HEIGHT);
    

    _player_up_attack[0].setx(0);
    _player_up_attack[0].sety(CH_HEIGHT*3);
    _player_up_attack[0].setw(CH_WIDTH);
    _player_up_attack[0].seth(CH_HEIGHT);
    
    _player_up_attack[1].setx(CH_WIDTH);
    _player_up_attack[1].sety(CH_HEIGHT*3);
    _player_up_attack[1].setw(CH_WIDTH);
    _player_up_attack[1].seth(CH_HEIGHT);
    
    _player_up_attack[2].setx(CH_WIDTH * 2);
    _player_up_attack[2].sety(CH_HEIGHT*3);
    _player_up_attack[2].setw(CH_WIDTH);
    _player_up_attack[2].seth(CH_HEIGHT);

	//Assign the right sprite to the player by default
	Characters_SpriteRect = _player_right_attack[0];

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
	//Camera.setx( (X + CH_WIDTH / 2) - CURRENT_SCREEN_WIDTH / 2 );
	//Camera.sety( (Y + CH_HEIGHT / 2) - CURRENT_SCREEN_HEIGHT / 2 );
	Camera.setw(CURRENT_SCREEN_WIDTH);
	Camera.seth(CURRENT_SCREEN_HEIGHT);

	//Collision Box Definition: The collision box has the size of the character
	Collision_Box.setx(X);
    Collision_Box.sety(Y);
    Collision_Box.setw(CH_WIDTH);
    Collision_Box.seth(CH_HEIGHT);

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
	Players_Tile_Melee = RGBSurface("Datas/Characters/Character_Fighter.bmp", Color(0xFF, 0xFF, 0xFF));
	Players_Tile_Distant = RGBSurface("Datas/Characters/Character_Archer.bmp", Color(0xFF, 0xFF, 0xFF));
	Characters_Tile = Players_Tile_Melee; //Default tile: the melee tile
	//Arrow surface
	Arrow_Tile = RGBSurface("Datas/Items/Arrow.bmp", Color(0xFF, 0xFF, 0xFF));

	//Fight Msgs Style
	//Font AttackMsg_Font("Datas/Fonts/ECHELON.TTF", 28);
	Font AttackMsg_Font("Datas/Fonts/SlimSansSerif.ttf", 28);

	//Msgs displayed in the status bar
	attack_msg = *AttackMsg_Font.render(" ", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0)); // Empty msg until the attack key is pressed once (when using empty msg the creator crash so until this bug is solved we will use " " insted of "")
	attack_melee_msg_hit = *AttackMsg_Font.render("Melee Hit", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
	attack_distant_msg_hit = *AttackMsg_Font.render("Distant Hit", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
	attack_melee_msg_miss = *AttackMsg_Font.render("Melee Miss", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
	attack_distant_msg_miss = *AttackMsg_Font.render("Distant Miss", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
}

//Character Graphic Style Initialiation regarding the attack style
bool Player_Base::Update_Graphic_Style()
{
try
{
	// Melee Style
	if (attack_style == 1)
	{
		Characters_Tile = Players_Tile_Melee;
		attack_msg_hit = attack_melee_msg_hit;
		attack_msg_miss = attack_melee_msg_miss;
		//P0_Logger << " Graphic Style Updated To Melee Style : OK " << std::endl;
	}
	// Distant Style
	else if (attack_style == 2)
	{
		Characters_Tile = Players_Tile_Distant;
		attack_msg_hit = attack_distant_msg_hit;
		attack_msg_miss = attack_distant_msg_miss;
		//P0_Logger << " Graphic Style Updated To Distant Style : OK " << std::endl;
	}
	return true;
}
catch (...) {
  return false; //error occured
}
}
//Show the Character on the screen
bool Player_Base::move(std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector)
{
try {
	if (! Check_Collisions(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector) )
	{ //No collisions found
		//move the player
		X = Collision_Box.getx();
		Y = Collision_Box.gety();

		//...and the arrow with his owner^^
		arrow_x = X;
		arrow_y = Y;
	}

	return true; //no error
} catch (...) {  //error occured
	return false;
}
}

//Set ground vs player rules
int Player_Base::Get_BG_vs_CH_Rules(int bgType)
{
	if( bgType == EMPTY_GROUND ) //Don't allow move
	{
		return 0;
	}
	else if( bgType == GRASS_GROUND ) //Allow move
	{
		return 1;
	}
	else if( bgType == SAND_GROUND ) //Don't allow move
	{
		return 0;
	}
	else if( bgType == RIVER_GROUND ) //Allow move
	{
		return 1;
	}
	else if( bgType == LAKE_GROUND ) //Don't allow move
	{
		return 0;
	}
	else // not listed type (impossible!!??). Don't allow move
	{
		return 0;
	}
}

//Set env vs player rules
int Player_Base::Get_Env_vs_CH_Rules(int envType)
{
	if( envType == NOTHING_ENV_ITEM )  //indicate no environement is present
	{
		return -1;
	}
	else if( envType == TREE_ENV_ITEM ) //Don't allow presence
	{
		return 0;
	}
	else if( envType == ROCK_ENV_ITEM ) //Don't allow presence
	{
		return 0;
	}
	else if( envType == WALL_ENV_ITEM ) //Don't allow presence
	{
		return 0;
	}
	else if( envType == HOUSE_ENV_ITEM ) //Allow presence
	{
		return 1;
	}
	else if( envType == BRIDGE_ENV_ITEM ) //Allow presence
	{
		return 1;
	}
	else // not listed type (impossible!!??). Allow presence
	{
		return 1;
	}
}

//check the move direction and assign the good sprite
bool Player_Base::assign_direction_sprite()
{
try {
	int old_move_status = move_status;

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
  
	if (!Get_Attack_Status()) //no attack is occuring
	{
		//assign the good sprite to the character sprite and the good arrow to the character arrow
		if( move_status == CH_RIGHT )
		{
			Characters_SpriteRect = _player_right_attack[0];
			Arrow_SpriteRect = Arrow_Right[0];
		}
		else if( move_status == CH_LEFT )
		{
			Characters_SpriteRect = _player_left_attack[0];
			Arrow_SpriteRect = Arrow_Left[0];
		}
		else if( move_status == CH_DOWN )
		{
			Characters_SpriteRect = _player_down_attack[0];
			Arrow_SpriteRect = Arrow_Down[0];
		}
		else if( move_status == CH_UP )
		{
			Characters_SpriteRect = _player_up_attack[0];
			Arrow_SpriteRect = Arrow_Up[0];
		}
	}

	//Check if we are changing direction
	if ( old_move_status != move_status )
	{ //change but dont move
		xVel = 0;
		yVel = 0;
		moving_status = false;
	} else {
		moving_status = true; //we're moving
	}

	return true; //no error
} catch (...) {
  return false; //error occured
}
}
//define character sprite which appear on the screen during moves
bool Player_Base::Set_Move_Animation_Sprite()
{
		//P0_Logger << " Set_Move_Animation_Sprite called" << std::endl;

		//end of the timer for the moment (until moved animation developped (future dev))
		return false; //no animation

}
//Handle character attack on monsters for all attack style and return the distance where the attack took place (in case of a distant attack for example)
int Player_Base::attack(std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector)
{
	int Hit_Distance = 0; //The Hit distance is the distance between the character and the monster by default the Melee Hit Distance (aka 0)

	//If the player has pushed the attack key => check if attack was seccessfull or not and act accordingly
	if ( Get_Attack_Status() )
	{
		//By default consider that no attack was successfull
		attack_successfull = 0;

		//
		//TODO: Get the weapon max hit range & damage and calculate character range and damage from them
		//TODO: put these value's definitions inside the constructor
		//TODO: use formula for character_real_damage
		//
		int character_max_damage = 100;
		int character_real_damage = character_max_damage;
		int character_current_damage = character_real_damage;

		//First Check attack style
		if (attack_style == 1) //Melee attack: Only hit at one square distant
		{
			int character_max_range = 1;
			Hit_Distance = character_max_range-1; //update the hit distance (used for arrow management)

			//Check if one of the monster is on the arrow traject
			attack_successfull = attack_check_status(character_max_range, character_current_damage, Global_Monster_Vector) ;
			//if (attack_successfull != 0) //One monster has been hitted
				

		}
		else if (attack_style == 2) //distant attack: 6 square hit distance max
		{
			int character_max_range = 6;
			Hit_Distance = character_max_range-1; //update the hit distance (used for arrow management)

			//loop for all the range traject
			for (int i=1; i<=character_max_range; i++)
			{
				//
				//TODO: Get this formula from config file if possible
				//
				character_current_damage = character_real_damage - (i-1)*character_real_damage/character_max_range;

				//Check if one of the monster is on the arrow traject
				attack_successfull = attack_check_status(i, character_current_damage, Global_Monster_Vector) ;
				if (attack_successfull != 0) { //One monster has been hitted
					Hit_Distance = i-1; //update the hit distance (used for arrow management)
					break;
				}
			}
		}
	}

	return Hit_Distance;
}
//Check if collision between the attack and one of the monsters on the battlefield regarding the number of movements that the attack collision is currently doing
int Player_Base::attack_check_status(int current_hit_distance, int character_damage, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector)
{
	int _attack_successfull = 0;
	//Check attack direction
	if( move_status == CH_RIGHT )
	{
		//move the collision box right of the character
		attack_collision_box.setx ( Collision_Box.getx() + (CH_WIDTH * current_hit_distance) );
		attack_collision_box.sety ( Collision_Box.gety());
	}
	else if( move_status == CH_LEFT )
	{
		//move the collision box left of the character
		attack_collision_box.setx( Collision_Box.getx() - (CH_WIDTH * current_hit_distance) );
		attack_collision_box.sety( Collision_Box.gety() );
	}
	else if( move_status == CH_DOWN )
	{
		//move the collision box down of the character
		attack_collision_box.setx( Collision_Box.getx() );
		attack_collision_box.sety( Collision_Box.gety() + (CH_HEIGHT * current_hit_distance) );
	}
	else if( move_status == CH_UP )
	{
		//move the collision box up of the character
		attack_collision_box.setx( Collision_Box.getx() );
		attack_collision_box.sety( Collision_Box.gety() - (CH_WIDTH * current_hit_distance) );
	}
	
	//Collision with Monsters
	//Loop for all monster's vector
	for (unsigned int j=0; j < Global_Monster_Vector->size(); j++)
	{
		//loop for the current monster's vector
		for(unsigned int i=0; i < Global_Monster_Vector->at(j)->size(); i++)
		{
			//Get the current monster
			Monster_Base* Current_Monster = (Monster_Base*)Global_Monster_Vector->at(j)->at(i);

			//In order to not check himself
			if ( ( X != Current_Monster->Get_X() ) || Y != Current_Monster->Get_Y() )
			{
				if (check_collision( attack_collision_box, Current_Monster->Get_Collision_Box() ))
				{
					//One monster has been hit so modify the The_Attack_Successfull status...
					_attack_successfull = Current_Monster->Get_Monster_ID();
					//...Send damage value to the monster
					Current_Monster->Calculate_Current_Life( character_damage );
					//...Than leave the check in order to touch only one monster at a time.
					return _attack_successfull;
				}
			}
		}
	}
	return _attack_successfull;
}
//Set Character Sprite Which change when attack occured
bool Player_Base::Set_Attack_Animation_Sprite()
{
	//increase frame each time the timer is run (from 0 to 2)
	frame++;

	//make the timer loop until end of animation (2 frames)
	if (frame > 2) //end of anim
	{
		frame = 0; //reset frame anim
	}

	P0_Logger << " Set_Attack_Animation_Sprite called FRAME:" << frame << std::endl;

	// Melee Style
	if (attack_style == 1)
	{
		//assign the good sprite rect to the character sprite rect depending of the frame and the direction
		if( move_status == CH_RIGHT )
		{
			//right sprite
			Characters_SpriteRect = _player_right_attack[frame];
		}
		else if( move_status == CH_LEFT )
		{
			//left sprite
			Characters_SpriteRect = _player_left_attack[frame];
		}
		else if( move_status == CH_DOWN )
		{
			//down sprite
			Characters_SpriteRect = _player_down_attack[frame];

		}
		else if( move_status == CH_UP )
		{
			//up sprite
			Characters_SpriteRect = _player_up_attack[frame];
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
bool Player_Base::Set_Arrow_Sprite_Coordinate()
{
	//increase arrow frame
	arrow_frame++;

	P0_Logger << " Set_Arrow_Sprite_Infos called FRAME:" << arrow_frame << std::endl;

	if (arrow_frame <= hit_monster_distance) //Move the arrow until hit_monster_distance reached. Equal, monster hit!
	{
		//set coordinate in fonction of the character direction
		if( move_status == CH_RIGHT )
		{
			arrow_x = X + (arrow_frame * CH_WIDTH);
			arrow_y = Y;
		}
		else if( move_status == CH_LEFT )
		{
			arrow_x = X - (arrow_frame * CH_WIDTH);
			arrow_y = Y;
		}
		else if( move_status == CH_DOWN )
		{
			arrow_x = X;
			arrow_y = Y + (arrow_frame * CH_HEIGHT);
		}
		else if( move_status == CH_UP )
		{
			arrow_x = X;
			arrow_y = Y - (arrow_frame * CH_HEIGHT);
		}
		return true;
	} else { //end of animation
		arrow_frame = 0; //end anim
		hit_monster_distance = 0; //reset the distance
		arrow_x = X; //reset coordinate (no need to reset rect coz it dont change)
		arrow_y = Y;
		return false;
	}	
}

//blit the arrow on the screen
bool Player_Base::Show_Arrow(VideoSurface& Screen)
{
try {
	if ( (X != arrow_x) || (Y != arrow_y) ) //dont display the arrow when it's at the same place than the character
	{
		Screen.blit(Arrow_Tile, Point::Point(arrow_x - Camera.getx(), arrow_y - Camera.gety()), Arrow_SpriteRect);
	}
	return true; //no error
} catch (...) {
	return false; //error occured
}
}
//Display attack msg on the status bar (hit or miss)
bool Player_Base::Display_Attack_Msg(VideoSurface& Screen)
{
try {
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
	return true; //no error
} catch (...) {
	return false; //error occured
}
}
//Managed the camera
bool Player_Base::following_camera()
{
try {
    //Center the camera over the Character
    Camera.setx( (X + CH_WIDTH / 2) - CURRENT_SCREEN_WIDTH / 2 );
    Camera.sety( (Y + CH_HEIGHT / 2) - CURRENT_SCREEN_HEIGHT / 2 );
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
	return true; //no error
} catch (...) {
	return false; //error occured
}  
}
