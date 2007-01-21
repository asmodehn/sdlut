#include "Menus.hh"

//Escape_Menu Constructor
Escape_Menu::Escape_Menu()
{
	SelectedItemId = 1; //initially select the first one (aka "Yes")
	ValidatedItemId = 0; //No validated id 
}

//Blit the good menu surface in function of what the user wants to select with the keyboard
bool Escape_Menu::Show_Menu(VideoSurface& Screen)
{
try {
	if (SelectedItemId == 1) //we want to show Yes selected
	{
		Screen.blit(RGBSurface("Datas/Interface/LeaveMenu_YesSelected.png"), Point::Point(CURRENT_SCREEN_WIDTH/2 - 100, CURRENT_SCREEN_HEIGHT/2 - 50) );
	}
	else if (SelectedItemId == 2) //we want to show No selected
	{
		Screen.blit(RGBSurface("Datas/Interface/LeaveMenu_NoSelected.png"), Point::Point(CURRENT_SCREEN_WIDTH/2 - 100, CURRENT_SCREEN_HEIGHT/2 - 50) );
	}
	return true; //no error
} catch (...) {
    return false; //error occured
}
}
//Managed validation on one item
bool Escape_Menu::Manage_Validation()
{
	if (ValidatedItemId == 1) //We have yes validated, the user wants to quit
	{
		// update _quitRequested to leave the mainloop
		return true;
	}
	else if (ValidatedItemId == 2) //We have no validated, the user wants to go back to the game
	{
		SelectedItemId = 1; //Reinit select item id
		ValidatedItemId = 0; //we leave the menu so no item is now validated
		GLOBAL_GAME_STATE = 3; //go back to normal game state
		return false;
	}
	else //ValidatedItemId == 0; do nothing but dont leave
	{
		return false;
	}

}
