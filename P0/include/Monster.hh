#ifndef Monster_HH
#define Monster_HH

#include "Base.hh"

//The Monster
class Monster
{
    private:
		//The X and Y offsets of the Monster
		int x, y;

		//Monster Tile
		RGBSurface _monsters_list;

		//Monster Tile Clip
		Rect _monster[1];

		//The velocity of the Monster
		int xVel, yVel;

	public:
		//The collision boxes of the Monster
		Rect collision_box;

		//Bool that will indicate if the monster is alive or dead
		bool Alive_Status;

		//Default construtor
		Monster();

		//Constructor that initialize the variables
		Monster(int X, int Y);

		//Copy construtor
		Monster(const Monster& ToCopy);

		//Destructor
		~Monster();

		//Move the Monster and check collision with the collision box of the character in parameter
		void move(Rect CharacterCollisionbox);
	    
		//Shows the Monster movement on the screen
		void move_animation(Rect Camera, VideoSurface* Screen);
};

#endif

