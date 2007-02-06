#include "Project0.hh"

//Initialization of the windows, SDL, SDL_TTF, the surface
bool InitEverything()
{
	//Load configuration from ini files
	if (!Set_Config())
	{
		P0_Logger << " Configuration could not been set " << GetError() << std::endl;
        return false;
	}

	//Set window name
	App::getInstance().setName(Window_Name);
	//SDL_WM_SetCaption( "Project 0 - 2D", NULL );

	//Initialize SDL Video
    if (! App::getInstance().initVideo(false,false,true,false) )
		//SDL_Init( SDL_INIT_EVERYTHING )
	{
		P0_Logger << " Init Video Failed : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << " Init Video : OK " << std::endl;

	//Intialize Timer
	if (! App::getInstance().initTimer() )
	{
		P0_Logger << " Init Timer Failed : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << " Init Timer : OK " << std::endl;

	//Initialize SDL_ttf
	if (! App::getInstance().initText())
		//if( TTF_Init() == -1 )
    {
		P0_Logger << " TTF Init Error : " << TTF::GetError() << std::endl;
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

	//Initialize Audio Mixer
	if (!App::getInstance().initAudio())
    {
		P0_Logger << " Audio Init Error : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << " Audio Init : OK " << std::endl;

	//Load Fxs & Musics Sounds Files to the mixer and set there respective channels
	if (!Set_Sounds_Channels())
	{
		P0_Logger << " Mixing Sound Error : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << " Mixing Sound : OK " << std::endl;

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
	KeyboardInput* myKeyboardInput = new KeyboardInput();
	myKeyboardInput->enableKeyRepeat();  //enable key repeat


	//Instanciate the timers class
	Daemons* myDaemons = new Daemons();

	//Engine instanciation
	Render_Engine* myRender_Engine = new Render_Engine();


		/****Battalefield****/
	//Initialize the BackGround
	BackGround* myBackGround = new BackGround();
	P0_Logger << " BackGround Init: OK " << std::endl;
	myRender_Engine->Set_BackGround(myBackGround); //inform the engine class of the background instance (as background is fixed for the moment)

	//Fill the BackGround vector with all BackGround sprite corresponding to the map file
#ifdef _DEBUG //debug mode
	std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector = new std::vector<BattleField_Sprite*>;
#else //rlz mode
	std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector = myBackGround->BackGround_Vector(); //Vector which will contains all BackGround type and clip
#endif
	P0_Logger << " BackGround_Sprite Vector Fill: OK " << std::endl;
	myKeyboardInput->Set_BackGround_Sprite_Vector( BackGround_Sprite_Vector ); //inform the input management
	myDaemons->Set_BackGround_Sprite_Vector( BackGround_Sprite_Vector ); //inform the timer class
	myRender_Engine->Set_BackGround_Sprite_Vector( BackGround_Sprite_Vector ); //inform the timer class (this the only moment where we get informed of the background as background is fixed for the moment)

	//Initialize the Environment
	Environment* myEnvironment = new Environment();
	P0_Logger << " Environment Init: OK " << std::endl;
	myRender_Engine->Set_Environment(myEnvironment); //inform the engine class of the environment instance

	//Fill the Environment vector with all Environment sprite corresponding to the map file
#ifdef _DEBUG //debug mode
	std::vector<BattleField_Sprite*>* Environment_Sprite_Vector = new std::vector<BattleField_Sprite*>;
#else //rlz mode*/
	std::vector<BattleField_Sprite*>* Environment_Sprite_Vector = myEnvironment->Environment_Vector(); //Vector which will contains all Environment items type and clip
#endif
	P0_Logger << " Environment_Sprite Vector Fill: OK " << std::endl;
	myKeyboardInput->Set_Environment_Sprite_Vector( Environment_Sprite_Vector );
	myDaemons->Set_Environment_Sprite_Vector( Environment_Sprite_Vector ); 
	myRender_Engine->Set_Environment_Sprite_Vector( Environment_Sprite_Vector ); //inform the timer class (this the only moment where we get informed of the environnement as environment is fixed for the moment)

			/****NPC****/

			/****Player****/
	//Create player & initialized it
	Player_Base* myPlayer = new Player_Base(CH_INITIAL_X, CH_INITIAL_Y);
	if( myPlayer->Update_Graphic_Style() == false ) //intialize Character's graphic aspect
	{ 
        P0_Logger << " Character Creation FAILED " << std::endl;
    	Delay(2000);
    	return 1;
    }
    P0_Logger << " Character Creation: OK " << std::endl;

	//Vector of players
	std::vector<Character_Base*>* Players_Vector = new std::vector<Character_Base*>;
	Players_Vector->push_back(myPlayer);

	//Vector containing pointers to vector of pointers to monsters
	std::vector< std::vector<Character_Base*> *>* Global_Player_Vector = new std::vector< std::vector<Character_Base*> *>;
	Global_Player_Vector->push_back(Players_Vector);

	myKeyboardInput->Set_Player_Base( myPlayer );
	myKeyboardInput->Set_Global_Player_Vector(Global_Player_Vector);
	myRender_Engine->Set_Player_Base( myPlayer );
	//myRender_Engine->Set_Global_Player_Vector(Global_Player_Vector);
	myDaemons->Set_Global_Player_Vector(Global_Player_Vector);
	myDaemons->Set_Player_Base(myPlayer);

		/****Monsters****/
	//Initialize the skeleton factory
	Monster_Factory<Monster_Skeleton>* Monster_Factory_Skeleton = new Monster_Factory<Monster_Skeleton>(INITIAL_MONSTERS);  //A factory of Monster Skeletons
	P0_Logger << " Skeleton Factory Init: OK " << std::endl;
	myKeyboardInput->Set_Monster_Factory_Skeleton( Monster_Factory_Skeleton );
	myDaemons->Set_Monster_Factory_Skeleton( Monster_Factory_Skeleton );
	myRender_Engine->Set_Monster_Factory_Skeleton( Monster_Factory_Skeleton );

	//Create all the monsters skeletons
	std::vector<Character_Base*>* Monster_Vector_Skeleton = Monster_Factory_Skeleton->Create_Monsters(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector);  //Vector which will contains all skeletons
	P0_Logger << " Skeleton Vector Fill: OK " << std::endl;
	
	//Initialize the worm factory
	Monster_Factory<Monster_Worm>* Monster_Factory_Worm = new Monster_Factory<Monster_Worm>(INITIAL_MONSTERS);  //A factory of Monster Worms
	P0_Logger << " Worm Factory Init: OK " << std::endl;
	myKeyboardInput->Set_Monster_Factory_Worm( Monster_Factory_Worm );
	myDaemons->Set_Monster_Factory_Worm( Monster_Factory_Worm );
	myRender_Engine->Set_Monster_Factory_Worm( Monster_Factory_Worm );

	//Create all the monsters worms
	std::vector<Character_Base*>* Monster_Vector_Worm = Monster_Factory_Worm->Create_Monsters(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector); //Vector which will contains all skeletons
	P0_Logger << " Worm Vector Fill: OK " << std::endl;

	//Vector containing pointers to vector of pointers to monsters
	std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector = new std::vector< std::vector<Character_Base*> *>;
	Global_Monster_Vector->push_back(Monster_Vector_Skeleton);
	Global_Monster_Vector->push_back(Monster_Vector_Worm);

	myKeyboardInput->Set_Global_Monster_Vector(Global_Monster_Vector);
	myDaemons->Set_Global_Monster_Vector(Global_Monster_Vector);

	/*********ENGINE************/

	//Create the ingame escape menu
	Escape_Menu* EscMenu = new Escape_Menu();
	myKeyboardInput->Set_Esc_Menu( EscMenu );
	myRender_Engine->Set_Esc_Menu( EscMenu );

	//Create the victory screen
	Victory_Screen* VictoryScreen = new Victory_Screen();
	myKeyboardInput->Set_Victory_Screen( VictoryScreen );
	myRender_Engine->Set_Victory_Screen(VictoryScreen);

	//Inform the keyboard of the engine instance
	myKeyboardInput->Set_Render_Engine(myRender_Engine);


	/********DEAMONS CREATION********/
	//Create monster's movement daemons
	Timer<Daemons>* myMonster_Factory_Monsters_Moves_Timer = new Timer<Daemons>(); //set definition
	myMonster_Factory_Monsters_Moves_Timer->setInterval( MONSTERS_MOVEMENT_INTERVAL ); //set interval
	myMonster_Factory_Monsters_Moves_Timer->setCallback(myDaemons,&Daemons::Move_Monsters, (void*)NULL); //set callback

	//Create monster's generation daemons
	Timer<Daemons>* myMonster_Factory_Monsters_Generation_Timer = new Timer<Daemons>; //set definition
	myMonster_Factory_Monsters_Generation_Timer->setInterval( MONSTERS_GENERATION_INTERVAL ); //set interval
	myMonster_Factory_Monsters_Generation_Timer->setCallback(myDaemons,&Daemons::Generate_Monsters, (void*)NULL); //set callback

	//Manage score
	Timer<Daemons>* myScore = new Timer<Daemons>; //set definition
	myScore->setInterval( 1000 / FRAMES_PER_SECOND ); //set interval
	myScore->setCallback(myDaemons,&Daemons::Score, (void*)NULL); //set callback

	//inform the keyboard of daemons process instance
	myKeyboardInput->Set_Daemons(myDaemons);


	/********ENGINE********/
	//Affect the game render engine to the windows
	App::getInstance().getWindow()->setEngine(myRender_Engine);

	//Affect the keyboard instance to the windows
    App::getInstance().getWindow()->getEventManager()->setKeyboard(myKeyboardInput);


	/********Start music********/
#ifndef _DEBUG //only on rlz mode
	App::getInstance().getMixer()->playChannel(GlobalMusic_Chan);
#endif

	/*******Score Management********/
	FiNiSH_TiME = (unsigned)time( NULL );

	/********Start Daemons Process********/
	myMonster_Factory_Monsters_Moves_Timer->start(); //monsters movement
	myMonster_Factory_Monsters_Generation_Timer->start(); //monsters generation
	myScore->start(); //Score

	/*******Score Management********/
	FiNiSH_TiME = (unsigned)time( NULL );

	/********Launch the mainloop that will use the render method of the Engine and so will render the screen and will manage all events********/
	App::getInstance().getWindow()->mainLoop(FRAMES_PER_SECOND);


	/********QUIT********/
	//Quit SDL
	//SDL_Quit();

    return 0; //no error occured
	
} catch (...) {
    P0_Logger << " Error in Main " << std::endl;
    Delay(2000);
    return 1;
}
}

