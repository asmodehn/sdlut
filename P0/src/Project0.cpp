
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

//The event structure that will be used
SDL_Event event;

//The portions of the sprite map to be blitted
SDL_Rect _monster[1];
SDL_Rect _character[1];

//Create surface from an image function and optimized image to the desired format
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
            //Set all pixels of color 0x00FFFF to be transparent
            SDL_SetColorKey( optimizedSurface, SDL_RLEACCEL | SDL_SRCCOLORKEY, 0x00FFFF );
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
bool Init()
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
//
//
//
//Clean All
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
	if( Init() == false ) { return 1; }
	//Load the files
	if( Load_Files() == false ) { return 1; }

	
     //Monster Clip definition range for the top left (Random monster from the 5th line)
    _monster[0].x = 32 * (rand()%8);
	_monster[0].y = 32*6;
    _monster[0].w = 32;
    _monster[0].h = 32;

	//Monster Clip definition range for the top left
    _character[0].x = 5*32;
    _character[0].y = 3*32;
    _character[0].w = 32;
    _character[0].h = 32;

    //Apply the background to the screen
    apply_surface(0, 0, _background, _screen );
    
    //Apply monsters to the screen
    apply_surface(180, 140, _monsters_list, _screen, &_monster[0]);

    //Apply character to the screen
	apply_surface(250, 200, _characters_list, _screen, &_character[0]);

    //Update the screen
    if( SDL_Flip(_screen) == -1 )
    {
        return 1;    
    }


    //Loop until close of the windows using the cross
	while( quit == false )
	{
		//While there's an event to handle
		while( SDL_PollEvent( &event ) )
		{
		//If the user has Xed out the window
			if( event.type == SDL_QUIT )
			{
				//Quit the program
				quit = true;
			}
		}
	}

    //Clean everything before exit the program
	Clean_Up();
	    
    //Quit SDL
    SDL_Quit();
    
    return 0;    
}

