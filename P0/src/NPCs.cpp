#include "NPCs.hh"

/*****NPCs #1*****/
//Constructor
NPCs::NPCs(int x, int y)
{
		//Initial position
	X = x;
    Y = y;

	//
	//TODO: put this in the ini file with another name than CH_*
	//
	//Sprite info
	Sprite_Width = CH_WIDTH, Sprite_Height = CH_HEIGHT;

		/****CLIP****/
	//Rect Player_Attack_Tile_Rect[8][PLAYER_SWORD_ATTACK_ANIMATION_FRAME];
	Player_Attack_Tile_Rect = new std::vector<Rect>;
	Rect _temp_ch_rect;
	//npc Clips definition
	for (signed int i = 0; i < 8; i++)  //The 8 directions
	{
			_temp_ch_rect.setx( 0 );
			_temp_ch_rect.sety( 0 );
			_temp_ch_rect.setw( Sprite_Width );
			_temp_ch_rect.seth( Sprite_Height );
			Player_Attack_Tile_Rect->push_back(_temp_ch_rect);
	}

	//Assign the right sprite to the player by default
	Characters_SpriteRect = Player_Attack_Tile_Rect->at(CH_RIGHT*PLAYER_SWORD_ATTACK_ANIMATION_FRAME);

		/****COLLISIONS BOXS****/
	//Collision Box Definition: The collision box has the size of the character
	Collision_Box.setx(X);
    Collision_Box.sety(Y);
    Collision_Box.setw(Sprite_Width);
    Collision_Box.seth(Sprite_Height);

		/****Surfaces****/
	//Characters Surfaces
	Players_Tile_Melee = RGBSurface("Datas/Characters/Characters.bmp", Color(0xFF, 0xFF, 0xFF));
	Players_Tile_Distant = RGBSurface("Datas/Characters/Characters.bmp", Color(0xFF, 0xFF, 0xFF));
	Characters_Tile = Players_Tile_Melee; //Default tile: the melee tile

		/****AREA****/
	//Only allowed inside city walls
	Allowed_Area.setx(31*32);
	Allowed_Area.sety(9*32);
	Allowed_Area.setw(6*32);
	Allowed_Area.seth(10*32);
}

//Destructor
NPCs::~NPCs()
{
}
