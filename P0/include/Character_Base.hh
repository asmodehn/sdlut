#ifndef Character_HH
#define Character_HH

#include "Base.hh"
#include "Monster.hh"
#include "Timer.hh"

//Character Class
class Character_Base
{
    private:
		//The X and Y offsets of the Character
		int x, y;

		//Display Surface
		SDL_Surface *screen;
		VideoSurface* Screen;
	    
		//Character tiles
		RGBSurface Characters_Tile;
		RGBSurface Characters_Tile_Melee;
		RGBSurface Characters_Tile_Distant;

		//Character Clips
		Rect _character_right_attack[3];
		Rect _character_left_attack[3];
		Rect _character_down_attack[3];
		Rect _character_up_attack[3];

		//The velocity of the Character
		int xVel, yVel;

		//animation variables
		int frame, move_status;

		//Attack msg, font & color
		SDL_Surface *attack_msg_hit;
		SDL_Surface *attack_msg_miss;
		SDL_Surface *attack_melee_msg_hit;
		SDL_Surface *attack_melee_msg_miss;
		SDL_Surface *attack_distant_msg_hit;
		SDL_Surface *attack_distant_msg_miss;
		TTF_Font *attack_font;
		SDL_Color attack_Text_Color;

		//Monster Vector which allow the character to know exactly all monsters on the battlefield
		std::vector<Monster*> Monster_Vector;

		//Fight variables
		bool attack_status; //Attack yes or no 
		int attack_style; //Manage the style of attack 

		/***Arrow***/
		RGBSurface Arrow_Tile;
		Rect Arrow_Left[1];
		Rect Arrow_Right[1];
		Rect Arrow_Down[1];
		Rect Arrow_Up[1];

		/***Methods***/
		//Check if collision between the attack and one of the monsters on the battlefield regarding the number of movements that the attack collision is currently doing
		bool attack_check_status(int collision_box_movement);

	public:

		//Initializes the variables
		Character_Base(int X, int Y, SDL_Surface *Screen_Surface_old, VideoSurface* Screen_Surface, std::vector<Monster*> monster_vector);
		
		//The Camera that follow the character
		Rect Camera;

		//The collision boxes of the Character and his attack colliosion box
		Rect collision_box, attack_collision_box;

		//Destructor which free the surface 
		~Character_Base();
		
		//Init of the character (surface, msgs)
		bool Init();

		//Update the graphic regarding the attack style
		void Update_Graphic_Style();
	    
		//Takes key presses and adjust things accordingly
		bool input_mgt(SDL_Event &event);

		//Move the Character and check collision with the collisionbox of the monster in parameter
		void move();

		//Shows the character movement on the screen
		void move_animation();

		//Manage the character attack
		int attack();

		//Shows the character attack on the screen
		void attack_animation(int character_hit_distance);
		
		//Camera which follow the Character
		void following_camera();

		//Update charaster's monster knowledge of monster presents on the battlefield (in case of one monster has been killed for example)
		void Update_Monster_Knowledge (std::vector<Monster*> monster_vector);
};

#endif
