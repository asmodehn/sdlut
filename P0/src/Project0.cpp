
#include "SDL.hh"
//#include "SDL_image.h"
#include <string>

//The attributes of the window
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 10;

//The dimensions of the Character
const int CH_WIDTH = 32;
const int CH_HEIGHT = 32;
const int MO_WIDTH = 32;
const int MO_HEIGHT = 32;

//The surfaces that will be used
SDL_Surface *_monsters_list = NULL;
SDL_Surface *_characters_list = NULL;
SDL_Surface *_background = NULL;
SDL_Surface *_screen = NULL;

//The portions of the sprite map to be blitted
SDL_Rect _monster[1];
SDL_Rect _character[1];
SDL_Rect _character_bg[1];

//Monster Collision Box
SDL_Rect Monster_collision_box;

//The event structure that will be used
SDL_Event event;

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
	_characters_list = create_surface ("data/Characters.bmp");
    _background = create_surface( "data/background.bmp" );
    
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
    
    //Takes key presses and adjusts the Monster's velocity
    bool input_mgt(SDL_Event &event);
    
    //Shows the Monster on the screen
    void show(SDL_Surface *screen);
};
//Initialization
Monster::Monster(int X, int Y)
{
    //Initial position
	collision_box.x = X;
    collision_box.y = Y;
    
    //Initial velocity
    xVel = 0;
    yVel = 0;

	//Collision Box Definition : The collision box has the size of the monster
    collision_box.w = MO_WIDTH;
    collision_box.h = MO_HEIGHT;
}
//Character Class
class Character
{
    private:
    //The X and Y offsets of the Character
    int x, y;
    
    //The velocity of the Character
    int xVel, yVel;

	public:
	//The collision boxes of the Character
    SDL_Rect collision_box;

    //Initializes the variables
    Character(int X, int Y);
    
    //Takes key presses and adjusts the velocity
    bool input_mgt(SDL_Event &event);

    //Shows the character on the screen
    void show( SDL_Surface *screen );
	//void show();
};
//Initialization
Character::Character(int X, int Y)
{
    //Initial position
	collision_box.x = X;
    collision_box.y = Y;
    
    //Initial velocity
    xVel = 0;
    yVel = 0;

	//Collision Box Definition : The collision box has the size of the character
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
void Character::show(SDL_Surface *screen)
{

	//Define Character BG position before moving to later used this to renew the BG over the character in case of mouvment
	_character_bg[0].w = CH_WIDTH;
    _character_bg[0].h = CH_HEIGHT;
	_character_bg[0].x = x;
	_character_bg[0].y = y;

	//Clear Character off the screen by adding the BG over him
	apply_surface(x, y, _background, screen, &_character_bg[0]);

	
	//Define Character BG position before moving to later used this to renew the BG over the character in case of mouvment
	_character_bg[0].w = CH_WIDTH;
    _character_bg[0].h = CH_HEIGHT;
	_character_bg[0].x = collision_box.x;
	_character_bg[0].y = collision_box.y;

	//Clear Character off the screen by adding the BG over him
	apply_surface(collision_box.x, collision_box.y, _background, screen, &_character_bg[0]);
						
    //Move the Character left or right
    collision_box.x  += xVel;
    
    //If the Character went too far to the left or right
	if((collision_box.x < 0) || (collision_box.x + CH_WIDTH > SCREEN_WIDTH) || (check_collision(collision_box, Monster_collision_box)))
	{
        //move back
        collision_box.x -= xVel;    
    }
    
    //Move the Character up or down
    collision_box.y += yVel;
    
    //If the Character went too far up or down
	if((collision_box.y < 0) || (collision_box.y + CH_HEIGHT > SCREEN_HEIGHT) || (check_collision(collision_box, Monster_collision_box)))
    {
        //move back
        collision_box.y -= yVel;    
    }

    //show the Character
	apply_surface(collision_box.x, collision_box.y, _characters_list, screen, &_character[0]);
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
	Monster myMonster(160, 160);

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

     //Monster Clip definition range for the top left (Random monster from the 7th line)
    _monster[0].x = 32 * (rand()%8);
	_monster[0].y = 32*6;
    _monster[0].w = 32;
    _monster[0].h = 32;

	//Static Monster collision Box for the moment
	Monster_collision_box = myMonster.collision_box;

    _character[0].x = 5*CH_WIDTH;
    _character[0].y = 3*CH_HEIGHT;
    _character[0].w = CH_WIDTH;
    _character[0].h = CH_HEIGHT;

    //Apply the background to the screen
    apply_surface(0, 0, _background, _screen );
	//Fill the screen white
	//SDL_FillRect( _screen, &_screen->clip_rect, SDL_MapRGB( _screen->format, 0xFF, 0xFF, 0xFF ) );
    
    //Apply monsters to the screen
    apply_surface(160, 160, _monsters_list, _screen, &_monster[0]);

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

		//Show the Character on the screen
		myCharacter.show(_screen);
        
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

