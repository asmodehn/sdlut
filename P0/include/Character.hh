#ifndef Character_HH
#define Character_HH

#include "Project0.hh"

//Character Class
class Character
{
    private:
		//The X and Y offsets of the Character
		int x, y;
	    
		//Chracter tile
		SDL_Surface *_characters_list;

		//Character Clips
		SDL_Rect _character_right_attack[3];
		SDL_Rect _character_left_attack[3];
		SDL_Rect _character_down_attack[3];
		SDL_Rect _character_up_attack[3];

		//The velocity of the Character
		int xVel, yVel;

		//animation variables
		int frame, move_status;
		bool attack_status;


	public:

		//Initializes the variables
		Character(int X, int Y);
		
		//The Camera that follow the character
		SDL_Rect camera;

		//The collision boxes of the Character and his attack colliosion box
		SDL_Rect collision_box, attack_collision_box;

		//Destructor which free the surface 
		~Character();
		
		//Surface Initialiation
		bool Init();
	    
		//Takes key presses and adjust things accordingly
		bool input_mgt(SDL_Event &event);

		//Move the Character and check collision with the collisionbox of the monster in parameter
		void Character::move(SDL_Rect &_MonsterCollisionbox);

		//Shows the character movement on the screen
		void move_animation(SDL_Surface *screen);

		//Manage the character attack
		void attack(SDL_Rect &_MonsterCollisionBoxToBeKilled);

		//Shows the character attack on the screen
		void attack_animation(SDL_Surface *screen);
		
		//Camera which follow the Character
		void following_camera();
};

#endif
