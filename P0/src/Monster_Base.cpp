#include "Monster_Base.hh"

//Default Constructor
Monster_Base::Monster_Base()
{
}

//Full Construtor
//Monster_Base::Monster_Base(int& x, int& y)
//{
//	//Initial position
//	X = x;
//    Y = y;
//
//	Sprite_Width = MO_WIDTH, Sprite_Height = MO_HEIGHT;
//	Sprite_Filename = ""; //Empty sprite for now
//
//	//Monster Tile Surface
//	Characters_Tile = new RGBSurface(Sprite_Filename, Color(0xFF, 0xFF, 0xFF));
//
//	 //Monster Clip definition range for the top left (Random monster from the 7th line)
//    _monster_clip.setx( Sprite_Width * (rand()%8) );
//	_monster_clip.sety( Sprite_Height*6 );
//    _monster_clip.setw( Sprite_Width );
//    _monster_clip.seth( Sprite_Height );
//
//	//Assign sprite
//	Current_Tile_Rect = _monster_clip;
//
//	//Monster type
//	Monster_ID = Humanoid;
//
//	//Collision Box Definition : The collision box has the size of the monster
//	Collision_Box.setx(X);
//    Collision_Box.sety(Y);
//    Collision_Box.setw(Sprite_Width);
//    Collision_Box.seth(Sprite_Height);
//
//	//Bool that indicate if the monster is alive or dead: by default the monster is created alive
//	Alive_Status = true;
//		
//	//Life bar infos
//	Life_Bar_Tile = new RGBSurface("Data/Characters/Life Bar Tile.bmp", Color(0xFF, 0xFF, 0xFF));
//	
//	empty_life_bar_rect.setx(0);
//	empty_life_bar_rect.sety(0);
//	empty_life_bar_rect.setw(LIFE_BAR_WIDTH);
//	empty_life_bar_rect.seth(LIFE_BAR_HEIGHT);
//
//	real_life_bar_rect.setx(0);
//	real_life_bar_rect.sety(LIFE_BAR_HEIGHT);
//	real_life_bar_rect.setw(LIFE_BAR_WIDTH);
//	real_life_bar_rect.seth(LIFE_BAR_HEIGHT);
//}

//Copy construtor
Monster_Base::Monster_Base(const Monster_Base& ToCopy)
{
	//
	//TODO: complete list !!
	//
	X = ToCopy.X;
	Y = ToCopy.Y;
	xVel = ToCopy.xVel;
	yVel = ToCopy.yVel;
	Ch_Vel = ToCopy.Ch_Vel;
	BASE_LIFE = ToCopy.BASE_LIFE;
	Real_Life = ToCopy.Real_Life;
	BASE_ARMOR = ToCopy.BASE_ARMOR;
	Real_Armor = ToCopy.Real_Armor;
	BASE_INFLICTED_DAMAGE = ToCopy.BASE_INFLICTED_DAMAGE;
	Real_Inflicted_Damage = ToCopy.Real_Inflicted_Damage;
	Sprite_Width = ToCopy.Sprite_Width;
	Sprite_Height = ToCopy.Sprite_Height;
	Characters_ID = ToCopy.Characters_ID;

	Alive_Status = ToCopy.Alive_Status;
	attack_status = ToCopy.attack_status;
	attack_style = ToCopy.attack_style;
	attack_successfull = ToCopy.attack_successfull;
	attack_direction = ToCopy.attack_direction;
	attack_initial_x = ToCopy.attack_initial_x;
	attack_initial_y = ToCopy.attack_initial_y;

	Allowed_Area = ToCopy.Allowed_Area;

	CB_X_Modifier = ToCopy.CB_X_Modifier;
	CB_Y_Modifier = ToCopy.CB_Y_Modifier;
	CB_Width = ToCopy.CB_Width;
	CB_Height = ToCopy.CB_Height;
	Collision_Box = ToCopy.Collision_Box;

	Current_Animations_Center = ToCopy.Current_Animations_Center;

	Life_Bar_Tile = ToCopy.Life_Bar_Tile;
	empty_life_bar_rect = ToCopy.empty_life_bar_rect;
	real_life_bar_rect = ToCopy.real_life_bar_rect;
}

//Destructor
Monster_Base::~Monster_Base()
{
}

//Intialize Monster: get all data from external files, assign surface, boxs, ...
void Monster_Base::Initialize( const string &Description_Filename,
		int &Ch_Vel, int &BASE_LIFE, int &BASE_ARMOR, int &BASE_INFLICTED_DAMAGE, int &Sprite_Width, int &Sprite_Height, Character_Types &Characters_ID,
		Rect &Allowed_Area,
		int &CB_X_Modifier, int &CB_Y_Modifier, int &CB_Width, int &CB_Height,
		Character_Animations_Center* &Current_Animations_Center,
		RGBSurface* &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect
		)
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
	//
	//todo: below define the 3 Animations centers
	//
	Character_Animations_Center* Unarmed_Animations_Center = new Character_Animations_Center( Data_Root_Directory, Default_Animations_Center_Filename );
	Current_Animations_Center = Unarmed_Animations_Center;


	//Life bar infos
	Life_Bar_Tile = new RGBSurface("Data/Characters/Life Bar Tile.png", Color(0xFF, 0xFF, 0xFF));
	
	empty_life_bar_rect.setx(0);
	empty_life_bar_rect.sety(0);
	empty_life_bar_rect.setw(LIFE_BAR_WIDTH);
	empty_life_bar_rect.seth(LIFE_BAR_HEIGHT);

	real_life_bar_rect.setx(0);
	real_life_bar_rect.sety(LIFE_BAR_HEIGHT);
	real_life_bar_rect.setw(LIFE_BAR_WIDTH);
	real_life_bar_rect.seth(LIFE_BAR_HEIGHT);

} catch (std::exception &exc) {
	throw std::logic_error( "From Monster_Base::Initialize(), " + (string)exc.what() );
} catch (...) {
	//unkown error occured
	throw std::logic_error( "Unhandled Error in Monster_Base::Initialize" );
}
}

//Move monster randomly
bool Monster_Base::Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
try {
	//character can move if: he is alived && he has not been hitted
	if ( (Get_Alive_Status() == 1) && (Get_Hitted_Status() == 0) )
	{
		//move only if a random number between 0 and 133 is below 49: 2 chances of 3 (This speed down monster movement)
		if (rand()%200 <= 133) 
		{
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
				Collision_Box.setx(X + CB_X_Modifier + xVel);
				Collision_Box.sety(Y + CB_Y_Modifier + yVel);

				//handle collisions
				if ( Manage_Collisions(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector, true) )
				{
					//No Error => Update position 
					X = Collision_Box.getx() - CB_X_Modifier;
					Y = Collision_Box.gety() - CB_Y_Modifier;
				}
			}
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
				if ( Characters_ID == Allowed_Monsters_Vector->at(j))
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

//Shows the life bar of the monster depending of it's current life
bool Monster_Base::Show_Life_Bar(const Rect& Camera, VideoSurface& Screen)
{
	int _Real_Life = Get_Real_Life();
	//only draw the life bar when monster alive
	if (_Real_Life > 0)
	{
		assert(BASE_LIFE>0 && "BASE_LIFE MUST BE SUPERIOR TO 0 TO DRAW The real_life_bar_rect !");
		real_life_bar_rect.setw( LIFE_BAR_WIDTH * _Real_Life / BASE_LIFE );

		//we blit the empty rect than the current life rect 8px on top of the monster
		//positions are def by monster pos
		Screen.blit(*Life_Bar_Tile, Point::Point(X + (Sprite_Width-LIFE_BAR_WIDTH)/2 - Camera.getx(), Collision_Box.gety() - 10 - Camera.gety()), empty_life_bar_rect);
		Screen.blit(*Life_Bar_Tile, Point::Point(X + (Sprite_Width-LIFE_BAR_WIDTH)/2 - Camera.getx(), Collision_Box.gety() - 10 - Camera.gety()), real_life_bar_rect);
	}

	return true;  //everything went fine
}
