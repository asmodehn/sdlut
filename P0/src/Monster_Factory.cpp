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
//Create Monster Method which create has many monsters has desired
std::vector<Monster*> Monster_Factory::Create_Monsters()
{

	//Loop until desired number of monsters has been reached
	for(int i=0; i < Number_Of_Monsters; i++)
	{
		//Create Monster & initialized it
		Monster* myMonster = new Monster(32 * random(0,39), 32 * random(0,39), Screen);
		//Check initialization
		if( myMonster->Init() == false)
		{
			printf("Init Monster %i failed\n", i+1);
			SDL_Delay(2000);
			//return 1;
		}
		else {
			//store the monster at the end of the vector
			Monster_Vector.push_back(myMonster);
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
