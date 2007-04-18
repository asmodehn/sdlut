#include "Monster_Base.hh"

//Default Constructor
Monster_Base::Monster_Base()
{
}

//Full Construtor
Monster_Base::Monster_Base(int& x, int& y)
{
	//Initial position
	X = x;
    Y = y;

	Sprite_Width = MO_WIDTH, Sprite_Height = MO_HEIGHT;
	Sprite_Filename = ""; //Empty sprite for now

	//Monster Tile Surface
	Characters_Tile = new RGBSurface(Sprite_Filename, Color(0xFF, 0xFF, 0xFF));

	 //Monster Clip definition range for the top left (Random monster from the 7th line)
    _monster_clip.setx( Sprite_Width * (rand()%8) );
	_monster_clip.sety( Sprite_Height*6 );
    _monster_clip.setw( Sprite_Width );
    _monster_clip.seth( Sprite_Height );

	//Assign sprite
	Characters_SpriteRect = _monster_clip;

	//Monster type
	Monster_ID = Humanoid;

	//Collision Box Definition : The collision box has the size of the monster
	Collision_Box.setx(X);
    Collision_Box.sety(Y);
    Collision_Box.setw(Sprite_Width);
    Collision_Box.seth(Sprite_Height);

	//Bool that indicate if the monster is alive or dead: by default the monster is created alive
	Alive_Status = true;
		
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
}

//Copy construtor
Monster_Base::Monster_Base(const Monster_Base& ToCopy)
{
	X = ToCopy.X;
	Y = ToCopy.Y;
	Sprite_Width = ToCopy.Sprite_Width;
	Sprite_Height = ToCopy.Sprite_Height;
	Characters_Tile = ToCopy.Characters_Tile;
	_monster_clip = ToCopy._monster_clip;
	Characters_SpriteRect = ToCopy.Characters_SpriteRect;
	Monster_ID = ToCopy.Monster_ID;
	xVel = ToCopy.xVel;
	yVel = ToCopy.yVel;
	Collision_Box = ToCopy.Collision_Box;
	Alive_Status = ToCopy.Alive_Status;
	Life_Bar_Tile = ToCopy.Life_Bar_Tile;
	empty_life_bar_rect = ToCopy.empty_life_bar_rect;
	real_life_bar_rect = ToCopy.real_life_bar_rect;
}

//Destructor
Monster_Base::~Monster_Base()
{
}

//Move monster randomly
bool Monster_Base::Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
try {
	//move only if a random number between 0 and 133 is below 49: 2 chances of 3 (This speed down monster movement)
	if (rand()%200 <= 133) 
	{
		//Random mvt
		xVel = (rand()%3-1)*Ch_Vel;
		yVel = (rand()%3-1)*Ch_Vel;

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
} catch (...) {
	return false; //error occured
}
}

//By default the ground allow the undefined monster presence
int Monster_Base::Get_BG_vs_CH_Rules(const int& bgType)
{
	return 1;
}

//Check if the environmemt allow the monster presence
int Monster_Base::Get_Env_vs_CH_Rules(const int& envType)
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
		return 0;
	}
	else // not listed type (impossible!!??). Allow presence
	{
		return 1;
	}
}

//Check if the battlefield cutting allow monster presence
bool Monster_Base::Check_Cutting_Allow_Monster(std::vector<BattleField_Zone*>* &BattleField_Cutting_Vector)
{
	Rect Area;
	std::vector<int>* Allowed_Monsters_Vector;

	//loop on all areas
	for(unsigned int i=0; i < BattleField_Cutting_Vector->size(); i++)
	{
		//Get the area
		Area = BattleField_Cutting_Vector->at(i)->Get_Area();
		Allowed_Monsters_Vector = BattleField_Cutting_Vector->at(i)->Get_Allowed_Monsters();

		//Check if the monster is designed to be present in the Area
		if ( ( X >= Area.getx() ) && ( (signed)X < (signed)(Area.getx() + Area.getw()) ) && ( Y >= Area.gety() ) && ( (signed)Y < (signed)(Area.gety() + Area.geth()) ) )
		{
			//Check if monster ID allow them to born in the area
			for(unsigned int j=0; j < Allowed_Monsters_Vector->size(); j++)
			{
				//the monster id must be listed inside the Allowed_Monsters_Vector in order to allow monster generation on the area
				if ( Monster_ID == Allowed_Monsters_Vector->at(j))
				{
					return true; //good area, monster id present => the cutting allow monster presence
				}
			}
			return false; //the monster id in not present inside the allowed id in this area => the cutting dont allow monster presence
		}
	}

	//not design to happen: obviously the monster must be inside one of the area
	return false;
}

//Calculate the current life of the monster depending on damage, malus, etc
bool Monster_Base::Calculate_Real_Life(int received_damage)
{
	int real_received_damage = (received_damage - Get_Real_Armor()); //TODO(future): Set the real damage formula base on mo's condition

	if ( (real_received_damage) < 0) //in case damage dont exceed armor value then set it to 0: no damage
		real_received_damage = 0;

	Set_Real_Life( Get_Real_Life() - real_received_damage) ;
	
	//Monster as no life => dead
	if ( Get_Real_Life() <= 0 )
		Set_Alive_Status(false);

	return true; //everything went fine
}

//Shows the life bar of the monster depending of it's current life
bool Monster_Base::Show_Life_Bar(const Rect& Camera, VideoSurface& Screen)
{
	int _Real_Life = Get_Real_Life();
	//to avoid draw pb when life is < 0
	if (_Real_Life < 0)
		_Real_Life = 0;

	real_life_bar_rect.setw( (LIFE_BAR_WIDTH * _Real_Life / BASE_LIFE) );

	//we blit the empty rect than the current life rect 8px on top of the monster
	//positions are def by monster pos
	Screen.blit(*Life_Bar_Tile, Point::Point(X - Camera.getx(), Y-8 - Camera.gety()), empty_life_bar_rect);
	Screen.blit(*Life_Bar_Tile, Point::Point(X - Camera.getx(), Y-8 - Camera.gety()), real_life_bar_rect);

	return true;  //everything went fine
}
