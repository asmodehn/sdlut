#include "Character.hh"

//Initialization
Character::Character(int X, int Y) //, SDL_Surface* Sprite_Source, SDL_Rect* Sprite_Clip = NULL)
{
    //Initial position
	x = X;
	y = Y;
    
    //Initial velocity
    xVel = 0;
    yVel = 0;

	//Character Tile
	_characters_list = NULL;	

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
	attack_status = false; //false = 0

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
}
//Destructor
Character::~Character()
{
	SDL_FreeSurface(_characters_list);
}
//Surface Initialiation
bool Character::Init()
{
	_characters_list = create_surface("data/Character_Fighter.bmp");
	if( _characters_list == NULL ) { return false; }
	return true;
}
// input Management
bool Character::input_mgt( SDL_Event &event )
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

			//Attacks Keys
			case SDLK_KP_DIVIDE: //Melee
				attack_status = true;
				break;
            case SDLK_KP_MULTIPLY:		//Distant
				//To DO *******
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
void Character::move(SDL_Rect &_MonsterCollisionbox)
{
    //Move the Character left or right and his collision box
	x  += xVel;
    collision_box.x  = x;
    
    //If the Character went too far to the left or right or in case of collision with the npc
	if((collision_box.x < 0) || (collision_box.x + CH_WIDTH > LEVEL_WIDTH) || (check_collision(collision_box, _MonsterCollisionbox)))
	{
        //move back
		x -= xVel;
        collision_box.x = x;    
    }
    
    //Move the Character up or down and his collision box
	y += yVel;
    collision_box.y = y;
    
    //If the Character went too far up or down or in case of collision with the npc
	if((collision_box.y < 0) || (collision_box.y + CH_HEIGHT > LEVEL_HEIGHT) || (check_collision(collision_box, _MonsterCollisionbox)))
    {
        //move back
		y -= yVel;
        collision_box.y = y;    
    }
}
//Show the Character on the screen
void Character::move_animation(SDL_Surface *screen)
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
		apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_right_attack[0]);
    }
    else if( move_status == CH_LEFT )
    {
        apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_left_attack[0]);
    }
	else if( move_status == CH_DOWN )
    {
        apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_down_attack[0]);
    }
	else if( move_status == CH_UP )
    {
        apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_up_attack[0]);
    }
}
//Handle character attack on monsters
void Character::attack(SDL_Rect &_MonsterCollisionBoxToBeKilled)
{
	//If the player has pushed the attack key => check if attack was seccessfull or not and act accordingly
	if (attack_status == true)
	{
		//First, check attack direction
		if( move_status == CH_RIGHT )
		{
			//move the collision box right of the character
			attack_collision_box.x = collision_box.x + CH_WIDTH;
			attack_collision_box.y = collision_box.y;

			//check if collision between monster and attack
			if (check_collision(attack_collision_box, _MonsterCollisionBoxToBeKilled))
			{
				printf("attack succesfull\n");
			}
			else
			{
				printf("attack failed\n");
			}
		}
		else if( move_status == CH_LEFT )
		{
			//move the collision box left of the character
			attack_collision_box.x = collision_box.x - CH_WIDTH;
			attack_collision_box.y = collision_box.y;

			//check if collision between monster and attack
			if (check_collision(attack_collision_box, _MonsterCollisionBoxToBeKilled))
			{
				printf("attack succesfull\n");
			}
			else
			{
				printf("attack failed\n");
			}
		}
		else if( move_status == CH_DOWN )
		{
			//move the collision box down of the character
			attack_collision_box.x = collision_box.x;
			attack_collision_box.y = collision_box.y + CH_HEIGHT;

			//check if collision between monster and attack
			if (check_collision(attack_collision_box, _MonsterCollisionBoxToBeKilled))
			{
				printf("attack succesfull\n");
			}
			else
			{
				printf("attack failed\n");
			}
		}
		else if( move_status == CH_UP )
		{
			//move the collision box up of the character
			attack_collision_box.x = collision_box.x;
			attack_collision_box.y = collision_box.y - CH_WIDTH;

			//check if collision between monster and attack
			if (check_collision(attack_collision_box, _MonsterCollisionBoxToBeKilled))
			{
				printf("attack succesfull\n");
			}
			else
			{
				printf("attack failed\n");
			}
		}

	}
}
//Attack animation
void Character::attack_animation(SDL_Surface *screen)
{
	//If the player has pushed the attack key => launch animation attack
	if (attack_status == true)
	{

	//The attack speed regulator
    Timer attack_regulator;
	attack_regulator.start();

		//Show the good attack in function of the position
		if( move_status == CH_RIGHT )
		{
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_right_attack[0]);

			//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_right_attack[1]);
			while( attack_regulator.get_ticks() < 150 )
			{
				//wait    
			}

			//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_right_attack[2]);
			attack_regulator.start();
			while( attack_regulator.get_ticks() < 300 )
			{
				//wait    
			}
			
			//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_right_attack[0]);
		}
		else if( move_status == CH_LEFT )
		{
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_left_attack[0]);

			//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_left_attack[1]);
			while( attack_regulator.get_ticks() < 150 )
			{
				//wait    
			}

			//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_left_attack[2]);
			attack_regulator.start();
			while( attack_regulator.get_ticks() < 300 )
			{
				//wait    
			}
			
			//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_left_attack[0]);
		}
		else if( move_status == CH_DOWN )
		{
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_down_attack[0]);

			//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_down_attack[1]);
			while( attack_regulator.get_ticks() < 150 )
			{
				//wait    
			}

			//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_down_attack[2]);
			attack_regulator.start();
			while( attack_regulator.get_ticks() < 300 )
			{
				//wait    
			}
			
			//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_down_attack[0]);
		}
		else if( move_status == CH_UP )
		{
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_up_attack[0]);

			//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_up_attack[1]);
			while( attack_regulator.get_ticks() < 150 )
			{
				//wait    
			}

			//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_up_attack[2]);
			attack_regulator.start();
			while( attack_regulator.get_ticks() < 300 )
			{
				//wait    
			}
			
			//apply_surface(x - camera.x, y - camera.y, _background, screen, &_bg[0]);
			apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_up_attack[0]);
		}
		//attack has been done => reset the status and stop the timer
		attack_regulator.stop();
		attack_status = false;
	}
}
//Managed the camera
void Character::following_camera()
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
