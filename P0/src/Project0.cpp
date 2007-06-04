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
	if (! App::getInstance().getWindow().resetDisplay(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP)  )
	{
		P0_Logger << nl << "Create Surface Failed : " << GetError() << std::endl;
        return false;
    }
	P0_Logger << nl << "Video Surface Creation : OK " << std::endl;

	//set the game exe icon
	//App::getInstance().getWindow().setIcon( RGBSurface("P0.ico") );

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
void ImplementEverything()
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
	*&BackGround_Sprite_Vector = *&myBackGround->Fill_BackGround_Vector(); //Vector which will contains all BackGround type and clip
	P0_Logger << nl << "BackGround_Sprite Vector Fill: OK " << std::endl;
	
	//Initialize the Environment
	myEnvironment = new Environment();
	P0_Logger << nl << "Environment Init: OK " << std::endl;

	//Fill the Environment vector with all Environment sprite corresponding to the map file
	*&Environment_Sprite_Vector = *&myEnvironment->Fill_Environment_Vector(); //Vector which will contains all Environment items type and clip
	P0_Logger << nl << "Environment_Sprite Vector Fill: OK " << std::endl;
	
/****PlayerS****/
	//Vector containing pointers to vector of pointers to monsters
	Global_Player_Vector = new std::vector< std::vector<Character_Base*> *>;

			/****NPC_Merchant****/
	//Vector of npcs
	NPCs_Vector = new std::vector<Character_Base*>;

	//Create npc & initialized it
	myNPC = new NPC_Merchant();
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
		throw std::logic_error( "Failed to center camera over Player" );
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
														Monster_Factory_Worm, myEsc_Menu, myVictory_Screen, myKeyboardInput, myMessages, Global_Player_Vector, Global_Monster_Vector );


	//Affect the keyboard instance to the windows
    App::getInstance().getWindow().getEventManager().setKeyboard(myKeyboardInput);

	//Affect the game render engine to the windows
	App::getInstance().getWindow().setEngine(myRender_Engine);

} catch (std::exception &exc)
{
	throw std::logic_error(exc.what());
}
catch (...)
{
	throw std::logic_error( "Unhandled Exception Occured In ImplementEverything()" );
}
}

//Run
void RunGame()
{
try {

	/********Start music********/
	if (ENABLE_MUSIC)
		App::getInstance().getMixer().getChannel(GlobalMusic_Chan).play();

	/*******Score Management********/
	FiNiSH_TiME = (unsigned)time( NULL );

	/********Start Daemons Process********/
	//myMonster_Factory_Monsters_Moves_Timer->launch(MONSTERS_MOVEMENT_INTERVAL); //monsters movements
	myMonster_Factory_Monsters_Generation_Timer->launch(MONSTERS_GENERATION_INTERVAL); //monsters generation
	//myNPCs_Moves_Timer->launch(NPCS_MOVEMENT_INTERVAL); //npcs movements
	myScore->launch(1000 / FRAMES_PER_SECOND); //Score


	/********Launch the mainloop that will use the render method of the Engine and so will render the screen and will manage all events********/
	App::getInstance().getWindow().mainLoop(FRAMES_PER_SECOND);


} catch (std::exception &exc)
{
	throw std::logic_error(exc.what());
}
catch (...)
{
	throw std::logic_error( "Unhandled Exception Occured In RunGame()" );
}
}

//Clean Up
bool CleanEverything()
{
try {

/********Stop Daemons Process********/
	if ( myMonster_Factory_Monsters_Moves_Timer != NULL )
		myMonster_Factory_Monsters_Moves_Timer->abort(); //monsters movements
	if ( myMonster_Factory_Monsters_Generation_Timer != NULL )
		myMonster_Factory_Monsters_Generation_Timer->abort(); //monsters generation
	if ( myNPCs_Moves_Timer != NULL )
		myNPCs_Moves_Timer->abort(); //npcs movements
	if ( myScore != NULL )
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

	XML_Manager::Clean_Up();

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

	//Create the windows and init everything (SDL, SDL_TTF, ...)
	if( InitEverything() == false )
	{ 
		throw std::logic_error("Init Everything failed... ");
	}
	P0_Logger << nl << "-> Windows, SDL, SDL_TTF And VideoSurface Where Initialized Successfully <-" << std::endl;
	


//
//XML TESTS
//
	//if ( XML_Manager::Validate_File( "Data/Characters/Player.xml" ) )
	//	P0_Logger << nl << "File Player.xml is valid " << std::endl;

	//string Death_Animation_Filename = XML_Manager::Get_Option_String("Data/Characters/Player.xml", "Death_Animation_Filename", true);
	//P0_Logger << nl << "Death_Animation_Filename: " << Death_Animation_Filename << std::endl;

	//string Data_Root_Directory = XML_Manager::Get_Option_String("Data/Characters/Player.xml", "Data_Root_Directory", true);
	//P0_Logger << nl << "Data_Root_Directory: " << Data_Root_Directory << std::endl;

	//int Default_Sprite_Width = XML_Manager::Get_Option_Value("Data/Characters/Player.xml", "Default_Sprite_Width");
	//P0_Logger << nl << "Default_Sprite_Width: " << Default_Sprite_Width << std::endl;

	//long Initial_Position_X_false_long = XML_Manager::Get_Option_Value_Long("Data/Characters/Player.xml", "Initial_Position_X");
	//P0_Logger << nl << "Initial_Position_X_false_long: " << Initial_Position_X_false_long << std::endl;


	//if ( XML_Manager::Validate_File( "Data/Characters/Human_w_Bow_Animations.xml" ) )
	//	P0_Logger << nl << "File Human_w_Bow_Animations.xml is valid " << std::endl;

	//string Attack_Animation_Filename = XML_Manager::Get_Option_String("Data/Characters/Human_w_Bow_Animations.xml", "Attack_Animation_Filename");
	//P0_Logger << nl << "Attack_Animation_Filename: " << Attack_Animation_Filename << std::endl;

	//long Frames_Interval = XML_Manager::Get_Option_Value_Long(Data_Root_Directory+Attack_Animation_Filename, "Frames_Interval", true);
	//P0_Logger << nl << "Attack_Animation\\Frames_Interval: " << Frames_Interval << std::endl;

	//XML_Manager::Clean_Up();



	//implement everything needed by the game
	ImplementEverything();
	P0_Logger << nl << "-> Everything Was Implemented Successfully <-" << std::endl;

	//Start everything needed during play time
	RunGame();

	P0_Logger << nl << "-> Game Stopped Running Succesffully <-" << std::endl;

	//Game stoped, clean b4 exit
	if( CleanEverything() == false )
	{ 
		P0_Logger << nl << "Clean Up failed... " << std::endl;
		Delay(2000);
		//SDL_Delay(2000);
		return 1;
	}

	P0_Logger << nl << "-> Everything Was Clean Up Succesffully <-" << std::endl;

    return 0; //no error occured

} catch (std::exception &exc)
{
	P0_Logger << nl << exc.what() << std::endl;
	if( CleanEverything() == false )
		P0_Logger << nl << "Clean Up failed... " << std::endl;
	Delay(2000);
	return 1;
}
catch (...)
{
    P0_Logger << nl << "Unhandled Exception occured in Main : " << std::endl;
    P0_Logger << nl << "P0 stopped in emergency" << std::endl;
	if( CleanEverything() == false )
		P0_Logger << nl << "Clean Up failed... " << std::endl;

    Delay(30000);
	return 1;
}
}

