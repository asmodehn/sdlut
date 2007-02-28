#include "Player.hh"

//Constructor
Player::Player(int x, int y)
{
	//Initial position
	X = x;
    Y = y;

	//
	//TODO: put this in the ini file
	//
	//Sprite info
	Sprite_Width = PC_WIDTH, Sprite_Height = PC_HEIGHT;

		/****CLIP****/
	//Rect Player_Attack_Tile_Rect[8][PLAYER_SWORD_ATTACK_ANIMATION_FRAME];
	Player_Attack_Tile_Rect = new std::vector<Rect>;
	Rect _temp_ch_rect;
	//Character Clips definition
	for (signed int i = 0; i < 8; i++)  //The 8 directions
	{
		for (signed int j = 0; j < PLAYER_SWORD_ATTACK_ANIMATION_FRAME; j++) //Frames
		{
			_temp_ch_rect.setx( Sprite_Width * j );
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

		/****CAMERA****/
	//Camera: at the begining it's in the top left corner of the level
	//Camera = {0, 0, Sprite_Width, Sprite_Height};
	Camera.setx(0);
	Camera.sety(0);
	//Camera.setx( (X + Sprite_Width / 2) - CURRENT_SCREEN_WIDTH / 2 );
	//Camera.sety( (Y + Sprite_Height / 2) - CURRENT_SCREEN_HEIGHT / 2 );
	Camera.setw(CURRENT_SCREEN_WIDTH);
	Camera.seth(CURRENT_SCREEN_HEIGHT);

		/****COLLISIONS BOXS****/
	//Collision Box Definition: The collision box has the size of the character
	Collision_Box.setx(X);
    Collision_Box.sety(Y);
    Collision_Box.setw(Sprite_Width);
    Collision_Box.seth(Sprite_Height);

	//Attack collsion box: currently in the same place of the character
	attack_collision_box = Collision_Box;

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
bool Player::Set_Attack_Msgs()
{
try
{
	// Melee Style
	if (attack_style == 1)
	{
		attack_msg_hit = attack_melee_msg_hit;
		attack_msg_miss = attack_melee_msg_miss;
	}
	// Distant Style
	else if (attack_style == 2)
	{
		attack_msg_hit = attack_distant_msg_hit;
		attack_msg_miss = attack_distant_msg_miss;
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

//Move the Player (based on input)
bool Player::Move(std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector)
{
try {
	//Move collision box to the futute position
	//Collision_Box.setx(X + (xVel*(DeltaTicks/1000)) );
	//Collision_Box.sety(Y + (yVel*(DeltaTicks/1000)) );
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
