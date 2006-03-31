#ifndef Monster_Factory_HH
#define Monster_Factory_HH

#include "Monsters.hh"
#include "Base.hh"

//Monster Factory which create monsters, initialize them, move them, etc
//template <typename Monster_Template>
class Monster_Factory
{
	private:

		//How many monster must be generated
		int Number_Of_Monsters;
		
		//Monster Vector which contains all monsters present on the battlefield and all theirs infos
		//std::vector<Monster_Template*> Monster_Vector;
		std::vector<Monster_Skeleton*> Monster_Vector;

		//Create Monster Method which create ONE SINGLE MONSTER ONLY and designed to by used by other method and not alone
		void Create_One_Monster(int Character_X, int Character_Y);

	public:

		//Default Constructor
		Monster_Factory();

		//Constructor
		Monster_Factory(int number_of_monsters);

		//Destructor
		~Monster_Factory();

		//Create Monster Method which create has many monsters has desired
		//std::vector<Monster_Template*> Create_Monsters(int Character_X, int Character_Y);
		std::vector<Monster_Skeleton*> Create_Monsters(int Character_X, int Character_Y);

		//Invoke all monsters movements
		void Move_Monsters(Rect Character_Collision_Box, std::vector<BattleField_Sprite*> BattleField_Sprite_Vector);

		//Invoke all monsters movements animation on the screen
		void Move_Monsters_Animation(Rect Camera, VideoSurface& Screen);

		//Remove all monster with dead status from the monster vector container
		//std::vector<Monster_Template*> Remove_Dead_Monsters();
		std::vector<Monster_Skeleton*> Remove_Dead_Monsters();

		//Generate new monsters until max monster has been reached
		//std::vector<Monster_Template*> Generate_New_Monster(int Character_X, int Character_Y);
		std::vector<Monster_Skeleton*> Generate_New_Monster(int Character_X, int Character_Y);

};

#endif
