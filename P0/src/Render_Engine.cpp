#include "Render_Engine.hh"

//Constructor
Render_Engine::Render_Engine()
{
	//Allocations
	myPlayer = new Player_Base(0,0);
	myBackGround = new BackGround();
	myEnvironment = new Environment;
	BackGround_Sprite_Vector = new std::vector<BattleField_Sprite*>;
	Environment_Sprite_Vector = new std::vector<BattleField_Sprite*>;
	Monster_Factory_Skeleton = new Monster_Factory<Monster_Skeleton>;
	Monster_Factory_Worm = new Monster_Factory<Monster_Worm>;
	EscMenu = new Escape_Menu() ;
	VictoryScreen = new Victory_Screen();
	MyKeyboard = new KeyboardInput();
	P0_Logger << nl << "Engine CONSTRUCTED Successfully " << std::endl;
}

//Destructor
Render_Engine::~Render_Engine()
{
	P0_Logger << nl << "Engine DESTRUCTED Successfully " << std::endl;
}

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
	myPlayer->Get_Camera().setw(CURRENT_SCREEN_WIDTH);
	myPlayer->Get_Camera().seth(CURRENT_SCREEN_HEIGHT);

	P0_Logger << nl << "Resize : OK " << std::endl;
	return true;
}

//Everything that must be calculated before the display of the screen must be defined in this method and then will be called by the mainloop each cycle
void Render_Engine::prerender(unsigned long deltaticks)
{
	//Handle movement each frames (for now)
	MyKeyboard->Player_Moves_Consequences(deltaticks);
}
//Inside this, we must put everything designed to draw the display. It will be called after the prerender by the mainloop and at the end of this method the screen will be flipped automatically to show everything
void Render_Engine::render(VideoSurface & screen) const
{
	//VideoSurface* Screen = &screen;
	//Generate the background on the screen
	if( myBackGround->Render(BackGround_Sprite_Vector, myPlayer->Get_Camera(), screen) == false )
	{ 
      P0_Logger << nl << "Background Render Failed " << std::endl;    
    }


	//Generate the environment on the screen
	if( myEnvironment->Render(Environment_Sprite_Vector, myPlayer->Get_Camera(), screen) == false )
	{ 
      P0_Logger << nl << "Environment Render Failed " << std::endl;    
    }

	//Show the Character on the screen
	if( myPlayer->Show(myPlayer->Get_Camera(), screen) == false )
	{ 
      P0_Logger << nl << "Character Render Failed " << std::endl;    
    }

	//show the arrow of the screen (if necessary)
	if (myPlayer->Get_Attack_Style() == 2)
	{
		if( myPlayer->Show_Arrow(screen) == false )
		{ 
		  P0_Logger << nl << "Arrow Render Failed " << std::endl;    
		}
	}

	//Apply monsters to the screen
	if(
	( Monster_Factory_Skeleton->Show_Monsters(myPlayer->Get_Camera(), screen) == false )
	||
	( Monster_Factory_Worm->Show_Monsters(myPlayer->Get_Camera(), screen) == false )
	) {
		P0_Logger << nl << "Monster Render Failed " << std::endl;    
    }																 

	//Display attack msg
	if( myPlayer->Show_Attack_Msg(screen) == false )
	{ 
      P0_Logger << nl << "Display Attack Msg Render Failed " << std::endl;    
    }

	//Display monsters numbers
	if( VictoryScreen->Show_Monsters_Stats(screen) == false )
	{ 
      P0_Logger << nl << "Display Monsters Stats Render Failed " << std::endl;    
    }
	
	if (GLOBAL_GAME_STATE == 4) {
		//Show Escape menu
		if( EscMenu->Show_Menu(screen) == false )
		{ 
	      P0_Logger << nl << "Display Esc Menu Failed " << std::endl;    
	    }
	}

	if (GLOBAL_GAME_STATE == 5) {
		//Show Vicotry Screen menu
		if( VictoryScreen->Show(screen) == false )
		{ 
	      P0_Logger << nl << "Display Victory Screen Failed " << std::endl;    
	    }
	}
	
	//Auto Flip by the mainloop here

	//P0_Logger << nl << "Render_Engine::Render() Used " << std::endl;
}

//Finally the post render method will be used by each cycle of mainloop after the draw of the screen. It designed to contain evrytinhg that will be updated after the render of the screen surface
void Render_Engine::postrender(void)
{
}
