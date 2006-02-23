
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

//The surfaces that will be used
SDL_Surface *_monsters_list = NULL;
SDL_Surface *_characters_list = NULL;
SDL_Surface *_background = NULL;
SDL_Surface *_screen = NULL;

//The portions of the sprite map to be blitted
SDL_Rect _monster[1];
SDL_Rect _character[1];
SDL_Rect _character_bg[1];

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
    SDL_WM_SetCaption( "Project 0 - v0.01", NULL );

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
//
//
//ALEX KEYBOARD *******************************
//
/*class MyKeyboard : public SDL::Keyboard
{
    Sprite * _activesprite;
public:

    void setActive(Sprite * s)
    {
        _activesprite=s;
    }

    bool handleKeyEvent (const Sym &s, bool pressed)
    {
        bool res = false;
        switch (s.getKey())
        {
            case KEscape:
            if (pressed==false)
            {
                _quitRequested=true;
                res=true;
            }
            break;
            case KUp :
            if (pressed)
            {
                _activesprite->setPos(_activesprite->getPos().getx(),_activesprite->getPos().gety() -5);
                res = true;
            }
            break;
            case KDown :
            if (pressed)
            {
                _activesprite->setPos(_activesprite->getPos().getx(),_activesprite->getPos().gety() + 5 );
                res = true;
            }
            break;
            case KLeft :
            if (pressed)
            {
                _activesprite->setPos(_activesprite->getPos().getx() -5,_activesprite->getPos().gety());
                res = true;
            }
            break;
            case KRight :
            if (pressed)
            {
                _activesprite->setPos(_activesprite->getPos().getx() +5,_activesprite->getPos().gety());
                res = true;
            }
            break;
            default :
            break;
        }
        return res;
    }
};
*/


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
    //The X and Y offsets of the dot
    int x, y;
    
    //The velocity of the dot
    int xVel, yVel;
    
    public:
    //Initializes the variables
    Monster();
    
    //Takes key presses and adjusts the dot's velocity
    bool input_mgt( SDL_Event &event );
    
    //Shows the dot on the screen
    void show( SDL_Surface *screen );
};
//Initialization
Monster::Monster()
{
    //Initial position
    x = 180;
    y = 140;
    
    //Initial velocity
    xVel = 0;
    yVel = 0;
}
/**********************Character**********************/
class Character
{
    private:
    //The X and Y offsets of the dot
    int x, y;
    
    //The velocity of the dot
    int xVel, yVel;
    
    public:
    //Initializes the variables
    Character();
    
    //Takes key presses and adjusts the velocity
    bool input_mgt( SDL_Event &event );
    
    //Shows the dot on the screen
    void show( SDL_Surface *screen );
};
//Initialization
Character::Character()
{
    //Initial position
    x = 250;
    y = 200;
    
    //Initial velocity
    xVel = 0;
    yVel = 0;
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
				yVel -= CH_HEIGHT / 2;
				break;
            case SDLK_DOWN:
				yVel += CH_HEIGHT / 2;
				break;
            case SDLK_LEFT:
				xVel -= CH_WIDTH / 2;
				break;
            case SDLK_RIGHT:
				xVel += CH_WIDTH / 2;
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
				yVel += CH_HEIGHT / 2;
				break;
            case SDLK_DOWN:
				yVel -= CH_HEIGHT / 2;
				break;
            case SDLK_LEFT:
				xVel += CH_WIDTH / 2;
				break;
            case SDLK_RIGHT:
				xVel -= CH_WIDTH / 2;
				break;
			default:
				quit = false;
				break;
        }        
    }
	return quit;
}

//Show the Character on the screen
void Character::show( SDL_Surface *screen )
{
	//Define Character BG position before moving to later used this to renew the BG over the character in case of mouvment
	_character_bg[0].w = CH_WIDTH;
    _character_bg[0].h = CH_HEIGHT;
	_character_bg[0].x = x;
	_character_bg[0].y = y;

	//Clear Character off the screen by adding the BG over him
	apply_surface(x, y, _background, _screen, &_character_bg[0]);
						
    //Move the Character left or right
    x += xVel;
    
    //If the Character went too far to the left or right
    if( ( x < 0 ) || ( x + CH_WIDTH > SCREEN_WIDTH ) )
    {
        //move back
        x -= xVel;    
    }
    
    //Move the Character up or down
    y += yVel;
    
    //If the Character went too far up or down
    if( ( y < 0 ) || ( y + CH_HEIGHT > SCREEN_HEIGHT ) )
    {
        //move back
        y -= yVel;    
    }
    
    //show the Character
	apply_surface(x, y, _characters_list, _screen, &_character[0]);
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
    Character myCharacter;
	Monster myMonster;

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

	//Initial Positions
	/*int _x_pos_character = 250; int _y_pos_character = 200;
	int _x_pos_monster = 180; int _y_pos_monster = 140;*/
	
     //Monster Clip definition range for the top left (Random monster from the 7th line)
    _monster[0].x = 32 * (rand()%8);
	_monster[0].y = 32*6;
    _monster[0].w = 32;
    _monster[0].h = 32;

	//Character Clip definition range for the top left
    _character[0].x = 5*CH_WIDTH;
    _character[0].y = 3*CH_HEIGHT;
    _character[0].w = CH_WIDTH;
    _character[0].h = CH_HEIGHT;

	//Character Background Clip definition range for the top left
   /*_character_bg[0].x = _x_pos_character;
    _character_bg[0].y = _y_pos_character;
    _character_bg[0].w = 32;
    _character_bg[0].h = 32;*/
	
    //Apply the background to the screen
    apply_surface(0, 0, _background, _screen );
    
    //Apply monsters to the screen
    apply_surface(180, 140, _monsters_list, _screen, &_monster[0]);

    //Apply character to the screen
	//apply_surface(_x_pos_character, _y_pos_character, _characters_list, _screen, &_character[0]);

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


 //   //Loop until close of the windows using the cross or escape key
	//while( quit == false )
	//{
	//	//While there's an event to handle
	//	while( SDL_PollEvent( &event ) )
	//	{
	//		//Keyboard Management variable initialisation
	//		SDLKey _KeySym = event.key.keysym.sym;
	//
	//		//Define Character BG position before moving to later used this to renew the BG over the character in case of mouvment
	//		_character_bg[0].x = myCharacter.x;
	//		_character_bg[0].y = myCharacter.y;

	//		//When a Key is pressed
	//		if( event.type == SDL_KEYDOWN ) {
	//			//Check which key is pressed than act accordingly
	//			switch( _KeySym ) {
	//				
	//				//Up Key Pressed
	//				case SDLK_UP:
	//					//Clear Character off the screen by adding the BG over him
	//					apply_surface(_x_pos_character, _y_pos_character, _background, _screen, &_character_bg[0]);

	//					/*//Diagonal check
	//					if(_KeySym = SDLK_LEFT)
	//						_x_pos_character = _x_pos_character - 32;
	//					if(_KeySym = SDLK_RIGHT)
	//						_x_pos_character = _x_pos_character + 32;*/

	//					//Move the character on the screen
	//					_y_pos_character = _y_pos_character - 32;
	//					apply_surface(_x_pos_character, _y_pos_character, _characters_list, _screen, &_character[0]);
	//					
	//					//Update Screen
	//					if( SDL_Flip(_screen) == -1 )
	//					{
	//						printf("Failed to update the screen");
	//						return 1;    
	//					}
	//					break;
	//				
	//				//Down Key Pressed
	//				case SDLK_DOWN:
	//					//Clear Character off the screen by adding the BG over him
	//					apply_surface(_x_pos_character, _y_pos_character, _background, _screen, &_character_bg[0]);

	//					/*//Diagonal check
	//					if(_KeySym = SDLK_LEFT)
	//						_x_pos_character = _x_pos_character - 32;
	//					if(_KeySym = SDLK_RIGHT)
	//						_x_pos_character = _x_pos_character + 32;*/

	//					//Move the character on the screen
	//					_y_pos_character = _y_pos_character + 32;
	//					apply_surface(_x_pos_character, _y_pos_character, _characters_list, _screen, &_character[0]);
	//					
	//					//Update Screen
	//					if( SDL_Flip(_screen) == -1 )
	//					{
	//						printf("Failed to update the screen");
	//						return 1;    
	//					}
	//					break;

	//				//Left Key Pressed
	//				case SDLK_LEFT:
	//					//Clear Character off the screen by adding the BG over him
	//					apply_surface(_x_pos_character, _y_pos_character, _background, _screen, &_character_bg[0]);

	//					/*//Diagonal check
	//					if(_KeySym = SDLK_UP)
	//						_y_pos_character = _y_pos_character - 32;
	//					if(_KeySym = SDLK_DOWN)
	//						_y_pos_character = _y_pos_character + 32;*/

	//					//Move the character on the screen
	//					_x_pos_character = _x_pos_character - 32;
	//					apply_surface(_x_pos_character, _y_pos_character, _characters_list, _screen, &_character[0]);
	//					
	//					//Update Screen
	//					if( SDL_Flip(_screen) == -1 )
	//					{
	//						printf("Failed to update the screen");
	//						return 1;    
	//					}
	//					break;

	//				//Right Key Pressed
	//				case SDLK_RIGHT:
	//					//Clear Character off the screen by adding the BG over him
	//					apply_surface(_x_pos_character, _y_pos_character, _background, _screen, &_character_bg[0]);
	//					
	//					/*//Diagonal check
	//					if(_KeySym = SDLK_UP)
	//						_y_pos_character = _y_pos_character - 32;
	//					if(_KeySym = SDLK_DOWN)
	//						_y_pos_character = _y_pos_character + 32;*/

	//					//Move the character on the screen
	//					_x_pos_character = _x_pos_character + 32;
	//					apply_surface(_x_pos_character, _y_pos_character, _characters_list, _screen, &_character[0]);
	//					
	//					//Update Screen
	//					if( SDL_Flip(_screen) == -1 )
	//					{
	//						printf("Failed to update the screen");
	//						return 1;    
	//					}
	//					break; 

	//				//Esc Key Pressed
	//				case SDLK_ESCAPE:
	//					quit = true;
	//					break;

	//				//Default:,do not quit !
	//				default:
	//					quit = false;
	//					break;
	//			}
	//		}
	//		
	//		//When a Key is released
	//		else if( event.type == SDL_KEYUP ) {
	//		//Nothing for the moment 
	//		}
	//		//When the windows is closed
	//		else if( event.type == SDL_QUIT )
	//		{
	//			//Quit the program
	//			quit = true;
	//		}
	//	}
	//}

    //Clean everything before exit the program
	Clean_Up();
	    
    //Quit SDL
	SDL_Quit();

    return 0;    
}

