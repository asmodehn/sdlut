
#include "SDL.hh"
//#include "SDL_image.h"
#include <string>

//The attributes of the window
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

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

//Initialisation
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
//Main
int main( int argc, char* args[] )
{
	//Make sure the program waits for a quit
	bool quit = false;

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
	int _x_pos_character = 250; int _y_pos_character = 200;
	int _x_pos_monster = 180; int _y_pos_monster = 140;
	
     //Monster Clip definition range for the top left (Random monster from the 7th line)
    _monster[0].x = 32 * (rand()%8);
	_monster[0].y = 32*6;
    _monster[0].w = 32;
    _monster[0].h = 32;

	//Character Clip definition range for the top left
    _character[0].x = 5*32;
    _character[0].y = 3*32;
    _character[0].w = 32;
    _character[0].h = 32;

	//Character Background Clip definition range for the top left
    _character_bg[0].x = _x_pos_character;
    _character_bg[0].y = _y_pos_character;
    _character_bg[0].w = 32;
    _character_bg[0].h = 32;

    //Apply the background to the screen
    apply_surface(0, 0, _background, _screen );
    
    //Apply monsters to the screen
    apply_surface(_x_pos_monster, _y_pos_monster, _monsters_list, _screen, &_monster[0]);

    //Apply character to the screen
	apply_surface(_x_pos_character, _y_pos_character, _characters_list, _screen, &_character[0]);

    //Update the screen
    if( SDL_Flip(_screen) == -1 )
    {
        return 1;    
    }


    //Loop until close of the windows using the cross or escape key
	while( quit == false )
	{
		//While there's an event to handle
		while( SDL_PollEvent( &event ) )
		{
			//Keyboard Management variable initialisation
			const Sym &s
			SDL_KeyboardEvent *key = &event.key;			//Key pressed
			SDLMod modifier = key->keysym.mod;				//Modifiers
			Uint8 *keystates = SDL_GetKeyState( NULL );		//Keys State

			//Switch witch test if there is an event
			switch(event.type)
			{
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					
					//Define Character BG position before moving to later used this to renew the BG over the character in case of mouvment
					_character_bg[0].x = _x_pos_character;
					_character_bg[0].y = _y_pos_character;

					//Print Key state: pressed or released
					if (key->type == SDL_KEYUP)
					{ printf("RELEASED: "); }
					else
					{ printf("PRESSED: "); }

					//Print all modifiers: alt, ctrl, ...
					if( modifier & KMOD_NUM ) printf( "NUMLOCK " );
					if( modifier & KMOD_CAPS ) printf( "CAPSLOCK " );
					if( modifier & KMOD_MODE ) printf( "MODE " );
					if( modifier & KMOD_LCTRL ) printf( "LCTRL " );
					if( modifier & KMOD_RCTRL ) printf( "RCTRL " );
					if( modifier & KMOD_LSHIFT ) printf( "LSHIFT " );
					if( modifier & KMOD_RSHIFT ) printf( "RSHIFT " );
					if( modifier & KMOD_LALT ) printf( "LALT " );
					if( modifier & KMOD_RALT ) printf( "RALT " );
					if( modifier & KMOD_LMETA ) printf( "LMETA " );
					if( modifier & KMOD_RMETA ) printf( "RMETA " );

					//Print key pressed
					printf( "%s\n", SDL_GetKeyName(key->keysym.sym));
	

					//Check the keystates
					if( keystates[ SDLK_ESCAPE ] )
					{
						quit = true;
					}
					if( keystates[SDLK_UP])
						{
							//Clear Character off the screen by adding the BG over him
							apply_surface(_x_pos_character, _y_pos_character, _background, _screen, &_character_bg[0]);

							//Diagonal check
							if( keystates[SDLK_LEFT])
								_x_pos_character = _x_pos_character - 32;
							if( keystates[SDLK_RIGHT])
								_x_pos_character = _x_pos_character + 32;

							//Move the character on the screen
							_y_pos_character = _y_pos_character - 32;
							apply_surface(_x_pos_character, _y_pos_character, _characters_list, _screen, &_character[0]);
							
							//Update Screen
							if( SDL_Flip(_screen) == -1 )
							{
								printf("Failed to update the screen");
								return 1;    
							}
							keystates = SDL_GetKeyState( NULL );
							break;
						}
					if( keystates[SDLK_DOWN])
						{
							//Clear Character off the screen by adding the BG over him
							apply_surface(_x_pos_character, _y_pos_character, _background, _screen, &_character_bg[0]);

							//Diagonal check
							if( keystates[SDLK_LEFT])
								_x_pos_character = _x_pos_character - 32;
							if( keystates[SDLK_RIGHT])
								_x_pos_character = _x_pos_character + 32;

							//Move the character on the screen
							_y_pos_character = _y_pos_character + 32;
							apply_surface(_x_pos_character, _y_pos_character, _characters_list, _screen, &_character[0]);
							
							//Update Screen
							if( SDL_Flip(_screen) == -1 )
							{
								printf("Failed to update the screen");
								return 1;    
							}
							keystates = SDL_GetKeyState( NULL );
							break;
						}
					if( keystates[SDLK_RIGHT] &! keystates[SDLK_UP] &! keystates[SDLK_DOWN])
						{
							//Clear Character off the screen by adding the BG over him
							apply_surface(_x_pos_character, _y_pos_character, _background, _screen, &_character_bg[0]);

							//Move the character on the screen
							_x_pos_character = _x_pos_character + 32;
							apply_surface(_x_pos_character, _y_pos_character, _characters_list, _screen, &_character[0]);
							
							//Update Screen
							if( SDL_Flip(_screen) == -1 )
							{
								printf("Failed to update the screen");
								return 1;    
							}
							keystates = SDL_GetKeyState( NULL );
							break;
						}
					if( keystates[SDLK_LEFT] &! keystates[SDLK_UP] &! keystates[SDLK_DOWN])
						{
							//Clear Character off the screen by adding the BG over him
							apply_surface(_x_pos_character, _y_pos_character, _background, _screen, &_character_bg[0]);

							//Move the character on the screen
							_x_pos_character = _x_pos_character - 32;
							apply_surface(_x_pos_character, _y_pos_character, _characters_list, _screen, &_character[0]);
							
							//Update Screen
							if( SDL_Flip(_screen) == -1 )
							{
								printf("Failed to update the screen");
								return 1;    
							}
							keystates = SDL_GetKeyState( NULL );
							break;
						}

					break;
				//If the user has Xed out the window
				case SDL_QUIT:
					quit = true;
					break;
				//Default: do not quit !
				default:
					quit = false;
					break;
			}
		}
	}

    //Clean everything before exit the program
	Clean_Up();
	    
    //Quit SDL
	SDL_Quit();

    return 0;    
}

