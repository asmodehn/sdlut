#include "Monster_Base.hh"

//Default Constructor
Monster_Base::Monster_Base()
{
	//Initial position
	x = 0;
    y = 0;

	//Monster Tile Surface with white transparent
	_monsters_list = RGBSurface("data/Monsters5.bmp", Color(0xFF, 0xFF, 0xFF));

	 //Monster Clip definition range for the top left (Random monster from the 7th line)
    _monster[0].setx( MO_WIDTH * (rand()%8) );
	_monster[0].sety( MO_HEIGHT*6 );
    _monster[0].setw( MO_WIDTH );
    _monster[0].seth( MO_HEIGHT );

	//Initial velocity
    xVel = 0;
    yVel = 0;

	//Collision Box Definition : The collision box has the size of the monster
	collision_box.setx(0);
    collision_box.sety(0);
    collision_box.setw(MO_WIDTH);
    collision_box.seth(MO_HEIGHT);

	//Monster type
	Monster_ID = Humanoid;

	//Bool that indicate if the monster is alive or dead: by default the monster is created alive
	Alive_Status = true;
}
//Full Construtor
Monster_Base::Monster_Base(int X, int Y)
{
    //Initial position
	x = X;
    y = Y;

	//Monster Tile Surface
	_monsters_list = RGBSurface("data/Monsters5.bmp", Color(0xFF, 0xFF, 0xFF));
	
	 //Monster Clip definition range for the top left (Random monster from the 7th line)
    _monster[0].setx( MO_WIDTH * (rand()%8) );
	_monster[0].sety( MO_HEIGHT*6 );
    _monster[0].setw( MO_WIDTH );
    _monster[0].seth( MO_HEIGHT );

	//Initial velocity
    xVel = 0;
    yVel = 0;

	//Monster type
	Monster_ID = Humanoid;

	//Collision Box Definition : The collision box has the size of the monster
	collision_box.setx(X);
    collision_box.sety(Y);
    collision_box.setw(MO_WIDTH);
    collision_box.seth(MO_HEIGHT);

	//Bool that indicate if the monster is alive or dead: by default the monster is created alive
	Alive_Status = true;
}
//Copy construtor
Monster_Base::Monster_Base(const Monster_Base& ToCopy)
{
	x = ToCopy.x;
	y = ToCopy.y;
	_monsters_list = ToCopy._monsters_list;
	_monster[0] = ToCopy._monster[0];
	xVel = ToCopy.xVel;
	yVel = ToCopy.yVel;
	collision_box = ToCopy.collision_box;
}
//Destructor
Monster_Base::~Monster_Base()
{
	//_monsters_list.~RGBSurface();
}
//Move monster randomly
void Monster_Base::move(Rect CharacterCollisionbox, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
	//move only if a random number is below 10 (This speed down monster movement)
	if (rand()%200 <= 13) 
	{
		//Random mvt
		xVel = ((rand()%3-1)*MO_WIDTH);
		yVel = ((rand()%3-1)*MO_HEIGHT);

		//Move the monster left or right and his collision box
		collision_box.setx(x + xVel);
		collision_box.sety(y + yVel);

		//If the Character went too far to the left or right or in case of collision with the npc
		if((collision_box.getx() < 0) || (collision_box.getx() + MO_WIDTH > LEVEL_WIDTH) || (check_collision(collision_box, CharacterCollisionbox)))
		{
			//move back
			collision_box.setx(x);
		}

		//If the Character went too far up or down (the -32 is here for the status bar) or in case of collision with the npc
		if((collision_box.gety() < 0) || (collision_box.gety() + MO_HEIGHT > LEVEL_HEIGHT-32) || (check_collision(collision_box, CharacterCollisionbox)))
		{
			//move back
			collision_box.sety(y);     
		}

		//Now that all collision has been checked, we must check if the battlefield allow the move
		if(! check_battlefield_allow_monster(collision_box.getx(), collision_box.gety(), Environment_Sprite_Vector, BackGround_Sprite_Vector) )
		{
			//move back
			collision_box.setx(x);
			collision_box.sety(y); 
		}
		
		//Finally move the monster in the same place of his collision box
		x = collision_box.getx();
		y = collision_box.gety();
	}
}
//Check if the battlefield allow the monster presence
bool Monster_Base::check_battlefield_allow_monster(int x, int y, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
	//1st, we must check if the environment allow the move
	if( check_environment_allow_monster(x, y, Environment_Sprite_Vector) == -1)
	{
		//No environement item present, the ground have priority
		if(! check_background_allow_monster(x, y, BackGround_Sprite_Vector) )
		{
			return false;
		}
	}
	 //environment item present and dont allow presence
	else if( check_environment_allow_monster(x, y, Environment_Sprite_Vector) == 0)
	{
		return false; //we can't move => no need to test more
	}
	else //environment item present and allow presence
	{
		return true;
	}

	return true;
}
//Check if the ground allow the monster presence
bool Monster_Base::check_background_allow_monster(int x, int y, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
	return true;
}
//Check if the environmemt allow the monster presence
int Monster_Base::check_environment_allow_monster(int x, int y, std::vector<BattleField_Sprite*> Environment_Sprite_Vector)
{
	//loop on all the vector
	for(int i=0; i < Environment_Sprite_Vector.size(); i++)
	{
		//when we have located the good destination inside the vector,...
		if (( x == Environment_Sprite_Vector[i]->Get_X() ) && ( y == Environment_Sprite_Vector[i]->Get_Y() ))
		{
			//...get the environment ground...
			int newEnv_Type = Environment_Sprite_Vector[i]->Get_BattleField_Type();
			
			//...then check if the environment allow the monster presence
			if( newEnv_Type == NOTHING_ENV_ITEM ) //indicate no environement is present
			{
				return -1; 
			}
			else if( newEnv_Type == TREE_ENV_ITEM ) //Don't allow presence
			{
				return 0;
			}
			else if( newEnv_Type == ROCK_ENV_ITEM ) //Don't allow presence
			{
				return 0;
			}
			else if( newEnv_Type == WALL_ENV_ITEM ) //Don't allow presence
			{
				return 0;
			}
			else if( newEnv_Type == HOUSE_ENV_ITEM ) //Don't allow presence
			{
				return 0;
			}
			else // not listed type (impossible!!??). Allow presence
			{
				return 1;  
			}
		}
	}
	//we can't locate the position inside the vector (impossible!!??)
	return -1;
}
//Check if the battlefield cutting allow monster presence
bool Monster_Base::check_cutting_allow_monster(int x, int y, std::vector<BattleField_Zone*> BattleField_Cutting_Vector)
{
	Rect Area;
	std::vector<int> Allowed_Monsters_Vector;

	//loop on all areas
	for(int i=0; i < BattleField_Cutting_Vector.size(); i++)
	{
		//Get the area
		Area = BattleField_Cutting_Vector[i]->Get_Area();
		Allowed_Monsters_Vector = BattleField_Cutting_Vector[i]->Get_Allowed_Monsters();

		//Check if the monster is designed to be present in the Area
		if ( ( x >= Area.getx() ) && ( x < (Area.getx() + Area.getw()) ) && ( y >= Area.gety() ) && ( y < (Area.gety() + Area.geth()) ) )
		{
			//Check if monster ID allow them to born in the area
			for(int j=0; j < Allowed_Monsters_Vector.size(); j++)
			{
				//the monster id must be listed inside the Allowed_Monsters_Vector in order to allow monster generation on the area
				if ( Monster_ID == Allowed_Monsters_Vector[j])
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
//Show monster on the screen
void Monster_Base::move_animation(Rect Camera, VideoSurface& Screen)
{
	//Check if the monster sprite is present on the screen minus the status bar
	//NOTE : CH_WIDTH/CH_HEIGHT are present because the camera is centered on the middle of the character and so we need to draw the screen a chracter 
	if ( ( (Camera.getx()-CH_WIDTH) <= x) && (x < (Camera.getx() + Camera.getw()) ) && ( (Camera.gety()-CH_HEIGHT) <= y) && (y < (Camera.gety() + Camera.geth() - 32) ) )
	{
		//It's present than draw it
		Screen.blit(_monsters_list, Point::Point(x - Camera.getx(), y - Camera.gety()), _monster[0]);
	}
}
