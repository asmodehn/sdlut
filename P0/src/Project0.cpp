
#include "SDL.hh"
//#include "SDL_image.h"
#include <string>

//The attributes of the window
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The dimensions of the level
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 1280;

//The frame rate
const int FRAMES_PER_SECOND = 15;

//The dimensions of the Character
const int CH_WIDTH = 32;
const int CH_HEIGHT = 32;
const int MO_WIDTH = 32;
const int MO_HEIGHT = 32;

//The direction status of the character
const int CH_RIGHT = 0;
const int CH_LEFT = 1;
const int CH_DOWN = 2;
const int CH_UP = 3;

//The surfaces that will be used
SDL_Surface *_monsters_list = NULL;
SDL_Surface *_characters_list = NULL;
SDL_Surface *_background = NULL;
SDL_Surface *_screen = NULL;

//The portions of the sprite map to be blitted
SDL_Rect _monster[1];

SDL_Rect _character_right_attack[3];
SDL_Rect _character_left_attack[3];
SDL_Rect _character_down_attack[3];
SDL_Rect _character_up_attack[3];

SDL_Rect _bg[1];

//Collisions Box
SDL_Rect Character_collision_box;
SDL_Rect Monster_collision_box;

//The event structure that will be used
SDL_Event event;

//Camera def initialized in the top right corner and with the width and height of the screen
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

//Enable UniCode
//SDL_EnableUNICODE()


//Create surface from an image function and optimized image to the desired format with white color as transparent color
SDL_Surface *create_surface( std::string filename ) 
{
    //Temporary storage for the Surface that's loaded
    SDL_Surface* loadedSurface = NULL;
    
    //The optimized Surface that will be used
    SDL_Surface* optimizedSurface = NULL;
    
    //Load the image
    loadedSurface = SDL_LoadBMP( filename.c_str() );

	/*************DEVRAIS PERMETTRE LE LOAD DE DIFFERENT TYPE D'IMAGE AUTRE KE BMP => VOIR AVEC ALEX**/
	//loadedSurface = IMG_Load( filename.c_str() );
    
    //If nothing went wrong in loading the image
    if( loadedSurface != NULL )
    {
        //Create an optimized Surface
        optimizedSurface = SDL_DisplayFormat( loadedSurface );
        
        //Free the old image
        SDL_FreeSurface( loadedSurface );
		
		//If the image was optimized just fine
        if( optimizedSurface != NULL )
        {
            //Set all pixels of color 0xFFFFFF (white) to be transparent
            SDL_SetColorKey( optimizedSurface, SDL_RLEACCEL | SDL_SRCCOLORKEY, 0xFFFFFF );
        }
    }
    
    //Return the optimized image
    return optimizedSurface;
}

//Surface blitting function wich blit a piece of a surface or the whole surface if no Rect area is defined
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Make a temporary rect to hold the offsets
    SDL_Rect Offset;
    
    //Give the offsets to the rect
    Offset.x = x;
    Offset.y = y;
    
    //Blit the surface
    SDL_BlitSurface( source, clip, destination, &Offset );
}

//To check colission (small beginning of a physical engine^^)
bool check_collision(SDL_Rect &A, SDL_Rect &B)
{
        //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
        
    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
            
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}

//Gnerate Background
void generate_bg()
{
	int i=0, j=0;
	while (i<(SCREEN_WIDTH/32))
	{
		while (j<(SCREEN_HEIGHT/32))
		{
			apply_surface(i*32, j*32, _background, _screen, &_bg[0]);
			j++;
		}
		i++;
		j=0;
	}
}
//Initialization
bool InitWindows()
{
    //Initialize all SDL sub systems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;    
    }
    
    //Set up the screen
    _screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was in error in setting up the screen
    if( _screen == NULL )
    {
        return false;    
    }
    
    //Set the window caption
    SDL_WM_SetCaption( "Project 0 - 2D - v0.01", NULL );

    //If eveything loads fine
    return true;    
}
//Load Images Files
bool Load_Files()
{
    //Load the sprites
    _monsters_list = create_surface( "data/Monsters5.bmp" );
	//_characters_list = create_surface ("data/Characters.bmp");
	_characters_list = create_surface ("data/Character_Fighter.bmp");
    _background = create_surface( "data/tankbrigade.bmp" );
    
    //If there was an problem loading sprites
    if( _monsters_list == NULL ) { return false; }
	if( _characters_list == NULL ) { return false; }
	if( _background == NULL ) { return false; }
    
    //If eveything loaded fine
    return true;    
}
//Clean Up Surface
void Clean_Up()
{
	SDL_FreeSurface(_monsters_list);
	SDL_FreeSurface(_characters_list);
	SDL_FreeSurface(_background);
	SDL_FreeSurface(_screen);
}
//The Monster
class Monster
{
    private:
    //The X and Y offsets of the Monster
    int x, y;

	//The velocity of the Monster
    int xVel, yVel;
    
	public:
	//The collision boxes of the Monster
    SDL_Rect collision_box;

    //Initializes the variables
    Monster(int X, int Y);
    
    //Takes key presses and adjust things accordingly
    void move();
    
    //Shows the Monster movement on the screen
    void move_animation(SDL_Surface *screen);
};
//Initialization
Monster::Monster(int X, int Y)
{
    //Initial position
	x = X;
    y = Y;

	//Initial velocity
    xVel = 0;
    yVel = 0;

	//Collision Box Definition : The collision box has the size of the monster
	collision_box.x = X;
    collision_box.y = Y;
    collision_box.w = MO_WIDTH;
    collision_box.h = MO_HEIGHT;
}
//Move monster randomly
void Monster::move()
{
	//move only if a random number is below 10 (This speed down monster movement)
	if (rand()%200 <= 10) 
	{
		//Random x mvt
		xVel = ((rand()%3-1)*MO_WIDTH);

		//Move the monster left or right and his collision box
		x  += xVel;
		collision_box.x  = x;

		//If the Character went too far to the left or right or in case of collision with the npc
		if((collision_box.x < 0) || (collision_box.x + MO_WIDTH > LEVEL_WIDTH) || (check_collision(collision_box, Character_collision_box)))
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

		//If the Character went too far up or down or in case of collision with the npc
		if((collision_box.y < 0) || (collision_box.y + MO_HEIGHT > LEVEL_HEIGHT) || (check_collision(collision_box, Character_collision_box)))
		{
			//move back
			y -= yVel;
			collision_box.y = y;    
		}
	}
}
//Show monster on the screen
void Monster::move_animation(SDL_Surface *screen)
{
	apply_surface(x - camera.x, y - camera.y, _monsters_list, screen, &_monster[0]);
}
//Character Class
class Character
{
    private:
    //The X and Y offsets of the Character
    int x, y;
    
    //The velocity of the Character
    int xVel, yVel;

	//animation variables
    int frame, status;


	public:
	//The collision boxes of the Character
    SDL_Rect collision_box;

    //Initializes the variables
    Character(int X, int Y);
    
    //Takes key presses and adjust things accordingly
    bool input_mgt(SDL_Event &event);

	//Move the Character
	void move();

    //Shows the character movement on the screen
    void move_animation(SDL_Surface *screen);

	//Shows the character attack on the screen
    void attack_animation(SDL_Surface *screen);
	
	//Camera which follow the Character
    void following_camera();
};
//Initialization
Character::Character(int X, int Y)
{
    //Initial position
	x = X;
	y = Y;
    
    //Initial velocity
    xVel = 0;
    yVel = 0;

	//Initialize animation variables
    frame = 0;
    status = CH_RIGHT;

	//Collision Box Definition : The collision box has the size of the character
	collision_box.x = X;
    collision_box.y = Y;
    collision_box.w = CH_WIDTH;
    collision_box.h = CH_HEIGHT;
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
            case SDLK_UP:
				yVel -= CH_HEIGHT;
				break;
            case SDLK_DOWN:
				yVel += CH_HEIGHT;
				break;
            case SDLK_LEFT:
				xVel -= CH_WIDTH;
				break;
            case SDLK_RIGHT:
				xVel += CH_WIDTH;
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
            case SDLK_UP:
				yVel += CH_HEIGHT;
				break;
            case SDLK_DOWN:
				yVel -= CH_HEIGHT;
				break;
            case SDLK_LEFT:
				xVel += CH_WIDTH;
				break;
            case SDLK_RIGHT:
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
void Character::move()
{
    //Move the Character left or right and his collision box
	x  += xVel;
    collision_box.x  = x;
    
    //If the Character went too far to the left or right or in case of collision with the npc
	if((collision_box.x < 0) || (collision_box.x + CH_WIDTH > LEVEL_WIDTH) || (check_collision(collision_box, Monster_collision_box)))
	{
        //move back
		x -= xVel;
        collision_box.x = x;    
    }
    
    //Move the Character up or down and his collision box
	y += yVel;
    collision_box.y = y;
    
    //If the Character went too far up or down or in case of collision with the npc
	if((collision_box.y < 0) || (collision_box.y + CH_HEIGHT > LEVEL_HEIGHT) || (check_collision(collision_box, Monster_collision_box)))
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
        status = CH_LEFT;
    }
    //If CH is moving right
    else if( xVel > 0 )
    {
        status = CH_RIGHT;
    }
    //If CH is moving down
    else if ( yVel > 0 )
    {
        status = CH_DOWN;  
    }
	//If CH is moving up
	else if( yVel < 0 )
	{
	    status = CH_UP;
	}
  
    //Show the character in his good position
    if( status == CH_RIGHT )
    {
		apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_right_attack[0]);
    }
    else if( status == CH_LEFT )
    {
        apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_left_attack[0]);
    }
	else if( status == CH_DOWN )
    {
        apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_down_attack[0]);
    }
	else if( status == CH_UP )
    {
        apply_surface(x - camera.x, y - camera.y, _characters_list, screen, &_character_up_attack[0]);
    }
}
//Attack animation
void Character::attack_animation(SDL_Surface *screen)
{

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
//Timer for FPS management
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;
    
    //The ticks stored when the timer was paused
    int pausedTicks;
    
    //The timer status
    bool paused;
    bool started;
    
    public:
    //Initializes variables
    Timer();
    
    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    
    //Get the number of ticks since the timer started
    //Or gets the number of ticks when the timer was paused
    int get_ticks();
    
    //Checks the status of the timer
    bool is_started();
    bool is_paused();    
};
Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;    
}

void Timer::start()
{
    //Start the timer
    started = true;
    
    //Unpause the timer
    paused = false;
    
    //Get the current clock time
    startTicks = SDL_GetTicks();    
}

void Timer::stop()
{
    //Stop the timer
    started = false;
    
    //Unpause the timer
    paused = false;    
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;
    
        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;
    
        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;
        
        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }    
    }
    
    //If the timer isn't running return 0
    return 0;    
}

bool Timer::is_started()
{
    return started;    
}

bool Timer::is_paused()
{
    return paused;    
}
//Main
int main( int argc, char* args[] )
{
	//Make sure the program waits for a quit
	bool quit = false;
	
	//Create Charactre & Monster
    Character myCharacter(192, 224);
	Monster myMonster(256, 288);

	//The frames rate regulator
    Timer fps;

	//Initialize
	if( InitWindows() == false ) { 
		printf("Init failed");
		return 1;
	}
	//Load the files
	if( Load_Files() == false ) {
		printf("File load failed");
		return 1;
	}

	//Background Clip definition range for the top left ()
    _bg[0].x = 198;
	_bg[0].y = 132;
    _bg[0].w = 32;
    _bg[0].h = 32;

     //Monster Clip definition range for the top left (Random monster from the 7th line)
    _monster[0].x = MO_WIDTH * (rand()%8);
	_monster[0].y = MO_HEIGHT*6;
    _monster[0].w = MO_WIDTH;
    _monster[0].h = MO_HEIGHT;

	//Character Clip definition
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

    
	//Update the screen
    if( SDL_Flip(_screen) == -1 )
    {
        return 1;    
    }

	//Loop until close of the windows using the cross or escape key
	while(quit == false)
	{
		//Start the FPS management
        fps.start();

		//While there's an event to handle
		while(SDL_PollEvent(&event))
		{

			//Handle events for the Character
			quit = myCharacter.input_mgt(event);

			//Window closed
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
		}

		//Collisions Box to check if monster collide with npc or npc collide with monster
		Character_collision_box = myCharacter.collision_box;
		Monster_collision_box = myMonster.collision_box;

		//Move the character
		myCharacter.move();

		//Move the chracter
		myMonster.move();

		//Set the camera
        myCharacter.following_camera();

		//Generate the background to the screen
		generate_bg();
		//apply_surface(0, 0, _background, _screen, &camera );
		//Fill the screen white
		//SDL_FillRect( _screen, &_screen->clip_rect, SDL_MapRGB( _screen->format, 0xFF, 0xFF, 0xFF ) );

		//Show the Character on the screen
		myCharacter.move_animation(_screen);

		//Apply monsters to the screenn
		myMonster.move_animation(_screen);

		//Update the screen
		if( SDL_Flip(_screen) == -1 )
		{
			return 1;    
		}

		//Cap the frame rate
        while( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //wait    
        }
	}

	//Clean Before Exit
	Clean_Up();
	    
    //Quit SDL
	SDL_Quit();

    return 0;    
}

