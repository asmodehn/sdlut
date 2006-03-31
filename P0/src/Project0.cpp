#include "Project0.hh"

//Create the keyboard instance that will managed input
KeyboardInput myKeyboardInput;

//Engine Class : that render the screen
class TheEngine : public Engine
{
private:
	BattleField* myBattleField;
	std::vector<BattleField_Sprite*> BattleField_Sprite_Vector; //Vector which will contains all battlefield type and clip
	Monster_Factory* myMonster_Factory;
	Character_Base* myCharacter;
	std::vector<Monster*> Monster_vector; //Vector which will contains all monsters
	Escape_Menu* EscMenu;
	int Character_Hit_Distance;

public:

    TheEngine()
    {
		Character_Hit_Distance = 0;

		//Initialize the battlefield
		myBattleField = new BattleField();
		P0_Logger << " BattleField Init: OK " << std::endl;

		//Fill the battlefield vector with all battlefield sprite corresponding to the map file
		BattleField_Sprite_Vector = myBattleField->BattleField_Vector();
		P0_Logger << " BattleField_Sprite Vector Fill: OK " << std::endl;

		//Initialize the factory
		myMonster_Factory = new Monster_Factory(INITIAL_MONSTERS);
		P0_Logger << " Monster Factory Init: OK " << std::endl;

		//Create all the monsters
		Monster_vector = myMonster_Factory->Create_Monsters(CH_INITIAL_X, CH_INITIAL_Y);
		P0_Logger << " Monster Vector Fill: OK " << std::endl;

		//Create Character & initialized it
		myCharacter = new Character_Base(CH_INITIAL_X, CH_INITIAL_Y, Monster_vector);
		//Character<Monster*>* myCharacter = new Character<Monster*>(192, 224, _screen, Monster_vector);
		P0_Logger << " Character Creation: OK " << std::endl;

		//Create the ingame escape menu
		EscMenu = new Escape_Menu();
		
		P0_Logger << " \nEngine CONSTRUCTED Successfully\n " << std::endl;

    }

    virtual ~TheEngine(){}

	//Methods that is used when resetdisplay is called and not to initialize the engine like is name could let think. Its used to update the engine only when the windows settings change
    bool init(int width, int height)
    {
		return true;
	}

	//Called when the windows is resized and if the engine need to be updated
    bool resize(int width, int height)
    { return true; }

    //Everything that must be calculated before the display on the screen must be defined in this method and then will be called my the mainloop each cycle
	void prerender(void)
	{
		//Update the graphic style of the character
		myCharacter->Update_Graphic_Style();

		//Move the character
		myCharacter->move();

		//Handle attacks
		Character_Hit_Distance = myCharacter->attack();

		//Remove Dead monsters from the vector and inform the character 
		Monster_vector = myMonster_Factory->Remove_Dead_Monsters();
		myCharacter->Update_Monster_Knowledge(Monster_vector);

		//Move Monsters
		myMonster_Factory->Move_Monsters(myCharacter->collision_box);

		//Set the camera
        myCharacter->following_camera();

		//transmit the character instance and the esc menu instance to the keyboard instance
		myKeyboardInput.Update_Character_Knowledge(myCharacter, EscMenu);
	}
	//Inside this, we must put everything designed to draw the display. It will be called after the prerender by the mainloop and at the end of this method the screen will be flipped automatically to show everything
	void render(VideoSurface & screen) const
    {
		//Generate the background to the screen
		myBattleField->Render(BattleField_Sprite_Vector, myCharacter->Camera, screen);

		//Show the Character on the screen
		myCharacter->move_animation(screen);
		
		if (GLOBAL_GAME_STATE == 3)
		//Show character attack animation
		myCharacter->attack_animation(Character_Hit_Distance, screen);

		//Display attack msg
		myCharacter->Display_Attack_Msg(screen);

		//Apply monsters to the screen
		myMonster_Factory->Move_Monsters_Animation(myCharacter->Camera, screen);

		if (GLOBAL_GAME_STATE == 4)
			//Show Escape menu
			EscMenu->Show_Menu(screen);

		//Auto Flip by the mainloop here

		//P0_Logger << " \n TheEngine Render Used\n " << std::endl;
    }

	//Finally the post render method will be used by each cycle of mainloop after the draw of the screen. It designed to contain evrytinhg that will be updated after the render of the screen surface
	void postrender(void)
	{
		//Eventually generate new monster and inform the character
		Monster_vector = myMonster_Factory->Generate_New_Monster( myCharacter->collision_box.getx(), myCharacter->collision_box.gety() );
		myCharacter->Update_Monster_Knowledge(Monster_vector);

		if (GLOBAL_GAME_STATE == 4)
			//Manage esc menu validation: leave if return is true
			myKeyboardInput.Set_quitRequested( EscMenu->Manage_Validation() );
	}

	//Return the character
	Character_Base* Get_Character()
	{
		return myCharacter;
	}
};

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
		P0_Logger << " TTF Error : " << GetError(TTF) << std::endl;
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

    //If eveything loads fine
    return true;    
}
//Main
int main( int argc, char* args[] )
{
	//Init the rand method using the current time in order to generate more random number
	srand( (unsigned)time( NULL ) );

	//Make sure the program waits for a quit
	bool quit = false;

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

	//Inform the keyboard instance of the character instance and then affect the keyboard instance to the windows
 	//myKeyboardInput.Update_Character_Knowledge(myEngine->Get_Character());
    App::getInstance().getWindow()->getEventManager()->setKeyboard(&myKeyboardInput);


	//Launch the mainloop that will use the render method of the Engine and so will render the screen and will manage all events
	App::getInstance().getWindow()->mainLoop(FRAMES_PER_SECOND);


	/*if(SDLNet_Init()==-1) {
		P0_Logger << " SDL_Net Init Failed " << std::endl;
		return 1;
	}
	P0_Logger << " SDL_Net Init : OK " << std::endl;*/

	//Quit SDL_NEt
	//SDLNet_Quit();

    //Quit SDL
	//SDL_Quit();

    return 0;    
}

