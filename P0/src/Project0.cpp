#include "Project0.hh"

//Initialization of the windows, SDL, SDL_TTF, the surface
bool InitEverything()
{
	//Set windows name
	App::getInstance().setName("Project 0 - 2D - v0.02");
	//SDL_WM_SetCaption( "Project 0 - 2D - v0.01", NULL );

	//Initialize SDL Video
    if (! App::getInstance().initVideo(false,false,true,false) )
		//SDL_Init( SDL_INIT_EVERYTHING )
	{
		P0_Logger << " SDL Init Video Failed : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << " Init Video : OK " << std::endl;

	if (! App::getInstance().initTimer() )
	{
		P0_Logger << " SDL Init Timer Failed : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << " Init Timer : OK " << std::endl;

	//Initialize SDL_ttf
	if (! App::getInstance().initText())
		//if( TTF_Init() == -1 )
    {
		P0_Logger << " TTF Error : " << TTF::GetError() << std::endl;
        return false;
    }
	P0_Logger << " TTF Init : OK " << std::endl;

	//Create the video surface aka the display
	if (App::getInstance().getWindow()->resetDisplay(SCREEN_WIDTH, SCREEN_HEIGHT) == NULL  )
	{
		P0_Logger << " Create Surface Failed : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << " Video Surface Creation : OK " << std::endl;

	//Enable timer
	App::getInstance().initTimer();

    //If eveything loads fine
    return true;    
}
//Main
int main( int argc, char* args[] )
{
try { //global error management
	
	//Init the rand method using the current time in order to generate more random numbers
	srand( (unsigned)time( NULL ) );


	/********INIT********/
	//Create the windows and init everything (SDL, SDL_TTF, ...)
	if( InitEverything() == false )
	{ 
		P0_Logger << " Init Windows failed... " << std::endl;
		Delay(2000);
		//SDL_Delay(2000);
		return 1;
	}
	P0_Logger << "-> Windows, SDL, SDL_TTF And VideoSurface Where Initialized Successfully <-" << std::endl;
	

	/********Classes Instanciation & Initialization********/
	//Create the keyboard instance that will managed input
	KeyboardInput myKeyboardInput;
	//myKeyboardInput.enableKeyRepeat(10,500);

	//Instanciate the timers class
	Daemons* myDaemons = new Daemons();

	//Engine instanciation
	Render_Engine* myRender_Engine = new Render_Engine();

	//Initialize the BackGround
	BackGround* myBackGround = new BackGround();
	P0_Logger << " BackGround Init: OK " << std::endl;
	myRender_Engine->Set_BackGround(myBackGround); //inform the engine class (as background is fixed for the moment)

	//Fill the BackGround vector with all BackGround sprite corresponding to the map file
	std::vector<BattleField_Sprite*> BackGround_Sprite_Vector = myBackGround->BackGround_Vector(); //Vector which will contains all BackGround type and clip
	P0_Logger << " BackGround_Sprite Vector Fill: OK " << std::endl;
	myKeyboardInput.Set_BackGround_Sprite_Vector( BackGround_Sprite_Vector ); //inform the input management
	myDaemons->Set_BackGround_Sprite_Vector( BackGround_Sprite_Vector ); //inform the timer class
	myRender_Engine->Set_BackGround_Sprite_Vector( BackGround_Sprite_Vector ); //inform the timer class (this the only moment where we get informed of the background as background is fixed for the moment)

	//Initialize the Environment
	Environment* myEnvironment = new Environment();
	P0_Logger << " Environment Init: OK " << std::endl;
	myRender_Engine->Set_Environment(myEnvironment); //inform the engine class (as environment is fixed for the moment)

	//Fill the Environment vector with all Environment sprite corresponding to the map file
	std::vector<BattleField_Sprite*> Environment_Sprite_Vector = myEnvironment->Environment_Vector(); //Vector which will contains all Environment items type and clip
	P0_Logger << " Environment_Sprite Vector Fill: OK " << std::endl;
	myKeyboardInput.Set_Environment_Sprite_Vector( Environment_Sprite_Vector );
	myDaemons->Set_Environment_Sprite_Vector( Environment_Sprite_Vector ); 
	myRender_Engine->Set_Environment_Sprite_Vector( Environment_Sprite_Vector ); //inform the timer class (this the only moment where we get informed of the environnement as environment is fixed for the moment)


	//Initialize the skeleton factory
	Monster_Factory<Monster_Skeleton>* Monster_Factory_Skeleton = new Monster_Factory<Monster_Skeleton>(INITIAL_MONSTERS);  //A factory of Monster Skeletons
	P0_Logger << " Skeleton Factory Init: OK " << std::endl;
	myKeyboardInput.Set_Monster_Factory_Skeleton( Monster_Factory_Skeleton );
	myDaemons->Set_Monster_Factory_Skeleton( Monster_Factory_Skeleton );
	myRender_Engine->Set_Monster_Factory_Skeleton( Monster_Factory_Skeleton );

	//Create all the monsters skeletons
	std::vector<Monster_Base*> Monster_Vector_Skeleton = Monster_Factory_Skeleton->Create_Monsters(CH_INITIAL_X, CH_INITIAL_Y, Environment_Sprite_Vector, BackGround_Sprite_Vector);  //Vector which will contains all skeletons
	P0_Logger << " Skeleton Vector Fill: OK " << std::endl;
	myKeyboardInput.Set_Monster_Vector_Skeleton( Monster_Vector_Skeleton );
	myDaemons->Set_Monster_Vector_Skeleton( Monster_Vector_Skeleton );
	
	//Initialize the worm factory
	Monster_Factory<Monster_Worm>* Monster_Factory_Worm = new Monster_Factory<Monster_Worm>(INITIAL_MONSTERS);  //A factory of Monster Worms
	P0_Logger << " Worm Factory Init: OK " << std::endl;
	myKeyboardInput.Set_Monster_Factory_Worm( Monster_Factory_Worm );
	myDaemons->Set_Monster_Factory_Worm( Monster_Factory_Worm );
	myRender_Engine->Set_Monster_Factory_Worm( Monster_Factory_Worm );

	//Create all the monsters worms
	std::vector<Monster_Base*> Monster_Vector_Worm = Monster_Factory_Worm->Create_Monsters(CH_INITIAL_X, CH_INITIAL_Y, Environment_Sprite_Vector, BackGround_Sprite_Vector); //Vector which will contains all skeletons
	P0_Logger << " Worm Vector Fill: OK " << std::endl;
	myKeyboardInput.Set_Monster_Vector_Worm( Monster_Vector_Worm );
	myDaemons->Set_Monster_Vector_Worm( Monster_Vector_Worm );

	//Create Character & initialized it
	Character_Base* myCharacter = new Character_Base(CH_INITIAL_X, CH_INITIAL_Y);
	//Character<Monster*>* myCharacter = new Character<Monster*>(192, 224, _screen, Monster_Vector_Skeleton);
	if( myCharacter->Update_Graphic_Style() == false ) //intialize Character's graphic aspect
	{ 
        P0_Logger << " Character Creation FAILED " << std::endl;
    	Delay(2000);
    	return 1;
    }
    P0_Logger << " Character Creation: OK " << std::endl;
    myKeyboardInput.Set_Character_Base( myCharacter );
	myRender_Engine->Set_Character_Base( myCharacter );
	
	//send character collision box to daemons
	myDaemons->Set_Character_Base(myCharacter);

	//Create the ingame escape menu
	Escape_Menu* EscMenu = new Escape_Menu();
	myKeyboardInput.Set_Esc_Menu( EscMenu );
	myRender_Engine->Set_Esc_Menu( EscMenu );

	//Inform the keyboard of the engine instance
	myKeyboardInput.Set_Render_Engine(myRender_Engine);


	/********DEAMONS CREATION********/
	//Create monster's movement daemons
	Timer<Daemons> myMonster_Factory_Monsters_Moves_Timer; //set definition
	myMonster_Factory_Monsters_Moves_Timer.setInterval( MONSTERS_MOVEMENT_INTERVAL ); //set interval
	myMonster_Factory_Monsters_Moves_Timer.setCallback(myDaemons,&Daemons::Move_Monsters, (void*)NULL); //set callback

	//Create monster's generation daemons
	Timer<Daemons> myMonster_Factory_Monsters_Generation_Timer; //set definition
	myMonster_Factory_Monsters_Generation_Timer.setInterval( MONSTERS_GENERATION_INTERVAL ); //set interval
	myMonster_Factory_Monsters_Generation_Timer.setCallback(myDaemons,&Daemons::Generate_Monsters, (void*)NULL); //set callback

	//inform the keyboard of daemons process instance
	myKeyboardInput.Set_Daemons(myDaemons);


	/********ENGINE********/
	//Affect the game render engine to the windows
	App::getInstance().getWindow()->setEngine(myRender_Engine);

	//Affect the keyboard instance to the windows
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&myKeyboardInput);


	/********Start Daemons Process********/
	myMonster_Factory_Monsters_Moves_Timer.start(); //monsters movement
	myMonster_Factory_Monsters_Generation_Timer.start(); //monsters generation

	/********Launch the mainloop that will use the render method of the Engine and so will render the screen and will manage all events********/
	App::getInstance().getWindow()->mainLoop(FRAMES_PER_SECOND);


	/********QUIT********/
	/*if(SDLNet_Init()==-1) {
		P0_Logger << " SDL_Net Init Failed " << std::endl;
		return 1;
	}
	P0_Logger << " SDL_Net Init : OK " << std::endl;*/

	//Quit SDL_NEt
	//SDLNet_Quit();

    //Quit SDL
	//SDL_Quit();

    return 0; //no error occured
	
} catch (...) {
    P0_Logger << " Error in Main " << std::endl;
    Delay(2000);
    return 1;
}
}

