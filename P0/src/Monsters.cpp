#include "Monsters.hh"

//Skeleton Full constructor
Monster_Skeleton::Monster_Skeleton(int x, int y, 
								   int &Ch_Vel, int &BASE_LIFE, int &Real_Life, int &BASE_ARMOR, int &Real_Armor, int &Sprite_Width, int &Sprite_Height,
								   RGBSurface &Characters_Tile, RGBSurface &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect
								   )
{
    //Initial position
	X = x;
    Y = y;

	this->Ch_Vel = Ch_Vel;
	this->BASE_LIFE = BASE_LIFE;
	this->Real_Life = Real_Life;
	this->BASE_ARMOR = BASE_ARMOR;
	this->Real_Armor = Real_Armor;
	this->Sprite_Width = Sprite_Width;
	this->Sprite_Height = Sprite_Height;
	this->Characters_Tile = Characters_Tile;
	this->Life_Bar_Tile = Life_Bar_Tile;
	this->empty_life_bar_rect = empty_life_bar_rect;
	this->real_life_bar_rect = real_life_bar_rect;
								   
	 //Monster Clip definition range for the top left (Random monster from the 1th line)
    _monster_clip.setx( Sprite_Width * (rand()%7) );
	_monster_clip.sety( 0 );
    _monster_clip.setw( Sprite_Width );
    _monster_clip.seth( Sprite_Height );

	//Assign the sprite
	Characters_SpriteRect = _monster_clip;

	//Monster type
	Monster_ID = Humanoid;

	//Collision Box Definition : The collision box has the size of the monster
	Collision_Box.setx(X);
    Collision_Box.sety(Y);
    Collision_Box.setw(Sprite_Width);
    Collision_Box.seth(Sprite_Height);
}

//Destructor
Monster_Skeleton::~Monster_Skeleton()
{
}

//Intialize Monster: get all data from external files, assign surface, boxs, ...
void Monster_Skeleton::Initialize(int &Ch_Vel, int &BASE_LIFE, int &Real_Life, int &BASE_ARMOR, int &Real_Armor, int &Sprite_Width, int &Sprite_Height, RGBSurface &Characters_Tile, 
								  RGBSurface &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect)
{
try {
	//Characteristics management
	string Monster_Ini = "Datas/Characters/Skeletons.ini";
	std::ifstream fi_monster(Monster_Ini.c_str()) ;
	if (! fi_monster.fail()) //Check file present
	{
		std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Width") ) >> Sprite_Width;
		std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Height") ) >> Sprite_Height;
		Characters_Tile = RGBSurface(Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Filename") , Color(0xFF, 0xFF, 0xFF));
		//Sprite_Filename = Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Filename");
		std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "CH_VEL") ) >> Ch_Vel;
		std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Life") ) >> BASE_LIFE;
		Real_Life = BASE_LIFE;
		std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Armor") ) >> BASE_ARMOR;
		Real_Armor = BASE_ARMOR;		
	}
	fi_monster.close();

	//Monster Tile Surface
	//Characters_Tile = RGBSurface(Sprite_Filename, Color(0xFF, 0xFF, 0xFF));

	//Life bar infos
	Life_Bar_Tile = RGBSurface("Datas/Characters/Life Bar Tile.bmp", Color(0xFF, 0xFF, 0xFF));
	
	empty_life_bar_rect.setx(0);
	empty_life_bar_rect.sety(0);
	empty_life_bar_rect.setw(LIFE_BAR_WIDTH);
	empty_life_bar_rect.seth(LIFE_BAR_HEIGHT);

	real_life_bar_rect.setx(0);
	real_life_bar_rect.sety(LIFE_BAR_HEIGHT);
	real_life_bar_rect.setw(LIFE_BAR_WIDTH);
	real_life_bar_rect.seth(LIFE_BAR_HEIGHT);

} catch (...) {
	//error occured
	P0_Logger << nl << "Monster_Skeleton::Initialize ErrOr " << std::endl;
}
}

//Set ground vs skeleton rules
int Monster_Skeleton::Get_BG_vs_CH_Rules(int bgType)
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
						   int &Ch_Vel, int &BASE_LIFE, int &Real_Life, int &BASE_ARMOR, int &Real_Armor, int &Sprite_Width, int &Sprite_Height,
						   RGBSurface &Characters_Tile, RGBSurface &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect
						   )
{
    //Initial position
	X = x;
    Y = y;

	this->Ch_Vel = Ch_Vel;
	this->BASE_LIFE = BASE_LIFE;
	this->Real_Life = Real_Life;
	this->BASE_ARMOR = BASE_ARMOR;
	this->Real_Armor = Real_Armor;
	this->Sprite_Width = Sprite_Width;
	this->Sprite_Height = Sprite_Height;
	this->Characters_Tile = Characters_Tile;
	this->Life_Bar_Tile = Life_Bar_Tile;
	this->empty_life_bar_rect = empty_life_bar_rect;
	this->real_life_bar_rect = real_life_bar_rect;

	//Monster Clip definition range for the top left (Random monster from the 7th line)
    _monster_clip.setx( Sprite_Width * (rand()%7) );
	_monster_clip.sety( Sprite_Height*6 );
    _monster_clip.setw( Sprite_Width );
    _monster_clip.seth( Sprite_Height );

	//Assign the sprite
	Characters_SpriteRect = _monster_clip;

	//Monster type
	Monster_ID = Worm;

	//Collision Box Definition : The collision box has the size of the monster
	Collision_Box.setx(X);
    Collision_Box.sety(Y);
    Collision_Box.setw(Sprite_Width);
    Collision_Box.seth(Sprite_Height);
}

//Destructor
Monster_Worm::~Monster_Worm()
{
}

//Intialize Monster: get all data from external files, assign surface, boxs, ...
void Monster_Worm::Initialize(int &Ch_Vel, int &BASE_LIFE, int &Real_Life, int &BASE_ARMOR, int &Real_Armor, int &Sprite_Width, int &Sprite_Height, RGBSurface &Characters_Tile,  
								  RGBSurface &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect)
{
try {
	//Characteristics management
	string Monster_Ini = "Datas/Characters/Worms.ini";
	std::ifstream fi_monster(Monster_Ini.c_str()) ;
	if (! fi_monster.fail()) //Check file present
	{
		std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Width") ) >> Sprite_Width;
		std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Height") ) >> Sprite_Height;
		Characters_Tile = RGBSurface(Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Filename") , Color(0xFF, 0xFF, 0xFF));
		//Sprite_Filename = Ini_Manager::Get_Option_String(Monster_Ini, "Sprite_Filename");
		std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "CH_VEL") ) >> Ch_Vel;
		std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Life") ) >> BASE_LIFE;
		Real_Life = BASE_LIFE;
		std::stringstream( Ini_Manager::Get_Option_String(Monster_Ini, "Armor") ) >> BASE_ARMOR;
		Real_Armor = BASE_ARMOR;
	}
	fi_monster.close();

	//Monster Tile Surface
	//Characters_Tile = RGBSurface(Sprite_Filename, Color(0xFF, 0xFF, 0xFF));

	//Life bar infos
	Life_Bar_Tile = RGBSurface("Datas/Characters/Life Bar Tile.bmp", Color(0xFF, 0xFF, 0xFF));
	
	empty_life_bar_rect.setx(0);
	empty_life_bar_rect.sety(0);
	empty_life_bar_rect.setw(LIFE_BAR_WIDTH);
	empty_life_bar_rect.seth(LIFE_BAR_HEIGHT);

	real_life_bar_rect.setx(0);
	real_life_bar_rect.sety(LIFE_BAR_HEIGHT);
	real_life_bar_rect.setw(LIFE_BAR_WIDTH);
	real_life_bar_rect.seth(LIFE_BAR_HEIGHT);

} catch (...) {
	//error occured
	P0_Logger << nl << "Monster_Worm::Initialize ErrOr " << std::endl;
}
}

//Set ground vs worm rules
int Monster_Worm::Get_BG_vs_CH_Rules(int bgType)
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
