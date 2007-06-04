#include "Render_Engine.hh"

//Constructor
Render_Engine::Render_Engine(Player* &myPlayer, NPC_Merchant* &myNPC, BackGround* &myBackGround, Environment* &myEnvironment,
							 Monster_Factory<Monster_Skeleton>* &Monster_Factory_Skeleton, Monster_Factory<Monster_Worm>* &Monster_Factory_Worm,
							 Escape_Menu* &myEsc_Menu, Victory_Screen* &myVictory_Screen, KeyboardInput* &myKeyboardInput, Messages* &myMessages,
							 std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector
							)
{
	//Allocations
	this->myPlayer = myPlayer;
	this->myNPC = myNPC;
	this->myBackGround = myBackGround;
	this->myEnvironment = myEnvironment;
	this->Monster_Factory_Skeleton = Monster_Factory_Skeleton;
	this->Monster_Factory_Worm = Monster_Factory_Worm;
	this->myEsc_Menu = myEsc_Menu;
	this->myVictory_Screen = myVictory_Screen;
	this->myKeyboardInput = myKeyboardInput;
	this->myMessages = myMessages;
	this->Global_Player_Vector = Global_Player_Vector;
	this->Global_Monster_Vector = Global_Monster_Vector;

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
	//reset camera
	//Rect NewCamera;
	//NewCamera.setw(CURRENT_SCREEN_WIDTH);
	//NewCamera.seth(CURRENT_SCREEN_HEIGHT);
	//myPlayer->Set_Camera(NewCamera);
	myPlayer->Get_Camera().setw(CURRENT_SCREEN_WIDTH);
	myPlayer->Get_Camera().seth(CURRENT_SCREEN_HEIGHT);
	myPlayer->Following_Camera();

	P0_Logger << nl << "Resize : OK " << std::endl;
	return true;
}

//Everything that must be calculated before the display of the screen must be defined in this method and then will be called by the mainloop each cycle
void Render_Engine::prerender(unsigned long deltaticks)
{
try {

//Player Movement
	//To handle movement based on time instead of frame
	myPlayer->Set_DeltaTicks(deltaticks);
	//Handle movement
	myKeyboardInput->Player_Moves_Consequences();

} catch (std::exception &exc) {
	P0_Logger << nl << " Render_Engine::prerender(), " << exc.what() << std::endl;
#ifdef _DEBUG
	throw std::logic_error("DEBUG_MODE -> Stop In Render_Engine::prerender()");
#endif
} catch (...) {
	P0_Logger << nl << "Unhandled Error In Render_Engine::prerender()" << std::endl; 
#ifdef _DEBUG
	throw std::logic_error("DEBUG_MODE -> Stop In Render_Engine::prerender()");
#endif
}
}

//Inside this, we must put everything designed to draw the display. It will be called after the prerender by the mainloop and at the end of this method the screen will be flipped automatically to show everything
void Render_Engine::render(VideoSurface & screen) const
{
	
	//Generate the background on the screen
	if( myBackGround->Render(myPlayer->Get_Camera(), screen) == false )
	{ 
      P0_Logger << nl << "Background Render Failed " << std::endl;    
    }


	//Generate the environment on the screen
	if( myEnvironment->Render(myPlayer->Get_Camera(), screen) == false )
	{ 
      P0_Logger << nl << "Environment Render Failed " << std::endl;    
    }

	//Show the Player on the screen
	if( myPlayer->Show(myPlayer->Get_Camera(), screen) == false )
	{ 
      P0_Logger << nl << "Player Render Failed " << std::endl;    
    }
	//Show the PC's arrow on the screen (if necessary)
	if (myPlayer->Get_Attack_Style() == 2)
	{
		if( myPlayer->Show_Arrow(myPlayer->Get_Camera(), screen) == false )
		{ 
		  P0_Logger << nl << "Player's Arrow Render Failed " << std::endl;    
		}
	}

	
	//Show the NPC on the screen
	if( myNPC->Show(myPlayer->Get_Camera(), screen) == false )
	{ 
      P0_Logger << nl << "NPC Render Failed " << std::endl;    
    }
	//Show the npc's arrow on the screen (if necessary)
	if (myNPC->Get_Attack_Style() == 2)
	{
		if( myNPC->Show_Arrow(myPlayer->Get_Camera(), screen) == false )
		{ 
		  P0_Logger << nl << "NPC's Arrow Render Failed " << std::endl;    
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

	//Display status msg
	if( myMessages->Show_Status_Msg(screen) == false )
	{ 
      P0_Logger << nl << "Display Attack Msg Render Failed " << std::endl;    
    }

	//Display monsters numbers
	if( myVictory_Screen->Show_Monsters_Stats(screen) == false )
	{ 
      P0_Logger << nl << "Display Monsters Stats Render Failed " << std::endl;    
    }

	if (GLOBAL_GAME_STATE == 4) {
		//Show Escape menu
		if( myEsc_Menu->Show_Menu(screen) == false )
		{ 
	      P0_Logger << nl << "Display Esc Menu Failed " << std::endl;    
	    }
	}

	if (GLOBAL_GAME_STATE == 5) {
		//Show Vicotry Screen menu
		if( myVictory_Screen->Show(screen) == false )
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
try {

//NPCs
/*	if (GLOBAL_GAME_STATE != 5 )//victory 
	{
		myNPC->Move(Global_Player_Vector, myEnvironment->Get_Environment_Sprite_Vector(), myBackGround->Get_BackGround_Sprite_Vector(), Global_Monster_Vector);
		//P0_Logger << nl << "Move NPC_Merchant " << std::endl;
	}
*/
//Monsters
	if (GLOBAL_GAME_STATE != 5 )//victory 
	{
		Monster_Factory_Skeleton->Move_Monsters( Global_Player_Vector, myEnvironment->Get_Environment_Sprite_Vector(), myBackGround->Get_BackGround_Sprite_Vector(), Global_Monster_Vector );
		//Monster_Factory_Worm->Move_Monsters( Global_Player_Vector, myEnvironment->Get_Environment_Sprite_Vector(), myBackGround->Get_BackGround_Sprite_Vector(), Global_Monster_Vector );
		//P0_Logger << nl << "Move Monsters " << std::endl;
	}

} catch (std::exception &exc) {
	P0_Logger << nl << " Render_Engine::postrender(), " << exc.what() << std::endl;
#ifdef _DEBUG
	throw std::logic_error("DEBUG_MODE -> Stop In Render_Engine::postrender()");
#endif
} catch (...) {
	P0_Logger << nl << "Unhandled Error In Render_Engine::postrender()" << std::endl; 
#ifdef _DEBUG
	throw std::logic_error("DEBUG_MODE -> Stop In Render_Engine::postrender()");
#endif
}
}
