#include "Project0.hh"

//Initialization of the windows, SDL, SDL_TTF, the surface
bool InitEverything()
{
	//Load configuration from ini files
	if (!Set_Config())
	{
		P0_Logger << nl <<  " Configuration could not been set " << GetError() << std::endl;
        return false;
	}

	//Set window name
	App::getInstance().setName(Window_Name);
	//SDL_WM_SetCaption( "Project 0 - 2D", NULL );

	//Initialize SDL Video
    if (! App::getInstance().initVideo(false,false,true,false) )
		//SDL_Init( SDL_INIT_EVERYTHING )
	{
		P0_Logger << nl << "Init Video Failed : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << nl << "Init Video : OK " << std::endl;

	//Intialize Timer
	if (! App::getInstance().initTimer() )
	{
		P0_Logger << nl << "Init Timer Failed : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << nl << "Init Timer : OK " << std::endl;

	//Initialize SDL_ttf
	if (! App::getInstance().initText())
		//if( TTF_Init() == -1 )
    {
		//P0_Logger << nl << "TTF Init Error : " << TTF::GetError() << std::endl;
		P0_Logger << nl <<  " TTF Init Error : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << nl << "TTF Init : OK " << std::endl;

	//Create the video surface aka the display
	if (App::getInstance().getWindow()->resetDisplay(SCREEN_WIDTH, SCREEN_HEIGHT) == NULL  )
	{
		P0_Logger << nl << "Create Surface Failed : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << nl << "Video Surface Creation : OK " << std::endl;

	//Initialize Audio Mixer
	if (!App::getInstance().initAudio())
    {
		P0_Logger << nl << "Audio Init Error : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << nl << "Audio Init : OK " << std::endl;

	//Load Fxs & Musics Sounds Files to the mixer and set there respective channels
	if (!Set_Sounds_Channels())
	{
		P0_Logger << nl << "Mixing Sound Error : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << nl << "Mixing Sound : OK " << std::endl;

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
		P0_Logger << nl << "Init Windows failed... " << std::endl;
		Delay(2000);
		//SDL_Delay(2000);
		return 1;
	}
	P0_Logger << nl << "-> Windows, SDL, SDL_TTF And VideoSurface Where Initialized Successfully <-" << std::endl;
	
/********Classes Instanciation & Initialization********/
	//Create the keyboard instance that will managed input
	KeyboardInput* myKeyboardInput = new KeyboardInput();
	//myKeyboardInput->enableKeyRepeat();  //enable key repeat


	//Instanciate the timers class
	Daemons* myDaemons = new Daemons();

	//Engine instanciation
	Render_Engine* myRender_Engine = new Render_Engine();

	//Inform the render engine of the keyboard instance
	myRender_Engine->Set_Keyboard(myKeyboardInput);

/****Battlefield****/
	//Initialize the BackGround
	BackGround* myBackGround = new BackGround();
	P0_Logger << nl << "BackGround Init: OK " << std::endl;
	myRender_Engine->Set_BackGround(myBackGround); //inform the engine class of the background instance (as background is fixed for the moment)

	//Fill the BackGround vector with all BackGround sprite corresponding to the map file
#ifdef _DEBUG //debug mode
	std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector = new std::vector<BattleField_Sprite*>;
#else //rlz mode
	std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector = myBackGround->BackGround_Vector(); //Vector which will contains all BackGround type and clip
#endif
	P0_Logger << nl << "BackGround_Sprite Vector Fill: OK " << std::endl;
	myKeyboardInput->Set_BackGround_Sprite_Vector( BackGround_Sprite_Vector ); //inform the input management
	myDaemons->Set_BackGround_Sprite_Vector( BackGround_Sprite_Vector ); //inform the timer class
	myRender_Engine->Set_BackGround_Sprite_Vector( BackGround_Sprite_Vector ); //inform the timer class (this the only moment where we get informed of the background as background is fixed for the moment)

	//Initialize the Environment
	Environment* myEnvironment = new Environment();
	P0_Logger << nl << "Environment Init: OK " << std::endl;
	myRender_Engine->Set_Environment(myEnvironment); //inform the engine class of the environment instance

	//Fill the Environment vector with all Environment sprite corresponding to the map file
#ifdef _DEBUG //debug mode
	std::vector<BattleField_Sprite*>* Environment_Sprite_Vector = new std::vector<BattleField_Sprite*>;
#else //rlz mode*/
	std::vector<BattleField_Sprite*>* Environment_Sprite_Vector = myEnvironment->Environment_Vector(); //Vector which will contains all Environment items type and clip
#endif
	P0_Logger << nl << "Environment_Sprite Vector Fill: OK " << std::endl;
	myKeyboardInput->Set_Environment_Sprite_Vector( Environment_Sprite_Vector );
	myDaemons->Set_Environment_Sprite_Vector( Environment_Sprite_Vector ); 
	myRender_Engine->Set_Environment_Sprite_Vector( Environment_Sprite_Vector ); //inform the timer class (this the only moment where we get informed of the environnement as environment is fixed for the moment)

/****PlayerS****/
	//Vector containing pointers to vector of pointers to monsters
	std::vector< std::vector<Character_Base*> *>* Global_Player_Vector = new std::vector< std::vector<Character_Base*> *>;

			/****NPCs****/
	//Vector of npcs
	std::vector<Character_Base*>* NPCs_Vector = new std::vector<Character_Base*>;

	//Create npc & initialized it
	//
	//TODO: put this in ini
	//
	NPCs* myNPC = new NPCs(32*32, 10*32);
	if( myNPC->Set_Graphic_Style() == false ) //intialize Character's graphic aspect
	{ 
        P0_Logger << nl << "Failed to set NPC Graphic " << std::endl;
    	Delay(2000);
    	return 1;
    }
    P0_Logger << nl << "NPC Creation: OK " << std::endl;

	NPCs_Vector->push_back(myNPC);

	myKeyboardInput->Set_NPC( myNPC );
	myDaemons->Set_NPC(myNPC);
	myRender_Engine->Set_NPC( myNPC );

	Global_Player_Vector->push_back(NPCs_Vector);

			/****Player****/
	//Vector of players
	std::vector<Character_Base*>* Players_Vector = new std::vector<Character_Base*>;

	//Create player & initialized it
	Player* myPlayer = new Player(CH_INITIAL_X, CH_INITIAL_Y);
	if( myPlayer->Set_Graphic_Style() == false ) //intialize Character's graphic aspect
	{ 
        P0_Logger << nl << "Failed to set Player Graphic " << std::endl;
    	Delay(2000);
    	return 1;
    }
	if( myPlayer->Set_Attack_Msgs() == false ) //intialize Character's predef msgs
	{ 
        P0_Logger << nl << "Failed to set predefined msgs " << std::endl;
    	Delay(2000);
    	return 1;
    }
    P0_Logger << nl << "Player Creation: OK " << std::endl;

	Players_Vector->push_back(myPlayer);
	
	myKeyboardInput->Set_Player( myPlayer );
	myDaemons->Set_Player(myPlayer);
	myRender_Engine->Set_Player( myPlayer );

	Global_Player_Vector->push_back(Players_Vector);

	myKeyboardInput->Set_Global_Player_Vector(Global_Player_Vector);
	//myRender_Engine->Set_Global_Player_Vector(Global_Player_Vector);
	myDaemons->Set_Global_Player_Vector(Global_Player_Vector);


/****Monsters****/
	//Initialize the skeleton factory
	Monster_Factory<Monster_Skeleton>* Monster_Factory_Skeleton = new Monster_Factory<Monster_Skeleton>(INITIAL_MONSTERS);  //A factory of Monster Skeletons
	P0_Logger << nl << "Skeleton Factory Init: OK " << std::endl;
	myKeyboardInput->Set_Monster_Factory_Skeleton( Monster_Factory_Skeleton );
	myDaemons->Set_Monster_Factory_Skeleton( Monster_Factory_Skeleton );
	myRender_Engine->Set_Monster_Factory_Skeleton( Monster_Factory_Skeleton );

	//Create all the monsters skeletons
	std::vector<Character_Base*>* Monster_Vector_Skeleton = Monster_Factory_Skeleton->Create_Monsters(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector);  //Vector which will contains all skeletons
	P0_Logger << nl << "Skeleton Vector Fill: OK " << std::endl;
	
	//Initialize the worm factory
	Monster_Factory<Monster_Worm>* Monster_Factory_Worm = new Monster_Factory<Monster_Worm>(INITIAL_MONSTERS);  //A factory of Monster Worms
	P0_Logger << nl << "Worm Factory Init: OK " << std::endl;
	myKeyboardInput->Set_Monster_Factory_Worm( Monster_Factory_Worm );
	myDaemons->Set_Monster_Factory_Worm( Monster_Factory_Worm );
	myRender_Engine->Set_Monster_Factory_Worm( Monster_Factory_Worm );

	//Create all the monsters worms
	std::vector<Character_Base*>* Monster_Vector_Worm = Monster_Factory_Worm->Create_Monsters(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector); //Vector which will contains all skeletons
	P0_Logger << nl << "Worm Vector Fill: OK " << std::endl;

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

/********DEAMONS CREATION********/
	//Create monster's movement daemons
	Timer<Daemons>* myMonster_Factory_Monsters_Moves_Timer = new Timer<Daemons>(); //set definition
	myMonster_Factory_Monsters_Moves_Timer->setInterval( MONSTERS_MOVEMENT_INTERVAL ); //set interval
	myMonster_Factory_Monsters_Moves_Timer->setCallback(myDaemons,&Daemons::Move_Monsters, (void*)NULL); //set callback

	//Create monster's generation daemons
	Timer<Daemons>* myMonster_Factory_Monsters_Generation_Timer = new Timer<Daemons>; //set definition
	myMonster_Factory_Monsters_Generation_Timer->setInterval( MONSTERS_GENERATION_INTERVAL ); //set interval
	myMonster_Factory_Monsters_Generation_Timer->setCallback(myDaemons,&Daemons::Generate_Monsters, (void*)NULL); //set callback

	//Create npcs's movement daemons
	Timer<Daemons>* myNPCs_Moves_Timer = new Timer<Daemons>(); //set definition
	myNPCs_Moves_Timer->setInterval( NPCS_MOVEMENT_INTERVAL ); //set interval
	myNPCs_Moves_Timer->setCallback(myDaemons,&Daemons::Move_NPCs, (void*)NULL); //set callback

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
	myMonster_Factory_Monsters_Moves_Timer->start(); //monsters movements
	myMonster_Factory_Monsters_Generation_Timer->start(); //monsters generation
	myNPCs_Moves_Timer->start(); //npcs movements
	myScore->start(); //Score



/********Launch the mainloop that will use the render method of the Engine and so will render the screen and will manage all events********/
	App::getInstance().getWindow()->mainLoop(FRAMES_PER_SECOND);


/********Clean UP********/
	delete myScore, myScore = NULL;
	delete myMonster_Factory_Monsters_Generation_Timer, myMonster_Factory_Monsters_Generation_Timer = NULL;
	delete myMonster_Factory_Monsters_Moves_Timer, myMonster_Factory_Monsters_Moves_Timer = NULL;
	delete VictoryScreen, VictoryScreen = NULL;
	delete EscMenu, EscMenu = NULL;
	delete Monster_Factory_Worm, Monster_Factory_Worm = NULL;
	delete Monster_Factory_Skeleton, Monster_Factory_Skeleton = NULL;
	delete Global_Monster_Vector, Global_Monster_Vector = NULL;
	delete myPlayer, myPlayer = NULL;

	delete Players_Vector, Players_Vector = NULL;
	
	delete Global_Player_Vector, Global_Player_Vector = NULL;
	delete myEnvironment, myEnvironment = NULL;
	delete Environment_Sprite_Vector, Environment_Sprite_Vector = NULL;
	delete myBackGround, myBackGround = NULL;
	delete BackGround_Sprite_Vector, BackGround_Sprite_Vector = NULL;

	delete myKeyboardInput, myKeyboardInput = NULL;
	
	delete myRender_Engine, myRender_Engine = NULL;
	delete myDaemons, myDaemons = NULL;


    return 0; //no error occured
	
} catch (std::exception e) {
    P0_Logger << nl << "Unhandled Exception occured in Main : " << e.what() << std::endl;
    P0_Logger << nl << "P0 stopped in emergency" << std::endl;
    Delay(2000);
    return 1;
}
}

