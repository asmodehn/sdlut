#include "Character_Base.hh"

//Constructor
Character_Base::Character_Base()
{
	X = 0, Y =0;
	xVel = 0, yVel = 0;

	Sprite_Width = 0, Sprite_Height = 0;

	BASE_LIFE = 0, Real_Life = BASE_LIFE;
	BASE_ARMOR = 0, Real_Armor = BASE_ARMOR;
	BASE_INFLICTED_DAMAGE = 0, Real_Inflicted_Damage = BASE_INFLICTED_DAMAGE;
	BASE_RANGE = 0, Real_Range = BASE_RANGE;

	//Default Area: the whole level
	Allowed_Area.setx(0);
	Allowed_Area.sety(0);
	Allowed_Area.setw(LEVEL_WIDTH);
	Allowed_Area.seth(LEVEL_HEIGHT);

	Alive_Status = true;
}

//Destructor
Character_Base::~Character_Base()
{
}

//Check if the bg allow the character presence
std::vector<int>* Character_Base::Check_background_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector)
{
	std::vector<int>* res_vect = new std::vector<int>; //vector of collision results
	Rect bf_rect;
	bf_rect.setw(BATF_SPRITE_W);
	bf_rect.seth(BATF_SPRITE_H);

	int it_x = 0, it_y = 0;
	if (BackGround_Sprite_Vector->size() > 0)
	{
		//to determine iterator of the top left corner of the collision_box
		for(int i=0; i < (LEVEL_WIDTH/BATF_SPRITE_W); i++)
		{
			if ( Collision_Box.getx()/BATF_SPRITE_W == (BackGround_Sprite_Vector->at(i)->Get_X())/BATF_SPRITE_W )
			{
				it_x = i;
				break;
			}
		}
		for(unsigned int i=0; i < BackGround_Sprite_Vector->size(); i+=(LEVEL_WIDTH/BATF_SPRITE_W) )
		{
			if ( Collision_Box.gety()/BATF_SPRITE_H == BackGround_Sprite_Vector->at(i)->Get_Y()/BATF_SPRITE_H )
			{
				it_y = i/(LEVEL_WIDTH/BATF_SPRITE_W);
				break;
			}
		}
	
		//P0_Logger << nl << "it_x: " << it_x << "\nit_y: " << it_y << std::endl;
		
		//Loop only on vector elements that are present on the screen
		unsigned int it = 0;
		for(int i = it_y; i < it_y + Sprite_Height/BATF_SPRITE_H + 1; i++ )
		{
			for(int j = it_x; j < it_x + (Sprite_Width/BATF_SPRITE_W) + 1; j++)
			{
				it = i * (LEVEL_WIDTH/BATF_SPRITE_W) + j;
				if (it >= BackGround_Sprite_Vector->size())
					break;

				bf_rect.setx(BackGround_Sprite_Vector->at(it)->Get_X());
				bf_rect.sety(BackGround_Sprite_Vector->at(it)->Get_Y());

				//When collision...
				if ( check_collision( Collision_Box, bf_rect ) )
				{
					//... fill the vector in function of the destination background rules
					res_vect->push_back( Get_BG_vs_CH_Rules( BackGround_Sprite_Vector->at(it)->Get_BattleField_Type() ) );
				}
			}
		}
	}
	/*//loop on all the vector
	for(unsigned int i=0; i < BackGround_Sprite_Vector->size(); i++)
	{
		bf_rect.setx(BackGround_Sprite_Vector->at(i)->Get_X());
		bf_rect.sety(BackGround_Sprite_Vector->at(i)->Get_Y());

		//When collision...
		if ( check_collision( Collision_Box, bf_rect ) )
		{
			//... fill the vector in function of the destination background rules
			res_vect->push_back( Get_BG_vs_CH_Rules( BackGround_Sprite_Vector->at(i)->Get_BattleField_Type() ) );
		}
	}*/

	return res_vect;
}

//Check if the env allow the character presence
std::vector<int>* Character_Base::Check_environment_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector)
{
	std::vector<int>* res_vect = new std::vector<int>; //vector of collision results
	Rect bf_rect;
	bf_rect.setw(BATF_SPRITE_W);
	bf_rect.seth(BATF_SPRITE_H);

	//loop on all the vector
	for(unsigned int i=0; i < Environment_Sprite_Vector->size(); i++)
	{
		bf_rect.setx(Environment_Sprite_Vector->at(i)->Get_X());
		bf_rect.sety(Environment_Sprite_Vector->at(i)->Get_Y());

		//When collision...
		if ( check_collision( Collision_Box, bf_rect ) )
		{
			//... fill the vector in function of the destination background rules
			res_vect->push_back( Get_Env_vs_CH_Rules( Environment_Sprite_Vector->at(i)->Get_BattleField_Type() ) );
		}
	}

	return res_vect;
}

//Check if the battlefield allow the character presence
bool Character_Base::Check_battlefield_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector)
{
	bool res = true;

	std::vector<int>* env_vs_ch_collisions = Check_environment_allow_character(Collision_Box, Environment_Sprite_Vector);
	std::vector<int>* bg_vs_ch_collisions = Check_background_allow_character(Collision_Box, BackGround_Sprite_Vector);


	if (bg_vs_ch_collisions->size() > 0)
	{
		for (unsigned int i = 0; i < bg_vs_ch_collisions->size(); i++)
		{
			if ( bg_vs_ch_collisions->at(i) == 0 )
			{
				res = false; //collision with bg
				delete env_vs_ch_collisions, env_vs_ch_collisions = NULL;
				delete bg_vs_ch_collisions, bg_vs_ch_collisions = NULL;
				return res; //no need to work more
			} else {
				res = true; //no collision
			}
		}
	} else {  //that means we have no bg 
		if (env_vs_ch_collisions->size() > 0)
		{
			for (unsigned int i = 0; i < env_vs_ch_collisions->size(); i++)
			{
				if ( env_vs_ch_collisions->at(i) == 0 ) //not allowed
				{
					res = false; //collision with env
					delete env_vs_ch_collisions, env_vs_ch_collisions = NULL;
					delete bg_vs_ch_collisions, bg_vs_ch_collisions = NULL;
					return res; //no need to work more
				} 
				else //allowed or empty
				{ 
					res = true; //no collision
				}
			}
		}
		//battlefield allow collision box
		delete env_vs_ch_collisions, env_vs_ch_collisions = NULL;
		delete bg_vs_ch_collisions, bg_vs_ch_collisions = NULL;
		return res;
	}

	if (env_vs_ch_collisions->size() > 0)
	{
		for (unsigned int i = 0; i < env_vs_ch_collisions->size(); i++)
		{
			if ( env_vs_ch_collisions->at(i) == 0 ) //not allowed
			{
				res = false; //collision with env
				delete env_vs_ch_collisions, env_vs_ch_collisions = NULL;
				delete bg_vs_ch_collisions, bg_vs_ch_collisions = NULL;
				return res; //no need to work more
			} 
			else //allowed or empty
			{ 
				res = true; //no collision
			}
		}
	}
	//battlefield allow collision box
	delete env_vs_ch_collisions, env_vs_ch_collisions = NULL;
	delete bg_vs_ch_collisions, bg_vs_ch_collisions = NULL;
	return res;


	/*if ( env_vs_ch_collisions->size() !=0 )
	{
		for (unsigned int i = 0; i < env_vs_ch_collisions->size(); i++)
		{
			if ( env_vs_ch_collisions->at(i) == -1 ) //environment is not present
			{
				if (bg_vs_ch_collisions->size() > 0) //in case of empty vector
				{
					if ( bg_vs_ch_collisions->at(i) == 0 )
					{
						res = false; //collision with bg
						return res; //no need to work more
					}
				}
			} else if ( env_vs_ch_collisions->at(i) == 0 ) 
			{
				res = false; //collision with env
				return res; //no need to work more
			} else {
				res = true; //no collision
			}
		}
		return res;
	} 
	else if (bg_vs_ch_collisions->size() > 0)
	{
		for (unsigned int i = 0; i < bg_vs_ch_collisions->size(); i++)
		{
			if ( bg_vs_ch_collisions->at(i) == 0 )
			{
				res = false; //collision with bg
				return res; //no need to work more
			} else {
				res = true; //no collision
			}
		}
		return res;
	}
	
//never used
	return res;*/
}

//Check collision with everything possible
bool Character_Base::Check_Collisions(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
	//If the character went too far to the left or right
	if((Collision_Box.getx() < Allowed_Area.getx() ) || ( (signed)(Collision_Box.getx() + Sprite_Width) > (signed)(Allowed_Area.getx() + Allowed_Area.getw()) ) )
		//we have found a collision no need to work more
		return true;

	//If the character went too far up or down (minus the status bar)
	if ( (Collision_Box.gety() < Allowed_Area.gety() ) || ( (signed)(Collision_Box.gety() + Sprite_Height) > (signed)(Allowed_Area.gety() + Allowed_Area.geth() - STATUS_BAR_H) ) )
		return true;   


	//Check if the battlefield allow the move
	if(! Check_battlefield_allow_character(Collision_Box, Environment_Sprite_Vector, BackGround_Sprite_Vector) )
		return true;
	
	//Check collision with Players
	//Loop for all players's vector
	for (unsigned int j=0; j < Global_Player_Vector->size(); j++)
	{
		//loop for the current monster's vector
		for(unsigned int i=0; i < Global_Player_Vector->at(j)->size(); i++)
		{
			//In order to the character to not check collision's with himself
			if ( ( X != Global_Player_Vector->at(j)->at(i)->Get_X() ) || Y != Global_Player_Vector->at(j)->at(i)->Get_Y() )
			{
				if (check_collision( Collision_Box, Global_Player_Vector->at(j)->at(i)->Get_Collision_Box() ))
				{
					//we have found a collision inside the vector
					P0_Logger << nl << "Collision between character " << " @ [ " << X << ", " << Y << "]" << std::endl;

					//no need to work more
					return true;
				}
			}
		}
	}
	
	//Collision with Monsters
	//Loop for all monsters's vector
	for (unsigned int j=0; j < Global_Monster_Vector->size(); j++)
	{
		//loop for the current monster's vector
		for(unsigned int i=0; i < Global_Monster_Vector->at(j)->size(); i++)
		{
			//In order to the character to not check collision's with himself
			if ( ( X != Global_Monster_Vector->at(j)->at(i)->Get_X() ) || Y != Global_Monster_Vector->at(j)->at(i)->Get_Y() )
			{
				if (check_collision( Collision_Box, Global_Monster_Vector->at(j)->at(i)->Get_Collision_Box() ))
				{
					//we have found a collision inside the vector
					P0_Logger << nl << "Collision between monster " << " @ [ " << X << ", " << Y << "]" << std::endl;

					//no need to work more
					return true;
				}
			}
		}
	}

	//No collisions
	return false;
}

//Show Character on the screen
bool Character_Base::Show(Rect Camera, VideoSurface& Screen)
{
try {
	//Check if the character sprite is present on the screen minus the status bar
	//NOTE : PC_WIDTH/PC_HEIGHT are present because the camera is centered on the middle of the player and so we need to draw the screen a little more than the camera dim
	if ( ( (Camera.getx()-PC_WIDTH) <= X) && (X < (signed)(Camera.getx() + Camera.getw()) ) && ( (Camera.gety()-PC_HEIGHT) <= Y) && (Y < (signed)(Camera.gety() + Camera.geth() - STATUS_BAR_H) ) )
	{
		//It's present than draw it
		Screen.blit(Characters_Tile, Point::Point(X - Camera.getx(), Y - Camera.gety()), Characters_SpriteRect);
	}
	return true; //no error
} catch (...) {
  		return false; //error occured
}
}
