#ifndef Monster_Factory_HH
#define Monster_Factory_HH

#include "Monsters.hh"
#include "Base.hh"
#include "BattleField.hh"

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

		//Create Monster Method which create ONE SINGLE MONSTER ONLY and check if not to near from the character
		Monster_Skeleton* Create_One_Monster(int Character_X, int Character_Y, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);

	public:

		//Default Constructor
		Monster_Factory();

		//Constructor
		Monster_Factory(int number_of_monsters);

		//Destructor
		~Monster_Factory();

		//Create Monster Method which create has many monsters has desired
		//std::vector<Monster_Template*> Create_Monsters(int Character_X, int Character_Y);
		std::vector<Monster_Skeleton*> Create_Monsters(int Character_X, int Character_Y, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);

		//Invoke all monsters movements
		void Move_Monsters(Rect Character_Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);

		//Invoke all monsters movements animation on the screen
		void Move_Monsters_Animation(Rect Camera, VideoSurface& Screen);

		//Remove all monster with dead status from the monster vector container
		//std::vector<Monster_Template*> Remove_Dead_Monsters();
		std::vector<Monster_Skeleton*> Remove_Dead_Monsters();

		//Generate new monsters until max monster has been reached
		//std::vector<Monster_Template*> Generate_New_Monster(int Character_X, int Character_Y);
		std::vector<Monster_Skeleton*> Generate_New_Monster(int Character_X, int Character_Y, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);

};

#endif
