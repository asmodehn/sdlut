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
	//Set windows name
	RAGE::SDL::App::getInstance().setName("Project 0 - 2D - v0.01");
	//SDL_WM_SetCaption( "Project 0 - 2D - v0.01", NULL );

	//Initialize SDL Video
    if (! RAGE::SDL::App::getInstance().initVideo(false,false,false,false) )
		//SDL_Init( SDL_INIT_EVERYTHING )
	{
        return false;
    }

	//Create the screen surface
	if (! RAGE::SDL::App::getInstance().getWindow()->reset(SCREEN_WIDTH, SCREEN_HEIGHT) )
		//_screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	{
        return false;
    }

	//Get a pointer to the SDL surface currently displayed
	_screen = SDL_GetVideoSurface();
	if( _screen == NULL )
    {
		P0_Logger << " Get Video Surface Failed : " << SDL_GetError() << std::endl;
        return false;
    }
	P0_Logger << " Get Video Surface : OK " << std::endl;

	//Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
		P0_Logger << " TTF Error : " << TTF_GetError() << std::endl;
        return false;
    }
	P0_Logger << " TTF Init : OK " << std::endl;



    //If eveything loads fine
    return true;    
}
//Load Images Files
bool Load_Files()
{

    _background = create_surface( "data/tankbrigade.bmp", 0xFFFFFF );
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
		P0_Logger << " Init Windows failed... " << std::endl;
		SDL_Delay(2000);
		return 1;
	}
	P0_Logger << " Windows Init: OK " << std::endl;

	//Load the files
	if( Load_Files() == false )
	{
		P0_Logger << " Loading File Failed... " << std::endl;
		SDL_Delay(2000);
		return 1;
	}
	P0_Logger << " File Load: OK " << std::endl;

	//Monster vector which will contains all monsters
	std::vector<Monster*> Monster_vector;
	P0_Logger << " Monster Vector Creation: OK " << std::endl;

	//Initialize the factory
	Monster_Factory* myMonster_Factory = new Monster_Factory(INITIAL_MONSTERS, _screen);
	P0_Logger << " Monster Factory Init: OK " << std::endl;

	//Create all the monsters
	Monster_vector = myMonster_Factory->Create_Monsters(CH_INITIAL_X, CH_INITIAL_Y);
	P0_Logger << " Initial Monster Creation: OK " << std::endl;

	//Create Character & initialized it
    Character_Base* myCharacter = new Character_Base(CH_INITIAL_X, CH_INITIAL_Y, _screen, Monster_vector);
	//Character<Monster*>* myCharacter = new Character<Monster*>(192, 224, _screen, Monster_vector);
	P0_Logger << " Character Creation: OK " << std::endl;
	
	//Init of the character (surface, msgs)
	if( myCharacter->Init() == false)
	{
		P0_Logger << " Character Init Failed... " << std::endl;
		SDL_Delay(2000);
		return 1;
	}
	P0_Logger << " Character Init: OK " << std::endl;


	//Background Clip definition range for the top left ()
    _bg[0].x = 198;
	_bg[0].y = 132;
    _bg[0].w = 32;
    _bg[0].h = 32;

	    
	/*//Update the screen
    if( SDL_Flip(_screen) == -1 )
    {
        return 1;    
    }*/

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
		//quit = RAGE::SDL::App::getInstance().getWindow()->mainLoop();

		//Update the graphic style of the character
		myCharacter->Update_Graphic_Style();

		//Move the character
		myCharacter->move();

		//Handle attacks
		int Character_Hit_Distance = myCharacter->attack();

		//Remove Dead monsters from the vector and inform the character 
		Monster_vector = myMonster_Factory->Remove_Dead_Monsters();
		myCharacter->Update_Monster_Knowledge(Monster_vector);

		//Move Monsters
		myMonster_Factory->Move_Monsters(myCharacter->collision_box);

		//Set the camera
        myCharacter->following_camera();

		//Generate the background to the screen
		generate_bg();

		//Show the Character on the screen
		myCharacter->move_animation();
		
		//Show character attack animation
		myCharacter->attack_animation(Character_Hit_Distance);

		//Apply monsters to the screen
		myMonster_Factory->Move_Monsters_Animation(myCharacter->camera);

		//Update the screen
		if( SDL_Flip(_screen) == -1 )
		{
			return 1;    
		}

		//Eventually generate new monster and inform the character
		Monster_vector = myMonster_Factory->Generate_New_Monster(myCharacter->collision_box.x, myCharacter->collision_box.y);
		myCharacter->Update_Monster_Knowledge(Monster_vector);

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

