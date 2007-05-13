#include "Monster_Factory.hh"

//Default Constructor
template <typename Monster_Template>
Monster_Factory<Monster_Template>::Monster_Factory()
{
	Initial_Number_Of_Monsters = 0;
	Monster_Vector = new std::vector<Character_Base*>;
	BattleField_Cutting_Vector = new std::vector<BattleField_Zone*>;

	Monster_Template::Initialize(Monster_Template::Description_Filename,
		Ch_Vel, BASE_LIFE, BASE_ARMOR, BASE_INFLICTED_DAMAGE, Sprite_Width, Sprite_Height, Characters_ID,
		Allowed_Area,
		CB_X_Modifier, CB_Y_Modifier, CB_Width, CB_Height,
		Default_Animations_Center,
		Life_Bar_Tile, empty_life_bar_rect, real_life_bar_rect
		);
}

//Constructor
template <typename Monster_Template>
Monster_Factory<Monster_Template>::Monster_Factory(int number_of_monsters, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
try {
	Initial_Number_Of_Monsters = number_of_monsters;
	Monster_Vector = new std::vector<Character_Base*>;
	Global_Monster_Vector->push_back(Monster_Vector);
	BattleField_Cutting_Vector = BattleField_Zone::Fill_Vector();

	Monster_Template::Initialize(Monster_Template::Description_Filename,
		Ch_Vel, BASE_LIFE, BASE_ARMOR, BASE_INFLICTED_DAMAGE, Sprite_Width, Sprite_Height, Characters_ID,
		Allowed_Area,
		CB_X_Modifier, CB_Y_Modifier, CB_Width, CB_Height,
		Default_Animations_Center,
		Life_Bar_Tile, empty_life_bar_rect, real_life_bar_rect
		);

	//P0_Logger << nl << "Factory CONSTRUCTED Successfully " << std::endl;
} catch (std::exception &exc) {
	throw std::logic_error( exc.what() );
} catch (...) {
	//unkown error occured
	throw std::logic_error( "Unhandled Error in Monster_Factory Constructor" );
}
}

//Destructor
template <typename Monster_Template>
Monster_Factory<Monster_Template>::~Monster_Factory()
{
	delete Default_Animations_Center, Default_Animations_Center = NULL;
	delete Life_Bar_Tile, Life_Bar_Tile = NULL;

	for (unsigned int i = 0; i < Monster_Vector->size(); i++)
	{
		delete Monster_Vector->at(i), Monster_Vector->at(i) = NULL;
	}
	delete Monster_Vector, Monster_Vector = NULL;
	
	for (unsigned int i = 0; i < BattleField_Cutting_Vector->size(); i++)
	{
		delete BattleField_Cutting_Vector->at(i), BattleField_Cutting_Vector->at(i) = NULL;
	}
	delete BattleField_Cutting_Vector, BattleField_Cutting_Vector = NULL;
}

//Create Monster Method which create ONE SINGLE MONSTER ONLY and designed to by used by other method and not alone
template <typename Monster_Template>
Monster_Template* Monster_Factory<Monster_Template>::Create_One_Monster(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
	//
	//TODO(future) cge that when necessary
	//
	/******TEMPORARY: we only have one player for now******/
	int Character_X = Global_Player_Vector->at(1)->at(0)->Get_X();
	int Character_Y = Global_Player_Vector->at(1)->at(0)->Get_Y();

	//Determine monster creation position
	int x = random(0,LEVEL_WIDTH-1), y = random(0,LEVEL_HEIGHT-1);

	//mini distance (3.5 bf square radius from the character border)²
	int distance_mini_carre = int( 3.5*sqrt( float((BATF_SPRITE_W*BATF_SPRITE_W) + (BATF_SPRITE_H*BATF_SPRITE_H)) ) );
	
	//(distance from the center - distance center to border of the character)²
	int distance_carre = (int)( sqrt( float( ((x - (Character_X+PC_WIDTH/2))*(x - (Character_X+PC_WIDTH/2))) + ((y - (Character_Y+PC_HEIGHT/2))*(y - (Character_Y+PC_HEIGHT/2))) ) )
						- 0.5*sqrt( float((PC_WIDTH*PC_WIDTH) + (PC_HEIGHT*PC_HEIGHT)) ) );
	
	//1st chek if we'r not too near
	while (distance_carre <= distance_mini_carre) 
	{
			//retry coordinate
			x = random(0,LEVEL_WIDTH-1);
			y = random(0,LEVEL_HEIGHT-1);
				
			distance_carre = int( sqrt( float( ((x - (Character_X+PC_WIDTH/2))*(x - (Character_X+PC_WIDTH/2))) + ((y - (Character_Y+PC_HEIGHT/2))*(y - (Character_Y+PC_HEIGHT/2))) ) )
								- 0.5*sqrt( float((PC_WIDTH*PC_WIDTH) + (PC_HEIGHT*PC_HEIGHT)) ) );
					
	}

	//first attempt to create the monster
	Monster_Template* myMonster = new Monster_Template(
		x, y, Ch_Vel, BASE_LIFE, BASE_ARMOR, BASE_INFLICTED_DAMAGE, Sprite_Width, Sprite_Height, Characters_ID,
		Allowed_Area,
		CB_X_Modifier, CB_Y_Modifier, CB_Width, CB_Height,
		Default_Animations_Center,
		Life_Bar_Tile, empty_life_bar_rect, real_life_bar_rect
		);

	//if something don't allow the monster to be here, loop
	while ( (! (myMonster->Check_Cutting_Allow_Monster(BattleField_Cutting_Vector)) ) || (! myMonster->Manage_Collisions(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector, false) ) )
	{
		//retry coordinate
		x = random(0,LEVEL_WIDTH-1);
		y = random(0,LEVEL_HEIGHT-1);
		distance_carre = int( sqrt( float( ((x - (Character_X+PC_WIDTH/2))*(x - (Character_X+PC_WIDTH/2))) + ((y - (Character_Y+PC_HEIGHT/2))*(y - (Character_Y+PC_HEIGHT/2))) ) )
							- 0.5*sqrt( float((PC_WIDTH*PC_WIDTH) + (PC_HEIGHT*PC_HEIGHT)) ) );

		//Check if we'r to near
		while (distance_carre <= distance_mini_carre) 
		{
			//retry coordinate
			x = random(0,LEVEL_WIDTH-1);
			y = random(0,LEVEL_HEIGHT-1);
				
			distance_carre = int( sqrt( float( ((x - (Character_X+PC_WIDTH/2))*(x - (Character_X+PC_WIDTH/2))) + ((y - (Character_Y+PC_HEIGHT/2))*(y - (Character_Y+PC_HEIGHT/2))) ) )
								- 0.5*sqrt( float((PC_WIDTH*PC_WIDTH) + (PC_HEIGHT*PC_HEIGHT)) ) );
					
		}
		
		//update the monster to the new coordinate with his CB
		myMonster->Set_X(x);
		myMonster->Set_Y(y);

		Rect NewCB;
		NewCB.setx(x + CB_X_Modifier );
		NewCB.sety(y + CB_Y_Modifier);
		NewCB.setw(CB_Width);
		NewCB.seth(CB_Height);
		myMonster->Set_Collision_Box(NewCB);
		
		//delete myMonster, myMonster = NULL;
		//ReCreate Monster
		//myMonster = new Monster_Template(x, y, Ch_Vel, BASE_LIFE, Real_Life, BASE_ARMOR, Real_Armor, Sprite_Width, Sprite_Height,
									//	Characters_Current_Tileset, Life_Bar_Tile, empty_life_bar_rect, real_life_bar_rect);

	}
	
	return myMonster;
}
//Create Monsters Method which create as many monsters has desired
template <typename Monster_Template>
std::vector<Character_Base*>* Monster_Factory<Monster_Template>::Create_Monsters(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
	//Loop until desired number of monsters has been reached
	for(int i=1; i <= Initial_Number_Of_Monsters; i++)
	{
		//Store the created monster at the end of the vector
		Monster_Vector->push_back( Create_One_Monster(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector) );
		
		//Add 1 to the number of monsters present
		ALiVE_MONSTERS++;
	}

	return Monster_Vector;
}
//Invoke all monsters movements
template <typename Monster_Template>
bool Monster_Factory<Monster_Template>::Move_Monsters(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector) //int nb_vector, ... )//, std::vector<Character_Base*> Monster_Vector_Skeleton, std::vector<Character_Base*> Monster_Vector_Worm)
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
bool Monster_Factory<Monster_Template>::Show_Monsters(const Rect& Camera, VideoSurface& Screen)
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
			//clean the dead monster
			delete Monster_Vector->at(i), Monster_Vector->at(i) == NULL;

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
std::vector<Character_Base*>* Monster_Factory<Monster_Template>::Generate_New_Monster(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
	unsigned int temp = 0;

	// Rebirth probabilities: 1/3 probability at MAX_MONSTERS_SIMULTANEOUSLY & 2/3 at 0 monsters with the number of monsters <= MAX_MONSTERS_SIMULTANEOUSLY
	temp = random(0, 100);
	if ( ( temp > (unsigned int)( 100 * ( (Monster_Vector->size() + (float)MAX_MONSTERS_SIMULTANEOUSLY) / (3*(float)MAX_MONSTERS_SIMULTANEOUSLY) ) ) ) && ( Monster_Vector->size() <= (unsigned)MAX_MONSTERS_SIMULTANEOUSLY ) )
	{
		//Store the new monster at the end of the vector
		Monster_Vector->push_back( Create_One_Monster(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector) );

		//Add 1 to the number of monsters present
		ALiVE_MONSTERS++;
	}
	
	//Finally return the new Vector wth eventual new monsters
	return Monster_Vector;
}

//To solve linking problem with template class defined in .cpp, we have to defined allowed template values (See: http://www.parashift.com/c++-faq-lite/templates.html#faq-35.15 for more info)
//#ifdef VISUAL_STUDIO
	//template class Monster_Factory<Monster_Base>;
	template class Monster_Factory<Monster_Skeleton>;
	template class Monster_Factory<Monster_Worm>;

//#endif
