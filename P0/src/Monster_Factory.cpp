#include "Monster_Factory.hh"

//Default Constructor
Monster_Factory::Monster_Factory()
{
	Number_Of_Monsters = 0;
	Screen = NULL;
}
//Constructor
Monster_Factory::Monster_Factory(int number_of_monsters, SDL_Surface *screen_surface)
{
	Number_Of_Monsters = number_of_monsters;
	Screen = screen_surface;
}
//Destructor
Monster_Factory::~Monster_Factory()
{
	SDL_FreeSurface(Screen);
}
//Create Monster Method which create ONE SINGLE MONSTER ONLY and designed to by used by other method and not alone
bool Monster_Factory::Create_One_Monster()
{
	//Create Monster & initialized it
	Monster* myMonster = new Monster(32 * random(0,39), 32 * random(0,39), Screen);
	//Check initialization
	if( myMonster->Init() == false)
	{
		return false;
	}
	//store the monster at the end of the vector
	Monster_Vector.push_back(myMonster);
	return true;

}
//Create Monsters Method which create as many monsters has desired
std::vector<Monster*> Monster_Factory::Create_Monsters()
{
	//Loop until desired number of monsters has been reached
	for(int i=0; i < Number_Of_Monsters; i++)
	{
		if ( Create_One_Monster() == false )
		{
			printf("Init Monster %i failed\n", i);
			SDL_Delay(2000);
		}
	}

	return Monster_Vector;
}
//Invoke all monsters movements
void Monster_Factory::Move_Monsters(SDL_Rect &Character_Collision_Box)
{
	//Move Monsters
	for(int i=0; i < Monster_Vector.size(); i++)
	{
		Monster_Vector[i]->move(Character_Collision_Box);		
	}
}
//Invoke all monsters movements animation on the screen
void Monster_Factory::Move_Monsters_Animation(SDL_Rect Camera)
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
std::vector<Monster*> Monster_Factory::Generate_New_Monster()
{
	int temp = 0;
	
	//The more the monster on the battlefield, the less there a chance a new one is generated until we reached the MAX_MONSTERS_SIMULTANEOUSLY constant
	temp = random(1, MAX_MONSTERS_SIMULTANEOUSLY);
	
	if (temp > Monster_Vector.size())
	{
		//Monster generation
		if ( Create_One_Monster() == false )
		{
			printf("New Monster Generation failed\n");
			SDL_Delay(2000);
		}
	}
	
	//Finally return the new Vector wth eventual new monsters
	return Monster_Vector;
}