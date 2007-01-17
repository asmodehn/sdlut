#include "Monster_Base.hh"

//Default Constructor
Monster_Base::Monster_Base()
{
	//Initial position
	X = 0;
    Y = 0;

	//Monster Tile Surface with white transparent
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
	X = ToCopy.X;
	Y = ToCopy.Y;
	Characters_Tile = ToCopy.Characters_Tile;
	Characters_SpriteRect = ToCopy.Characters_SpriteRect;
	xVel = ToCopy.xVel;
	yVel = ToCopy.yVel;
	collision_box = ToCopy.collision_box;
}
//Destructor
Monster_Base::~Monster_Base()
{
	//Characters_Tile.~RGBSurface();
}
//Move monster randomly
bool Monster_Base::move(Rect CharacterCollisionbox, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector, std::vector< std::vector<Monster_Base*> *> Global_Monster_Vector)
{
try {
	//move only if a random number between 0 and 133 is below 49: 2 chances of 3 (This speed down monster movement)
	if (rand()%200 <= 133) 
	{
		//Random mvt
		//xVel = ((rand()%3-1)*MO_WIDTH);
		//yVel = ((rand()%3-1)*MO_HEIGHT);
		xVel = (rand()%3-1);
		yVel = (rand()%3-1);

		//Move the monster's collision box
		collision_box.setx(X + xVel);
		collision_box.sety(Y + yVel);

		//If the monster went too far to the left or right
		if((collision_box.getx() < 0) || (collision_box.getx() + MO_WIDTH > LEVEL_WIDTH) )
		{
			//move back
			collision_box.setx(X);
			collision_box.sety(Y);
			//we have found a collision no need to work more
			return true;
		}

		//If the monster went too far up or down (minus the status bar)
		if((collision_box.gety() < 0) || (collision_box.gety() + MO_HEIGHT > LEVEL_HEIGHT - STATUS_BAR_H) )
		{
			//move back
			collision_box.setx(X);
			collision_box.sety(Y); 
			return true;   
		}

		//Check if the battlefield allow the move
		if(! check_battlefield_allow_monster(collision_box, Environment_Sprite_Vector, BackGround_Sprite_Vector) )
		{
			//move back
			collision_box.setx(X);
			collision_box.sety(Y);
			return true;
		}
		
		//Check collision with PC
		if ( check_collision(collision_box, CharacterCollisionbox) )
		{
		   	 //move back
			collision_box.setx(X);
			collision_box.sety(Y);
			return true;
	 	}
		
		//Collision with Monsters
		//Loop for all monster's vector
		for (unsigned int j=0; j < Global_Monster_Vector.size(); j++)
		{
			//loop for the current monster's vector
			for(unsigned int i=0; i < Global_Monster_Vector.at(j)->size(); i++)
			{
				//In order to the monster to not check collision's with himself
				if ( ( X != Global_Monster_Vector.at(j)->at(i)->Get_X() ) || Y != Global_Monster_Vector.at(j)->at(i)->Get_Y() )
				{
					if (check_collision( collision_box, Global_Monster_Vector.at(j)->at(i)->Get_Collision_Box() ))
					{
						//we have found a collision inside the vector
						P0_Logger << " Collision with monster " << " @ [ " << X << ", " << Y << "]" << std::endl;
						
						//move back
						collision_box.setx(X);
						collision_box.sety(Y); 

						//no need to work more
						return true;
					}
				}
			}
		}
			
		//Finally move the monster in the same place of his collision box (no collision found)
		X = collision_box.getx();
		Y = collision_box.gety();
	}
	return true; //no error
} catch (...) {
	return false; //error occured
}
}

//Check if the battlefield allow the monster presence
bool Monster_Base::check_battlefield_allow_monster(Rect Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
	bool res = true;

	std::vector<int> env_vs_mo_collisions = check_environment_allow_monster(Collision_Box, Environment_Sprite_Vector);
	std::vector<int> bg_vs_mo_collisions = check_background_allow_monster(Collision_Box, BackGround_Sprite_Vector);

	for (unsigned int i = 0; i < env_vs_mo_collisions.size(); i++)
	{
		if ( env_vs_mo_collisions.at(i) == -1 ) //environment is not present
		{
			if ( bg_vs_mo_collisions.at(i) == 0 )
			{
				res = false; //collision with bg
				return res; //no need to work more
			}

		} else if ( env_vs_mo_collisions.at(i) == 0 ) 
		{
			res = false; //collision with env
			return res; //no need to work more
		} else {
			res = true; //no collision
		}
	}
	if ( res == false )
	{
		P0_Logger << "BLAH BLAH BLAH" << std::endl;
	}
	
	//Never happend (just 4 warning)
	return res;
}
//Check if the ground allow the monster presence
std::vector<int> Monster_Base::check_background_allow_monster(Rect Collision_Box, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
	std::vector<int> res;
	res.push_back(1);
	return res;
}
//Check if the environmemt allow the monster presence
std::vector<int> Monster_Base::check_environment_allow_monster(Rect Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector)
{
	std::vector<int> res; //vector of collision results
    int Env_Type;
	Rect env_rect;

	//loop on all the vector
	for(unsigned int i=0; i < Environment_Sprite_Vector.size(); i++)
	{
		env_rect.setx(Environment_Sprite_Vector[i]->Get_X());
		env_rect.sety(Environment_Sprite_Vector[i]->Get_Y());
		env_rect.setw(BATF_SPRITE_W);
		env_rect.seth(BATF_SPRITE_H);

		if ( check_collision( Collision_Box, env_rect ) )
		{
			//Get the destination environment
			Env_Type = Environment_Sprite_Vector[i]->Get_BattleField_Type();
			//Check if the environment allow the monster's collision box presence
			if( Env_Type == NOTHING_ENV_ITEM )  //indicate no environement is present
			{
				res.push_back(-1);
			}
			else if( Env_Type == TREE_ENV_ITEM ) //Don't allow presence
			{
				res.push_back(0);
			}
			else if( Env_Type == ROCK_ENV_ITEM ) //Don't allow presence
			{
				res.push_back(0);
			}
			else if( Env_Type == WALL_ENV_ITEM ) //Don't allow presence
			{
				res.push_back(0);
			}
			else if( Env_Type == HOUSE_ENV_ITEM ) //Allow presence
			{
				res.push_back(0);
			}
			else if( Env_Type == BRIDGE_ENV_ITEM ) //Allow presence
			{
				res.push_back(1);
			}
			else // not listed type (impossible!!??). Allow presence
			{
				res.push_back(1);
			}
		}
	}

	return res;
}
//Check if the battlefield cutting allow monster presence
bool Monster_Base::check_cutting_allow_monster(int x, int y, std::vector<BattleField_Zone*> BattleField_Cutting_Vector)
{
	Rect Area;
	std::vector<int> Allowed_Monsters_Vector;

	//loop on all areas
	for(unsigned int i=0; i < BattleField_Cutting_Vector.size(); i++)
	{
		//Get the area
		Area = BattleField_Cutting_Vector[i]->Get_Area();
		Allowed_Monsters_Vector = BattleField_Cutting_Vector[i]->Get_Allowed_Monsters();

		//Check if the monster is designed to be present in the Area
		if ( ( x >= Area.getx() ) && ( x < (Area.getx() + Area.getw()) ) && ( y >= Area.gety() ) && ( y < (Area.gety() + Area.geth()) ) )
		{
			//Check if monster ID allow them to born in the area
			for(unsigned int j=0; j < Allowed_Monsters_Vector.size(); j++)
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
bool Monster_Base::move_animation(Rect Camera, VideoSurface& Screen)
{
try {
	//Check if the monster sprite is present on the screen minus the status bar
	//NOTE : CH_WIDTH/CH_HEIGHT are present because the camera is centered on the middle of the character and so we need to draw the screen a little more than the camera dim
	if ( ( (Camera.getx()-CH_WIDTH) <= X) && (X < (Camera.getx() + Camera.getw()) ) && ( (Camera.gety()-CH_HEIGHT) <= Y) && (Y < (Camera.gety() + Camera.geth() - STATUS_BAR_H) ) )
	{
		//It's present than draw it
		Screen.blit(Characters_Tile, Point::Point(X - Camera.getx(), Y - Camera.gety()), Characters_SpriteRect);
	}
	return true; //no error
} catch (...) {
  		return false; //error occured
}
}
