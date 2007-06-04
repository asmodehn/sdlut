#ifndef Player_Base_HH
#define Player_Base_HH

#include "Character_Base.hh"
#include "Monster_Factory.hh"


//Player Base Class
class Player_Base : public Character_Base
{
    protected:
		//The X and Y offsets of the Arrow
		int arrow_x, arrow_y;
		int Arrow_Sprite_Width, Arrow_Sprite_Height;
		int Arrow_Vel;

		/***Arrow***/
		RGBSurface* Arrow_Tile;
		std::vector<Rect>* Arrow_SpriteRect;
		//Rect Arrow_SpriteRect[8][PLAYER_ARROW_ATTACK_ANIMATION_FRAME];
		Rect Current_Arrow_SpriteRect;

		//Battlefield rules
		/* virtual */ int Get_BG_vs_CH_Rules(const int& bgType);
		/* virtual */ int Get_Env_vs_CH_Rules(const int& envType);

		//Parse the xml file (called by the constructor)
		void Parse_Description_File(const string &Description_Filename);
		//Create an animation Center from the animation center filename
		Character_Animations_Center* Generate_Animation_Center(const string &Data_Root_Directory, const string &Animation_Center_Filename);


		//only to allow player to reimplement it else do the same thing as the character base method
		virtual void Attack_Reset();

	public:

		/****Definition****/

		//Initialize
		Player_Base();
		//Player_Base(int X, int Y);
		virtual ~Player_Base();

		/****Accessor****/

		inline void Set_Arrow_X(int new_Arrow_X)
		{
			arrow_x = new_Arrow_X;
		}
		inline int Get_Arrow_X() const
		{
			return arrow_x;
		}
		
		inline void Set_Arrow_Y(int new_Arrow_Y)
		{
			arrow_y = new_Arrow_Y;
		}
		inline int Get_Arrow_Y() const
		{
			return arrow_y;
		}

		inline void Set_Arrow_Vel(int new_Arrow_Vel)
		{
			Arrow_Vel = new_Arrow_Vel;
		}
		inline int Get_Arrow_Vel() const
		{
			return Arrow_Vel;
		}

		/****Methods****/

		//Move the Character and check collisions with everything (default: random move)
		virtual void Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector);

		//Set Arrow info for render (callback)
		bool Set_Arrow_Sprite_Coordinate();

		//blit the arrow on the screen
		bool Show_Arrow(const Rect& Camera, VideoSurface& Screen);
};

#endif
