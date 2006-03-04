#include "Project0.hh"

//The surfaces that will be used
//SDL_Surface *_monsters_list = NULL;
//SDL_Surface *_characters_list = NULL;
SDL_Surface *_background = NULL;
SDL_Surface *_screen = NULL;

//The portions of the sprite map to be blitted
//SDL_Rect _monster[1];

//SDL_Rect _character_right_attack[3];
//SDL_Rect _character_left_attack[3];
//SDL_Rect _character_down_attack[3];
//SDL_Rect _character_up_attack[3];

SDL_Rect _bg[1];


//Collisions Box
//SDL_Rect Character_collision_box;
//SDL_Rect Monster_collision_box;

//The event structure that will be used
SDL_Event event;

//Camera def initialized in the top right corner and with the width and height of the screen
//SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};


//Create surface from an image function and optimized image to the desired format with white color as transparent color
SDL_Surface *create_surface( std::string filename ) 
{
    //Temporary storage for the Surface that's loaded
    SDL_Surface* loadedSurface = NULL;
    
    //The optimized Surface that will be used
    SDL_Surface* optimizedSurface = NULL;
    
    //Load the image
    //loadedSurface = SDL_LoadBMP( filename.c_str() );
	loadedSurface = IMG_Load( filename.c_str() );
    
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
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
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

    _background = create_surface( "data/tankbrigade.bmp" );
 	if( _background == NULL ) { return false; }
    
    //If eveything loaded fine
    return true;    
}
//Clean Up Surface
void Clean_Up()
{
	SDL_FreeSurface(_background);
	SDL_FreeSurface(_screen);
}

//Main
int main( int argc, char* args[] )
{
	//Make sure the program waits for a quit
	bool quit = false;

	//Camera initial Definition
	//camera.x = 0;
	//camera.y = 0;
	//camera.w = SCREEN_WIDTH;
	//camera.h = SCREEN_HEIGHT;
	
	//Create Character & check if nothing went wrong
    Character* myCharacter = new Character(192, 224);
	if( myCharacter->Init() == false) {
		printf("Init Character failed");
		return 1;
	}

	//Create Monster & check if nothing went wrong
	Monster* myMonster = new Monster(224, 224);
	if( myMonster->Init() == false) {
		printf("Init Monster failed\n");
		return 1;
	}


	//Collisions Box to check if monster collide with npc or npc collide with monster
	//Character_collision_box = myCharacter.collision_box;
	//Monster_collision_box = myMonster.collision_box;

	//The frames rate regulator
    Timer fps;

	//Initialize
	if( InitWindows() == false ) { 
		printf("Init failed\n");
		return 1;
	}
	//Load the files
	if( Load_Files() == false ) {
		printf("File load failed\n");
		return 1;
	}

	//Background Clip definition range for the top left ()
    _bg[0].x = 198;
	_bg[0].y = 132;
    _bg[0].w = 32;
    _bg[0].h = 32;

	    
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
			quit = myCharacter->input_mgt(event);

			//Window closed
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
		}

		//Move the character
		myCharacter->move(myMonster->collision_box);

		//Update Character Collisions Box after move
		//Character_collision_box = myCharacter.collision_box;

		//Handle attacks
		myCharacter->attack(myMonster->collision_box);

		//Move the Monster
		myMonster->move(myCharacter->collision_box);

		//Update Monster Collisions Box after move
		//Monster_collision_box = myMonster.collision_box;

		//Set the camera
        myCharacter->following_camera();

		//Generate the background to the screen
		generate_bg();
		//apply_surface(0, 0, _background, _screen, &camera );
		//Fill the screen white
		//SDL_FillRect( _screen, &_screen->clip_rect, SDL_MapRGB( _screen->format, 0xFF, 0xFF, 0xFF ) );

		//Show the Character on the screen
		myCharacter->move_animation(_screen);
		
		//Show character attack animation
		myCharacter->attack_animation(_screen);

		//Apply monsters to the screenn
		myMonster->move_animation(_screen, myCharacter->camera);

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
	//delete myCharacter;
	//delete myMonster;
	Clean_Up();
	    
    //Quit SDL
	SDL_Quit();

    return 0;    
}

