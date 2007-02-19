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

	//Sprite info
	Sprite_Width = CH_WIDTH;
	Sprite_Height = CH_HEIGHT;

	//Initial moving status
	moving_status = false;

	//Rect Player_Attack_Tile_Rect[8][PLAYER_SWORD_ATTACK_ANIMATION_FRAME];
	Player_Attack_Tile_Rect = new std::vector<Rect>;
	Rect _temp_ch_rect;
	//Character Clips definition
	for (unsigned int i = 0; i < 8; i++)  //The 8 directions
	{
		for (unsigned int j = 0; j < PLAYER_SWORD_ATTACK_ANIMATION_FRAME; j++) //Frames
		{
			_temp_ch_rect.setx( Sprite_Width * j);
			_temp_ch_rect.sety( Sprite_Height * i );
			_temp_ch_rect.setw( Sprite_Width );
			_temp_ch_rect.seth( Sprite_Height );
			Player_Attack_Tile_Rect->push_back(_temp_ch_rect);
			//->at(i*PLAYER_SWORD_ATTACK_ANIMATION_FRAME + j)
			//
			//TODO find a way to make insert by iterator insted of pushback
			//
		}
	}

	//Assign the right sprite to the player by default
	Characters_SpriteRect = Player_Attack_Tile_Rect->at(CH_RIGHT*PLAYER_SWORD_ATTACK_ANIMATION_FRAME);

	//Initialize animation variables
    frame = 0;  // for animation
	arrow_frame = 0; //for arrow animation
    move_status = CH_RIGHT;

	//Attack variable
	attack_status = false; //false = 0
	attack_style = 1; //0: nothing (future dev), 1: Sword attack (default), 2: Bow attack, 3: magic attack (future dev), ...
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
    Collision_Box.setw(Sprite_Width);
    Collision_Box.seth(Sprite_Height);

	//Attack collsion box: currently in the same place of the character
	attack_collision_box.setx(X);
    attack_collision_box.sety(Y);
    attack_collision_box.setw(Sprite_Width);
    attack_collision_box.seth(Sprite_Height);

	/****Arrow***/
	//Clip
	Arrow_SpriteRect = new std::vector<Rect>;
	Rect _temp_arrow_rect;
	for (unsigned int i = 0; i < 8; i++)  //The 8 directions
	{
		_temp_arrow_rect.setx(0);
		_temp_arrow_rect.sety(Sprite_Height*i);
		_temp_arrow_rect.setw(Sprite_Width);
		_temp_arrow_rect.seth(Sprite_Height);
		Arrow_SpriteRect->push_back(_temp_arrow_rect);
		//->at(i*PLAYER_ARROW_ATTACK_ANIMATION_FRAME)
		//
		//TODO find a way to make insert by iterator insted of pushback
		//
	}

	//default arrow sprite rect
	Current_Arrow_SpriteRect = Arrow_SpriteRect->at(CH_RIGHT*PLAYER_ARROW_ATTACK_ANIMATION_FRAME);


	/****Surfaces****/
	//Characters Surfaces
	Players_Tile_Melee = RGBSurface("Datas/Characters/Character_Fighter.png", Color(0xFF, 0xFF, 0xFF));
	Players_Tile_Distant = RGBSurface("Datas/Characters/Character_Archer.png", Color(0xFF, 0xFF, 0xFF));
	Characters_Tile = Players_Tile_Melee; //Default tile: the melee tile
	//Arrow surface
	Arrow_Tile = RGBSurface("Datas/Items/Arrow.png", Color(0x80, 0x80, 0x80));

	//Fight Msgs Style
	//Font AttackMsg_Font("Datas/Fonts/ECHELON.TTF", 28);
	Font* AttackMsg_Font = new Font("Datas/Fonts/SlimSansSerif.ttf", 28);

	//Msgs displayed in the status bar
	attack_msg = *AttackMsg_Font->render(" ", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0)); // Empty msg until the attack key is pressed once (when using empty msg the creator crash so until this bug is solved we will use " " insted of "")
	attack_melee_msg_hit = *AttackMsg_Font->render("Melee Hit", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
	attack_distant_msg_hit = *AttackMsg_Font->render("Distant Hit", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
	attack_melee_msg_miss = *AttackMsg_Font->render("Melee Miss", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
	attack_distant_msg_miss = *AttackMsg_Font->render("Distant Miss", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
}

//Destructor
Player_Base::~Player_Base()
{
	delete Player_Attack_Tile_Rect, Player_Attack_Tile_Rect = NULL;
	delete Arrow_SpriteRect, Arrow_SpriteRect = NULL;
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
		//P0_Logger << nl << "Graphic Style Updated To Melee Style : OK " << std::endl;
	}
	// Distant Style
	else if (attack_style == 2)
	{
		Characters_Tile = Players_Tile_Distant;
		attack_msg_hit = attack_distant_msg_hit;
		attack_msg_miss = attack_distant_msg_miss;
		//P0_Logger << nl << "Graphic Style Updated To Distant Style : OK " << std::endl;
	}
	return true;
}
catch (...) {
  return false; //error occured
}
}
//Move the Player
bool Player_Base::move(unsigned long deltaticks, std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector)
{
try {
	//Move collision box to the futute position
	//Collision_Box.setx(X + (xVel*(deltaticks/1000)) );
	//Collision_Box.sety(Y + (yVel*(deltaticks/1000)) );
	Collision_Box.setx(X + xVel);
	Collision_Box.sety(Y + yVel);

	//check collisions
	if ( Check_Collisions(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector) )
	{
		//Collision found => move back collision box
		Collision_Box.setx(X);
		Collision_Box.sety(Y); 
	}

	//Update position
	X = Collision_Box.getx();
	Y = Collision_Box.gety();

	//Update arrow position
	arrow_x = X;
	arrow_y = Y;

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
	if (!Get_Attack_Status()) //no attack is occuring
	{
		int old_move_status = move_status;

		//check velocities
		if ( (Get_xVel() > 0) && (Get_yVel() == 0) ) //CH is moving right
		{
			move_status = CH_RIGHT;
		}
		else if ( (Get_xVel() > 0) && (Get_yVel() > 0) )  //right down
		{
			move_status = CH_RIGHT_DOWN;

		}
		else if ( (Get_xVel() == 0) && (Get_yVel() > 0) )  //down
		{
			move_status = CH_DOWN;
		}
		else if ( (Get_xVel() < 0) && (Get_yVel() > 0) ) //left down
		{
			move_status = CH_LEFT_DOWN;
		}
		else if ( (Get_xVel() < 0) && (Get_yVel() == 0) ) //left
		{
			move_status = CH_LEFT;
		}
		else if ( (Get_xVel() < 0) && (Get_yVel() < 0) ) //left up
		{
			move_status = CH_LEFT_UP;
		}
		else if ( (Get_xVel() == 0) && (Get_yVel() < 0) ) //up
		{
			move_status = CH_UP;
		}
		else if ( (Get_xVel() > 0) && (Get_yVel() < 0) ) //right up
		{
			move_status = CH_RIGHT_UP;
		}
		
		//Good sprites for the direction
		Characters_SpriteRect = Player_Attack_Tile_Rect->at(move_status*PLAYER_SWORD_ATTACK_ANIMATION_FRAME + 0);
		Current_Arrow_SpriteRect = Arrow_SpriteRect->at(move_status*PLAYER_ARROW_ATTACK_ANIMATION_FRAME + 0);

		//Check if we are changing direction
		if ( old_move_status != move_status )
		{ //change but dont move
			//xVel = 0;
			//yVel = 0;
			moving_status = false;
		} else {
			moving_status = true; //we're moving
		}
	}
	return true; //no error
} catch (...) {
  return false; //error occured
}
}
//define character sprite which appear on the screen during moves
bool Player_Base::Set_Move_Animation_Sprite()
{
		//P0_Logger << nl << "Set_Move_Animation_Sprite called" << std::endl;

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
		attack_collision_box.setx ( Collision_Box.getx() + (CH_WIDTH * current_hit_distance) );
		attack_collision_box.sety ( Collision_Box.gety());
	}
	else if( move_status == CH_RIGHT_DOWN )
	{
		attack_collision_box.setx ( Collision_Box.getx() + (CH_WIDTH * current_hit_distance) );
		attack_collision_box.sety ( Collision_Box.gety() + (CH_HEIGHT * current_hit_distance) );
	}
	else if( move_status == CH_DOWN )
	{
		attack_collision_box.setx( Collision_Box.getx() );
		attack_collision_box.sety( Collision_Box.gety() + (CH_HEIGHT * current_hit_distance) );
	}
	else if( move_status == CH_LEFT_DOWN )
	{
		attack_collision_box.setx( Collision_Box.getx() - (CH_WIDTH * current_hit_distance) );
		attack_collision_box.sety( Collision_Box.gety() + (CH_HEIGHT * current_hit_distance) );
	}
	else if( move_status == CH_LEFT )
	{
		attack_collision_box.setx( Collision_Box.getx() - (CH_WIDTH * current_hit_distance) );
		attack_collision_box.sety( Collision_Box.gety() );
	}
	else if( move_status == CH_LEFT_UP )
	{
		attack_collision_box.setx( Collision_Box.getx() - (CH_WIDTH * current_hit_distance) );
		attack_collision_box.sety( Collision_Box.gety() - (CH_WIDTH * current_hit_distance) );
	}
	else if( move_status == CH_UP )
	{
		attack_collision_box.setx( Collision_Box.getx() );
		attack_collision_box.sety( Collision_Box.gety() - (CH_WIDTH * current_hit_distance) );
	}
	else if( move_status == CH_RIGHT_UP )
	{
		attack_collision_box.setx( Collision_Box.getx() + (CH_WIDTH * current_hit_distance) );
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

	//reset the frame status at end of animation depending of the attack style 
	if ( Get_Attack_Style() == 1 ) // Melee Style
	{
		if (frame > (PLAYER_SWORD_ATTACK_ANIMATION_FRAME-1) )
			frame = 0; //reset frame anim

		//assign the good sprite rect to the character sprite rect depending on the frame and the direction
		Characters_SpriteRect = Player_Attack_Tile_Rect->at(move_status*PLAYER_SWORD_ATTACK_ANIMATION_FRAME + frame);
	}
	else if ( Get_Attack_Style() == 2 ) // Distant Style
	{
		if (frame > (PLAYER_BOW_ATTACK_ANIMATION_FRAME-1) )
			frame = 0; //reset frame anim
		
		//
		//TODO: define the good character sprite (future devs: depending of the frame and the direction)
		//
		//frame = 0;
	}


	P0_Logger << nl << "Set_Attack_Animation_Sprite called FRAME:" << frame << std::endl;

	if ( frame == 0 )
		return false; //end of anim

	//anim is still looping
	return true;

}
//arrow animation (callback method)
bool Player_Base::Set_Arrow_Sprite_Coordinate()
{
	//increase arrow frame
	arrow_frame++;

	P0_Logger << nl << "Set_Arrow_Sprite_Infos called FRAME:" << arrow_frame << std::endl;

	if (arrow_frame <= hit_monster_distance) //Move the arrow until hit_monster_distance reached. Equal, monster hit!
	{
		//set coordinate in fonction of the character direction
		if( move_status == CH_RIGHT )
		{
			arrow_x = X + (arrow_frame * Sprite_Width);
			arrow_y = Y;
		}
		else if( move_status == CH_RIGHT_DOWN )
		{
			arrow_x = X + (arrow_frame * Sprite_Width);
			arrow_y = Y + (arrow_frame * Sprite_Height);
		}
		else if( move_status == CH_DOWN )
		{
			arrow_x = X;
			arrow_y = Y + (arrow_frame * Sprite_Height);
		}
		else if( move_status == CH_LEFT_DOWN )
		{
			arrow_x = X - (arrow_frame * Sprite_Width);
			arrow_y = Y + (arrow_frame * Sprite_Height);
		}
		else if( move_status == CH_LEFT )
		{
			arrow_x = X - (arrow_frame * Sprite_Width);
			arrow_y = Y;
		}
		else if( move_status == CH_LEFT_UP )
		{
			arrow_x = X - (arrow_frame * Sprite_Width);
			arrow_y = Y - (arrow_frame * Sprite_Height);
		}
		else if( move_status == CH_UP )
		{
			arrow_x = X;
			arrow_y = Y - (arrow_frame * Sprite_Height);
		}
		else if( move_status == CH_RIGHT_UP )
		{
			arrow_x = X + (arrow_frame * Sprite_Width);
			arrow_y = Y - (arrow_frame * Sprite_Height);
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
		Screen.blit(Arrow_Tile, Point::Point(arrow_x - Camera.getx(), arrow_y - Camera.gety()), Current_Arrow_SpriteRect);
	}
	return true; //no error
} catch (...) {
	return false; //error occured
}
}
//Display attack msg on the status bar (hit or miss)
bool Player_Base::Show_Attack_Msg(VideoSurface& Screen)
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
				P0_Logger << nl << ">>> Skeleton Hit <<< " << std::endl;
			if (attack_successfull == 2)
				P0_Logger << nl << ">>> Worm Hit <<< " << std::endl;
		}
		else
		{
			attack_msg = attack_msg_miss;
			P0_Logger << nl << ">>> Monster Miss <<< " << std::endl;
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
    Camera.setx( (X + Sprite_Width / 2) - CURRENT_SCREEN_WIDTH / 2 );
    Camera.sety( (Y + Sprite_Height / 2) - CURRENT_SCREEN_HEIGHT / 2 );
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
