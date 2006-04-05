#include "Monster_Factory.hh"

//Default Constructor
//template <typename Monster_Template>
//Monster_Factory<Monster_Template>::Monster_Factory()
Monster_Factory::Monster_Factory()
{
	Number_Of_Monsters = 0;
}
//Constructor
//template <typename Monster_Template>
//Monster_Factory<Monster_Template>::Monster_Factory(int number_of_monsters)
Monster_Factory::Monster_Factory(int number_of_monsters)
{
	Number_Of_Monsters = number_of_monsters;
}
//Destructor
//template <typename Monster_Template>
//Monster_Factory<Monster_Template>::~Monster_Factory()
Monster_Factory::~Monster_Factory()
{
}
//Create Monster Method which create ONE SINGLE MONSTER ONLY and designed to by used by other method and not alone
//template <typename Monster_Template>
//void Monster_Factory<Monster_Template>::Create_One_Monster(int Character_X, int Character_Y)
Monster_Skeleton* Monster_Factory::Create_One_Monster(int Character_X, int Character_Y)
{
	//Determine monster creation position
	int x = 0, y = 0;

	//mini distance (3 square radius from the character border)
	int distance_mini = int( 3.5*sqrt( float(CH_WIDTH*CH_WIDTH + CH_HEIGHT*CH_HEIGHT) ) );
	
	//Monster coord
	x = random(0,39);
	y = random(0,39);

	//distance from the center - distance center to border of the character
	int distance = int( sqrt( float( (x*CH_WIDTH - (Character_X+CH_WIDTH/2))*(x*CH_WIDTH - (Character_X+CH_WIDTH/2)) + (y*CH_HEIGHT - (Character_Y+CH_HEIGHT/2))*(y*CH_HEIGHT - (Character_Y+CH_HEIGHT/2)) ) )
						- 0.5*sqrt( float(CH_WIDTH*CH_WIDTH + CH_HEIGHT*CH_HEIGHT) ) );
	while (distance <= distance_mini) //we are too near
	{
		//retry
		x = random(0,39);
		y = random(0,39);
		distance = int( sqrt( float( (x*CH_WIDTH - (Character_X+CH_WIDTH/2))*(x*CH_WIDTH - (Character_X+CH_WIDTH/2)) + (y*CH_HEIGHT - (Character_Y+CH_HEIGHT/2))*(y*CH_HEIGHT - (Character_Y+CH_HEIGHT/2)) ) )
					- 0.5*sqrt( float(CH_WIDTH*CH_WIDTH + CH_HEIGHT*CH_HEIGHT) ) );
	}

	//Create Monster & initialized it
	//Monster_Template* myMonster = new Monster_Template(MO_WIDTH * x, MO_HEIGHT * y);
	Monster_Skeleton* myMonster = new Monster_Skeleton(MO_WIDTH * x, MO_HEIGHT * y);

	return myMonster;
}
//Create Monsters Method which create as many monsters has desired
//template <typename Monster_Template>
//std::vector<Monster_Template*> Monster_Factory<Monster_Template>::Create_Monsters(int Character_X, int Character_Y)
//std::vector<Monster*> Monster_Factory<Monster_Template>::Create_Monsters(int Character_X, int Character_Y)
std::vector<Monster_Skeleton*> Monster_Factory::Create_Monsters(int Character_X, int Character_Y, std::vector<BattleField_Sprite*> environment_sprite_vector, std::vector<BattleField_Sprite*> background_sprite_vector)
{
	//Loop until desired number of monsters has been reached
	for(int i=1; i <= Number_Of_Monsters; i++)
	{
		//Monster generation
		Monster_Skeleton* newMonster = Create_One_Monster(Character_X, Character_Y);

		//Check if the battlefield allow the monster creation
		while(! newMonster->check_battlefield_allow_monster(newMonster->collision_box.getx(), newMonster->collision_box.gety(), environment_sprite_vector, background_sprite_vector) )
		{
			//regeneration
			delete(newMonster);
			newMonster = Create_One_Monster(Character_X, Character_Y);
		}

		//Store the monster at the end of the vector
		Monster_Vector.push_back(newMonster);
	}

	return Monster_Vector;
}
//Invoke all monsters movements
//template <typename Monster_Template>
//void Monster_Factory<Monster_Template>::Move_Monsters(Rect Character_Collision_Box, std::vector<BattleField_Sprite*> BattleField_Sprite_Vector)
void Monster_Factory::Move_Monsters(Rect Character_Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
	//Move Monsters
	for(int i=0; i < Monster_Vector.size(); i++)
	{
		Monster_Vector[i]->move(Character_Collision_Box, Environment_Sprite_Vector, BackGround_Sprite_Vector);		
	}
}
//Invoke all monsters movements animation on the screen
//template <typename Monster_Template>
//void Monster_Factory<Monster_Template>::Move_Monsters_Animation(Rect Camera, VideoSurface& Screen)
void Monster_Factory::Move_Monsters_Animation(Rect Camera, VideoSurface& Screen)
{
	for(int i=0; i < Monster_Vector.size(); i++)
	{
		Monster_Vector[i]->move_animation(Camera, Screen);		
	}
}
//Method that will remove all monster with Alive_Status status to false (aka dead monsters) from the monster vector container
//template <typename Monster_Template>
//std::vector<Monster_Template*> Monster_Factory<Monster_Template>::Remove_Dead_Monsters()
//std::vector<Monster_Skeleton*> Monster_Factory<Monster_Template>::Remove_Dead_Monsters()
std::vector<Monster_Skeleton*> Monster_Factory::Remove_Dead_Monsters()
{
	//Loop on all the vector
	for(int i=0; i < Monster_Vector.size(); i++)
	{
		//Check if Alive_Status is false
		if (Monster_Vector[i]->Alive_Status == false)
		{
			//remove the monster from the scope (only the ième monster at a time)
			Monster_Vector.erase(Monster_Vector.begin()+i, Monster_Vector.begin()+i+1);

			//Then go back of one in the loop because elements has been shifted
			i--;
		}
	}
	//Finally return the new Vector with only alive monsters
	return Monster_Vector;
}

//Generate new monsters until max monster has been reached
//template <typename Monster_Template>
//std::vector<Monster_Template*> Monster_Factory<Monster_Template>::Generate_New_Monster(int Character_X, int Character_Y)
//std::vector<Monster_Skeleton*> Monster_Factory<Monster_Template>::Generate_New_Monster(int Character_X, int Character_Y)
std::vector<Monster_Skeleton*> Monster_Factory::Generate_New_Monster(int Character_X, int Character_Y, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
	int temp = 0;
	
	//The more the monster on the battlefield, the less there a chance a new one is generated until we reached the MAX_MONSTERS_SIMULTANEOUSLY constant
	temp = random(1, MAX_MONSTERS_SIMULTANEOUSLY);
	if (temp > Monster_Vector.size())
	{
		//Monster generation
		Monster_Skeleton* newMonster = Create_One_Monster(Character_X, Character_Y);

		//Check if the battlefield allow the monster creation
		while(! newMonster->check_battlefield_allow_monster(newMonster->collision_box.getx(), newMonster->collision_box.gety(), Environment_Sprite_Vector, BackGround_Sprite_Vector) )
		{
			//regeneration
			delete(newMonster);
			newMonster = Create_One_Monster(Character_X, Character_Y);
		}

		//Store the monster at the end of the vector
		Monster_Vector.push_back(newMonster);
	}
	
	//Finally return the new Vector wth eventual new monsters
	return Monster_Vector;
}
