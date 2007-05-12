#include "Player_Base.hh"

//Default construtor
Player_Base::Player_Base()
{
	//Initial positions
	X = CH_INITIAL_X;
	Y = CH_INITIAL_Y;

/****Arrow***/
	//Initial arrow position
	arrow_x = X;
	arrow_y = Y;

	string Arrow_Ini = "Data/Items/Arrow.ini";
	std::ifstream fi_arrow(Arrow_Ini.c_str()) ;
	if (! fi_arrow.fail()) //Check file present
	{
		std::stringstream( Ini_Manager::Get_Option_String(Arrow_Ini, "Sprite_Width") ) >> Arrow_Sprite_Width;
		std::stringstream( Ini_Manager::Get_Option_String(Arrow_Ini, "Sprite_Height") ) >> Arrow_Sprite_Height;
		//Arrow surface
		Arrow_Tile = new RGBSurface( Ini_Manager::Get_Option_String(Arrow_Ini, "Filename") , Color(0x80, 0x80, 0x80));
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
}

//Initialization construtor
//Player_Base::Player_Base(int x, int y)
//{
//    //Initial position
//	X = x;
//	Y = y;
//    
//	//Initial arrow position
//	arrow_x = X;
//	arrow_y = Y;
//
//	Sprite_Width = PC_WIDTH, Sprite_Height = PC_HEIGHT;
//	Sprite_Filename = ""; //Empty sprite for now
//
//	//Player Tile Surface
//	Characters_Tile = new RGBSurface(Sprite_Filename, Color(0xFF, 0xFF, 0xFF));
//
//	//Initial moving status
//	Moving_Status = false;
//
//	Attack_Tile_Rect = new std::vector<Rect>;
//	Attack_Tile_Rect->reserve(8 * PLAYER_SWORD_ATTACK_ANIMATION_FRAME);
//	
//	Rect _temp_ch_rect;
//	_temp_ch_rect.setw( Sprite_Width );
//	_temp_ch_rect.seth( Sprite_Height );
//
//	//First allocation by pushback
//	for (signed int i = 0; i < 8 * PLAYER_SWORD_ATTACK_ANIMATION_FRAME; i++)
//	{
//		Attack_Tile_Rect->push_back(_temp_ch_rect);
//	}
//	//Now allocation by iterator
//	for (signed int i = 0; i < 8; i++)  //The 8 directions
//	{
//		for (signed int j = 0; j < PLAYER_SWORD_ATTACK_ANIMATION_FRAME; j++) //Frames
//		{
//			_temp_ch_rect.setx( Sprite_Width * j );
//			_temp_ch_rect.sety( Sprite_Height * i );
//			Attack_Tile_Rect->at(i*PLAYER_SWORD_ATTACK_ANIMATION_FRAME + j) = _temp_ch_rect;
//		}
//	}
//	
//	//Assign the right sprite to the player by default
//	Current_Tile_Rect = Attack_Tile_Rect->at(CH_RIGHT*PLAYER_SWORD_ATTACK_ANIMATION_FRAME);
//
//	//Initialize animation variables
//    frame = 0;  // for animation
//
//	//Default time between frame
//	DeltaTicks = 1000/FRAMES_PER_SECOND;
//
//	//Attack variable
//	attack_status = false; //false = 0
//	attack_style = 0; //default: unarmed
//	attack_successfull = 0; //Tells if a monster has been hit, by default no
//	attack_initial_x = -1;
//	attack_initial_y = -1;
//	attack_direction = -1;
//
//	//Collision Box Definition: The collision box has the size of the character
//	Collision_Box.setx(X);
//    Collision_Box.sety(Y);
//    Collision_Box.setw(Sprite_Width);
//    Collision_Box.seth(Sprite_Height);
//
//	/****Arrow***/
//	string Arrow_Ini = "Data/Items/Arrow.ini";
//	std::ifstream fi_arrow(Arrow_Ini.c_str()) ;
//	if (! fi_arrow.fail()) //Check file present
//	{
//		std::stringstream( Ini_Manager::Get_Option_String(Arrow_Ini, "Sprite_Width") ) >> Arrow_Sprite_Width;
//		std::stringstream( Ini_Manager::Get_Option_String(Arrow_Ini, "Sprite_Height") ) >> Arrow_Sprite_Height;
//		//Arrow surface
//		Arrow_Tile = new RGBSurface( Ini_Manager::Get_Option_String(Arrow_Ini, "Filename") , Color(0x80, 0x80, 0x80));
//		std::stringstream( Ini_Manager::Get_Option_String(Arrow_Ini, "Arrow_Vel") ) >> Arrow_Vel;
//	}
//	fi_arrow.close();
//
//	//Clip
//	Arrow_SpriteRect = new std::vector<Rect>;
//
//	Rect _temp_arrow_rect;
//	_temp_arrow_rect.setx(0);
//	_temp_arrow_rect.setw(Arrow_Sprite_Width);
//	_temp_arrow_rect.seth(Arrow_Sprite_Height);
//
//	//First allocation by pushback
//	for (signed int i = 0; i < 8 * PLAYER_SWORD_ATTACK_ANIMATION_FRAME; i++)
//	{
//		Arrow_SpriteRect->push_back(_temp_arrow_rect);
//	}
//	//Now allocation by iterator
//	for (signed int i = 0; i < 8; i++)  //The 8 directions
//	{
//		_temp_arrow_rect.sety(Arrow_Sprite_Height*i);
//		Arrow_SpriteRect->at(i*PLAYER_ARROW_ATTACK_ANIMATION_FRAME) = _temp_arrow_rect;
//	}
//
//	//default arrow sprite rect
//	Current_Arrow_SpriteRect = Arrow_SpriteRect->at(CH_RIGHT*PLAYER_ARROW_ATTACK_ANIMATION_FRAME);
//
//	//initialize
//	Manage_Attack_Style();
//}

//Destructor
Player_Base::~Player_Base()
{
	delete Arrow_SpriteRect, Arrow_SpriteRect = NULL;
	delete Arrow_Tile, Arrow_Tile = NULL;
}

//parse the xml description file
void Player_Base::Parse_Description_File(const string &Description_Filename)
{
try {
	//
	//TODO Managed the 0 or 1 value for options !!!!
	//
	XML_Manager::Validate_File(Description_Filename);

	Characters_ID = String_To_Character_Types( XML_Manager::Get_Option_String(Description_Filename, "Characters_ID") );

	string Data_Root_Directory = XML_Manager::Get_Option_String(Description_Filename, "Data_Root_Directory");
	
	Sprite_Width = XML_Manager::Get_Option_Value(Description_Filename, "Default_Sprite_Width");
	Sprite_Height = XML_Manager::Get_Option_Value(Description_Filename, "Default_Sprite_Height");
	
	X = XML_Manager::Get_Option_Value(Description_Filename, "Initial_Position_X");
	Y = XML_Manager::Get_Option_Value(Description_Filename, "Initial_Position_Y");

	//Managed the allowed area if defined, else take the default
	if ( XML_Manager::Check_Node_Exists(Description_Filename, "Allowed_Area") )
	{
		Allowed_Area.setx( XML_Manager::Get_Option_Value(Description_Filename, "Allowed_Area_X") );
		Allowed_Area.sety( XML_Manager::Get_Option_Value(Description_Filename, "Allowed_Area_Y") );
		Allowed_Area.setw( XML_Manager::Get_Option_Value(Description_Filename, "Allowed_Area_W") );
		Allowed_Area.seth( XML_Manager::Get_Option_Value(Description_Filename, "Allowed_Area_H") );
	}
	
	CB_X_Modifier = XML_Manager::Get_Option_Value(Description_Filename, "X_Modifier");
	Collision_Box.setx(X+CB_X_Modifier);
	CB_Y_Modifier = XML_Manager::Get_Option_Value(Description_Filename, "Y_Modifier");
	Collision_Box.sety(Y+CB_Y_Modifier);
	CB_Width = XML_Manager::Get_Option_Value(Description_Filename, "CB_Width");
	Collision_Box.setw(CB_Width);
	CB_Height = XML_Manager::Get_Option_Value(Description_Filename, "CB_Height");
    Collision_Box.seth(CB_Height);

	Ch_Vel = XML_Manager::Get_Option_Value(Description_Filename, "Velocity"); //in px/s coz its the player
	BASE_LIFE = XML_Manager::Get_Option_Value(Description_Filename, "Life");
	Real_Life = BASE_LIFE;
	BASE_ARMOR = XML_Manager::Get_Option_Value(Description_Filename, "Armor");
	Real_Armor = BASE_ARMOR;
	BASE_INFLICTED_DAMAGE = XML_Manager::Get_Option_Value(Description_Filename, "Damage");
	Real_Inflicted_Damage = BASE_INFLICTED_DAMAGE;
	
	string Default_Animations_Center_Filename = Data_Root_Directory + XML_Manager::Get_Option_String(Description_Filename, "Animation_Center_Filename");

	//Default Animations Center
	Default_Animations_Center = new Character_Animations_Center( Data_Root_Directory, Default_Animations_Center_Filename );


} catch (std::exception &exc)
{
	throw std::logic_error(exc.what());
}
catch (...)
{
	throw std::logic_error("Unhandled Exception When Parsing XML Description File" + Description_Filename);
}
}


//Move the Player
bool Player_Base::Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
try {
	//Random mvt
	xVel = (rand()%3-1)*Ch_Vel;
	yVel = (rand()%3-1)*Ch_Vel;

	if( Assign_Direction_Sprite() == false )
	{ 
		P0_Logger << nl << "Check character direction Failed " << std::endl;    
	}
	if ( Get_Moving_Status() ) //we're really moving but not simply changing the direction
	{

		//Move collision box to the futute position
		Collision_Box.setx(X + xVel);
		Collision_Box.sety(Y + yVel);

		//handle collisions
		if ( Manage_Collisions(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector, true) )
		{
			//No Error => Update position 
			X = Collision_Box.getx();
			Y = Collision_Box.gety();
		}
	}

	return true; //no error
} catch (...) {  //error occured
	return false;
}
}

//Set ground vs player rules
int Player_Base::Get_BG_vs_CH_Rules(const int& bgType)
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
int Player_Base::Get_Env_vs_CH_Rules(const int& envType)
{
	if( envType == NOTHING_ENV )  //indicate no environement is present
	{
		return -1;
	}
	else if( envType == TREE_ENV ) //Don't allow presence
	{
		return 0;
	}
	else if( envType == ROCK_ENV ) //Don't allow presence
	{
		return 0;
	}
	else if( envType == WALL_ENV ) //Don't allow presence
	{
		return 0;
	}
	else if( envType == HOUSE_ENV ) //Allow presence
	{
		return 1;
	}
	else // not listed type (impossible!!??). Allow presence
	{
		return 1;
	}
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
bool Player_Base::Show_Arrow(const Rect& Camera, VideoSurface& Screen)
{
try {
	if ( attack_direction != -1 ) //dont display the arrow when its not useffull
	{
		Screen.blit(*Arrow_Tile, Point::Point(arrow_x - Camera.getx(), arrow_y - Camera.gety()), Current_Arrow_SpriteRect);
	}
	return true; //no error
} catch (...) {
	return false; //error occured
}
}
