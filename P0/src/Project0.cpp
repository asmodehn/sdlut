#include "Project0.hh"

//Initialization of the windows, SDL, SDL_TTF, the surface
bool InitEverything()
{
	//Load configuration from ini files
	if (!Set_Config())
	{
		cout << "\nConfiguration could not been set " << std::endl;
        return false;
	}
	P0_Logger << nl << "Configuration Set" << std::endl;

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

//Implementation
bool ImplementEverything()
{
try {
/*********Interface Stuff************/

	//Create the ingame escape menu
	myEsc_Menu = new Escape_Menu();

	//Create the victory screen
	myVictory_Screen = new Victory_Screen();

	myMessages = new Messages();

/****Battlefield****/
	//Initialize the BackGround
	myBackGround = new BackGround();
	P0_Logger << nl << "BackGround Init: OK " << std::endl;
	
	//Fill the BackGround vector with all BackGround sprite corresponding to the map file
	BackGround_Sprite_Vector = myBackGround->BackGround_Vector(); //Vector which will contains all BackGround type and clip
	P0_Logger << nl << "BackGround_Sprite Vector Fill: OK " << std::endl;
	
	//Initialize the Environment
	myEnvironment = new Environment();
	P0_Logger << nl << "Environment Init: OK " << std::endl;

	//Fill the Environment vector with all Environment sprite corresponding to the map file
	Environment_Sprite_Vector = myEnvironment->Environment_Vector(); //Vector which will contains all Environment items type and clip
	P0_Logger << nl << "Environment_Sprite Vector Fill: OK " << std::endl;
	
/****PlayerS****/
	//Vector containing pointers to vector of pointers to monsters
	Global_Player_Vector = new std::vector< std::vector<Character_Base*> *>;

			/****NPCs****/
	//Vector of npcs
	NPCs_Vector = new std::vector<Character_Base*>;

	//Create npc & initialized it
	myNPC = new NPCs();
	if( myNPC->Set_Attack_Style() == false ) //intialize Character's graphic aspect
	{ 
        P0_Logger << nl << "Failed to set NPC Graphic " << std::endl;
    	Delay(2000);
    	return 1;
    }
    P0_Logger << nl << "NPC Creation: OK " << std::endl;

	NPCs_Vector->push_back(myNPC);

	Global_Player_Vector->push_back(NPCs_Vector);

			/****Player****/
	//Vector of players
	Players_Vector = new std::vector<Character_Base*>;

	//Create player & initialized it
	myPlayer = new Player();
	if( myPlayer->Following_Camera() == false ) //center camera
	{ 
        P0_Logger << nl << "Failed to center camera over Player" << std::endl;
    	Delay(2000);
    	return 1;
    }
	if( myPlayer->Set_Attack_Style() == false ) //intialize Character's graphic aspect
	{ 
        P0_Logger << nl << "Failed to set Player Graphic " << std::endl;
    	Delay(2000);
    	return 1;
    }
    P0_Logger << nl << "Player Creation: OK " << std::endl;

	Players_Vector->push_back(myPlayer);

	Global_Player_Vector->push_back(Players_Vector);



/****Monsters****/
	//Vector containing pointers to vector of pointers to monsters
	Global_Monster_Vector = new std::vector< std::vector<Character_Base*> *>;
	
	//Initialize the skeleton factory
	Monster_Factory_Skeleton = new Monster_Factory<Monster_Skeleton>(INITIAL_MONSTERS, Global_Monster_Vector);  //A factory of Monster Skeletons
	P0_Logger << nl << "Skeleton Factory Init: OK " << std::endl;

	//Create all the monsters skeletons
	//std::vector<Character_Base*>* Monster_Vector_Skeleton = 
	Monster_Factory_Skeleton->Create_Monsters(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector);  //Vector which will contains all skeletons
	P0_Logger << nl << "Skeleton Vector Fill: OK " << std::endl;
	
	//Initialize the worm factory
	Monster_Factory_Worm = new Monster_Factory<Monster_Worm>(INITIAL_MONSTERS, Global_Monster_Vector);  //A factory of Monster Worms
	P0_Logger << nl << "Worm Factory Init: OK " << std::endl;

	//Create all the monsters worms
	//std::vector<Character_Base*>* Monster_Vector_Worm = 
	Monster_Factory_Worm->Create_Monsters(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector); //Vector which will contains all skeletons
	P0_Logger << nl << "Worm Vector Fill: OK " << std::endl;

/********DEAMONS CREATION********/
	//Instanciate the daemon class
	myDaemons = new Daemons(myPlayer, myNPC, BackGround_Sprite_Vector, Environment_Sprite_Vector, Monster_Factory_Skeleton,
									Monster_Factory_Worm, Global_Player_Vector, Global_Monster_Vector );

	//Create monster's movement daemons
	myMonster_Factory_Monsters_Moves_Timer = new Timer<Daemons>(); //set definition
	myMonster_Factory_Monsters_Moves_Timer->setCallback(myDaemons,&Daemons::Move_Monsters, (void*)NULL); //set callback

	//Create monster's generation daemons
	myMonster_Factory_Monsters_Generation_Timer = new Timer<Daemons>; //set definition
	myMonster_Factory_Monsters_Generation_Timer->setCallback(myDaemons,&Daemons::Generate_Monsters, (void*)NULL); //set callback

	//Create npcs's movement daemons
	myNPCs_Moves_Timer = new Timer<Daemons>(); //set definition
	myNPCs_Moves_Timer->setCallback(myDaemons,&Daemons::Move_NPCs, (void*)NULL); //set callback

	//Manage score
	myScore = new Timer<Daemons>; //set definition
	myScore->setCallback(myDaemons,&Daemons::Score, (void*)NULL); //set callback


/********ENGINE********/
	//Create the keyboard instance that will managed input
	myKeyboardInput = new KeyboardInput(myPlayer, myNPC, BackGround_Sprite_Vector, Environment_Sprite_Vector, Monster_Factory_Skeleton,
													Monster_Factory_Worm, Global_Player_Vector, Global_Monster_Vector, myEsc_Menu,
													myVictory_Screen, myDaemons );
	//myKeyboardInput->enableKeyRepeat();  //enable key repeat

	//Engine instanciation
	myRender_Engine = new Render_Engine(myPlayer, myNPC, myBackGround, myEnvironment, Monster_Factory_Skeleton,
														Monster_Factory_Worm, myEsc_Menu, myVictory_Screen, myKeyboardInput, myMessages );


	//Affect the keyboard instance to the windows
    App::getInstance().getWindow()->getEventManager()->setKeyboard(myKeyboardInput);

	//Affect the game render engine to the windows
	App::getInstance().getWindow()->setEngine(myRender_Engine);

	return true; //no error

} catch (...) {
	return false; //error occured
}
}

//Run
bool RunGame()
{
try {

	/********Start music********/
	if (ENABLE_MUSIC)
		App::getInstance().getMixer()->playChannel(GlobalMusic_Chan);

	/*******Score Management********/
	FiNiSH_TiME = (unsigned)time( NULL );

	/********Start Daemons Process********/
	myMonster_Factory_Monsters_Moves_Timer->launch(MONSTERS_MOVEMENT_INTERVAL); //monsters movements
	myMonster_Factory_Monsters_Generation_Timer->launch(MONSTERS_GENERATION_INTERVAL); //monsters generation
	myNPCs_Moves_Timer->launch(NPCS_MOVEMENT_INTERVAL); //npcs movements
	myScore->launch(1000 / FRAMES_PER_SECOND); //Score


	/********Launch the mainloop that will use the render method of the Engine and so will render the screen and will manage all events********/
	App::getInstance().getWindow()->mainLoop(FRAMES_PER_SECOND);

	return true; //no error

} catch (...) {
	return false; //error occured
}
}

//Clean Up
bool CleanEverything()
{
try {

/********Stop Daemons Process********/
	myMonster_Factory_Monsters_Moves_Timer->abort(); //monsters movements
	myMonster_Factory_Monsters_Generation_Timer->abort(); //monsters generation
	myNPCs_Moves_Timer->abort(); //npcs movements
	myScore->abort(); //Score

/********Clean UP********/
	delete myMonster_Factory_Monsters_Moves_Timer, myMonster_Factory_Monsters_Moves_Timer = NULL;
	delete myMonster_Factory_Monsters_Generation_Timer, myMonster_Factory_Monsters_Generation_Timer = NULL;
	delete myNPCs_Moves_Timer, myNPCs_Moves_Timer = NULL;
	delete myScore, myScore = NULL;

	delete myVictory_Screen, myVictory_Screen = NULL;
	delete myEsc_Menu, myEsc_Menu = NULL;
	delete myMessages, myMessages = NULL;	

	delete Monster_Factory_Worm, Monster_Factory_Worm = NULL;
	delete Monster_Factory_Skeleton, Monster_Factory_Skeleton = NULL;
	delete Global_Monster_Vector, Global_Monster_Vector = NULL;

	delete myPlayer, myPlayer = NULL;
	delete myNPC, myNPC = NULL;
	delete NPCs_Vector, NPCs_Vector = NULL;
	delete Players_Vector, Players_Vector = NULL;
	delete Global_Player_Vector, Global_Player_Vector = NULL;

	delete myEnvironment, myEnvironment = NULL;
	delete myBackGround, myBackGround = NULL;
	
	delete myKeyboardInput, myKeyboardInput = NULL;
	
	delete myRender_Engine, myRender_Engine = NULL;

	delete myDaemons, myDaemons = NULL;

	return true; //no error

} catch (...) {
	return false; //error occured
}
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
		P0_Logger << nl << "Init Everything failed... " << std::endl;
		Delay(2000);
		//SDL_Delay(2000);
		return 1;
	}
	P0_Logger << nl << "-> Windows, SDL, SDL_TTF And VideoSurface Where Initialized Successfully <-" << std::endl;
	
	//implement everything needed by the game
	if( ImplementEverything() == false )
	{ 
		P0_Logger << nl << "Implementation failed... " << std::endl;
		Delay(2000);
		//SDL_Delay(2000);
		return 1;
	}
	P0_Logger << nl << "-> Everything Was Implemented Successfully <-" << std::endl;

	//Start everything needed during play time
	if( RunGame() == false )
	{ 
		P0_Logger << nl << "Run Game failed... " << std::endl;
		Delay(2000);
		//SDL_Delay(2000);
		return 1;
	}


	P0_Logger << nl << "-> Game Stopped Running Succesffully <-" << std::endl;

	//Game stopeed, clean b4 exit
	if( CleanEverything() == false )
	{ 
		P0_Logger << nl << "Clean Up failed... " << std::endl;
		Delay(2000);
		//SDL_Delay(2000);
		return 1;
	}

	P0_Logger << nl << "-> Everything Was Clean Up Succesffully <-" << std::endl;

    return 0; //no error occured
	
} catch (std::exception e) {
    P0_Logger << nl << "Unhandled Exception occured in Main : " << e.what() << std::endl;
    P0_Logger << nl << "P0 stopped in emergency" << std::endl;
    Delay(30000);
    return 1;
}
}

