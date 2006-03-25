#ifndef Menus_HH
#define Menus_HH

#include "Base.hh"

//Escape Menu Class that is used when the user push the escape key while ingame
class Escape_Menu
{
    private:
		int SelectedItemId;
		int ValidatedItemId;

	public:

		Escape_Menu();
		~Escape_Menu();

		/****Wrapper****/
		void Set_SelectedItemId(int new_SelectedItemId)
		{
			SelectedItemId=new_SelectedItemId;
		}
		int Get_SelectedItemId()
		{
			return SelectedItemId;
		}
		void Set_ValidatedItemId(int new_ValidatedItemId)
		{
			ValidatedItemId = new_ValidatedItemId;
		}
		int Get_ValidatedItemId()
		{
			return ValidatedItemId;
		}

		/****Methods****/
		//Blit the good menu surface in function of what the user wants to select with the keyboard
		void Show_Menu(VideoSurface& Screen);
		//Managed validation on one item (if return true => quit program)
		bool Escape_Menu::Manage_Validation();

};

#endif
