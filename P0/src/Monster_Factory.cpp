#include "Monster_Factory.hh"

//Default Constructor
template <typename Monster_Template>
Monster_Factory<Monster_Template>::Monster_Factory()
{
	Initial_Number_Of_Monsters = 0;
	Monster_Vector = new std::vector<Character_Base*>;
	BattleField_Cutting_Vector = new std::vector<BattleField_Zone*>;
}

//Constructor
template <typename Monster_Template>
Monster_Factory<Monster_Template>::Monster_Factory(int number_of_monsters)
{
	Initial_Number_Of_Monsters = number_of_monsters;
	Monster_Vector = new std::vector<Character_Base*>;
	BattleField_Cutting_Vector = BattleField_Zone::Fill_Vector();

	Monster_Template::Initialize(BASE_LIFE, Current_Life, BASE_ARMOR, Current_Armor, Sprite_Width, Sprite_Height, Characters_Tile,
								Life_Bar_Tile, empty_life_bar_rect, current_life_bar_rect);

	P0_Logger << nl << "Factory CONSTRUCTED Successfully " << std::endl;
}

//Destructor
template <typename Monster_Template>
Monster_Factory<Monster_Template>::~Monster_Factory()
{
	delete Monster_Vector, Monster_Vector = NULL;
	delete BattleField_Cutting_Vector, BattleField_Cutting_Vector = NULL;
}

//Create Monster Method which create ONE SINGLE MONSTER ONLY and designed to by used by other method and not alone
template <typename Monster_Template>
Monster_Template* Monster_Factory<Monster_Template>::Create_One_Monster(int Character_X, int Character_Y)
{
	//Determine monster creation position
	int x = 0, y = 0;

	//mini distance (3 square radius from the character border)²
	/*int distance_mini = int( 3.5*sqrt( float(PC_WIDTH*PC_WIDTH + PC_HEIGHT*PC_HEIGHT) ) );*/
	int distance_mini_carre = int( 3.5*sqrt( float(PC_WIDTH*PC_WIDTH + PC_HEIGHT*PC_HEIGHT) ) ); //int( 12.25*(PC_WIDTH*PC_WIDTH + PC_HEIGHT*PC_HEIGHT ) );
	
	//(distance from the center - distance center to border of the character)²
	/*int distance = int( sqrt( float( (x*PC_WIDTH - (Character_X+PC_WIDTH/2))*(x*PC_WIDTH - (Character_X+PC_WIDTH/2)) + (y*PC_HEIGHT - (Character_Y+PC_HEIGHT/2))*(y*PC_HEIGHT - (Character_Y+PC_HEIGHT/2)) ) )
						- 0.5*sqrt( float(PC_WIDTH*PC_WIDTH + PC_HEIGHT*PC_HEIGHT) ) );*/
	int distance_carre = distance_mini_carre;
	
		//while (distance <= distance_mini) //we are too near
	while ( distance_carre <= distance_mini_carre ) //we are too near
	{
		//try coordinate
		x = random(0,39);
		y = random(0,39);
		/*distance = int( sqrt( float( (x*PC_WIDTH - (Character_X+PC_WIDTH/2))*(x*PC_WIDTH - (Character_X+PC_WIDTH/2)) + (y*PC_HEIGHT - (Character_Y+PC_HEIGHT/2))*(y*PC_HEIGHT - (Character_Y+PC_HEIGHT/2)) ) )
					- 0.5*sqrt( float(PC_WIDTH*PC_WIDTH + PC_HEIGHT*PC_HEIGHT) ) );*/
		distance_carre = int( sqrt( float( (x*PC_WIDTH - (Character_X+PC_WIDTH/2))*(x*PC_WIDTH - (Character_X+PC_WIDTH/2)) + (y*PC_HEIGHT - (Character_Y+PC_HEIGHT/2))*(y*PC_HEIGHT - (Character_Y+PC_HEIGHT/2)) ) )
						- 0.5*sqrt( float(PC_WIDTH*PC_WIDTH + PC_HEIGHT*PC_HEIGHT) ) );
			/*int( (x*PC_WIDTH - (Character_X+PC_WIDTH/2))*(x*PC_WIDTH - (Character_X+PC_WIDTH/2)) + (y*PC_HEIGHT - (Character_Y+PC_HEIGHT/2))*(y*PC_HEIGHT - (Character_Y+PC_HEIGHT/2))
						+ 0.25*(PC_WIDTH*PC_WIDTH + PC_HEIGHT*PC_HEIGHT)
						- ( (x*PC_WIDTH - (Character_X+PC_WIDTH/2))*(x*PC_WIDTH - (Character_X+PC_WIDTH/2)) + (y*PC_HEIGHT - (Character_Y+PC_HEIGHT/2))*(y*PC_HEIGHT - (Character_Y+PC_HEIGHT/2)) ) * (PC_WIDTH*PC_WIDTH + PC_HEIGHT*PC_HEIGHT) );*/
	}

	//Create Monster & initialized it
	Monster_Template* myMonster = new Monster_Template(BATF_SPRITE_W * x,  BATF_SPRITE_H * y, 
														BASE_LIFE, Current_Life, BASE_ARMOR, Current_Armor, Sprite_Width, Sprite_Height, Characters_Tile,
														Life_Bar_Tile, empty_life_bar_rect, current_life_bar_rect);

	return myMonster;
}
//Create Monsters Method which create as many monsters has desired
template <typename Monster_Template>
std::vector<Character_Base*>* Monster_Factory<Monster_Template>::Create_Monsters(std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*>* environment_sprite_vector, std::vector<BattleField_Sprite*>* background_sprite_vector)
{
	//
	//TODO cge that
	//
	/******TEMPORARY: we only have one player for now and no npc ******/
	int Character_X = Global_Player_Vector->at(1)->at(0)->Get_Collision_Box().getx();
	int Character_Y = Global_Player_Vector->at(1)->at(0)->Get_Collision_Box().gety();

	//Loop until desired number of monsters has been reached
	for(int i=1; i <= Initial_Number_Of_Monsters; i++)
	{
		//Monster generation
		Monster_Template* newMonster = Create_One_Monster(Character_X, Character_Y);

		//Check if the battlefield allow the monster creation
		/******BUG HERE: We're not checking if other monsters allow the new created one *****/
		while( !(newMonster->Check_battlefield_allow_character( newMonster->Get_Collision_Box(), environment_sprite_vector, background_sprite_vector) ) || !(newMonster->Check_Cutting_Allow_Monster(newMonster->Get_X(), newMonster->Get_Y(), BattleField_Cutting_Vector)) )
		{
			//Monster regeneration
			delete newMonster, newMonster = NULL;
			newMonster = Create_One_Monster(Character_X, Character_Y);
		}

		//Store the monster at the end of the vector
		Monster_Vector->push_back(newMonster);
		
		//Add 1 to the number of monsters present
		ALiVE_MONSTERS++;
	}

	return Monster_Vector;
}
//Invoke all monsters movements
template <typename Monster_Template>
bool Monster_Factory<Monster_Template>::Move_Monsters(std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector) //int nb_vector, ... )//, std::vector<Character_Base*> Monster_Vector_Skeleton, std::vector<Character_Base*> Monster_Vector_Worm)
{
try {
	//Move Monsters
	for(unsigned int i=0; i < Monster_Vector->size(); i++)
	{
		if( Monster_Vector->at(i)->Move( Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector) == false )
		{ 
			P0_Logger << nl << "Failed to move monster N°" << i << std::endl;
			return false; //error occured 
   		}	
	}
	return true; //no error
} catch (...) {
	return false; //error occured
}
}
//Invoke all monsters movements animation on the screen
template <typename Monster_Template>
bool Monster_Factory<Monster_Template>::Show_Monsters(Rect Camera, VideoSurface& Screen)
{
try {
	for(unsigned int i=0; i < Monster_Vector->size(); i++)
	{
	 	if( Monster_Vector->at(i)->Show(Camera, Screen) == false )
		{ 
	    	P0_Logger << nl << "Failed to render monster movement on monster N°" << i << std::endl;  
			#ifdef _DEBUG //debug mode
	    	  return false; //error occured
			#endif

   		}
		if( ((Monster_Base*)Monster_Vector->at(i))->Show_Life_Bar(Camera, Screen) == false )
		{ 
			P0_Logger << nl << "Failed to render monster life bar on monster N°" << i << std::endl;   
			#ifdef _DEBUG //debug mode
	    		return false; //error occured
			#endif
   		}
	}
	return true; //no error occured
} catch (...) {
    return false; //error occured
}
}
//Method that will remove all monster with Alive_Status status to false (aka dead monsters) from the monster vector container
template <typename Monster_Template>
std::vector<Character_Base*>* Monster_Factory<Monster_Template>::Remove_Dead_Monsters()
{
	//Loop on all the vector
	for(unsigned int i=0; i < Monster_Vector->size(); i++)
	{
		//Check if Alive_Status is false
		if (Monster_Vector->at(i)->Get_Alive_Status() == false)
		{
			//remove the monster from the scope (only the ième monster at a time)
			Monster_Vector->erase(Monster_Vector->begin()+i, Monster_Vector->begin()+i+1);

			//remove 1 to the number of monsters present
			ALiVE_MONSTERS--;
			//Add 1 to killed numbers
			KiLLED_MONSTERS++;

			//Then go back of one in the loop because elements has been shifted
			i--;
		}
	}
	//Finally return the new Vector with only alive monsters
	return Monster_Vector;
}

//Generate new monsters until max monster has been reached
template <typename Monster_Template>
std::vector<Character_Base*>* Monster_Factory<Monster_Template>::Generate_New_Monster(std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*>* environment_sprite_vector, std::vector<BattleField_Sprite*>* background_sprite_vector)
{
	unsigned int temp = 0;

	//
	//TODO cge that
	//
	/******TEMPORARY: we only have one player for now and no npc ******/
	int Character_X = Global_Player_Vector->at(1)->at(0)->Get_Collision_Box().getx();
	int Character_Y = Global_Player_Vector->at(1)->at(0)->Get_Collision_Box().gety();
	
	//The more the monster on the battlefield, the less there a chance a new one is generated until we reached the MAX_MONSTERS_SIMULTANEOUSLY constant
	temp = random(1, MAX_MONSTERS_SIMULTANEOUSLY);
	if (temp > Monster_Vector->size())
	{
		//Monster generation
		Monster_Template* newMonster = Create_One_Monster(Character_X, Character_Y);

		//Check if the battlefield allow the monster creation
		/******BUG HERE: We're not checking if other monsters allow the new created one *****/
		while( !(newMonster->Check_battlefield_allow_character( newMonster->Get_Collision_Box(), environment_sprite_vector, background_sprite_vector) ) || !(newMonster->Check_Cutting_Allow_Monster(newMonster->Get_X(), newMonster->Get_Y(), BattleField_Cutting_Vector)) )
		{
			//regeneration
			delete(newMonster);
			newMonster = Create_One_Monster(Character_X, Character_Y);
		}

		//Store the monster at the end of the vector
		Monster_Vector->push_back(newMonster);

		//Add 1 to the number of monsters present
		ALiVE_MONSTERS++;
	}
	
	//Finally return the new Vector wth eventual new monsters
	return Monster_Vector;
}

//If we build using VS, To solve linking problem with template we have to defined allowed template values (See: http://www.parashift.com/c++-faq-lite/templates.html#faq-35.15 for more info)
//#ifdef VISUAL_STUDIO
	//template class Monster_Factory<Monster_Base>;
	template class Monster_Factory<Monster_Skeleton>;
	template class Monster_Factory<Monster_Worm>;

//#endif
