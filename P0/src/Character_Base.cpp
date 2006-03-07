#include "Character_Base.hh"

//Initialization construtor
Character_Base::Character_Base(int X, int Y, SDL_Surface *Screen_Surface, std::vector<Monster*> monster_vector)
{
    //Initial position
	x = X;
	y = Y;

	//Display Surface
	screen = Screen_Surface;
    
    //Initial velocity
    xVel = 0;
    yVel = 0;

	//Character Tile
	Characters_Tile = NULL;
	Characters_Tile_Melee = NULL;
	Characters_Tile_Distant = NULL;

	//Character Clips definition
	_character_left_attack[0].x = 0;
    _character_left_attack[0].y = 0;
    _character_left_attack[0].w = CH_WIDTH;
    _character_left_attack[0].h = CH_HEIGHT;
    
    _character_left_attack[1].x = CH_WIDTH;
    _character_left_attack[1].y = 0;
    _character_left_attack[1].w = CH_WIDTH;
    _character_left_attack[1].h = CH_HEIGHT;
    
    _character_left_attack[2].x = CH_WIDTH * 2;
    _character_left_attack[2].y = 0;
    _character_left_attack[2].w = CH_WIDTH;
    _character_left_attack[2].h = CH_HEIGHT;
    

    _character_right_attack[0].x = 0;
    _character_right_attack[0].y = CH_HEIGHT;
    _character_right_attack[0].w = CH_WIDTH;
    _character_right_attack[0].h = CH_HEIGHT;
    
    _character_right_attack[1].x = CH_WIDTH;
    _character_right_attack[1].y = CH_HEIGHT;
    _character_right_attack[1].w = CH_WIDTH;
    _character_right_attack[1].h = CH_HEIGHT;
    
    _character_right_attack[2].x = CH_WIDTH * 2;
    _character_right_attack[2].y = CH_HEIGHT;
    _character_right_attack[2].w = CH_WIDTH;
    _character_right_attack[2].h = CH_HEIGHT;


	_character_down_attack[0].x = 0;
    _character_down_attack[0].y = CH_HEIGHT*2;
    _character_down_attack[0].w = CH_WIDTH;
    _character_down_attack[0].h = CH_HEIGHT;
    
    _character_down_attack[1].x = CH_WIDTH;
    _character_down_attack[1].y = CH_HEIGHT*2;
    _character_down_attack[1].w = CH_WIDTH;
    _character_down_attack[1].h = CH_HEIGHT;
    
    _character_down_attack[2].x = CH_WIDTH * 2;
    _character_down_attack[2].y = CH_HEIGHT*2;
    _character_down_attack[2].w = CH_WIDTH;
    _character_down_attack[2].h = CH_HEIGHT;
    

    _character_up_attack[0].x = 0;
    _character_up_attack[0].y = CH_HEIGHT*3;
    _character_up_attack[0].w = CH_WIDTH;
    _character_up_attack[0].h = CH_HEIGHT;
    
    _character_up_attack[1].x = CH_WIDTH;
    _character_up_attack[1].y = CH_HEIGHT*3;
    _character_up_attack[1].w = CH_WIDTH;
    _character_up_attack[1].h = CH_HEIGHT;
    
    _character_up_attack[2].x = CH_WIDTH * 2;
    _character_up_attack[2].y = CH_HEIGHT*3;
    _character_up_attack[2].w = CH_WIDTH;
    _character_up_attack[2].h = CH_HEIGHT;

	//Initialize animation variables
    frame = 0;  // for future moves animation
    move_status = CH_RIGHT;

	//Attack variable
	attack_status = false; //false = 0
	attack_style = 1; //0: nothing (future dev), 1: Melee attack (default), 2: Distant attack, 3: magic attack (future dev)

	//Camera: at the begining it's in the top left corner of the level
	//camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	camera.x = 0;
	camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;

	//Collision Box Definition: The collision box has the size of the character
	collision_box.x = X;
    collision_box.y = Y;
    collision_box.w = CH_WIDTH;
    collision_box.h = CH_HEIGHT;

	//Attack collsion box: currently in the same place of the character
	attack_collision_box.x = X;
    attack_collision_box.y = Y;
    attack_collision_box.w = CH_WIDTH;
    attack_collision_box.h = CH_HEIGHT;

	//Msgs displayed in the status bar
	attack_msg_hit = NULL;
	attack_msg_miss = NULL;
	attack_melee_msg_hit = NULL;
	attack_melee_msg_miss = NULL;
	attack_distant_msg_hit = NULL;
	attack_distant_msg_miss = NULL;

	//The monster vector that containt all monsters
	Monster_Vector = monster_vector; 

	/****Arrow***/
	Arrow_Tile = NULL;

	Arrow_Left[0].x = 0;
    Arrow_Left[0].y = 0;
    Arrow_Left[0].w = CH_WIDTH;
    Arrow_Left[0].h = CH_HEIGHT;

	Arrow_Right[0].x = 0;
    Arrow_Right[0].y = CH_HEIGHT;
    Arrow_Right[0].w = CH_WIDTH;
    Arrow_Right[0].h = CH_HEIGHT;

	Arrow_Down[0].x = 0;
    Arrow_Down[0].y = CH_HEIGHT*2;
    Arrow_Down[0].w = CH_WIDTH;
    Arrow_Down[0].h = CH_HEIGHT;

	Arrow_Up[0].x = 0;
    Arrow_Up[0].y = CH_HEIGHT*3;
    Arrow_Up[0].w = CH_WIDTH;
    Arrow_Up[0].h = CH_HEIGHT;
}
//Destructor
Character_Base::~Character_Base()
{
	//Close the font that was used
    TTF_CloseFont(attack_font);

	//Free the msgs
	SDL_FreeSurface(attack_msg_hit);
	SDL_FreeSurface(attack_msg_miss);
	SDL_FreeSurface(attack_melee_msg_hit);
	SDL_FreeSurface(attack_melee_msg_miss);
	SDL_FreeSurface(attack_distant_msg_hit);
	SDL_FreeSurface(attack_distant_msg_miss);

	//Free the surface
	SDL_FreeSurface(Characters_Tile);
	SDL_FreeSurface(Characters_Tile_Melee);
	SDL_FreeSurface(Characters_Tile_Distant);
	SDL_FreeSurface(Arrow_Tile);
	SDL_FreeSurface(screen);
}
//Init of the character
bool Character_Base::Init()
{
	//Fight Msgs Style
	attack_Text_Color.b = 255; attack_Text_Color.g = 255; attack_Text_Color.r = 255;
	attack_font = TTF_OpenFont( "data/ECHELON.TTF", 28 );
	if (attack_font == NULL)  {
		return false; }

	//Surfaces
	Characters_Tile_Melee = create_surface("data/Character_Fighter.bmp");
	if( Characters_Tile_Melee == NULL ) {
		return false; }

	Characters_Tile_Distant = create_surface("data/Character_Archer.bmp");
	if( Characters_Tile_Distant == NULL ) {
		return false; }

	Characters_Tile = Characters_Tile_Melee;

	//Arrow surface
	Arrow_Tile = create_surface("data/Arrow.bmp");
	if( Arrow_Tile == NULL ) {
		return false; }

	//Msgs (by default melee type)
	attack_melee_msg_hit = NULL;
	attack_melee_msg_hit = TTF_RenderText_Solid( attack_font, "Melee Hit", attack_Text_Color );
	if( attack_melee_msg_hit == NULL ) {
		return false; }

	attack_distant_msg_hit = NULL;
	attack_distant_msg_hit = TTF_RenderText_Solid( attack_font, "Distant Hit", attack_Text_Color );
	if( attack_distant_msg_hit == NULL ) {
		return false; }
	
	attack_melee_msg_miss = NULL;
	attack_melee_msg_miss = TTF_RenderText_Solid( attack_font, "Melee Miss", attack_Text_Color );
	if( attack_melee_msg_miss == NULL ) {
		return false; }

	attack_distant_msg_miss = NULL;
	attack_distant_msg_miss = TTF_RenderText_Solid( attack_font, "Distant Miss", attack_Text_Color );
	if( attack_distant_msg_miss == NULL ) {
		return false; }

	//Everything went fine
	return true;
}
//Character Graphic Style Initialiation regarding the attack style
void Character_Base::Update_Graphic_Style()
{
	// Melee Style
	if (attack_style == 1)
	{
		Characters_Tile = Characters_Tile_Melee;
		attack_msg_hit = attack_melee_msg_hit;
		attack_msg_miss = attack_melee_msg_miss;
	}
	// Distant Style
	else if (attack_style == 2)
	{
		Characters_Tile = Characters_Tile_Distant;
		attack_msg_hit = attack_distant_msg_hit;
		attack_msg_miss = attack_distant_msg_miss;
	}
}
// input Management
bool Character_Base::input_mgt( SDL_Event &event )
{
	bool quit = false;
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
	{
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
			//Moves Keys
            case SDLK_KP8:
				yVel -= CH_HEIGHT;
				break;
            case SDLK_KP5:
				yVel += CH_HEIGHT;
				break;
            case SDLK_KP7:
				xVel -= CH_WIDTH;
				break;
            case SDLK_KP9:
				xVel += CH_WIDTH;
				break;

			//Attacks Key
			case SDLK_KP_DIVIDE:
				attack_status = true;
				break;
			//Change weapon style by looping between the available styles (2 for the moment)
            case SDLK_KP_MULTIPLY:
				attack_style++;
				if (attack_style > 2) { attack_style = 1; }
				break;

			//Leave/appears on the Battlefield and save but do not quit
			case SDLK_KP_ENTER:
				//To DO *******
				break;

			//Esc Key Pressed
			case SDLK_ESCAPE:
				quit = true;
				break;
			//Default, do not quit !
			default:
				quit = false;
				break;
        }
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
			//Moves Keys
            case SDLK_KP8:
				yVel += CH_HEIGHT;
				break;
            case SDLK_KP5:
				yVel -= CH_HEIGHT;
				break;
            case SDLK_KP7:
				xVel += CH_WIDTH;
				break;
            case SDLK_KP9:
				xVel -= CH_WIDTH;
				break;
			default:
				quit = false;
				break;
        }        
    }
	return quit;
}

//Show the Character on the screen
void Character_Base::move()
{
    //Move the Character left or right and his collision box
	x  += xVel;
    collision_box.x  = x;
    
    //If the Character went too far to the left or right
	if( (collision_box.x < 0) || (collision_box.x + CH_WIDTH > LEVEL_WIDTH) )
	{
        //move back
		x -= xVel;
        collision_box.x = x;    
    }

	//Collision with monster when moving on the x axis
	for(int i=0; i < Monster_Vector.size(); i++)
	{
		if (check_collision(collision_box, Monster_Vector[i]->collision_box))
		{
			x -= xVel;
			collision_box.x = x;
			break;
		}
	}
    
    //Move the Character up or down and his collision box
	y += yVel;
    collision_box.y = y;
    
    //If the Character went too far up or down (the -32 is here for the status bar)
	if((collision_box.y < 0) || (collision_box.y + CH_HEIGHT > LEVEL_HEIGHT-32) )
    {
        //move back
		y -= yVel;
        collision_box.y = y;    
    }
	//Collision with monster when moving on the y axis
	for(int i=0; i < Monster_Vector.size(); i++)
	{
		if (check_collision(collision_box, Monster_Vector[i]->collision_box))
		{
			y -= yVel;
			collision_box.y = y;
			break;
		}
	}
}
//Show the Character on the screen
void Character_Base::move_animation()
{
	//If CH is moving left
    if( xVel < 0 )
    {
        move_status = CH_LEFT;
    }
    //If CH is moving right
    else if( xVel > 0 )
    {
        move_status = CH_RIGHT;
    }
    //If CH is moving down
    else if ( yVel > 0 )
    {
        move_status = CH_DOWN;  
    }
	//If CH is moving up
	else if( yVel < 0 )
	{
	    move_status = CH_UP;
	}
  
    //Show the character in his good position
    if( move_status == CH_RIGHT )
    {
		apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_right_attack[0]);
    }
    else if( move_status == CH_LEFT )
    {
        apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_left_attack[0]);
    }
	else if( move_status == CH_DOWN )
    {
        apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_down_attack[0]);
    }
	else if( move_status == CH_UP )
    {
        apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_up_attack[0]);
    }
}
//Handle character attack on monsters for all attack style
int Character_Base::attack()
{
	int Hit_Distance = 0; //The Hit distane is the distance between the character and the monster by default the Melee Hit Distance

	//If the player has pushed the attack key => check if attack was seccessfull or not and act accordingly
	if (attack_status == true)
	{
		//By default consider that no attack was successfull
		bool attack_successfull = false;

		//First Check attack style
		if (attack_style == 1) //Melee attack: Only hit at one square distant
		{
			Hit_Distance = 0;
			attack_successfull = attack_check_status(1);
		}
		else if (attack_style == 2) //distant attack: 3 square hit distance max
		{
			Hit_Distance = 3;
			for (int i=1; i<=3; i++)
			{
				attack_successfull = attack_check_status(i);
				if (attack_successfull) { //One monster has been hit
					Hit_Distance = i-1; //update the hit distance
					break;
				}
			}
		}
		

		/*****Display MSG on the status bar *****/
		//Clean the status Bar (last line of the screen)
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00) );

		//If a monster was hit displayed the msg, if no display miss msg
		if (attack_successfull)
		{
			apply_surface( 5, SCREEN_HEIGHT - 30, attack_msg_hit, screen );
			printf("attack succesfull\n");
		}
		else
		{
			apply_surface( 5, SCREEN_HEIGHT - 30, attack_msg_miss, screen );
			printf("attack failed\n");
		}
	}

	return Hit_Distance;
}
//Check if collision between the attack and one of the monsters on the battlefield regarding the number of movements that the attack collision is currently doing
bool Character_Base::attack_check_status(int collision_box_movement)
{
	bool _attack_successfull = false;
	//Check attack direction
	if( move_status == CH_RIGHT )
	{
		//move the collision box right of the character
		attack_collision_box.x = collision_box.x + (CH_WIDTH * collision_box_movement);
		attack_collision_box.y = collision_box.y;
	}
	else if( move_status == CH_LEFT )
	{
		//move the collision box left of the character
		attack_collision_box.x = collision_box.x - (CH_WIDTH * collision_box_movement);
		attack_collision_box.y = collision_box.y;
	}
	else if( move_status == CH_DOWN )
	{
		//move the collision box down of the character
		attack_collision_box.x = collision_box.x;
		attack_collision_box.y = collision_box.y + (CH_HEIGHT * collision_box_movement);
	}
	else if( move_status == CH_UP )
	{
		//move the collision box up of the character
		attack_collision_box.x = collision_box.x;
		attack_collision_box.y = collision_box.y - (CH_WIDTH * collision_box_movement);
	}
	

	//Check attack with all monsters inside the vector and return true if one of the monster was hit also update the monster Alive_Status
	for(int i=0; i < Monster_Vector.size(); i++)
	{
		//check if collision between monster and attack now that the attack_collision_box has been moved
		if (check_collision(attack_collision_box, Monster_Vector[i]->collision_box))
		{
			//One monster has been hit so modify the attack_successfull status...
			_attack_successfull = true;
			//...Change the monster status to false aka monster dead...
			Monster_Vector[i]->Alive_Status = false;
			//...Than leave the check in order to touch only one monster at a timer.
			break;
		}			
	}

	return _attack_successfull;
}
//Attack animation regarding of the style
void Character_Base::attack_animation(int character_hit_distance)
{
	//If the player has pushed the attack key => launch animation attack
	if (attack_status == true)
	{

	//The attack speed regulator
    Timer attack_regulator;
	attack_regulator.start();

		// Melee Style (character_hit_distance = 1 so do not care)
		if (attack_style == 1)
		{
			//Show the good attack in function of the position
			if( move_status == CH_RIGHT )
			{
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_right_attack[0]);

				//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_right_attack[1]);
				while( attack_regulator.get_ticks() < 150 )
				{
					//wait    
				}

				//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_right_attack[2]);
				attack_regulator.start();
				while( attack_regulator.get_ticks() < 300 )
				{
					//wait    
				}
				
				//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_right_attack[0]);
			}
			else if( move_status == CH_LEFT )
			{
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_left_attack[0]);

				//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_left_attack[1]);
				while( attack_regulator.get_ticks() < 150 )
				{
					//wait    
				}

				//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_left_attack[2]);
				attack_regulator.start();
				while( attack_regulator.get_ticks() < 300 )
				{
					//wait    
				}
				
				//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_left_attack[0]);
			}
			else if( move_status == CH_DOWN )
			{
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_down_attack[0]);

				//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_down_attack[1]);
				while( attack_regulator.get_ticks() < 150 )
				{
					//wait    
				}

				//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_down_attack[2]);
				attack_regulator.start();
				while( attack_regulator.get_ticks() < 300 )
				{
					//wait    
				}
				
				//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_down_attack[0]);
			}
			else if( move_status == CH_UP )
			{
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_up_attack[0]);

				//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_up_attack[1]);
				while( attack_regulator.get_ticks() < 150 )
				{
					//wait    
				}

				//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_up_attack[2]);
				attack_regulator.start();
				while( attack_regulator.get_ticks() < 300 )
				{
					//wait    
				}
				
				//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
				apply_surface(x - camera.x, y - camera.y, Characters_Tile, screen, &_character_up_attack[0]);
			}
		}
		// Distant Style
		if (attack_style == 2)
		{
			//In case of distant attack character_hit_distance may vary if we have to take care of it
			for (int i=1; i <= character_hit_distance; i++) //Move the arrow until character_hit_distance reached that represents monster hit
			{
				//Show the good arrow in function of the position
				if( move_status == CH_RIGHT )
				{
					apply_surface(x - camera.x + (i * CH_WIDTH), y - camera.y, Arrow_Tile, screen, &Arrow_Right[0]);
					attack_regulator.start();
					while( attack_regulator.get_ticks() < 200 )
					{
						//wait    
					}
				}
				else if( move_status == CH_LEFT )
				{
					apply_surface(x - camera.x - (i * CH_WIDTH), y - camera.y, Arrow_Tile, screen, &Arrow_Left[0]);
					attack_regulator.start();
					while( attack_regulator.get_ticks() < 200 )
					{
						//wait    
					}
				}
				else if( move_status == CH_DOWN )
				{
					apply_surface(x - camera.x, y - camera.y + (i * CH_HEIGHT), Arrow_Tile, screen, &Arrow_Down[0]);
					attack_regulator.start();
					while( attack_regulator.get_ticks() < 200 )
					{
						//wait    
					}
				}
				else if( move_status == CH_UP )
				{
					apply_surface(x - camera.x, y - camera.y - (i * CH_HEIGHT), Arrow_Tile, screen, &Arrow_Up[0]);
					attack_regulator.start();
					while( attack_regulator.get_ticks() < 200 )
					{
						//wait    
					}
				}
			}
		}

		//attack has been done => reset the status and stop the timer
		attack_regulator.stop();
		attack_status = false;
	}
}
//Managed the camera
void Character_Base::following_camera()
{
    //Center the camera over the Character
    camera.x = (x + CH_WIDTH / 2) - SCREEN_WIDTH / 2;
    camera.y = (y + CH_HEIGHT / 2) - SCREEN_HEIGHT / 2;
    //Keep the camera in bounds.
    if(camera.x < 0)
    {
        camera.x = 0;    
    }
    if(camera.y < 0)
    {
        camera.y = 0;    
    }
    if(camera.x > LEVEL_WIDTH - camera.w)
    {
        camera.x = LEVEL_WIDTH - camera.w;    
    }
    if(camera.y > LEVEL_HEIGHT - camera.h)
    {
        camera.y = LEVEL_HEIGHT - camera.h;    
    }    
}

//Update charaster's monster knowledge of monster presents on the battlefield
void Character_Base::Update_Monster_Knowledge(std::vector<Monster*> monster_vector)
{
	//Update only if the two vector have not the same size (only here to gain execution speed when vector will have an important size)
	if (monster_vector.size() != Monster_Vector.size())
	{
		Monster_Vector = monster_vector;
	}
}