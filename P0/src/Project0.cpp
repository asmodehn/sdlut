#include "Project0.hh"

//The surfaces that will be used
SDL_Surface *_background = NULL;
SDL_Surface *_screen = NULL;

//Background Clip
SDL_Rect _bg[1];

//The event structure that will be used
SDL_Event event;

//Gnerate Background
void generate_bg()
{
	int i=0, j=0;
	while (i<(SCREEN_WIDTH/32))
	{
		while (j<(SCREEN_HEIGHT/32-1)) //the -1 is here in order to not apply bg on the last line of the screen: the status bar
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

	//Initialize SDL_ttf
    if( TTF_Init() == -1 )
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

	//The frames rate regulator
    Timer fps;

	//Initialize
	if( InitWindows() == false )
	{ 
		printf("Init Windows failed\n");
		SDL_Delay(2000);
		return 1;
	}
	//Load the files
	if( Load_Files() == false )
	{
		printf("File load failed\n");
		SDL_Delay(2000);
		return 1;
	}

	//Monster vector which will contains all monsters
	std::vector<Monster*> Monster_vector;

	int number_of_monster = 20;
	for(int i=0; i < number_of_monster; i++)
	{
		//Create Monster & initialized it
		Monster* myMonster = new Monster(32 * random(0,39), 32 * random(0,39), _screen);
		if( myMonster->Init() == false)
		{
			printf("Init Monster failed\n");
			SDL_Delay(2000);
			return 1;
		}

		//store the monster at the end of the vector
		Monster_vector.push_back(myMonster);
					
	}

	//Create Character & initialized it
    Character* myCharacter = new Character(192, 224, _screen, Monster_vector);
	//Character<Monster*>* myCharacter = new Character<Monster*>(192, 224, _screen, Monster_vector);
		
	if( myCharacter->Init() == false)
	{
		printf("Init Character failed\n");
		SDL_Delay(2000);
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
		myCharacter->move();

		//Handle attacks
		myCharacter->attack();

		//Move Monsters
		for(int i=0; i < Monster_vector.size(); i++)
		{
			Monster_vector[i]->move(myCharacter->collision_box);		
		}

		//Set the camera
        myCharacter->following_camera();

		//Generate the background to the screen
		generate_bg();
		//Fill the screen white
		//SDL_FillRect( _screen, &_screen->clip_rect, SDL_MapRGB( _screen->format, 0xFF, 0xFF, 0xFF ) );

		//Show the Character on the screen
		myCharacter->move_animation();
		
		//Show character attack animation
		myCharacter->attack_animation();

		//Apply monsters to the screen
		for(int i=0; i < Monster_vector.size(); i++)
		{
			Monster_vector[i]->move_animation(myCharacter->camera);		
		}

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
	
	//Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
	SDL_Quit();

    return 0;    
}

