#include "Animations.hh"

Character_Animation::Character_Animation()
{
	Animation_Tileset = NULL;
	Animation_Tile_Rect = NULL;
}
Character_Animation::Character_Animation(const char *Animation_Name, const string &Data_Root_Directory, const string &Description_File)
{
try {
	//to be able to delete pointers at any time
	Animation_Tileset = NULL;
	Animation_Tile_Rect = NULL;

	//
	//TODO Managed the 0 or 1 value for options !!!!: initialize & Check Node Exists
	//

	string Animation_Filename = Data_Root_Directory + XML_Manager::Get_Option_String(Description_File, Animation_Name);
	XML_Manager::Validate_File(Animation_Filename);

	string Animation_TS_Filename = Data_Root_Directory + XML_Manager::Get_Option_String(Animation_Filename, "Animation_TS_Filename");
	int ColorKey_R = XML_Manager::Get_Option_Value(Animation_Filename, "ColorKey_R");
	int ColorKey_G = XML_Manager::Get_Option_Value(Animation_Filename, "ColorKey_G");
	int ColorKey_B = XML_Manager::Get_Option_Value(Animation_Filename, "ColorKey_B");
	Animation_Tileset = new RGBSurface(Animation_TS_Filename, Color((unsigned char)ColorKey_R, (unsigned char)ColorKey_G, (unsigned char)ColorKey_B) );
	Animation_Frame_Number = XML_Manager::Get_Option_Value(Animation_Filename, "Frames");
	Animation_KeyFrame = 0;
	if ( XML_Manager::Check_Node_Exists(Animation_Filename, "KeyFrame") )
		Animation_KeyFrame = XML_Manager::Get_Option_Value(Animation_Filename, "KeyFrame");
	Animation_Frames_Interval = 1; //coz 0 make timer loop
	if (Animation_Frame_Number > 1) //when there is a real animation, not a single frame
		Animation_Frames_Interval = XML_Manager::Get_Option_Value_Long(Animation_Filename, "Frames_Interval");

	Animation_Sprite_Width = XML_Manager::Get_Option_Value(Animation_Filename, "Width");
	Animation_Sprite_Height = XML_Manager::Get_Option_Value(Animation_Filename, "Height");

	//Clip def
	Animation_Tile_Rect = new std::vector<Rect>;
	Animation_Tile_Rect->reserve(8 * Animation_Frame_Number);

	Rect _temp_ch_rect;
	_temp_ch_rect.setw( Animation_Sprite_Width );
	_temp_ch_rect.seth( Animation_Sprite_Height );

		//First allocation by pushback
	for (signed int i = 0; i < 8 * Animation_Frame_Number; i++)
	{
		Animation_Tile_Rect->push_back(_temp_ch_rect);
	}
		//Now allocation by iterator
	for (signed int i = 0; i < 8; i++)  //The 8 directions
	{
		for (signed int j = 0; j < Animation_Frame_Number; j++) //Frames
		{
			_temp_ch_rect.setx( Animation_Sprite_Width * j );
			_temp_ch_rect.sety( Animation_Sprite_Height * i );
			Animation_Tile_Rect->at(i*Animation_Frame_Number + j) = _temp_ch_rect;
		}
	}

} catch (std::exception &exc) {
	Clean_Animation();
	throw std::logic_error(exc.what());
} catch (...) {
	Clean_Animation();
	throw std::logic_error("Error In Character_Animation Constructor");
}
}

Character_Animation::~Character_Animation()
{
	Clean_Animation();
}

void Character_Animation::Clean_Animation()
{
	delete Animation_Tileset, Animation_Tileset = NULL;
	delete Animation_Tile_Rect, Animation_Tile_Rect = NULL;
}
