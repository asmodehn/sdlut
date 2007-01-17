#ifndef Player_Base_HH
#define Player_Base_HH

#include "Character_Base.hh"
#include "Monsters.hh"


//Character Class
class Player_Base : public Character_Base
{
    private:
		//The X and Y offsets of the Arrow
		int arrow_x, arrow_y;

		//Moving status define if the player is moving or just changing direction or staying at the same place
		bool moving_status;

		//Fight variables
		bool attack_status; //Attack key pressed yes or no 
		int attack_style; //Manage the style of attack 
		int attack_successfull; //Manage the attack displayed msg (0: nothing, 1: melee attack success; 2: distant attack success; 3&+: TO DO)

		//players specifics tiles
		RGBSurface Players_Tile_Melee;
		RGBSurface Players_Tile_Distant;

		//Character Clips
		Rect _player_right_attack[3];
		Rect _player_left_attack[3];
		Rect _player_down_attack[3];
		Rect _player_up_attack[3];
		Rect Player_SpriteRect;

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
		Rect Arrow_Left[1];
		Rect Arrow_Right[1];
		Rect Arrow_Down[1];
		Rect Arrow_Up[1];
		Rect Arrow_SpriteRect;

		//Hit distance
		int hit_monster_distance;

		//Check if collision between the attack and one of the monsters on the battlefield regarding the number of movements that the attack collision is currently doing
		int attack_check_status(int collision_box_movement, std::vector<Monster_Base*> Monster_Vector_Skeleton, std::vector<Monster_Base*> Monster_Vector_Worm);

		//Check if the ground allow the player presence
		std::vector<int> check_background_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);

		//Check if the environment allow the player presence
		std::vector<int> check_environment_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector);

		//Check if the battlefield allow the player presence
		bool check_battlefield_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);

	public:

		/****Variables****/

		//The Camera that follow the character
		Rect Camera;

		//The collision boxes of the Character and his attack colliosion box
		Rect collision_box, attack_collision_box;


		/****Definitions****/

		//Initializes the variables
		Player_Base(int X, int Y);

		//Destructor which free the surface 
		~Player_Base();
		

		/****Accessor****/

		void Set_xVel(int new_xVel)
        {
            xVel = new_xVel;
        }
		int Get_xVel() const
        {
            return xVel;
        }

		void Set_yVel(int new_yVel)
        {
            yVel = new_yVel;
        }
        int Get_yVel() const
        {
            return yVel;
        }

		//Define if the player has push the attack Key
		void Set_Attack_Status(bool new_attack_status)
        {
            attack_status=new_attack_status;
        }
		bool Get_Attack_Status() const
        {
            return attack_status;
        }

		void Set_Attack_Style(int new_attack_style)
        {
            attack_style = new_attack_style;
        }
        int Get_Attack_Style() const
        {
            return attack_style;
        }

		void Set_Attack_Successfull(int new_Attack_Successfull)
        {
            attack_successfull = new_Attack_Successfull;
        }
        int Get_Attack_Successfull() const
        {
            return attack_successfull;
        }
		
		void Set_Hit_Monster_Distance(int new_Hit_Monster_Distance)
        {
            hit_monster_distance = new_Hit_Monster_Distance;
        }
        int Get_Hit_Monster_Distance() const
        {
            return hit_monster_distance;
        }

		void Set_Moving_Status(bool new_moving_status)
        {
            moving_status = new_moving_status;
        }
        bool Get_Moving_Status() const
        {
            return moving_status;
        }



		/****Methods****/

		//Update the graphic regarding the attack style
		bool Update_Graphic_Style();
	    
		//Move the Character and check collision with monsters and the battlefield (environment and background)
		bool move(std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector, std::vector<Monster_Base*> Monster_Vector_Skeleton, std::vector<Monster_Base*> Monster_Vector_Worm);

		//check the direction where the character is turn to
		bool assign_direction_sprite();

		//define character sprite which appear on the screen during moves
		bool Set_Move_Animation_Sprite();

		//Manage the character attack
		int attack(std::vector<Monster_Base*> Monster_Vector_Skeleton, std::vector<Monster_Base*> Monster_Vector_Worm);

		//Set Character Sprite Which change when attack occured
		bool Set_Attack_Animation_Sprite();

		//Set Arrow info for animation
		bool Set_Arrow_Sprite_Coordinate();

		//blit the character on the screen
		bool Show_Player(VideoSurface& Screen);

		//blit the arrow on the screen
		bool Show_Arrow(VideoSurface& Screen);

		//Display attack msg on the status bar (hit or miss)
		bool Display_Attack_Msg(VideoSurface& Screen);
		
		//Camera which follow the Character
		bool following_camera();
};

#endif
