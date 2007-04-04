#include "Menus.hh"

///***ESCAPE MENU***///
//Escape_Menu Constructor
Escape_Menu::Escape_Menu()
{
	SelectedItemId = 1; //initially select the first one (aka "Yes")
	Yes_Tile = new RGBSurface("Data/Interface/LeaveMenu_YesSelected.png");
	No_Tile = new RGBSurface("Data/Interface/LeaveMenu_NoSelected.png");
}

//Destructor
Escape_Menu::~Escape_Menu()
{
	delete Yes_Tile, Yes_Tile = NULL;
	delete No_Tile, No_Tile = NULL;;
}

//Blit the good menu surface in function of what the user wants to select with the keyboard
bool Escape_Menu::Show_Menu(VideoSurface& Screen)
{
try {
	if (SelectedItemId == 1) //we want to show Yes selected
	{
		Screen.blit( *Yes_Tile, Point::Point(CURRENT_SCREEN_WIDTH/2 - 100, CURRENT_SCREEN_HEIGHT/2 - 50) );
	}
	else if (SelectedItemId == 2) //we want to show No selected
	{
		Screen.blit( *No_Tile, Point::Point(CURRENT_SCREEN_WIDTH/2 - 100, CURRENT_SCREEN_HEIGHT/2 - 50) );
	}
	return true; //no error
} catch (...) {
    return false; //error occured
}
}
//Managed validation on one item
bool Escape_Menu::Manage_Validation(int ValidatedItemId)
{
	if (ValidatedItemId == 1) //We have yes validated, the user wants to quit
	{
		// update _quitRequested to leave the mainloop
		return true;
	}
	else if (ValidatedItemId == 2) //We have no validated, the user wants to go back to the game
	{
		SelectedItemId = 1; //Reinit select item id
		GLOBAL_GAME_STATE = 3; //go back to normal game state
		return false;
	}
	else //ValidatedItemId == 0; do nothing but dont leave
	{
		return false;
	}

}


///***ViCTORY SCREEN***///
//Constructor
Victory_Screen::Victory_Screen()
{
	//Time
	Time_Font = new Font("Data/Fonts/SlimSansSerif.ttf", 20);
	//Monsters Stats
	Monsters_Stats_Font = new Font("Data/Fonts/SlimSansSerif.ttf", 14);
	//Victory Screen Tile
	Victory_Tile = new RGBSurface("Data/Interface/Victory Screen.png");
}

//Destructor
Victory_Screen::~Victory_Screen()
{
	delete Victory_Tile, Victory_Tile = NULL;
	delete Monsters_Stats_Font, Monsters_Stats_Font = NULL;
	delete Time_Font, Time_Font = NULL;
}

//show victory screen
bool Victory_Screen::Show(VideoSurface& Screen)
{
try {
	//Show Victory Screen
	Screen.blit( *Victory_Tile, Point::Point(CURRENT_SCREEN_WIDTH/2 - 100, CURRENT_SCREEN_HEIGHT/2 - 50) );
	
	//Show Time
	Screen.blit(*Time_Font->render(Time_Style(FiNiSH_TiME), Color(0, 0, 0), Font::Shaded, Color(0xFF, 0xFF, 0xFF)),
				Point::Point(CURRENT_SCREEN_WIDTH/2 - 10 , CURRENT_SCREEN_HEIGHT/2 + 7 ) );
	
	return true;
} catch (...) {
    return false; //error occured
}
}

//Save Victory Time
bool Victory_Screen::Save_Time()
{
try {
	std::ifstream fi_score("Best_Times.txt") ;
	if (fi_score.fail()) //File does not exist
	{
		Ini_Manager::Write_New_Ini_File("Best_Times.txt", Int_To_String(KiLLED_MONSTERS) + " Monsters Killed in : " + Time_Style(FiNiSH_TiME) + "\n" );
	} else {
		
		Ini_Manager::Append_To_Ini_File("Best_Times.txt", Int_To_String(KiLLED_MONSTERS) + " Monsters Killed in : " + Time_Style(FiNiSH_TiME) + "\n" );
	}

	fi_score.close();
	return true;
} catch (...) {
    return false; //error occured
}
}

//show number of killed & number of present monsters
bool Victory_Screen::Show_Monsters_Stats(VideoSurface& Screen)
{
try {
	//Show Numbers
	Screen.blit( *Monsters_Stats_Font->render("Monsters ALiVED: " + Int_To_String(ALiVE_MONSTERS) + "; Monsters KiLLED: " + Int_To_String(KiLLED_MONSTERS) , Color(0xFF, 0xFF, 0xFF), Font::Shaded),
				Point::Point(CURRENT_SCREEN_WIDTH - 200, CURRENT_SCREEN_HEIGHT - 20) );
	
	return true;
} catch (...) {
    return false; //error occured
}
}
