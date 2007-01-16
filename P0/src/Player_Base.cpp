#include "Player_Base.hh"

//Initialization construtor
Player_Base::Player_Base(int X, int Y)
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

	//Assign the right sprite to character by default
	Player_SpriteRect = _player_right_attack[0];

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
	Players_Tile_Melee = RGBSurface("Datas/Characters/Character_Fighter.bmp", Color(0xFF, 0xFF, 0xFF));
	Players_Tile_Distant = RGBSurface("Datas/Characters/Character_Archer.bmp", Color(0xFF, 0xFF, 0xFF));
	Players_Tile = Players_Tile_Melee; //Default tile: the melee tile
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
//Destructor
Player_Base::~Player_Base()
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
bool Player_Base::Update_Graphic_Style()
{
try
{
	// Melee Style
	if (attack_style == 1)
	{
		Players_Tile = Players_Tile_Melee;
		attack_msg_hit = attack_melee_msg_hit;
		attack_msg_miss = attack_melee_msg_miss;
		//P0_Logger << " Graphic Style Updated To Melee Style : OK " << std::endl;
	}
	// Distant Style
	else if (attack_style == 2)
	{
		Players_Tile = Players_Tile_Distant;
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
bool Player_Base::move(std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector, std::vector<Monster_Base*> Monster_Vector_Skeleton, std::vector<Monster_Base*> Monster_Vector_Worm)
{
try {
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

	//Check if the battlefield allow the move
	if(! check_battlefield_allow_character(collision_box, Environment_Sprite_Vector, BackGround_Sprite_Vector) )
	{
		//move back
		collision_box.setx(x);
		collision_box.sety(y);
		//collision found no need to work more
		return true;
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
			return true;
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
			return true;
		}
	}
    
	//Finally move the character in the same place of his collision box...
	x = collision_box.getx();
	y = collision_box.gety();
	
	//...and the arrow with his owner^^
	arrow_x = x;
	arrow_y = y;
	
	return true; //no error
} catch (...) {  //error occured
	return false;
}
}
//Check if the battlefield allow the character presence
bool Player_Base::check_battlefield_allow_character(Rect Collision_Box , std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
	bool res = true;

	std::vector<int> env_vs_pc_collisions = check_environment_allow_character(Collision_Box, Environment_Sprite_Vector);
	std::vector<int> bg_vs_pc_collisions = check_background_allow_character(Collision_Box, BackGround_Sprite_Vector);

	for (unsigned int i = 0; i < env_vs_pc_collisions.size(); i++)
	{
		if ( env_vs_pc_collisions.at(i) == -1 ) //environment is not present
		{
			if ( bg_vs_pc_collisions.at(i) == 0 )
			{
				res = false; //collision with bg
				return res; //no need to work more
			}

		} else if ( env_vs_pc_collisions.at(i) == 0 ) 
		{
			res = false; //collision with env
			return res; //no need to work more
		} else {
			res = true; //no collision
		}
	}
	
	//Never happend (just 4 warning)
	return res;
}
//Check if the ground allow the move
std::vector<int> Player_Base::check_background_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
	std::vector<int> res; //vector of collision results
	int Ground_Type;
	Rect bg_rect;

	//loop on all the vector
	for(unsigned int i=0; i < BackGround_Sprite_Vector.size(); i++)
	{
		bg_rect.setx(BackGround_Sprite_Vector[i]->Get_X());
		bg_rect.sety(BackGround_Sprite_Vector[i]->Get_Y());
		bg_rect.setw(BATF_SPRITE_W);
		bg_rect.seth(BATF_SPRITE_H);

		if ( check_collision( Collision_Box, bg_rect ) )
		{
			//Get the destination ground
			Ground_Type = BackGround_Sprite_Vector[i]->Get_BattleField_Type();
			//Ask the background if the collision box is allowed to go there
			if( Ground_Type == EMPTY_GROUND ) //Don't allow move
			{
				res.push_back(0);
			}
			else if( Ground_Type == GRASS_GROUND ) //Allow move
			{
				res.push_back(1);
			}
			else if( Ground_Type == SAND_GROUND ) //Don't allow move
			{
				res.push_back(0);
			}
			else if( Ground_Type == RIVER_GROUND ) //Allow move
			{
				res.push_back(1);
			}
			else if( Ground_Type == LAKE_GROUND ) //Don't allow move
			{
				res.push_back(0);
			}
			else // not listed type (impossible!!??). Don't allow move
			{
				res.push_back(0);
			}
		}
	}

	return res;
}
//Check if the environment allow the move
std::vector<int> Player_Base::check_environment_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector)
{
	std::vector<int> res; //vector of collision results
    int Env_Type;
	Rect env_rect;

	//loop on all the vector
	for(unsigned int i=0; i < Environment_Sprite_Vector.size(); i++)
	{
		env_rect.setx(Environment_Sprite_Vector[i]->Get_X());
		env_rect.sety(Environment_Sprite_Vector[i]->Get_Y());
		env_rect.setw(BATF_SPRITE_W);
		env_rect.seth(BATF_SPRITE_H);

		if ( check_collision( Collision_Box, env_rect ) )
		{
			//Get the destination environment
			Env_Type = Environment_Sprite_Vector[i]->Get_BattleField_Type();
			//Check if the environment allow the player's collision box presence
			if( Env_Type == NOTHING_ENV_ITEM )  //indicate no environement is present
			{
				res.push_back(-1);
			}
			else if( Env_Type == TREE_ENV_ITEM ) //Don't allow presence
			{
				res.push_back(0);
			}
			else if( Env_Type == ROCK_ENV_ITEM ) //Don't allow presence
			{
				res.push_back(0);
			}
			else if( Env_Type == WALL_ENV_ITEM ) //Don't allow presence
			{
				res.push_back(0);
			}
			else if( Env_Type == HOUSE_ENV_ITEM ) //Allow presence
			{
				res.push_back(1);
			}
			else if( Env_Type == BRIDGE_ENV_ITEM ) //Allow presence
			{
				res.push_back(1);
			}
			else // not listed type (impossible!!??). Allow presence
			{
				res.push_back(1);
			}
		}
	}

	return res;
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
  
	if (attack_status == false) //no attack is occuring
	{
		//assign the good sprite to the character sprite and the good arrow to the character arrow
		if( move_status == CH_RIGHT )
		{
			Player_SpriteRect = _player_right_attack[0];
			Arrow_SpriteRect = Arrow_Right[0];
		}
		else if( move_status == CH_LEFT )
		{
			Player_SpriteRect = _player_left_attack[0];
			Arrow_SpriteRect = Arrow_Left[0];
		}
		else if( move_status == CH_DOWN )
		{
			Player_SpriteRect = _player_down_attack[0];
			Arrow_SpriteRect = Arrow_Down[0];
		}
		else if( move_status == CH_UP )
		{
			Player_SpriteRect = _player_up_attack[0];
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
int Player_Base::attack(std::vector<Monster_Base*> Monster_Vector_Skeleton, std::vector<Monster_Base*> Monster_Vector_Worm)
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
int Player_Base::attack_check_status(int collision_box_movement, std::vector<Monster_Base*> Monster_Vector_Skeleton, std::vector<Monster_Base*> Monster_Vector_Worm)
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
bool Player_Base::Set_Attack_Animation_Sprite()
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
			Player_SpriteRect = _player_right_attack[frame];
		}
		else if( move_status == CH_LEFT )
		{
			//left sprite
			Player_SpriteRect = _player_left_attack[frame];
		}
		else if( move_status == CH_DOWN )
		{
			//down sprite
			Player_SpriteRect = _player_down_attack[frame];

		}
		else if( move_status == CH_UP )
		{
			//up sprite
			Player_SpriteRect = _player_up_attack[frame];
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
bool Player_Base::Show_Player(VideoSurface& Screen)
{
try {
	Screen.blit(Players_Tile, Point::Point(x - Camera.getx(), y - Camera.gety()), Player_SpriteRect);
	return true; //no error
} catch (...) {
	return false; //error occured
}
}
//blit the arrow on the screen
bool Player_Base::Show_Arrow(VideoSurface& Screen)
{
try {
	if ( (x != arrow_x) || (y != arrow_y) ) //dont display the arrow when it's at the same place than the character
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
	return true; //no error
} catch (...) {
	return false; //error occured
}  
}
