#include "Monster.hh"

//Default Constructor
Monster::Monster()
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

	//Bool that indicate if the monster is alive or dead: by default the monster is created alive
	Alive_Status = true;
}
//Full Construtor
Monster::Monster(int X, int Y, VideoSurface* Screen_Surface)
{
    //Initial position
	x = X;
    y = Y;

	//Display Surface
	Screen = Screen_Surface;

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
//Copy construtor
Monster::Monster(const Monster& ToCopy)
{
	x = ToCopy.x;
	y = ToCopy.y;
	Screen = ToCopy.Screen;
	_monsters_list = ToCopy._monsters_list;
	_monster[0] = ToCopy._monster[0];
	xVel = ToCopy.xVel;
	yVel = ToCopy.yVel;
	collision_box = ToCopy.collision_box;
}
//Destructor
Monster::~Monster()
{
	_monsters_list.~RGBSurface();
	delete Screen;
	//SDL_FreeSurface(_monsters_list);
	//SDL_FreeSurface(screen);
}
//Move monster randomly
void Monster::move(Rect CharacterCollisionbox)
{
	//move only if a random number is below 10 (This speed down monster movement)
	if (rand()%200 <= 13) 
	{
		//Random x mvt
		xVel = ((rand()%3-1)*MO_WIDTH);

		//Move the monster left or right and his collision box
		x  += xVel;
		collision_box.setx(x);

		//If the Character went too far to the left or right or in case of collision with the npc
		if((collision_box.getx() < 0) || (collision_box.getx() + MO_WIDTH > LEVEL_WIDTH) || (check_collision(collision_box, CharacterCollisionbox)))
		{
			//move back
			x -= xVel;
			collision_box.setx(x);    
		}

		//Random y mvt
		yVel = ((rand()%3-1)*MO_HEIGHT);
		
		//Move the monster up or down and his collision box
		y += yVel;
		collision_box.sety(y);

		//If the Character went too far up or down (the -32 is here for the status bar) or in case of collision with the npc
		if((collision_box.gety() < 0) || (collision_box.gety() + MO_HEIGHT > LEVEL_HEIGHT-32) || (check_collision(collision_box, CharacterCollisionbox)))
		{
			//move back
			y -= yVel;
			collision_box.sety(y);    
		}
	}
}
//Show monster on the screen
void Monster::move_animation(Rect Camera)
{
	//Display the monster only if visible in the Camera range minus the status bar at the bottom
	if ( (Camera.getx() <= x) && (x < Camera.getx() + Camera.getw()) && (Camera.gety() <= y) && (y < Camera.gety() + Camera.geth() - 32) )
	{
		Screen->blit(_monsters_list, Point::Point(x - Camera.getx(), y - Camera.gety()), _monster[0]);
		//apply_surface(x - Camera.getx(), y - Camera.gety(), _monsters_list, screen, &_monster[0]);
	}
}
