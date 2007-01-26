#include "Monsters.hh"

//Skeleton Full constructor
Monster_Skeleton::Monster_Skeleton(int x, int y)
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

	//Assign the sprite
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
	else // not listed type (impossible!!??). Don't allow move
	{
		return 0;
	}
}


//Worm Full constructor
Monster_Worm::Monster_Worm(int x, int y)
{
    //Initial position
	X = x;
    Y = y;

	//Monster Tile Surface
	Characters_Tile = RGBSurface("Datas/Characters/Monsters5.bmp", Color(0xFF, 0xFF, 0xFF));
	
	 //Monster Clip definition range for the top left (Random monster from the 5th line)
    _monster[0].setx( MO_WIDTH * (rand()%8) );
	_monster[0].sety( MO_HEIGHT*4 );
    _monster[0].setw( MO_WIDTH );
    _monster[0].seth( MO_HEIGHT );

	//Assign the sprite
	Characters_SpriteRect = _monster[0];

	//Initial velocity
    xVel = 0;
    yVel = 0;

	//Monster type
	Monster_ID = Worm;

	//Collision Box Definition : The collision box has the size of the monster
	Collision_Box.setx(X);
    Collision_Box.sety(Y);
    Collision_Box.setw(MO_WIDTH);
    Collision_Box.seth(MO_HEIGHT);

	//Bool that indicate if the monster is alive or dead: by default the monster is created alive
	Alive_Status = true;
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
	else // not listed type (impossible!!??). Don't allow move
	{
		return 0;
	}
}
