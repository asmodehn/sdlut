#include "Monsters.hh"

//Skeleton Full constructor
Monster_Skeleton::Monster_Skeleton(int X, int Y)
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

	//Collision Box Definition : The collision box has the size of the monster
	collision_box.setx(X);
    collision_box.sety(Y);
    collision_box.setw(MO_WIDTH);
    collision_box.seth(MO_HEIGHT);

	//Bool that indicate if the monster is alive or dead: by default the monster is created alive
	Alive_Status = true;
}
//Check if the ground allow the Skeleton to move
bool Monster_Skeleton::check_background_allow_monster(int x, int y, std::vector<BattleField_Sprite*> BattleField_Sprite_Vector)
{
	//loop on all the vector
	for(int i=0; i < BattleField_Sprite_Vector.size(); i++)
	{
		//when we have located the good destination inside the vector,...
		if (( x == BattleField_Sprite_Vector[i]->Get_X() ) && ( y == BattleField_Sprite_Vector[i]->Get_Y() ))
		{
			//...get the destination ground...
			int newGround_Type = BattleField_Sprite_Vector[i]->Get_BattleField_Type();
			
			//...then check if the ground allow the character move
			if( newGround_Type == EMPTY_GROUND ) //Don't allow presence
			{
				return false; 
			}
			else if( newGround_Type == GRASS_GROUND ) //Allow presence
			{
				return true;
			}
			else if( newGround_Type == SAND_GROUND ) //Don't allow presence
			{
				return false;  
			}
			else if( newGround_Type == RIVER_GROUND ) //Allow presence
			{
				return true;
			}
			else // not listed type (impossible!!??). Don't allow presence
			{
				return false;  
			}
		}
	}
	//we can't locate the position inside the vector (impossible!!??)
	return false;
}

//Worm Full constructor
Monster_Worm::Monster_Worm(int X, int Y)
{
    //Initial position
	x = X;
    y = Y;

	//Monster Tile Surface
	_monsters_list = RGBSurface("data/Monsters5.bmp", Color(0xFF, 0xFF, 0xFF));
	
	 //Monster Clip definition range for the top left (Random monster from the 5th line)
    _monster[0].setx( MO_WIDTH * (rand()%8) );
	_monster[0].sety( MO_HEIGHT*4 );
    _monster[0].setw( MO_WIDTH );
    _monster[0].seth( MO_HEIGHT );

	//Initial velocity
    xVel = 0;
    yVel = 0;

	//Collision Box Definition : The collision box has the size of the monster
	collision_box.setx(X);
    collision_box.sety(Y);
    collision_box.setw(MO_WIDTH);
    collision_box.seth(MO_HEIGHT);

	//Bool that indicate if the monster is alive or dead: by default the monster is created alive
	Alive_Status = true;
}
//Check if the ground allow the worm to exists
bool Monster_Worm::check_background_allow_monster(int x, int y, std::vector<BattleField_Sprite*> BattleField_Sprite_Vector)
{
	//loop on all the vector
	for(int i=0; i < BattleField_Sprite_Vector.size(); i++)
	{
		//when we have located the good destination inside the vector,...
		if (( x == BattleField_Sprite_Vector[i]->Get_X() ) && ( y == BattleField_Sprite_Vector[i]->Get_Y() ))
		{
			//...get the destination ground...
			int newGround_Type = BattleField_Sprite_Vector[i]->Get_BattleField_Type();
			
			//...then check if the ground allow the character move
			if( newGround_Type == EMPTY_GROUND ) //Don't allow presence
			{
				return false; 
			}
			else if( newGround_Type == GRASS_GROUND ) //Allow presence
			{
				return true;
			}
			else if( newGround_Type == SAND_GROUND ) //Allow presence
			{
				return true;  
			}
			else if( newGround_Type == RIVER_GROUND ) //Don't Allow presence
			{
				return false;
			}
			else // not listed type (impossible!!??). Don't allow presence
			{
				return false;  
			}
		}
	}
	//we can't locate the position inside the vector (impossible!!??)
	return false;
}
