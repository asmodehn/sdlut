#include "Player_Base.hh"

//Default construtor
Player_Base::Player_Base()
{
	//Initial positions
	X = CH_INITIAL_X;
	Y = CH_INITIAL_Y;

	//Initial arrow position
	arrow_x = X;
	arrow_y = Y;

	//Initial moving status
	moving_status = false;

	//Empty clip for all directions
	Player_Attack_Tile_Rect = new std::vector<Rect>;
	Rect _temp_ch_rect;
	//Character Clips definition
	for (signed int i = 0; i < 8; i++)  //The 8 directions
	{
		Player_Attack_Tile_Rect->push_back(_temp_ch_rect);
	}

	//Initialize animation variables
    frame = 0;  // for animation
    move_status = CH_RIGHT;

	//Default time between frame
	DeltaTicks = 1000/FRAMES_PER_SECOND;

	//Attack variable
	attack_status = false; //false = 0
	attack_style = 1; //0: nothing (future dev), 1: Sword attack (default), 2: Bow attack, 3: magic attack (future dev), ...
	attack_successfull = 0; //Tells if a monster has been hit, by default no
	attack_initial_x = -1;
	attack_initial_y = -1;
	attack_direction = -1;

	/****Arrow***/
	string Arrow_Ini = "Datas/Items/Arrow.ini";
	std::ifstream fi_arrow(Arrow_Ini.c_str()) ;
	if (! fi_arrow.fail()) //Check file present
	{
		std::stringstream( Ini_Manager::Get_Option_String(Arrow_Ini, "Sprite_Width") ) >> Arrow_Sprite_Width;
		std::stringstream( Ini_Manager::Get_Option_String(Arrow_Ini, "Sprite_Height") ) >> Arrow_Sprite_Height;
		std::stringstream( Ini_Manager::Get_Option_String(Arrow_Ini, "Arrow_Vel") ) >> Arrow_Vel;
	}
	fi_arrow.close();

	//Clip
	Arrow_SpriteRect = new std::vector<Rect>;

	Rect _temp_arrow_rect;
	_temp_arrow_rect.setx(0);
	_temp_arrow_rect.setw(Arrow_Sprite_Width);
	_temp_arrow_rect.seth(Arrow_Sprite_Height);

	//First allocation by pushback
	for (signed int i = 0; i < 8 * PLAYER_SWORD_ATTACK_ANIMATION_FRAME; i++)
	{
		Arrow_SpriteRect->push_back(_temp_arrow_rect);
	}
	//Now allocation by iterator
	for (signed int i = 0; i < 8; i++)  //The 8 directions
	{
		_temp_arrow_rect.sety(Arrow_Sprite_Height*i);
		Arrow_SpriteRect->at(i*PLAYER_ARROW_ATTACK_ANIMATION_FRAME) = _temp_arrow_rect;
	}

	//default arrow sprite rect
	Current_Arrow_SpriteRect = Arrow_SpriteRect->at(CH_RIGHT*PLAYER_ARROW_ATTACK_ANIMATION_FRAME);

	//Arrow surface
	Arrow_Tile = RGBSurface("Datas/Items/Arrow.png", Color(0x80, 0x80, 0x80));
}

//Initialization construtor
Player_Base::Player_Base(int x, int y)
{
    //Initial position
	X = x;
	Y = y;
    
	//Initial arrow position
	arrow_x = X;
	arrow_y = Y;

	Sprite_Width = PC_WIDTH, Sprite_Height = PC_HEIGHT;

	//Initial moving status
	moving_status = false;

	Player_Attack_Tile_Rect = new std::vector<Rect>;
	Player_Attack_Tile_Rect->reserve(8 * PLAYER_SWORD_ATTACK_ANIMATION_FRAME);
	
	Rect _temp_ch_rect;
	_temp_ch_rect.setw( Sprite_Width );
	_temp_ch_rect.seth( Sprite_Height );

	//First allocation by pushback
	for (signed int i = 0; i < 8 * PLAYER_SWORD_ATTACK_ANIMATION_FRAME; i++)
	{
		Player_Attack_Tile_Rect->push_back(_temp_ch_rect);
	}
	//Now allocation by iterator
	for (signed int i = 0; i < 8; i++)  //The 8 directions
	{
		for (signed int j = 0; j < PLAYER_SWORD_ATTACK_ANIMATION_FRAME; j++) //Frames
		{
			_temp_ch_rect.setx( Sprite_Width * j );
			_temp_ch_rect.sety( Sprite_Height * i );
			Player_Attack_Tile_Rect->at(i*PLAYER_SWORD_ATTACK_ANIMATION_FRAME + j) = _temp_ch_rect;
		}
	}
	
	//Assign the right sprite to the player by default
	Characters_SpriteRect = Player_Attack_Tile_Rect->at(CH_RIGHT*PLAYER_SWORD_ATTACK_ANIMATION_FRAME);

	//Initialize animation variables
    frame = 0;  // for animation
    move_status = CH_RIGHT;

	//Default time between frame
	DeltaTicks = 1000/FRAMES_PER_SECOND;

	//Attack variable
	attack_status = false; //false = 0
	attack_style = 1; //0: nothing (future dev), 1: Sword attack (default), 2: Bow attack, 3: magic attack (future dev), ...
	attack_successfull = 0; //Tells if a monster has been hit, by default no
	attack_initial_x = -1;
	attack_initial_y = -1;
	attack_direction = -1;

	//Collision Box Definition: The collision box has the size of the character
	Collision_Box.setx(X);
    Collision_Box.sety(Y);
    Collision_Box.setw(Sprite_Width);
    Collision_Box.seth(Sprite_Height);

	/****Arrow***/
	string Arrow_Ini = "Datas/Items/Arrow.ini";
	std::ifstream fi_arrow(Arrow_Ini.c_str()) ;
	if (! fi_arrow.fail()) //Check file present
	{
		std::stringstream( Ini_Manager::Get_Option_String(Arrow_Ini, "Sprite_Width") ) >> Arrow_Sprite_Width;
		std::stringstream( Ini_Manager::Get_Option_String(Arrow_Ini, "Sprite_Height") ) >> Arrow_Sprite_Height;
		std::stringstream( Ini_Manager::Get_Option_String(Arrow_Ini, "Arrow_Vel") ) >> Arrow_Vel;
	}
	fi_arrow.close();

	//Clip
	Arrow_SpriteRect = new std::vector<Rect>;

	Rect _temp_arrow_rect;
	_temp_arrow_rect.setx(0);
	_temp_arrow_rect.setw(Arrow_Sprite_Width);
	_temp_arrow_rect.seth(Arrow_Sprite_Height);

	//First allocation by pushback
	for (signed int i = 0; i < 8 * PLAYER_SWORD_ATTACK_ANIMATION_FRAME; i++)
	{
		Arrow_SpriteRect->push_back(_temp_arrow_rect);
	}
	//Now allocation by iterator
	for (signed int i = 0; i < 8; i++)  //The 8 directions
	{
		_temp_arrow_rect.sety(Arrow_Sprite_Height*i);
		Arrow_SpriteRect->at(i*PLAYER_ARROW_ATTACK_ANIMATION_FRAME) = _temp_arrow_rect;
	}

	//default arrow sprite rect
	Current_Arrow_SpriteRect = Arrow_SpriteRect->at(CH_RIGHT*PLAYER_ARROW_ATTACK_ANIMATION_FRAME);

	//Arrow surface
	Arrow_Tile = RGBSurface("Datas/Items/Arrow.png", Color(0x80, 0x80, 0x80));

	//initialize
	Set_Attack_Style();
}

//Destructor
Player_Base::~Player_Base()
{
	delete Player_Attack_Tile_Rect, Player_Attack_Tile_Rect = NULL;
	delete Arrow_SpriteRect, Arrow_SpriteRect = NULL;
}

//Character Graphic Style Initialiation regarding the attack style
bool Player_Base::Set_Attack_Style()
{
try
{
	//
	//TODO(future): Set weapons max hit range & damage and calculate character range and damage from them
	//TODO(future): put these value's definitions inside the constructor (when monster/npc will be allowed to attack)
	//TODO(future): use formula for character_real_damage depending on character condition (disease, etc)
	//
	//int character_max_damage = Real_Inflicted_Damage;
	//int character_real_damage = character_max_damage;
	//int character_current_damage = character_real_damage;

	//int character_max_range = 0;

	// Melee Style
	if (attack_style == 1)
	{
		Characters_Tile = Players_Tile_Melee;
		
		//range: Only hit at contact (TODO future: find a more realistic hit with the sword)
		BASE_RANGE = 1;
		Real_Range = BASE_RANGE;

		//P0_Logger << nl << "Graphic Style Updated To Melee Style : OK " << std::endl;
	}
	// Distant Style
	else if (attack_style == 2)
	{
		Characters_Tile = Players_Tile_Distant;
			
		//range: 6 square
		BASE_RANGE = BATF_SPRITE_W*6;
		Real_Range = BASE_RANGE;

		//P0_Logger << nl << "Graphic Style Updated To Distant Style : OK " << std::endl;
	}
	return true;
}
catch (...) {
  return false; //error occured
}
}
//Move the Player
bool Player_Base::Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
try {
	//Random mvt
	xVel = (rand()%3-1);
	yVel = (rand()%3-1);

	//Move collision box to the futute position
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
	else if( bgType == BRIDGE_GROUND ) //Allow presence
	{
		return 1;
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
	else // not listed type (impossible!!??). Allow presence
	{
		return 1;
	}
}

//check the move direction and assign the good sprite
bool Player_Base::Assign_Direction_Sprite()
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
		
		//Good sprite for the direction
		Characters_SpriteRect = Player_Attack_Tile_Rect->at(move_status*PLAYER_SWORD_ATTACK_ANIMATION_FRAME + 0);

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
//Set values defining attack for all attack styles
bool Player_Base::Attack()
{
try
{
	attack_status = true;
	attack_direction = move_status;

	//By default consider that no attack was successfull
	attack_successfull = 0;

	if (attack_style == 1)
	{
		//Move the attack box at border of the character sprite in the good direction
		if( attack_direction == CH_RIGHT )
		{
			attack_initial_x = X+PC_WIDTH;
			attack_initial_y = Y;
			attack_CB.setw( PC_WIDTH/8 );
			attack_CB.seth( PC_HEIGHT );
		}
		else if( attack_direction == CH_RIGHT_DOWN )
		{
			attack_initial_x = X+(5*PC_WIDTH/8);
			attack_initial_y = Y+(5*PC_HEIGHT/8);
			attack_CB.setw( 5*PC_WIDTH/8 );
			attack_CB.seth( 5*PC_HEIGHT/8 );
		}
		else if( attack_direction == CH_DOWN )
		{
			attack_initial_x = X;
			attack_initial_y = Y+PC_HEIGHT;
			attack_CB.setw( PC_WIDTH );
			attack_CB.seth( PC_HEIGHT/8 );
		}
		else if( attack_direction == CH_LEFT_DOWN )
		{
			attack_initial_x = X-PC_WIDTH/8;
			attack_initial_y = Y+(5*PC_HEIGHT/8);
			attack_CB.setw( 5*PC_WIDTH/8 );
			attack_CB.seth( 5*PC_HEIGHT/8 );
		}
		else if( attack_direction == CH_LEFT )
		{
			attack_initial_x = X-PC_WIDTH/8;
			attack_initial_y = Y;
			attack_CB.setw( PC_WIDTH/8 );
			attack_CB.seth( PC_HEIGHT );
		}
		else if( attack_direction == CH_LEFT_UP )
		{			
			attack_initial_x = X-PC_WIDTH/8;
			attack_initial_y = Y-PC_HEIGHT/8;
			attack_CB.setw( 5*PC_WIDTH/8 );
			attack_CB.seth( 5*PC_HEIGHT/8 );
		}
		else if( attack_direction == CH_UP )
		{
			attack_initial_x = X;
			attack_initial_y = Y-PC_HEIGHT/8;
			attack_CB.setw( PC_WIDTH );
			attack_CB.seth( PC_HEIGHT/8 );
		}
		else if( attack_direction == CH_RIGHT_UP )
		{
			attack_initial_x = X+(5*PC_WIDTH/8);
			attack_initial_y = Y-PC_HEIGHT/8;
			attack_CB.setw( 5*PC_WIDTH/8 );
			attack_CB.seth( 5*PC_HEIGHT/8 );
		}
		
		//Set Attack BOX
		attack_CB.setx( attack_initial_x );
		attack_CB.sety( attack_initial_y );

	}
	else if (attack_style == 2)
	{
		//Move the attack box at the middle of the character sprite in the good direction
		if( attack_direction == CH_RIGHT )
		{
			attack_initial_x = X+PC_WIDTH;
			attack_initial_y = Y+(PC_HEIGHT/2);
		}
		else if( attack_direction == CH_RIGHT_DOWN )
		{
			attack_initial_x = (int)( X+ceil(PC_WIDTH/sqrt(2.f)) ) ;
			attack_initial_y = (int)( Y+ceil(PC_HEIGHT/sqrt(2.f)) ) ;
		}
		else if( attack_direction == CH_DOWN )
		{
			attack_initial_x = X+(PC_WIDTH/2);
			attack_initial_y = Y+PC_HEIGHT;
		}
		else if( attack_direction == CH_LEFT_DOWN )
		{
			attack_initial_x = (int)( X+PC_WIDTH-ceil(PC_WIDTH/sqrt(2.f)) );
			attack_initial_y = (int)( Y+ceil(PC_HEIGHT/sqrt(2.f)) );
		}
		else if( attack_direction == CH_LEFT )
		{
			attack_initial_x = X;
			attack_initial_y = Y+(PC_HEIGHT/2);
		}
		else if( attack_direction == CH_LEFT_UP )
		{
			attack_initial_x = (int)( X+PC_WIDTH-ceil(PC_WIDTH/sqrt(2.f)) );
			attack_initial_y = (int)( Y+PC_HEIGHT-ceil(PC_HEIGHT/sqrt(2.f)) );
		}
		else if( attack_direction == CH_UP )
		{
			attack_initial_x = X+(PC_WIDTH/2);
			attack_initial_y = Y ;
		}
		else if( attack_direction == CH_RIGHT_UP )
		{
			attack_initial_x = (int)( X+ceil(PC_WIDTH/sqrt(2.f)) );
			attack_initial_y = (int)( Y+PC_HEIGHT-ceil(PC_HEIGHT/sqrt(2.f)) );
		}
		
		//Good Arrow sprite
		Current_Arrow_SpriteRect = Arrow_SpriteRect->at(attack_direction*PLAYER_ARROW_ATTACK_ANIMATION_FRAME);
		
		//Set Attack BOX
		attack_CB.setx( attack_initial_x );
		attack_CB.sety( attack_initial_y );
				//the arrow only hit with it tip
		attack_CB.setw(1);
		attack_CB.seth(1);

		//initial arrow position
		Set_Arrow_Sprite_Coordinate();
	}

	//no error
	return true;
}
catch (...) {
  return false; //error occured
}
}
//Check if collision between the attack and one of the monsters on the battlefield regarding the number of movements that the attack collision is currently doing (callback method)
int Player_Base::Attack_Check_Status(int attack_distance, int inflicted_damage, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
	//Check attack direction
	if( attack_direction == CH_RIGHT )
	{
		attack_CB.setx ( attack_CB.getx() + attack_distance );
	}
	else if( attack_direction == CH_RIGHT_DOWN )
	{
		attack_CB.setx ( (int)(attack_CB.getx() + ceil(attack_distance/sqrt(2.f))) );
		attack_CB.sety ( (int)(attack_CB.gety() + ceil(attack_distance/sqrt(2.f))) );
	}
	else if( attack_direction == CH_DOWN )
	{
		attack_CB.sety( attack_CB.gety() + attack_distance );
	}
	else if( attack_direction == CH_LEFT_DOWN )
	{
		attack_CB.setx( (int)(attack_CB.getx() - ceil(attack_distance/sqrt(2.f))) );
		attack_CB.sety( (int)(attack_CB.gety() + ceil(attack_distance/sqrt(2.f))) );
	}
	else if( attack_direction == CH_LEFT )
	{
		attack_CB.setx( attack_CB.getx() - attack_distance );
	}
	else if( attack_direction == CH_LEFT_UP )
	{
		attack_CB.setx( (int)(attack_CB.getx() - ceil(attack_distance/sqrt(2.f))) );
		attack_CB.sety( (int)(attack_CB.gety() - ceil(attack_distance/sqrt(2.f))) );
	}
	else if( attack_direction == CH_UP )
	{
		attack_CB.sety( attack_CB.gety() - attack_distance );
	}
	else if( attack_direction == CH_RIGHT_UP )
	{
		attack_CB.setx( (int)(attack_CB.getx() + ceil(attack_distance/sqrt(2.f))) );
		attack_CB.sety( (int)(attack_CB.gety() - ceil(attack_distance/sqrt(2.f))) );
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
				if (check_collision( attack_CB, Current_Monster->Get_Collision_Box() ))
				{
					//One monster has been hit so send damage value to the monster
					Current_Monster->Calculate_Real_Life( inflicted_damage );
					//Than leave the check returning the ID (which will be saved inside the attack_sucessful) in order to hit only one monster at a time.
					return Current_Monster->Get_Monster_ID();
				}
			}
		}
	}
	//miss
	return 0;
}
//Set Character Sprite Which change when attack occured (callback)
bool Player_Base::Set_Attack_Animation_Sprite(std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
	//increase frame each time the timer is run (from 0 to 2)
	frame++;

	//reset the frame status at end of animation depending of the attack style 
	if ( Get_Attack_Style() == 1 ) // Melee Style
	{
		if (frame >= PLAYER_SWORD_ATTACK_ANIMATION_FRAME )
			frame = 0; //reset frame anim

		//assign the good sprite rect to the character sprite rect depending on the frame and the direction
		Characters_SpriteRect = Player_Attack_Tile_Rect->at(attack_direction*PLAYER_SWORD_ATTACK_ANIMATION_FRAME + frame);
		
		//at the second frame of the anim we check if attack hit a monster
		if ( frame == 1 )
		{
			attack_successfull = Attack_Check_Status(Real_Range, Real_Inflicted_Damage, Global_Monster_Vector) ;
		}
	}
	else if ( Get_Attack_Style() == 2 ) // Distant Style
	{
		if (frame > (PLAYER_BOW_ATTACK_ANIMATION_FRAME-1) )
			frame = 0; //reset frame anim
		
		//
		//TODO(future): define the good character sprite (future devs: depending of the frame and the direction)
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
try {
	//set coordinate in fonction of the character direction
	if( attack_direction == CH_RIGHT )
	{
		arrow_x = attack_CB.getx() - PC_WIDTH;
		arrow_y = attack_CB.gety() - (PC_HEIGHT/2) ;
	}
	else if( attack_direction == CH_RIGHT_DOWN )
	{
		arrow_x = (int)(attack_CB.getx() - ceil(PC_WIDTH/sqrt(2.f)) );
		arrow_y = (int)( attack_CB.gety() - ceil(PC_HEIGHT/sqrt(2.f)) );
	}
	else if( attack_direction == CH_DOWN )
	{
		arrow_x = attack_CB.getx() - (PC_WIDTH/2) ;
		arrow_y = attack_CB.gety() - PC_HEIGHT;
	}
	else if( attack_direction == CH_LEFT_DOWN )
	{
		arrow_x = (int)( attack_CB.getx() - PC_WIDTH+ceil(PC_WIDTH/sqrt(2.f)) );
		arrow_y = (int)( attack_CB.gety() - ceil(PC_HEIGHT/sqrt(2.f)) );
	}
	else if( attack_direction == CH_LEFT )
	{
		arrow_x = attack_CB.getx() ;
		arrow_y = attack_CB.gety() - (PC_HEIGHT/2) ;
	}
	else if( attack_direction == CH_LEFT_UP )
	{
		arrow_x = (int)( attack_CB.getx() - PC_WIDTH+ceil(PC_WIDTH/sqrt(2.f)) );
		arrow_y = (int)( attack_CB.gety() - PC_HEIGHT+ceil(PC_HEIGHT/sqrt(2.f)) );
	}
	else if( attack_direction == CH_UP )
	{
		arrow_x = attack_CB.getx() - (PC_WIDTH/2) ;
		arrow_y = attack_CB.gety() ;
	}
	else if( attack_direction == CH_RIGHT_UP )
	{
		arrow_x = (int)( attack_CB.getx() - ceil(PC_WIDTH/sqrt(2.f)) );
		arrow_y = (int)( attack_CB.gety() - PC_HEIGHT+(PC_HEIGHT/sqrt(2.f)) );
	}

	//no error occured
	return true;
} catch (...) {
	P0_Logger << nl << "Failed to set arrow sprite coordinate" << std::endl;
	return false;
}
}

//blit the arrow on the screen
bool Player_Base::Show_Arrow(Rect Camera, VideoSurface& Screen)
{
try {
	if ( attack_direction != -1 ) //dont display the arrow when its not useffull
	{
		Screen.blit(Arrow_Tile, Point::Point(arrow_x - Camera.getx(), arrow_y - Camera.gety()), Current_Arrow_SpriteRect);
	}
	return true; //no error
} catch (...) {
	return false; //error occured
}
}
