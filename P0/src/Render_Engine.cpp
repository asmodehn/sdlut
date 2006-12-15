#include "Render_Engine.hh"

//Constructor
Render_Engine::Render_Engine()
{
	P0_Logger << " Engine CONSTRUCTED Successfully " << std::endl;
}

//Destructor
Render_Engine::~Render_Engine(){}

//Methods that is used when resetdisplay is called and not to initialize the engine like is name could let think. Its used to update the engine only when the windows settings change
bool Render_Engine::init(int width, int height)
{
	return true;
}

//Called when the windows is resized and if the engine need to be updated
bool Render_Engine::resize(int width, int height)
{
	CURRENT_SCREEN_WIDTH = width;
	CURRENT_SCREEN_HEIGHT = height;
	myCharacter->Camera.setw(CURRENT_SCREEN_WIDTH);
	myCharacter->Camera.seth(CURRENT_SCREEN_HEIGHT);

	P0_Logger << " Resize : OK " << std::endl;
	return true;
}

//Everything that must be calculated before the display of the screen must be defined in this method and then will be called by the mainloop each cycle
void Render_Engine::prerender(void)
{
}
//Inside this, we must put everything designed to draw the display. It will be called after the prerender by the mainloop and at the end of this method the screen will be flipped automatically to show everything
void Render_Engine::render(VideoSurface & screen) const
{
	//Generate the background on the screen
	myBackGround->Render(BackGround_Sprite_Vector, myCharacter->Camera, screen);

	//Generate the environment on the screen
	myEnvironment->Render(Environment_Sprite_Vector, myCharacter->Camera, screen);

	//Show the Character on the screen
	myCharacter->Show_Character(screen);

	//show the arrow of the screen (if necessary)
	myCharacter->Show_Arrow(screen);

	//Apply monsters to the screen
	Monster_Factory_Skeleton->Move_Monsters_Animation(myCharacter->Camera, screen);
	Monster_Factory_Worm->Move_Monsters_Animation(myCharacter->Camera, screen);

	//Display attack msg
	myCharacter->Display_Attack_Msg(screen);

	if (GLOBAL_GAME_STATE == 4)
		//Show Escape menu
		EscMenu->Show_Menu(screen);

	//Auto Flip by the mainloop here

	//P0_Logger << " Render_Engine::Render() Used " << std::endl;
}

//Finally the post render method will be used by each cycle of mainloop after the draw of the screen. It designed to contain evrytinhg that will be updated after the render of the screen surface
void Render_Engine::postrender(void)
{
}