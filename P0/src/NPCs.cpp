#include "NPCs.hh"

/*****NPCs #1*****/
//Constructor
NPCs::NPCs()
{
	string NPC_Ini = "Datas/Characters/NPC.ini";
	std::ifstream fi_npc( NPC_Ini.c_str() ) ;
	if (! fi_npc.fail()) //Check file present
	{
//Initial position
		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Initial_Position_X") ) >> X;
		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Initial_Position_Y") ) >> Y;
/****AREA****/
		int temp;
		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Allowed_Area_X") ) >> temp;
		Allowed_Area.setx( temp );
		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Allowed_Area_Y") ) >> temp;
		Allowed_Area.sety(  temp );
		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Allowed_Area_W") ) >> temp;
		Allowed_Area.setw( temp );
		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Allowed_Area_H") ) >> temp;
		Allowed_Area.seth( temp );
/****Sprite****/
		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Sprite_Width") ) >> Sprite_Width;
		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Sprite_Height") ) >> Sprite_Height;
/****Velocity****/
		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "CH_VEL") ) >> Ch_Vel;
/****Characts****/
		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Life") ) >> BASE_LIFE;
		Real_Life = BASE_LIFE;
		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Armor") ) >> BASE_ARMOR;
		Real_Armor = BASE_ARMOR;

	}
	fi_npc.close();

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
	Players_Tile_Melee = RGBSurface("Datas/Characters/NPC.bmp", Color(0xFF, 0xFF, 0xFF));
	Players_Tile_Distant = RGBSurface("Datas/Characters/NPC.bmp", Color(0xFF, 0xFF, 0xFF));
	Characters_Tile = Players_Tile_Melee; //Default tile: the melee tile
}

//Destructor
NPCs::~NPCs()
{
}
