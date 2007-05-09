#include "NPCs.hh"

/*****NPC_Merchant #1*****/
//Constructor
NPC_Merchant::NPC_Merchant()
{
try{
//characteristics parsing (xml parsing)
	Parse_Description_File("Data/Characters/NPC_Merchant.xml");

//Initials default
	Characters_Current_Unarmed_Tileset = Stop_Animation->Get_Animation_Tileset();
	Characters_Current_Tileset = Characters_Current_Unarmed_Tileset;
	Current_Tile_Rect = Stop_Animation->Get_Animation_Tile_Rect()->at(CH_RIGHT); //right direction by default


//	string NPC_Ini = "Data/Characters/NPC.ini";
//	std::ifstream fi_npc( NPC_Ini.c_str() ) ;
//	if (! fi_npc.fail()) //Check file present
//	{
////Initial position
//		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Initial_Position_X") ) >> X;
//		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Initial_Position_Y") ) >> Y;
///****AREA****/
//		int temp;
//		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Allowed_Area_X") ) >> temp;
//		Allowed_Area.setx( temp );
//		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Allowed_Area_Y") ) >> temp;
//		Allowed_Area.sety(  temp );
//		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Allowed_Area_W") ) >> temp;
//		Allowed_Area.setw( temp );
//		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Allowed_Area_H") ) >> temp;
//		Allowed_Area.seth( temp );
///****Sprite****/
//		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Sprite_Width") ) >> Sprite_Width;
//		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Sprite_Height") ) >> Sprite_Height;
//		Sprite_Filename = Ini_Manager::Get_Option_String(NPC_Ini, "Sprite_Filename");
///****Velocity****/
//		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "CH_VEL") ) >> Ch_Vel;
///****Characts****/
//		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Life") ) >> BASE_LIFE;
//		Real_Life = BASE_LIFE;
//		std::stringstream( Ini_Manager::Get_Option_String(NPC_Ini, "Armor") ) >> BASE_ARMOR;
//		Real_Armor = BASE_ARMOR;
//
//	}
//	fi_npc.close();
//
//		/****CLIP****/
//	//Rect Attack_Tile_Rect[8][PLAYER_SWORD_ATTACK_ANIMATION_FRAME];
//	Rect _temp_ch_rect;
//	//npc Clips definition
//	for (signed int i = 0; i < 8; i++)  //The 8 directions
//	{
//			_temp_ch_rect.setx( 0 );
//			_temp_ch_rect.sety( 0 );
//			_temp_ch_rect.setw( Sprite_Width );
//			_temp_ch_rect.seth( Sprite_Height );
//			Attack_Tile_Rect->push_back(_temp_ch_rect);
//	}
//
//	//Assign the right sprite to the player by default
//	Current_Tile_Rect = Attack_Tile_Rect->at(CH_RIGHT*PLAYER_SWORD_ATTACK_ANIMATION_FRAME);
//
//		/****COLLISIONS BOXS****/
//	//Collision Box Definition: The collision box has the size of the character
//	Collision_Box.setx(X);
//    Collision_Box.sety(Y);
//    Collision_Box.setw(Sprite_Width);
//    Collision_Box.seth(Sprite_Height);

		/****Surfaces****/
	//Characters Surfaces
	//Players_Tile_Melee = NULL; //designed to disapear
	//Players_Tile_Distant = NULL; //designed to disapear
	//Players_Tile_Melee = new RGBSurface("Data/Characters/NPC.bmp", Color(0xFF, 0xFF, 0xFF));
	//Players_Tile_Distant = new RGBSurface("Data/Characters/NPC.bmp", Color(0xFF, 0xFF, 0xFF));
	//attack_style = 0; //designed to disapear
	//Characters_Tile = Players_Tile_Melee; //Default tile

} catch (std::exception &exc)
{
	Clean_NPC_Merchant(); //clean
	throw std::logic_error(exc.what());
}
catch (...)
{
	P0_Logger << nl << "Error In NPC_Merchant Constructor " << std::endl;
	Clean_NPC_Merchant(); //clean
	throw std::logic_error("Unhandled Exception");
}
}

//Destructor
NPC_Merchant::~NPC_Merchant()
{
	Clean_NPC_Merchant();
}

void NPC_Merchant::Clean_NPC_Merchant()
{	
	delete Attack_Animation, Attack_Animation = NULL;
	delete Death_Animation, Death_Animation = NULL;
	delete Walk_Animation, Walk_Animation = NULL;
	delete Hit_Animation, Hit_Animation = NULL;
	delete Run_Animation, Run_Animation = NULL;
	delete Stop_Animation, Stop_Animation = NULL;
	delete Pause_Animation, Pause_Animation = NULL;
}
