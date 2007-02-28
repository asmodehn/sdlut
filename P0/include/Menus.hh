#ifndef Menus_HH
#define Menus_HH

#include "Base.hh"

//Escape Menu Class that is used when the user push the escape key while ingame
class Escape_Menu
{
    private:
		int SelectedItemId;
		RGBSurface Yes_Tile, No_Tile;

	public:

		Escape_Menu();

		/****Wrapper****/
		inline void Set_SelectedItemId(int new_SelectedItemId)
		{
			SelectedItemId=new_SelectedItemId;
		}
		inline int Get_SelectedItemId()
		{
			return SelectedItemId;
		}

		/****Methods****/
		//Blit the good menu surface in function of what the user wants to select with the keyboard
		bool Show_Menu(VideoSurface& Screen);
		//Managed validation on one item (if return true => quit program)
		bool Manage_Validation(int ValidatedItemId);

};

//Victory screen
class Victory_Screen
{
	private:
		Font* Time_Font;
		Font* Monsters_Stats_Font;
		RGBSurface Victory_Tile;

		RGBSurface time_msg;
		RGBSurface monsters_stats_msg;
		
		
	public:
		Victory_Screen();
		~Victory_Screen();

		//Save Victory Time
		bool Save_Time();
		//show victory screen
		bool Show(VideoSurface& Screen);
		//show number of killed & number of present monsters
		bool Show_Monsters_Stats(VideoSurface& Screen);
};

#endif
