#include "Player.hh"

//Constructor
Player::Player()
{
	string Save_File = "Saves/player.sav";
	std::ifstream fi_pc( Save_File.c_str() ) ;
	if (fi_pc.fail()) //Check file present
	{
		Ini_Manager::Write_New_Ini_File(Save_File,
			"Sprite_Width = 32\nSprite_Height = 32\n\nInitial_Position_X = 192\nInitial_Position_Y = 224\n\nLife = 100\nArmor = 0\n\nDamage = 100"
			);
		P0_Logger << nl << "Save File Creation Successfull " << std::endl;
	}
	fi_pc.close();


//Initial position
	std::stringstream( Ini_Manager::Get_Option_String(Save_File, "Initial_Position_X") ) >> X;
	std::stringstream( Ini_Manager::Get_Option_String(Save_File, "Initial_Position_Y") ) >> Y;

/****Sprite****/
	std::stringstream( Ini_Manager::Get_Option_String(Save_File, "Sprite_Width") ) >> Sprite_Width;
	std::stringstream( Ini_Manager::Get_Option_String(Save_File, "Sprite_Height") ) >> Sprite_Height;
/****Characts****/
	std::stringstream( Ini_Manager::Get_Option_String(Save_File, "Life") ) >> BASE_LIFE;
	Real_Life = BASE_LIFE;
	std::stringstream( Ini_Manager::Get_Option_String(Save_File, "Armor") ) >> BASE_ARMOR;
	Real_Armor = BASE_ARMOR;
	std::stringstream( Ini_Manager::Get_Option_String(Save_File, "Damage") ) >> BASE_INFLICTED_DAMAGE;
	Real_Inflicted_Damage = BASE_INFLICTED_DAMAGE;

	P0_Logger << nl << "Save File Parsed Successfully " << std::endl;
	
		/****CLIP****/
	//Rect Player_Attack_Tile_Rect[8][PLAYER_SWORD_ATTACK_ANIMATION_FRAME];
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

		/****CAMERA****/
	Camera.setw(CURRENT_SCREEN_WIDTH);
	Camera.seth(CURRENT_SCREEN_HEIGHT);

		/****COLLISIONS BOXS****/
	//Collision Box Definition: The collision box has the size of the character
	Collision_Box.setx(X);
    Collision_Box.sety(Y);
    Collision_Box.setw(Sprite_Width);
    Collision_Box.seth(Sprite_Height);

		/****Surfaces****/
	//Characters Surfaces
	Players_Tile_Melee = RGBSurface("Datas/Characters/Character_Fighter.png", Color(0xFF, 0xFF, 0xFF));
	Players_Tile_Distant = RGBSurface("Datas/Characters/Character_Archer.png", Color(0xFF, 0xFF, 0xFF));
	Characters_Tile = Players_Tile_Melee; //Default tile: the melee tile

	//Fight Msgs Style
	//Font AttackMsg_Font("Datas/Fonts/ECHELON.TTF", 28);
	Font* AttackMsg_Font = new Font("Datas/Fonts/SlimSansSerif.ttf", 28);

		/****MSGs****/
	//Msgs displayed in the status bar
	attack_msg = *AttackMsg_Font->render(" ", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0)); // Empty msg until the attack key is pressed once (when using empty msg the creator crash so until this bug is solved we will use " " insted of "")
	attack_melee_msg_hit = *AttackMsg_Font->render("Melee Hit", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
	attack_distant_msg_hit = *AttackMsg_Font->render("Distant Hit", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
	attack_melee_msg_miss = *AttackMsg_Font->render("Melee Miss", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));
	attack_distant_msg_miss = *AttackMsg_Font->render("Distant Miss", Color(0xFF, 0xFF, 0xFF), Font::Shaded, Color(0, 0, 0));

	delete AttackMsg_Font, AttackMsg_Font = NULL;
}

//Destructor
Player::~Player()
{
}

//Manage Attack Msg regarding the attack style
bool Player::Set_Attack_Msg()
{
try
{
	// Melee Style
	if (attack_style == 1)
	{
		//If a monster has been hit displayed the hit msg, if no display miss msg
		if (attack_successfull != 0)
		{
			attack_msg = attack_melee_msg_hit;

			if (attack_successfull == 1)
				P0_Logger << nl << ">>> Skeleton Hit <<< " << std::endl;
			if (attack_successfull == 2)
				P0_Logger << nl << ">>> Worm Hit <<< " << std::endl;
		}
		else
		{
			attack_msg = attack_melee_msg_miss;
			P0_Logger << nl << ">>> Monster Miss <<< " << std::endl;
		}
	}
	// Distant Style
	else if (attack_style == 2)
	{
		//If a monster has been hit displayed the hit msg, if no display miss msg
		if (attack_successfull != 0)
		{
			attack_msg = attack_distant_msg_hit;

			if (attack_successfull == 1)
				P0_Logger << nl << ">>> Skeleton Hit <<< " << std::endl;
			if (attack_successfull == 2)
				P0_Logger << nl << ">>> Worm Hit <<< " << std::endl;
		}
		else
		{
			attack_msg = attack_distant_msg_miss;
			P0_Logger << nl << ">>> Monster Miss <<< " << std::endl;
		}
	}
	return true;
}
catch (...) {
  return false; //error occured
}
}

//Display attack msg on the status bar (hit or miss)
bool Player::Show_Attack_Msg(VideoSurface& Screen)
{
try {
	//Clean the status Bar
	Screen.fill( Color(0x00, 0x00, 0x00), Rect(0, CURRENT_SCREEN_HEIGHT - STATUS_BAR_H, CURRENT_SCREEN_WIDTH, STATUS_BAR_H) );
	
	Screen.blit( attack_msg, Point::Point(5, CURRENT_SCREEN_HEIGHT - 30) );
	return true; //no error
} catch (...) {
	return false; //error occured
}
}

//Managed the camera
bool Player::Following_Camera()
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
    if( (signed)Camera.getx() > (signed)(LEVEL_WIDTH - Camera.getw()) )
    {
        Camera.setx(LEVEL_WIDTH - Camera.getw());    
    }
	if( (signed)Camera.gety() > (signed)(LEVEL_HEIGHT + STATUS_BAR_H - Camera.geth()) )
    {
        Camera.sety(LEVEL_HEIGHT + STATUS_BAR_H - Camera.geth());    
    }
	return true; //no error
} catch (...) {
	return false; //error occured
}  
}

//Move the Player (based on input)
bool Player::Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
try {
		//Move collision box to the futute position
	if ( (move_status == CH_RIGHT ) || (move_status == CH_LEFT) || (move_status == CH_DOWN) || (move_status == CH_UP) )
	{
		Collision_Box.setx(X + ( (xVel*Ch_Vel*DeltaTicks)/1000) );
		Collision_Box.sety(Y + ( (yVel*Ch_Vel*DeltaTicks)/1000) );
		/*Collision_Box.setx(X + xVel);
		Collision_Box.sety(Y + yVel);*/
	} else //diagonals
	{
		Collision_Box.setx( X + (int)ceil( ((xVel*Ch_Vel*DeltaTicks)/1000)/sqrt(2.f)) );
		Collision_Box.sety( Y + (int)ceil( ((yVel*Ch_Vel*DeltaTicks)/1000)/sqrt(2.f)) );
	}

	//Handle collisions
	if ( Manage_Collisions(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector, true) )
	{
		//No Error => Update position 
		X = Collision_Box.getx();
		Y = Collision_Box.gety();
	}

	return true; //no error
} catch (...) {  //error occured
	return false;
}
}
