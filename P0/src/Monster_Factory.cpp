#include "Monster_Factory.hh"

//Default Constructor
Monster_Factory::Monster_Factory()
{
	Number_Of_Monsters = 0;
	Screen = NULL;
}
//Constructor
Monster_Factory::Monster_Factory(int number_of_monsters, VideoSurface* Screen_Surface)
{
	Number_Of_Monsters = number_of_monsters;
	Screen = Screen_Surface;
}
//Destructor
Monster_Factory::~Monster_Factory()
{
	delete Screen;
}
//Create Monster Method which create ONE SINGLE MONSTER ONLY and designed to by used by other method and not alone
bool Monster_Factory::Create_One_Monster(int Character_X, int Character_Y)
{
	//Determine monster creation position
	int x = 0, y = 0;

	//Check if monster is not too near of the character if so try again: monsters can't born in the 3 square radius near the character
	x = random(0,39);
	while ( (x >= (Character_X/32 - 3)) && (x <= (Character_X/32 + 3)) )
	{
		x = random(0,39);
	}

	y = random(0,39);
	while ( (y >= (Character_Y/32 - 3)) && (y <= (Character_Y/32 + 3)) )
	{
		y = random(0,39);
	}

	//Create Monster & initialized it
	Monster* myMonster = new Monster(32 * x, 32 * y, Screen);

	//store the monster at the end of the vector
	Monster_Vector.push_back(myMonster);
	return true;

}
//Create Monsters Method which create as many monsters has desired
std::vector<Monster*> Monster_Factory::Create_Monsters(int Character_X, int Character_Y)
{
	//Loop until desired number of monsters has been reached
	for(int i=1; i <= Number_Of_Monsters; i++)
	{
		if ( Create_One_Monster(Character_X, Character_Y) == false )
		{
			printf("Init Monster %i failed\n", i);
			Timer::delay(2000);
		}
	}

	return Monster_Vector;
}
//Invoke all monsters movements
void Monster_Factory::Move_Monsters(Rect Character_Collision_Box)
{
	//Move Monsters
	for(int i=0; i < Monster_Vector.size(); i++)
	{
		Monster_Vector[i]->move(Character_Collision_Box);		
	}
}
//Invoke all monsters movements animation on the screen
void Monster_Factory::Move_Monsters_Animation(Rect Camera)
{
	for(int i=0; i < Monster_Vector.size(); i++)
	{
		Monster_Vector[i]->move_animation(Camera);		
	}
}
//Method that will remove all monster with Alive_Status status to false (aka dead monsters) from the monster vector container
std::vector<Monster*> Monster_Factory::Remove_Dead_Monsters()
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
std::vector<Monster*> Monster_Factory::Generate_New_Monster(int Character_X, int Character_Y)
{
	int temp = 0;
	
	//The more the monster on the battlefield, the less there a chance a new one is generated until we reached the MAX_MONSTERS_SIMULTANEOUSLY constant
	temp = random(1, MAX_MONSTERS_SIMULTANEOUSLY);
	if (temp > Monster_Vector.size())
	{
		//Monster generation
		if ( Create_One_Monster(Character_X, Character_Y) == false )
		{
			printf("New Monster Generation failed\n");
			Timer::delay(2000);
		}
	}
	
	//Finally return the new Vector wth eventual new monsters
	return Monster_Vector;
}