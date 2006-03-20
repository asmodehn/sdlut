#include "Project0.hh"

//The VideoSurfaces that will be used
//SDL_Surface *_screen = NULL;

VideoSurface *_screen = NULL;
RGBSurface Background;

//Background Clip
Rect BG_Clip[1];

//The event structure that will be used
SDL_Event event;

//engine Class : No idea whats used for but neccessary for mainloop
class TheEngine : public Engine
{
private:
	Monster_Factory* myMonster_Factory;
	Character_Base* myCharacter;
	//Monster vector which will contains all monsters
	std::vector<Monster*> Monster_vector;

public:
	VideoSurface *_screen;

    TheEngine()
    {
		P0_Logger << " \nTheEngine Creator Used\n " << std::endl;
    }

    virtual ~TheEngine(){}

    bool init(int width, int height)
    {
		//Create rgbsurface that will be the BG with white color as transparent
		Background = RGBSurface("data/tankbrigade.bmp", Color(0xFF, 0xFF, 0xFF));
		//Background.setColorKey((0xFF, 0xFF, 0xFF));
		P0_Logger << " Background Surface Loaded : OK " << std::endl;

		//Initialize the factory
		myMonster_Factory = new Monster_Factory(INITIAL_MONSTERS, _screen);
		P0_Logger << " Monster Factory Init: OK " << std::endl;

		//Create all the monsters
		Monster_vector = myMonster_Factory->Create_Monsters(CH_INITIAL_X, CH_INITIAL_Y);
		P0_Logger << " Monster Vector Fill: OK " << std::endl;

		//Create Character & initialized it
		myCharacter = new Character_Base(CH_INITIAL_X, CH_INITIAL_Y, _screen, Monster_vector);
		//Character<Monster*>* myCharacter = new Character<Monster*>(192, 224, _screen, Monster_vector);
		P0_Logger << " Character Creation: OK " << std::endl;
		
		//Init of the character (surface, msgs)
		if( myCharacter->Init() == false)
		{
			P0_Logger << " Character Init Failed... " << std::endl;
			Timer::delay(2000);
			return 1;
		}
		P0_Logger << " Character Init: OK " << std::endl;

		P0_Logger << " \nEngine Init Successfully\n " << std::endl;
		return true;
	}

    bool resize(int width, int height)
    { return true; }

    //The mainloop will loop using this method and so will generate everything that is displayed because the screen is flip automaticly with at the end of each cycle
	bool render(void) const
    {
		//The frames rate regulator
		Timer fps;

		//Start the FPS management
        fps.start();

		/*****PRE RENDER*****/

		//Update the graphic style of the character
		myCharacter->Update_Graphic_Style();

		//Move the character
		myCharacter->move();

		//Handle attacks
		int Character_Hit_Distance = myCharacter->attack();

		//Remove Dead monsters from the vector and inform the character 
		//Monster_vector = myMonster_Factory->Remove_Dead_Monsters();
		myCharacter->Update_Monster_Knowledge(Monster_vector);

		//Move Monsters
		myMonster_Factory->Move_Monsters(myCharacter->collision_box);

		//Set the camera
        myCharacter->following_camera();

		/*****RENDER*****/

		//Generate the background to the screen
		generate_bg();

		//Show the Character on the screen
		myCharacter->move_animation();
		
		//Show character attack animation
		myCharacter->attack_animation(Character_Hit_Distance);

		//Apply monsters to the screen
		myMonster_Factory->Move_Monsters_Animation(myCharacter->Camera);

		//Flip

		/*****POST RENDER*****/

		//Eventually generate new monster and inform the character
		//Monster_vector = myMonster_Factory->Generate_New_Monster( myCharacter->collision_box.getx(), myCharacter->collision_box.gety() );
		myCharacter->Update_Monster_Knowledge(Monster_vector);

		/*****END RENDER*****/

		//Cap the frame rate
        while( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //wait    
        }


		P0_Logger << " \n TheEngine Render Used\n " << std::endl;
	
		return true;
    }

	Character_Base* Get_Character()
	{
		return myCharacter;
	}
};

//Generate Background
void generate_bg()
{
	int i=0, j=0;
	while (i<(SCREEN_WIDTH/32))
	{
		while (j<(SCREEN_HEIGHT/32 - 1)) //the -1 is here in order to not apply bg on the last line of the screen: the status bar
		{
			if (! _screen->blit(Background, Point::Point(i*32, j*32), BG_Clip[0]) )
			//apply_surface(i*32, j*32, _background, _screen, &_bg[0]);
			{
				P0_Logger << " Background Generation Failed " << GetError() << std::endl;
			}
			j++;
		}
		i++;
		j=0;
	}
	//P0_Logger << " Background Generation : OK " << std::endl;
}
//Initialization of the windows, SDL, SDL_TTF, the surface
bool InitEverything()
{
	//Set windows name
	App::getInstance().setName("Project 0 - 2D - v0.01");
	//SDL_WM_SetCaption( "Project 0 - 2D - v0.01", NULL );

	//Initialize SDL Video
    if (! App::getInstance().initVideo(false,false,false,false) )
		//SDL_Init( SDL_INIT_EVERYTHING )
	{
		P0_Logger << " SDL Init Video Failed : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << " Init Video : OK " << std::endl;

	//Create the screen surface
	_screen = App::getInstance().getWindow()->resetDisplay(SCREEN_WIDTH, SCREEN_HEIGHT);
	//_screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	if (_screen == NULL  )
	{
		P0_Logger << " Create Surface Failed : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << " Video Surface Creation : OK " << std::endl;

	//Initialize SDL_ttf
	if (! App::getInstance().initText())
		//if( TTF_Init() == -1 )
    {
		P0_Logger << " TTF Error : " << GetError(TTF) << std::endl;
        return false;
    }
	P0_Logger << " TTF Init : OK " << std::endl;

    //If eveything loads fine
    return true;    
}
//Load Images Files
void Load_Files()
{
	//Create rgbsurface that will be the BG with white color as transparent
	Background = RGBSurface("data/tankbrigade.bmp", Color(0xFF, 0xFF, 0xFF));
	//Background.setColorKey((0xFF, 0xFF, 0xFF));
	P0_Logger << " Background Surface Loaded : OK " << std::endl;
  
}
//Clean Up Surface
void Clean_Up()
{
	//Background.~RGBSurface();
	//SDL_FreeSurface(_background);
	//SDL_FreeSurface(_screen);
	//delete _screen;
}

//Main
int main( int argc, char* args[] )
{
	//Init the rand method using the current time in order to generate more random number
	srand( (unsigned)time( NULL ) );

	//Make sure the program waits for a quit
	bool quit = false;

	//Background Clip definition range from the top left
	BG_Clip->setx(198);
	BG_Clip->sety(132);
	BG_Clip->setw(32);
	BG_Clip->seth(32);

	//Create the windows and init everything (SDL, SDL_TTF, ...)
	if( InitEverything() == false )
	{ 
		P0_Logger << " Init Windows failed... " << std::endl;
		Timer::delay(2000);
		//SDL_Delay(2000);
		return 1;
	}
	P0_Logger << "-> Windows, SDL, SDL_TTF And VideoSurface Where Initialized Successfully <-" << std::endl;

	//Create the game engine, initialized it and affect it to the windows
	TheEngine* myEngine = new TheEngine();
	App::getInstance().getWindow()->setEngine(myEngine);

	//Create the keyboard input management, inform it of the character and then affect the keyboard management to the windows
    KeyboardInput myKeyboardInput;
	myKeyboardInput.Character_Knowledge(myEngine->Get_Character());
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&myKeyboardInput);


	//Launch the mainloop that will use the render method of the Engine and so will render the screen and will manage all events
	App::getInstance().getWindow()->mainLoop();


	/*if(SDLNet_Init()==-1) {
		P0_Logger << " SDL_Net Init Failed " << std::endl;
		return 1;
	}
	P0_Logger << " SDL_Net Init : OK " << std::endl;*/

	//Loop until close of the windows using the cross or escape key
	/*while(quit == false)
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
			//immediate leave when quit = true, no need for further treatment as the user want to quit
			if (quit == true) {break;}
		}

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
		myMonster_Factory->Move_Monsters_Animation(myCharacter->Camera);

		//Update the screen
		if( SDL_Flip(_screen) == -1 )
		{
			return 1;    
		}
		//Update the whole screen
		if (! Screen->update() )
		//SDL_Flip(_screen)
		//SDL_UpdateRect(_screen, 0, 0, 0, 0);
		{
			return 1;    
		}

		//Eventually generate new monster and inform the character
		Monster_vector = myMonster_Factory->Generate_New_Monster( myCharacter->collision_box.getx(), myCharacter->collision_box.gety() );
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
	//myMonster_Factory->~Monster_Factory();
	//myCharacter->~Character_Base();*/
	//Clean_Up();
	
	//Quit SDl_NEt
	//SDLNet_Quit();

    //Quit SDL
	//SDL_Quit();

    return 0;    
}

