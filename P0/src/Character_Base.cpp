#include "Character_Base.hh"

//Constructor
Character_Base::Character_Base()
{
	X = 0, Y =0;
	xVel = 0, yVel = 0;
	Sprite_Width = 0, Sprite_Height = 0;
	BASE_LIFE = 0, Current_Life = BASE_LIFE;
	BASE_ARMOR = 0, Current_Armor = BASE_ARMOR;

	Characters_Tile = RGBSurface(Color(0xFF, 0xFF, 0xFF), 0, 0, 32);

	Characters_SpriteRect.setx(0);
	Characters_SpriteRect.sety(0);
	Characters_SpriteRect.setw(0);
	Characters_SpriteRect.seth(0);

	Collision_Box.setx(0);
	Collision_Box.sety(0);
	Collision_Box.setw(0);
	Collision_Box.seth(0);

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
	std::vector<int>* res = new std::vector<int>; //vector of collision results
	Rect env_rect;

	//loop on all the vector
	for(unsigned int i=0; i < BackGround_Sprite_Vector->size(); i++)
	{
		env_rect.setx(BackGround_Sprite_Vector->at(i)->Get_X());
		env_rect.sety(BackGround_Sprite_Vector->at(i)->Get_Y());
		env_rect.setw(BATF_SPRITE_W);
		env_rect.seth(BATF_SPRITE_H);

		//When collision...
		if ( check_collision( Collision_Box, env_rect ) )
		{
			//... fill the vector in function of the destination background rules
			res->push_back( Get_BG_vs_CH_Rules( BackGround_Sprite_Vector->at(i)->Get_BattleField_Type() ) );
		}
	}

	return res;
}

//Check if the env allow the character presence
std::vector<int>* Character_Base::Check_environment_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector)
{
	std::vector<int>* res = new std::vector<int>; //vector of collision results
	Rect env_rect;

	//loop on all the vector
	for(unsigned int i=0; i < Environment_Sprite_Vector->size(); i++)
	{
		env_rect.setx(Environment_Sprite_Vector->at(i)->Get_X());
		env_rect.sety(Environment_Sprite_Vector->at(i)->Get_Y());
		env_rect.setw(BATF_SPRITE_W);
		env_rect.seth(BATF_SPRITE_H);

		//When collision...
		if ( check_collision( Collision_Box, env_rect ) )
		{
			//... fill the vector in function of the destination background rules
			res->push_back( Get_Env_vs_CH_Rules( Environment_Sprite_Vector->at(i)->Get_BattleField_Type() ) );
		}
	}

	return res;
}

//Check if the battlefield allow the character presence
bool Character_Base::Check_battlefield_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector)
{
	bool res = true;

	std::vector<int>* env_vs_ch_collisions = Check_environment_allow_character(Collision_Box, Environment_Sprite_Vector);
	std::vector<int>* bg_vs_ch_collisions = Check_background_allow_character(Collision_Box, BackGround_Sprite_Vector);

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

//Check collision with everything possible
bool Character_Base::Check_Collisions(std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector)
{
	//If the character went too far to the left or right
	if((Collision_Box.getx() < Allowed_Area.getx() ) || (Collision_Box.getx() + Sprite_Width > Allowed_Area.getx() + Allowed_Area.getw() ) )
		//we have found a collision no need to work more
		return true;

	//If the character went too far up or down (minus the status bar)
	if((Collision_Box.gety() < Allowed_Area.gety() ) || (Collision_Box.gety() + Sprite_Height > Allowed_Area.gety() + Allowed_Area.geth() - STATUS_BAR_H) )
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
	//NOTE : CH_WIDTH/CH_HEIGHT are present because the camera is centered on the middle of the player and so we need to draw the screen a little more than the camera dim
	if ( ( (Camera.getx()-CH_WIDTH) <= X) && (X < (Camera.getx() + Camera.getw()) ) && ( (Camera.gety()-CH_HEIGHT) <= Y) && (Y < (Camera.gety() + Camera.geth() - STATUS_BAR_H) ) )
	{
		//It's present than draw it
		Screen.blit(Characters_Tile, Point::Point(X - Camera.getx(), Y - Camera.gety()), Characters_SpriteRect);
	}
	return true; //no error
} catch (...) {
  		return false; //error occured
}
}
