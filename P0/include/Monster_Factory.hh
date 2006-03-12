#ifndef Monster_Factory_HH
#define Monster_Factory_HH

#include "Monster.hh"
#include "Base.hh"

//Monster Factory which create monsters, initialize them, move them, etc
class Monster_Factory
{
	private:

		int Number_Of_Monsters;
		VideoSurface* Screen;
		
		//Monster Vector which contains all monsters present on the battlefield and all theirs infos
		std::vector<Monster*> Monster_Vector;

		//Create Monster Method which create ONE SINGLE MONSTER ONLY and designed to by used by other method and not alone
		bool Create_One_Monster(int Character_X, int Character_Y);

	public:

		//Default Constructor
		Monster_Factory();

		//Constructor
		Monster_Factory(int number_of_monsters, VideoSurface* Screen_Surface);

		//Destructor
		~Monster_Factory();

		//Create Monster Method which create has many monsters has desired
		std::vector<Monster*> Create_Monsters(int Character_X, int Character_Y);

		//Invoke all monsters movements
		void Move_Monsters(Rect Character_Collision_Box);

		//Invoke all monsters movements animation on the screen
		void Move_Monsters_Animation(Rect Camera);

		//Remove all monster with dead status from the monster vector container
		std::vector<Monster*> Remove_Dead_Monsters();

		//Generate new monsters until max monster has been reached
		std::vector<Monster*> Generate_New_Monster(int Character_X, int Character_Y);

};

#endif
