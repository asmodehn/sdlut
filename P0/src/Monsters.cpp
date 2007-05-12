#include "Monsters.hh"

//Skeleton Full constructor
Monster_Skeleton::Monster_Skeleton(int x, int y,
		int &Ch_Vel, int &BASE_LIFE, int &BASE_ARMOR, int &BASE_INFLICTED_DAMAGE, int &Sprite_Width, int &Sprite_Height, Character_Types &Characters_ID,
		Rect &Allowed_Area,
		int &CB_X_Modifier, int &CB_Y_Modifier, int &CB_Width, int &CB_Height,
		Character_Animations_Center* &Default_Animations_Center,
		RGBSurface* &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect
		)
{
try {
    //Initial position
	X = x;
    Y = y;

	this->Ch_Vel = Ch_Vel;
	this->BASE_LIFE = BASE_LIFE;
	Real_Life = BASE_LIFE;
	this->BASE_ARMOR = BASE_ARMOR;
	Real_Armor = BASE_ARMOR;
	this->BASE_INFLICTED_DAMAGE = BASE_INFLICTED_DAMAGE;
	Real_Inflicted_Damage = BASE_INFLICTED_DAMAGE;
	this->Sprite_Width = Sprite_Width;
	this->Sprite_Height = Sprite_Height;
	this->Characters_ID = Characters_ID;

	this->Allowed_Area = Allowed_Area;

	this->CB_X_Modifier = CB_X_Modifier;
	this->CB_Y_Modifier = CB_Y_Modifier;
	this->CB_Width = CB_Width;
	this->CB_Height = CB_Height;

	this->Default_Animations_Center = Default_Animations_Center;

	this->Life_Bar_Tile = Life_Bar_Tile;
	this->empty_life_bar_rect = empty_life_bar_rect;
	this->real_life_bar_rect = real_life_bar_rect;
								   
	////Monster Clip definition range for the top left (Random monster from the 1th line)
    //_monster_clip.setx( Sprite_Width * (rand()%7) );
	//_monster_clip.sety( 0 );
    //_monster_clip.setw( Sprite_Width );
    //_monster_clip.seth( Sprite_Height );

	//Assign the sprite
	Current_Tile_Rect = _monster_clip;

	//Monster type
	//Characters_ID = Undead; 

	//Collision Box Definition
	Collision_Box.setx(X+CB_X_Modifier);
	Collision_Box.sety(Y+CB_Y_Modifier);
	Collision_Box.setw(CB_Width);
	Collision_Box.seth(CB_Height);
	////Collision Box Definition : The collision box has the size of the monster
	//Collision_Box.setx(X);
    //Collision_Box.sety(Y);
    //Collision_Box.setw(Sprite_Width);
    //Collision_Box.seth(Sprite_Height);

	Characters_Current_Tileset = Default_Animations_Center->Get_Stop_Animation()->Get_Animation_Tileset();
	Current_Tile_Rect = Default_Animations_Center->Get_Stop_Animation()->Get_Animation_Tile_Rect()->at(CH_RIGHT); //right direction by default

} catch (std::exception &exc) {
	throw std::logic_error( "Error in Monster_Skeleton Constructor: " + (string)exc.what() );
} catch (...) {
	//unkown error occured
	throw std::logic_error( "Unhandled Error in Monster_Skeleton Constructor" );
}
}

//Destructor
Monster_Skeleton::~Monster_Skeleton()
{
}

//Intialize Monster: get all data from external files, assign surface, boxs, ...
void Monster_Skeleton::Initialize(
		int &Ch_Vel, int &BASE_LIFE, int &BASE_ARMOR, int &BASE_INFLICTED_DAMAGE, int &Sprite_Width, int &Sprite_Height, Character_Types &Characters_ID,
		Rect &Allowed_Area,
		int &CB_X_Modifier, int &CB_Y_Modifier, int &CB_Width, int &CB_Height,
		Character_Animations_Center* &Default_Animations_Center,
		RGBSurface* &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect
		)
{
try {

	//
	//TODO Managed the 0 or 1 value for options !!!!
	//
	
	string Description_Filename = "Data/Characters/Monster_Skeleton.xml";
	XML_Manager::Validate_File(Description_Filename);

	Characters_ID = String_To_Character_Types( XML_Manager::Get_Option_String(Description_Filename, "Characters_ID") );

	string Data_Root_Directory = XML_Manager::Get_Option_String(Description_Filename, "Data_Root_Directory");
	
	Sprite_Width = XML_Manager::Get_Option_Value(Description_Filename, "Default_Sprite_Width");
	Sprite_Height = XML_Manager::Get_Option_Value(Description_Filename, "Default_Sprite_Height");

	//Default Area: the whole level
	Allowed_Area.setx(0);
	Allowed_Area.sety(0);
	Allowed_Area.setw(LEVEL_WIDTH);
	Allowed_Area.seth(LEVEL_HEIGHT);

	//Managed the allowed area if defined, else keep the default
	if ( XML_Manager::Check_Node_Exists(Description_Filename, "Allowed_Area") )
	{
		Allowed_Area.setx( XML_Manager::Get_Option_Value(Description_Filename, "Allowed_Area_X") );
		Allowed_Area.sety( XML_Manager::Get_Option_Value(Description_Filename, "Allowed_Area_Y") );
		Allowed_Area.setw( XML_Manager::Get_Option_Value(Description_Filename, "Allowed_Area_W") );
		Allowed_Area.seth( XML_Manager::Get_Option_Value(Description_Filename, "Allowed_Area_H") );
	}
	
	CB_X_Modifier = XML_Manager::Get_Option_Value(Description_Filename, "X_Modifier");
	CB_Y_Modifier = XML_Manager::Get_Option_Value(Description_Filename, "Y_Modifier");
	CB_Width = XML_Manager::Get_Option_Value(Description_Filename, "CB_Width");
	CB_Height = XML_Manager::Get_Option_Value(Description_Filename, "CB_Height");

	Ch_Vel = XML_Manager::Get_Option_Value(Description_Filename, "Velocity"); //in px/s coz its the player
	BASE_LIFE = XML_Manager::Get_Option_Value(Description_Filename, "Life");
	BASE_ARMOR = XML_Manager::Get_Option_Value(Description_Filename, "Armor");
	BASE_INFLICTED_DAMAGE = XML_Manager::Get_Option_Value(Description_Filename, "Damage");
	
	
	string Default_Animations_Center_Filename = Data_Root_Directory + XML_Manager::Get_Option_String(Description_Filename, "Animation_Center_Filename");

	//Default Animations Center
	Default_Animations_Center = new Character_Animations_Center( Data_Root_Directory, Default_Animations_Center_Filename );






	////Characteristics management
	//string Monster_Ini = "Data/Characters/Skeletons.ini";
	//std::ifstream fi_monster(Monster_Ini.c_str()) ;
	//if (! fi_monster.fail()) //Check file present
	//{
	//	std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Width") ) >> Sprite_Width;
	//	std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Height") ) >> Sprite_Height;
	//	Characters_Current_Tileset = new RGBSurface(Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Filename") , Color(0xFF, 0xFF, 0xFF));
	//	//Sprite_Filename = Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Filename");
	//	std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "CH_VEL") ) >> Ch_Vel;
	//	std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Life") ) >> BASE_LIFE;
	//	Real_Life = BASE_LIFE;
	//	std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Armor") ) >> BASE_ARMOR;
	//	Real_Armor = BASE_ARMOR;		
	//}
	//else { //can't read file
	//	Sprite_Width = 0, Sprite_Height = 0;
	//	Characters_Current_Tileset = NULL;
	//	Ch_Vel = 0;
	//	BASE_LIFE = 0;
	//	BASE_ARMOR = 0;
	//	fi_monster.close();
	//	throw std::logic_error("Can't Read File " + Monster_Ini);
	//}
	//fi_monster.close();

	//Life bar infos
	Life_Bar_Tile = new RGBSurface("Data/Characters/Life Bar Tile.bmp", Color(0xFF, 0xFF, 0xFF));
	
	empty_life_bar_rect.setx(0);
	empty_life_bar_rect.sety(0);
	empty_life_bar_rect.setw(LIFE_BAR_WIDTH);
	empty_life_bar_rect.seth(LIFE_BAR_HEIGHT);

	real_life_bar_rect.setx(0);
	real_life_bar_rect.sety(LIFE_BAR_HEIGHT);
	real_life_bar_rect.setw(LIFE_BAR_WIDTH);
	real_life_bar_rect.seth(LIFE_BAR_HEIGHT);

} catch (std::exception &exc) {
	throw std::logic_error( "Error in Monster_Skeleton::Initialize(): " + (string)exc.what() );
} catch (...) {
	//unkown error occured
	throw std::logic_error( "Unhandled Error in Monster_Skeleton::Initialize" );
}
}

//Set ground vs skeleton rules
int Monster_Skeleton::Get_BG_vs_CH_Rules(const int& bgType)
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



//Worm Full constructor
Monster_Worm::Monster_Worm(int x, int y,
		int &Ch_Vel, int &BASE_LIFE, int &BASE_ARMOR, int &BASE_INFLICTED_DAMAGE, int &Sprite_Width, int &Sprite_Height, Character_Types &Characters_ID,
		Rect &Allowed_Area,
		int &CB_X_Modifier, int &CB_Y_Modifier, int &CB_Width, int &CB_Height,
		Character_Animations_Center* &Default_Animations_Center,
		RGBSurface* &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect
		)
{
try {
    //Initial position
	X = x;
    Y = y;

	this->Ch_Vel = Ch_Vel;
	this->BASE_LIFE = BASE_LIFE;
	Real_Life = BASE_LIFE;
	this->BASE_ARMOR = BASE_ARMOR;
	Real_Armor = BASE_ARMOR;
	this->BASE_INFLICTED_DAMAGE = BASE_INFLICTED_DAMAGE;
	Real_Inflicted_Damage = BASE_INFLICTED_DAMAGE;
	this->Sprite_Width = Sprite_Width;
	this->Sprite_Height = Sprite_Height;
	this->Characters_ID = Characters_ID;

	this->Allowed_Area = Allowed_Area;

	this->CB_X_Modifier = CB_X_Modifier;
	this->CB_Y_Modifier = CB_Y_Modifier;
	this->CB_Width = CB_Width;
	this->CB_Height = CB_Height;

	this->Characters_Current_Tileset = Characters_Current_Tileset;
	this->Default_Animations_Center = Default_Animations_Center;

	this->Life_Bar_Tile = Life_Bar_Tile;
	this->empty_life_bar_rect = empty_life_bar_rect;
	this->real_life_bar_rect = real_life_bar_rect;

	////Monster Clip definition range for the top left (Random monster from the 7th line)
    //_monster_clip.setx( Sprite_Width * (rand()%7) );
	//_monster_clip.sety( Sprite_Height*6 );
    //_monster_clip.setw( Sprite_Width );
    //_monster_clip.seth( Sprite_Height );

	////Assign the sprite
	//Current_Tile_Rect = _monster_clip;

	//Monster type
	//Characters_ID = Crawler;

	//Collision Box Definition
	Collision_Box.setx(X+CB_X_Modifier);
	Collision_Box.sety(Y+CB_Y_Modifier);
	Collision_Box.setw(CB_Width);
	Collision_Box.seth(CB_Height);
	////Collision Box Definition : The collision box has the size of the monster
	//Collision_Box.setx(X);
    //Collision_Box.sety(Y);
    //Collision_Box.setw(Sprite_Width);
    //Collision_Box.seth(Sprite_Height);

	//
	//TODO
	//warning walk animation below coz thre is no stop animation: manage that inside the animation center
	//
	Characters_Current_Tileset = Default_Animations_Center->Get_Stop_Animation()->Get_Animation_Tileset();
	Current_Tile_Rect = Default_Animations_Center->Get_Stop_Animation()->Get_Animation_Tile_Rect()->at(CH_RIGHT); //right direction by default

} catch (std::exception &exc) {
	throw std::logic_error( "Error in Monster_Worm Constructor: " + (string)exc.what() );
} catch (...) {
	//unkown error occured
	throw std::logic_error( "Unhandled Error in Monster_Worm Constructor" );
}
}

//Destructor
Monster_Worm::~Monster_Worm()
{
}

//Intialize Monster: get all data from external files, assign surface, boxs, ...
void Monster_Worm::Initialize(
		int &Ch_Vel, int &BASE_LIFE, int &BASE_ARMOR, int &BASE_INFLICTED_DAMAGE, int &Sprite_Width, int &Sprite_Height, Character_Types &Characters_ID,
		Rect &Allowed_Area,
		int &CB_X_Modifier, int &CB_Y_Modifier, int &CB_Width, int &CB_Height,
		Character_Animations_Center* &Default_Animations_Center,
		RGBSurface* &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect
		)
{
try {
	//
	//TODO Managed the 0 or 1 value for options !!!!
	//
	
	string Description_Filename = "Data/Characters/Monster_Worm.xml";
	XML_Manager::Validate_File(Description_Filename);

	Characters_ID = String_To_Character_Types( XML_Manager::Get_Option_String(Description_Filename, "Characters_ID") );

	string Data_Root_Directory = XML_Manager::Get_Option_String(Description_Filename, "Data_Root_Directory");
	
	Sprite_Width = XML_Manager::Get_Option_Value(Description_Filename, "Default_Sprite_Width");
	Sprite_Height = XML_Manager::Get_Option_Value(Description_Filename, "Default_Sprite_Height");

	//Default Area: the whole level
	Allowed_Area.setx(0);
	Allowed_Area.sety(0);
	Allowed_Area.setw(LEVEL_WIDTH);
	Allowed_Area.seth(LEVEL_HEIGHT);

	//Managed the allowed area if defined, else keep the default
	if ( XML_Manager::Check_Node_Exists(Description_Filename, "Allowed_Area") )
	{
		Allowed_Area.setx( XML_Manager::Get_Option_Value(Description_Filename, "Allowed_Area_X") );
		Allowed_Area.sety( XML_Manager::Get_Option_Value(Description_Filename, "Allowed_Area_Y") );
		Allowed_Area.setw( XML_Manager::Get_Option_Value(Description_Filename, "Allowed_Area_W") );
		Allowed_Area.seth( XML_Manager::Get_Option_Value(Description_Filename, "Allowed_Area_H") );
	}
	
	CB_X_Modifier = XML_Manager::Get_Option_Value(Description_Filename, "X_Modifier");
	CB_Y_Modifier = XML_Manager::Get_Option_Value(Description_Filename, "Y_Modifier");
	CB_Width = XML_Manager::Get_Option_Value(Description_Filename, "CB_Width");
	CB_Height = XML_Manager::Get_Option_Value(Description_Filename, "CB_Height");

	Ch_Vel = XML_Manager::Get_Option_Value(Description_Filename, "Velocity"); //in px/s coz its the player
	BASE_LIFE = XML_Manager::Get_Option_Value(Description_Filename, "Life");
	BASE_ARMOR = XML_Manager::Get_Option_Value(Description_Filename, "Armor");
	BASE_INFLICTED_DAMAGE = XML_Manager::Get_Option_Value(Description_Filename, "Damage");
	
	
	string Default_Animations_Center_Filename = Data_Root_Directory + XML_Manager::Get_Option_String(Description_Filename, "Animation_Center_Filename");

	//Default Animations Center
	Default_Animations_Center = new Character_Animations_Center( Data_Root_Directory, Default_Animations_Center_Filename );






	////Characteristics management
	//string Monster_Ini = "Data/Characters/Worms.ini";
	//std::ifstream fi_monster(Monster_Ini.c_str()) ;
	//if (! fi_monster.fail()) //Check file present
	//{
	//	std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Width") ) >> Sprite_Width;
	//	std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Height") ) >> Sprite_Height;
	//	Characters_Current_Tileset = new RGBSurface(Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Filename") , Color(0xFF, 0xFF, 0xFF));
	//	//Sprite_Filename = Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Filename");
	//	std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "CH_VEL") ) >> Ch_Vel;
	//	std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Life") ) >> BASE_LIFE;
	//	Real_Life = BASE_LIFE;
	//	std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Armor") ) >> BASE_ARMOR;
	//	Real_Armor = BASE_ARMOR;		
	//}
	//else { //can't read file
	//	Sprite_Width = 0, Sprite_Height = 0;
	//	Characters_Current_Tileset = NULL;
	//	Ch_Vel = 0;
	//	BASE_LIFE = 0;
	//	BASE_ARMOR = 0;
	//	fi_monster.close();
	//	throw std::logic_error("Can't Read File " + Monster_Ini);
	//}
	//fi_monster.close();

	//Life bar infos
	Life_Bar_Tile = new RGBSurface("Data/Characters/Life Bar Tile.bmp", Color(0xFF, 0xFF, 0xFF));
	
	empty_life_bar_rect.setx(0);
	empty_life_bar_rect.sety(0);
	empty_life_bar_rect.setw(LIFE_BAR_WIDTH);
	empty_life_bar_rect.seth(LIFE_BAR_HEIGHT);

	real_life_bar_rect.setx(0);
	real_life_bar_rect.sety(LIFE_BAR_HEIGHT);
	real_life_bar_rect.setw(LIFE_BAR_WIDTH);
	real_life_bar_rect.seth(LIFE_BAR_HEIGHT);

} catch (std::exception &exc) {
	throw std::logic_error( "Error in Monster_Worm::Initialize(): " + (string)exc.what() );
} catch (...) {
	//unkown error occured
	throw std::logic_error( "Unhandled Error in Monster_Worm::Initialize" );
}
}

//Set ground vs worm rules
int Monster_Worm::Get_BG_vs_CH_Rules(const int& bgType)
{
	if( bgType == EMPTY_GROUND ) //Don't allow move
	{
		return 0;
	}
	else if( bgType == GRASS_GROUND ) //Allow move
	{
		return 1;
	}
	else if( bgType == SAND_GROUND ) //Allow move
	{
		return 1;
	}
	else if( bgType == RIVER_GROUND ) //Don't allow move
	{
		return 0;
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
