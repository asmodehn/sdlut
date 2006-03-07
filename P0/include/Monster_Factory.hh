#ifndef Monster_Factory_HH
#define Monster_Factory_HH

#include "Monster.hh"
#include "Base.hh"

//Monster Factory which create monsters, initialize them, move them, etc
class Monster_Factory
{
	private:

		int Number_Of_Monsters;
		SDL_Surface *Screen;
		//Monster Vector
		std::vector<Monster*> Monster_Vector;

	public:

		//Default Constructor
		Monster_Factory();

		//Constructor
		Monster_Factory(int number_of_monsters, SDL_Surface *screen_surface);

		//Destructor
		~Monster_Factory();

		//Create Monster Method which create has many monsters has desired
		std::vector<Monster*> Create_Monsters();

		//Invoke all monsters movements
		void Move_Monsters(SDL_Rect &Character_Collision_Box);

		//Invoke all monsters movements animation on the screen
		void Move_Monsters_Animation(SDL_Rect Camera);

		//Remove all monster with dead status from the monster vector container
		std::vector<Monster*> Remove_Dead_Monsters();

};

#endif
