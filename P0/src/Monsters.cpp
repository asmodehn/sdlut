#include "Monsters.hh"

string Monster_Skeleton::Description_Filename = "Data/Characters/Monster_Skeleton.xml";

//Skeleton Full constructor
Monster_Skeleton::Monster_Skeleton(int x, int y,
		int &Ch_Vel, int &BASE_LIFE, int &BASE_ARMOR, int &BASE_INFLICTED_DAMAGE, int &Sprite_Width, int &Sprite_Height, Character_Types &Characters_ID,
		Rect &Allowed_Area,
		int &CB_X_Modifier, int &CB_Y_Modifier, int &CB_Width, int &CB_Height,
		Character_Animations_Center* &Current_Animations_Center,
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

	this->Current_Animations_Center = Current_Animations_Center;

	this->Life_Bar_Tile = Life_Bar_Tile;
	this->empty_life_bar_rect = empty_life_bar_rect;
	this->real_life_bar_rect = real_life_bar_rect;
								   
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


string Monster_Worm::Description_Filename = "Data/Characters/Monster_Worm.xml";

//Worm Full constructor
Monster_Worm::Monster_Worm(int x, int y,
		int &Ch_Vel, int &BASE_LIFE, int &BASE_ARMOR, int &BASE_INFLICTED_DAMAGE, int &Sprite_Width, int &Sprite_Height, Character_Types &Characters_ID,
		Rect &Allowed_Area,
		int &CB_X_Modifier, int &CB_Y_Modifier, int &CB_Width, int &CB_Height,
		Character_Animations_Center* &Current_Animations_Center,
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

	this->Current_Animations_Center = Current_Animations_Center;

	this->Life_Bar_Tile = Life_Bar_Tile;
	this->empty_life_bar_rect = empty_life_bar_rect;
	this->real_life_bar_rect = real_life_bar_rect;

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
