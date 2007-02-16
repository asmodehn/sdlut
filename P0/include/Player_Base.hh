#ifndef Player_Base_HH
#define Player_Base_HH

#include "Character_Base.hh"
#include "Monster_Factory.hh"


//Character Class
class Player_Base : public Character_Base
{
    private:
		//The X and Y offsets of the Arrow
		int arrow_x, arrow_y;

		//Moving status define if the player is moving or just changing direction or staying at the same place
		bool moving_status;

		//The collision boxes of the Character and his attack colliosion box
		Rect attack_collision_box;

		//Fight variables
		bool attack_status; //Attack key pressed yes or no 
		int attack_style; //Manage the style of attack 
		int attack_successfull; //Manage the attack displayed msg (0: nothing, 1: melee attack success; 2: distant attack success; 3&+: TO DO)

		//players specifics tiles
		RGBSurface Players_Tile_Melee;
		RGBSurface Players_Tile_Distant;

		//Character Clips Vector
		std::vector<Rect>* Player_Attack_Tile_Rect;
		//
		//TODO: newxt version, define one vector per style
		//

		//animation variables
		int frame, arrow_frame, move_status;

		//Attack msg, font & color
		RGBSurface attack_msg; //Will contains the final attack display msg after all other check (style, status, attack successfull, ...)
		RGBSurface attack_msg_hit;
		RGBSurface attack_msg_miss;
		RGBSurface attack_melee_msg_hit;
		RGBSurface attack_melee_msg_miss;
		RGBSurface attack_distant_msg_hit;
		RGBSurface attack_distant_msg_miss;
		//Font AttackMsg_Font(28);

		/***Arrow***/
		RGBSurface Arrow_Tile;
		std::vector<Rect>* Arrow_SpriteRect;
		//Rect Arrow_SpriteRect[8][PLAYER_ARROW_ATTACK_ANIMATION_FRAME];
		Rect Current_Arrow_SpriteRect;

		//Hit distance
		int hit_monster_distance;

		//The Camera that follow the character
		Rect Camera;

		//Check if collision between the attack and one of the monsters on the battlefield regarding the number of movements that the attack collision is currently doing and character infos
		int attack_check_status(int current_hit_distance, int character_damage, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector);

		//Battlefield rules
		/* virtual */ int Get_BG_vs_CH_Rules(int bgType);
		/* virtual */ int Get_Env_vs_CH_Rules(int envType);
	public:

		/****Definition****/

		//Initializes the variables
		Player_Base(int X, int Y);

		/****Accessor****/
		inline void Set_Camera(Rect new_Camera)
        {
            Camera = new_Camera;
        }
        inline Rect Get_Camera() const
        {
            return Camera;
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
		
		inline void Set_Hit_Monster_Distance(int new_Hit_Monster_Distance)
        {
            hit_monster_distance = new_Hit_Monster_Distance;
        }
        inline int Get_Hit_Monster_Distance() const
        {
            return hit_monster_distance;
        }

		inline void Set_Moving_Status(bool new_moving_status)
        {
            moving_status = new_moving_status;
        }
        inline bool Get_Moving_Status() const
        {
            return moving_status;
        }



		/****Methods****/

		//Update the graphic regarding the attack style
		bool Update_Graphic_Style();
	    
		//Move the Character and check collisions with everything
		bool move(unsigned long deltaticks, std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector);

		//check the direction where the character is turn to
		bool assign_direction_sprite();

		//define character sprite which appear on the screen during moves
		bool Set_Move_Animation_Sprite();

		//Manage the character attack
		int attack(std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector);

		//Set Character Sprite Which change when attack occured
		bool Set_Attack_Animation_Sprite();

		//Set Arrow info for animation
		bool Set_Arrow_Sprite_Coordinate();

		//blit the arrow on the screen
		bool Show_Arrow(VideoSurface& Screen);

		//Display attack msg on the status bar (hit or miss)
		bool Show_Attack_Msg(VideoSurface& Screen);
		
		//Camera which follow the Character
		bool following_camera();
};

#endif
