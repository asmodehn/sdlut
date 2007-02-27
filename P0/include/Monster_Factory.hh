#ifndef Monster_Factory_HH
#define Monster_Factory_HH

#include "Monsters.hh"
//#include "Base.hh"
//#include "BattleField.hh"

//Monster Factory which create monsters, initialize them, move them, etc
template <typename Monster_Template>
class Monster_Factory
{
	private:

		//How many monster must be generated
		int Initial_Number_Of_Monsters;
		
		//Monster Vector which contains all monsters present on the battlefield and all theirs infos
		std::vector<Character_Base*>* Monster_Vector;

		//Area vector which contain the battlefield cutting design
		std::vector<BattleField_Zone*>* BattleField_Cutting_Vector;

		//Create Monster Method which create ONE SINGLE MONSTER ONLY and check if not to near from the character
		Monster_Template* Create_One_Monster(int Character_X, int Character_Y);

	public:

		//Default Constructor
		Monster_Factory();

		//Constructor
		Monster_Factory(int number_of_monsters);
		
		//Destructor
		~Monster_Factory();

		//Create Monster Method which create has many monsters has desired
		std::vector<Character_Base*>* Create_Monsters(std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*>* environment_sprite_vector, std::vector<BattleField_Sprite*>* background_sprite_vector);
		
		//Invoke all monsters movements
		bool Move_Monsters(std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector ); //int nb_vector, ... );//, std::vector<Character_Base*> Monster_Vector_Skeleton, std::vector<Character_Base*> Monster_Vector_Worm);

		//Render all monsters on the screen
		bool Show_Monsters(Rect Camera, VideoSurface& Screen);

		//Remove all monster with dead status from the monster vector container
		std::vector<Character_Base*>* Remove_Dead_Monsters();
		
		//Generate new monsters until max monster has been reached
		std::vector<Character_Base*>* Generate_New_Monster(std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*> *environment_sprite_vector, std::vector<BattleField_Sprite*>* background_sprite_vector);
		
};

#endif
