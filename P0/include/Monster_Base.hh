#ifndef Monster_Base_HH
#define Monster_Base_HH

#include "Base.hh"
#include "BattleField.hh"

//The Monster
class Monster_Base
{
    protected:
		//The X and Y offsets of the Monster
		int x, y;

		//Monster Tile
		RGBSurface _monsters_list;

		//Monster Tile Clip
		Rect _monster[1];

		//The velocity of the Monster
		int xVel, yVel;

		//Check if the background allow the monster presence
		virtual bool check_background_allow_monster(int x, int y, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);
		//Check if the environment allow the monster presence
		virtual int check_environment_allow_monster(int x, int y, std::vector<BattleField_Sprite*> Environment_Sprite_Vector);

	public:
		//The collision boxes of the Monster
		Rect collision_box;

		//Bool that will indicate if the monster is alive or dead
		bool Alive_Status;

		//Default construtor
		Monster_Base();

		//Constructor that initialize the variables
		Monster_Base(int X, int Y);

		//Copy construtor
		Monster_Base(const Monster_Base& ToCopy);

		//Destructor
		~Monster_Base();

		//Move the Monster and check collision with the collision box of the character in parameter
		void move(Rect CharacterCollisionbox, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);
	    
		//Check if the battlefield allow the monster presence
		virtual bool check_battlefield_allow_monster(int x, int y, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);

		//Shows the Monster movement on the screen
		void move_animation(Rect Camera, VideoSurface& Screen);
};

#endif

