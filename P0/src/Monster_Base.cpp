#include "Monster_Base.hh"

//Default Constructor
Monster_Base::Monster_Base()
{
	//Initial position
	X = 0;
    Y = 0;

	//Monster Tile Surface with white transparent
	Characters_Tile = RGBSurface(Color(0xFF, 0xFF, 0xFF), 0, 0, 32);

	 //Monster Clip definition range for the top left (Random monster from the 7th line)
    _monster[0].setx( MO_WIDTH * (rand()%8) );
	_monster[0].sety( MO_HEIGHT*6 );
    _monster[0].setw( MO_WIDTH );
    _monster[0].seth( MO_HEIGHT );

	//Assign sprite
	Characters_SpriteRect = _monster[0];

	//Initial velocity
    xVel = 0;
    yVel = 0;

	//Collision Box Definition : The collision box has the size of the monster
	Collision_Box.setx(0);
    Collision_Box.sety(0);
    Collision_Box.setw(MO_WIDTH);
    Collision_Box.seth(MO_HEIGHT);

	//Monster type
	Monster_ID = Humanoid;

	//Bool that indicate if the monster is alive or dead: by default the monster is created alive
	Alive_Status = true;
}

//Full Construtor
Monster_Base::Monster_Base(int x, int y)
{
    //Initial position
	X = x;
    Y = y;

	//Monster Tile Surface
	Characters_Tile = RGBSurface("Datas/Characters/Monsters5.bmp", Color(0xFF, 0xFF, 0xFF));
	
	 //Monster Clip definition range for the top left (Random monster from the 7th line)
    _monster[0].setx( MO_WIDTH * (rand()%8) );
	_monster[0].sety( MO_HEIGHT*6 );
    _monster[0].setw( MO_WIDTH );
    _monster[0].seth( MO_HEIGHT );

	//Assign sprite
	Characters_SpriteRect = _monster[0];

	//Initial velocity
    xVel = 0;
    yVel = 0;

	//Monster type
	Monster_ID = Humanoid;

	//Collision Box Definition : The collision box has the size of the monster
	Collision_Box.setx(X);
    Collision_Box.sety(Y);
    Collision_Box.setw(MO_WIDTH);
    Collision_Box.seth(MO_HEIGHT);

	//Bool that indicate if the monster is alive or dead: by default the monster is created alive
	Alive_Status = true;
}

//Copy construtor
Monster_Base::Monster_Base(const Monster_Base& ToCopy)
{
	X = ToCopy.X;
	Y = ToCopy.Y;
	Characters_Tile = ToCopy.Characters_Tile;
	Characters_SpriteRect = ToCopy.Characters_SpriteRect;
	xVel = ToCopy.xVel;
	yVel = ToCopy.yVel;
	Collision_Box = ToCopy.Collision_Box;
}


//Move monster randomly
bool Monster_Base::move(std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector)
{
try {
	//move only if a random number between 0 and 133 is below 49: 2 chances of 3 (This speed down monster movement)
	if (rand()%200 <= 133) 
	{
		//Random mvt
#ifdef _DEBUG //debug mode
		xVel = ((rand()%3-1)*MO_WIDTH);
		yVel = ((rand()%3-1)*MO_HEIGHT);
#else //rlz mode
		xVel = (rand()%3-1);
		yVel = (rand()%3-1);
#endif
		if (! Check_Collisions(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector) )
		{ //No collisions found
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
int Monster_Base::Get_BG_vs_CH_Rules(int bgType)
{
	return 1;
}

//Check if the environmemt allow the monster presence
int Monster_Base::Get_Env_vs_CH_Rules(int envType)
{
	if( envType == NOTHING_ENV_ITEM )  //indicate no environement is present
	{
		return -1;
	}
	else if( envType == TREE_ENV_ITEM ) //Don't allow presence
	{
		return 0;
	}
	else if( envType == ROCK_ENV_ITEM ) //Don't allow presence
	{
		return 0;
	}
	else if( envType == WALL_ENV_ITEM ) //Don't allow presence
	{
		return 0;
	}
	else if( envType == HOUSE_ENV_ITEM ) //Allow presence
	{
		return 0;
	}
	else if( envType == BRIDGE_ENV_ITEM ) //Allow presence
	{
		return 1;
	}
	else // not listed type (impossible!!??). Allow presence
	{
		return 1;
	}
}

//Check if the battlefield cutting allow monster presence
bool Monster_Base::check_cutting_allow_monster(int x, int y, std::vector<BattleField_Zone*>* BattleField_Cutting_Vector)
{
	Rect Area;
	std::vector<int>* Allowed_Monsters_Vector = new std::vector<int>;

	//loop on all areas
	for(unsigned int i=0; i < BattleField_Cutting_Vector->size(); i++)
	{
		//Get the area
		Area = BattleField_Cutting_Vector->at(i)->Get_Area();
		Allowed_Monsters_Vector = BattleField_Cutting_Vector->at(i)->Get_Allowed_Monsters();

		//Check if the monster is designed to be present in the Area
		if ( ( x >= Area.getx() ) && ( x < (Area.getx() + Area.getw()) ) && ( y >= Area.gety() ) && ( y < (Area.gety() + Area.geth()) ) )
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
