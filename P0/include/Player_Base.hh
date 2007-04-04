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

		//Moving status define if the player is moving or just changing direction or staying at the same place
		bool moving_status;

		//The attack collision box of the player
		Rect attack_CB;

		//Fight variables
		bool attack_status; //Attack key pressed yes or no 
		int attack_style; //Manage the style of attack (0: nothing, 1: melee attack success; 2: distant attack success; 3&+: TO DO)
		int attack_successfull; //get the monster ID that has been hitted to print the good attack msg
			//initial info of the attack (-1 means no attack)
		int attack_initial_x;
		int attack_initial_y;
		int attack_direction;

		//players specifics tiles
		RGBSurface* Players_Tile_Melee;
		RGBSurface* Players_Tile_Distant;

		//Character Clips Vector
		std::vector<Rect>* Player_Attack_Tile_Rect;
		//
		//TODO(future): define one vector per style
		//

		//animation variables
		int frame;

		long DeltaTicks;

		/***Arrow***/
		RGBSurface* Arrow_Tile;
		std::vector<Rect>* Arrow_SpriteRect;
		//Rect Arrow_SpriteRect[8][PLAYER_ARROW_ATTACK_ANIMATION_FRAME];
		Rect Current_Arrow_SpriteRect;

		//Battlefield rules
		/* virtual */ int Get_BG_vs_CH_Rules(const int& bgType);
		/* virtual */ int Get_Env_vs_CH_Rules(const int& envType);
	public:

		/****Definition****/

		//Initialize
		Player_Base();
		Player_Base(int X, int Y);
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

		inline void Set_Attack_CB(Rect new_Attack_CB)
		{
			attack_CB = new_Attack_CB;
		}
		inline Rect Get_Attack_CB() const
		{
			return attack_CB;
		}

		//Define if the player has push the attack Key
		inline void Set_Attack_Status(bool new_attack_status)
        {
            attack_status=new_attack_status;
        }
		inline bool Get_Attack_Status() const
        {
            return attack_status;
        }

		inline void Set_Attack_Style(int new_attack_style)
        {
            attack_style = new_attack_style;
        }
        inline int Get_Attack_Style() const
        {
            return attack_style;
        }

		inline void Set_Attack_Successfull(int new_Attack_Successfull)
        {
            attack_successfull = new_Attack_Successfull;
        }
        inline int Get_Attack_Successfull() const
        {
            return attack_successfull;
        }

		inline void Set_Attack_Initial_X(int new_attack_initial_x)
        {
            attack_initial_x = new_attack_initial_x;
        }
        inline int Get_Attack_Initial_X() const
        {
            return attack_initial_x;
        }
		inline void Set_Attack_Initial_Y(int new_attack_initial_y)
        {
            attack_initial_y = new_attack_initial_y;
        }
        inline int Get_Attack_Initial_Y() const
        {
            return attack_initial_y;
        }
		inline void Set_Attack_Direction(int new_attack_direction)
        {
            attack_direction = new_attack_direction;
        }
        inline int Get_Attack_Direction() const
        {
            return attack_direction;
        }
		
		inline void Set_Moving_Status(bool new_moving_status)
        {
            moving_status = new_moving_status;
        }
        inline bool Get_Moving_Status() const
        {
            return moving_status;
        }

		inline void Set_DeltaTicks(long new_DeltaTicks)
        {
            DeltaTicks = new_DeltaTicks;
        }
        inline long Get_DeltaTicks() const
        {
            return DeltaTicks;
        }



		/****Methods****/

		//Update the graphic regarding the attack style
		bool Set_Attack_Style();
	    
		//Move the Character and check collisions with everything (default: random move)
		virtual bool Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector);

		//check the direction where the character is turn to
		bool Assign_Direction_Sprite();

		//define character sprite which appear on the screen during moves
		bool Set_Move_Animation_Sprite();

		//Manage the character attack
		bool Attack();

		//Check if collision between the attack and one of the monsters on the battlefield regarding the number of movements that the attack collision is currently doing and character infos
		int Attack_Check_Status(int attack_distance, int inflicted_damage, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector);

		//Set Character Sprite Which change when attack occured(callback)
		bool Set_Attack_Animation_Sprite(std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector);

		//Set Arrow info for render (callback)
		bool Set_Arrow_Sprite_Coordinate();

		//blit the arrow on the screen
		bool Show_Arrow(const Rect& Camera, VideoSurface& Screen);
};

#endif
