#include "Monster.hh"

//Defalut Constructor
Monster::Monster()
{
	//Initial position
	x = 0;
    y = 0;

	//Display Surface
	screen = NULL;
	
	//Monster Sprite
	_monsters_list = NULL;

	 //Monster Clip definition range for the top left (Random monster from the 7th line)
    _monster[0].x = MO_WIDTH * (rand()%8);
	_monster[0].y = MO_HEIGHT*6;
    _monster[0].w = MO_WIDTH;
    _monster[0].h = MO_HEIGHT;

	//Initial velocity
    xVel = 0;
    yVel = 0;

	//Collision Box Definition : The collision box has the size of the monster
	collision_box.x = 0;
    collision_box.y = 0;
    collision_box.w = MO_WIDTH;
    collision_box.h = MO_HEIGHT;

	//Bool that indicate if the monster is alive or dead: by default the monster is created alive
	Alive_Status = true;
}
//Full Construtor
Monster::Monster(int X, int Y, SDL_Surface *Screen_Surface)
{
    //Initial position
	x = X;
    y = Y;

	//Display Surface
	screen = Screen_Surface;
	
	//Monster Sprite
	_monsters_list = NULL;

	 //Monster Clip definition range for the top left (Random monster from the 7th line)
    _monster[0].x = MO_WIDTH * (rand()%8);
	_monster[0].y = MO_HEIGHT*6;
    _monster[0].w = MO_WIDTH;
    _monster[0].h = MO_HEIGHT;

	//Initial velocity
    xVel = 0;
    yVel = 0;

	//Collision Box Definition : The collision box has the size of the monster
	collision_box.x = X;
    collision_box.y = Y;
    collision_box.w = MO_WIDTH;
    collision_box.h = MO_HEIGHT;

	//Bool that indicate if the monster is alive or dead: by default the monster is created alive
	Alive_Status = true;
}
//Copy construtor
Monster::Monster(const Monster& ToCopy)
{
	x = ToCopy.x;
	y = ToCopy.y;
	screen = ToCopy.screen;
	_monsters_list = NULL;
	_monsters_list = ToCopy._monsters_list;
	_monster[0] = ToCopy._monster[0];
	xVel = ToCopy.xVel;
	yVel = ToCopy.yVel;
	collision_box = ToCopy.collision_box;
}
//Destructor
Monster::~Monster()
{
	SDL_FreeSurface(_monsters_list);
	SDL_FreeSurface(screen);
}
//Surface Initialiation
bool Monster::Init()
{
	_monsters_list = create_surface( "data/Monsters5.bmp" );
	if( _monsters_list == NULL ) { return false; }
	return true;
}
//Move monster randomly
void Monster::move(SDL_Rect &_CharacterCollisionbox)
{
	//move only if a random number is below 10 (This speed down monster movement)
	if (rand()%200 <= 13) 
	{
		//Random x mvt
		xVel = ((rand()%3-1)*MO_WIDTH);

		//Move the monster left or right and his collision box
		x  += xVel;
		collision_box.x  = x;

		//If the Character went too far to the left or right or in case of collision with the npc
		if((collision_box.x < 0) || (collision_box.x + MO_WIDTH > LEVEL_WIDTH) || (check_collision(collision_box, _CharacterCollisionbox)))
		{
			//move back
			x -= xVel;
			collision_box.x = x;    
		}

		//Random y mvt
		yVel = ((rand()%3-1)*MO_HEIGHT);
		
		//Move the monster up or down and his collision box
		y += yVel;
		collision_box.y = y;

		//If the Character went too far up or down (the -32 is here for the status bar) or in case of collision with the npc
		if((collision_box.y < 0) || (collision_box.y + MO_HEIGHT > LEVEL_HEIGHT-32) || (check_collision(collision_box, _CharacterCollisionbox)))
		{
			//move back
			y -= yVel;
			collision_box.y = y;    
		}
	}
}
//Show monster on the screen
void Monster::move_animation(SDL_Rect camera)
{
	//Display the monster only if visible in the camera range minus the status bar at the bottom
	if ( (camera.x <= x) && (x < camera.x + camera.w) && (camera.y <= y) && (y < camera.y + camera.h - 32) )
	{
		apply_surface(x - camera.x, y - camera.y, _monsters_list, screen, &_monster[0]);
	}
}
