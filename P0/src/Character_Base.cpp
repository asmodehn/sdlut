#include "Character_Base.hh"

//Constructor
Character_Base::Character_Base()
{
	X = 0, Y =0;
	Ch_Vel = CH_VEL;
	xVel = 0, yVel = 0;

	Sprite_Width = 0, Sprite_Height = 0;
	Sprite_Filename = "";

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

	move_status = CH_RIGHT;
}

//Destructor
Character_Base::~Character_Base()
{
}

//move the character_base's collision box to a place its allowed to be when moving
bool Character_Base::Manage_Collisions(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector, bool Handle_Collisions )
{
try {
//Handle collisions with Allowed area
	if (Handle_Collisions) //Handle Mode ON
	{
		if ( Collision_Box.getx() < Allowed_Area.getx() )
			Collision_Box.setx( Allowed_Area.getx() );
		if ( (signed)(Collision_Box.getx() + Sprite_Width) > (signed)(Allowed_Area.getx() + Allowed_Area.getw()) )
			Collision_Box.setx( Allowed_Area.getx() + Allowed_Area.getw() - Sprite_Width );
		if ( Collision_Box.gety() < Allowed_Area.gety() ) 
			Collision_Box.sety( Allowed_Area.gety() ); 
		if ( (signed)(Collision_Box.gety() + Sprite_Height) > (signed)(Allowed_Area.gety() + Allowed_Area.geth()) )
			Collision_Box.sety( Allowed_Area.gety() + Allowed_Area.geth() - Sprite_Height );
	} else { //Handle Mode OFF
		//outside the allowed area
		if ( ( Collision_Box.getx() < Allowed_Area.getx() ) || ( (signed)(Collision_Box.getx() + Sprite_Width) > (signed)(Allowed_Area.getx() + Allowed_Area.getw()) ) || ( Collision_Box.gety() < Allowed_Area.gety() ) || ( (signed)(Collision_Box.gety() + Sprite_Height) > (signed)(Allowed_Area.gety() + Allowed_Area.geth()) ) )
			return false; //presence not allowed no need to work more
	}

Rect inf_rect;

//Handle collisions with Battlefield
	Rect bf_rect;
	bf_rect.setw(BATF_SPRITE_W);
	bf_rect.seth(BATF_SPRITE_H);

		//BG
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

				inf_rect = Collision_Box.inf( bf_rect );
				if ( ( inf_rect.getw() != 0 ) || ( inf_rect.geth() != 0 ) ) //we'r collisioning
				{
					if ( ! Get_BG_vs_CH_Rules( BackGround_Sprite_Vector->at(it)->Get_BattleField_Type() ) ) //BG dont allow presence
					{
						if (Handle_Collisions) //Handle Mode ON
						{
							if ( inf_rect.getw() <= inf_rect.geth() )
							{
								if ( inf_rect.getx() <= ( BackGround_Sprite_Vector->at(it)->Get_X() + BATF_SPRITE_W/2 ) )
								{
									Collision_Box.setx( BackGround_Sprite_Vector->at(it)->Get_X() - Sprite_Width );
								} 
								else 
								{
									Collision_Box.setx( BackGround_Sprite_Vector->at(it)->Get_X() + BATF_SPRITE_W );
								}
								
							} 
							else
							{
								if ( inf_rect.gety() <= ( BackGround_Sprite_Vector->at(it)->Get_Y() + BATF_SPRITE_H/2 ) ) 
								{
									Collision_Box.sety( BackGround_Sprite_Vector->at(it)->Get_Y() - Sprite_Height );
								} 
								else 
								{
									Collision_Box.sety( BackGround_Sprite_Vector->at(it)->Get_Y() + BATF_SPRITE_H );
								}
							}
						} else { //Handle Mode OFF
							return false; //presence not allowed no need to work more
						}
					}
				}
			}
		}
	}

		//env
	//loop on all the vector
	for(unsigned int i=0; i < Environment_Sprite_Vector->size(); i++)
	{
		bf_rect.setx(Environment_Sprite_Vector->at(i)->Get_X());
		bf_rect.sety(Environment_Sprite_Vector->at(i)->Get_Y());

		inf_rect = Collision_Box.inf( bf_rect );
		if ( ( inf_rect.getw() != 0 ) || ( inf_rect.geth() != 0 ) ) //we'r collisioning
		{
			if ( ! Get_Env_vs_CH_Rules( Environment_Sprite_Vector->at(i)->Get_BattleField_Type() ) ) //Env dont allow presence
			{
				if (Handle_Collisions) //Handle Mode ON
				{
					if ( inf_rect.getw() <= inf_rect.geth() )
					{
						if ( inf_rect.getx() <= ( Environment_Sprite_Vector->at(i)->Get_X() + BATF_SPRITE_W/2 ) )
						{
							Collision_Box.setx( Environment_Sprite_Vector->at(i)->Get_X() - Sprite_Width );
						} 
						else 
						{
							Collision_Box.setx( Environment_Sprite_Vector->at(i)->Get_X() + BATF_SPRITE_W );
						}
						
					} 
					else
					{
						if ( inf_rect.gety() <= ( Environment_Sprite_Vector->at(i)->Get_Y() + BATF_SPRITE_H/2) )
						{
							Collision_Box.sety( Environment_Sprite_Vector->at(i)->Get_Y() - Sprite_Height );
						} 
						else 
						{
							Collision_Box.sety( Environment_Sprite_Vector->at(i)->Get_Y() + BATF_SPRITE_H );
						}
					}
				} else { //Handle Mode OFF
					return false; //presence not allowed no need to work more
				}
			}
		}
	}


//Handle collisions with Players
	//Loop for all players's vector
	for (unsigned int j=0; j < Global_Player_Vector->size(); j++)
	{
		//loop for the current monster's vector
		for(unsigned int i=0; i < Global_Player_Vector->at(j)->size(); i++)
		{
			//In order to the character to not check collision's with himself
			if ( ( X != Global_Player_Vector->at(j)->at(i)->Get_X() ) || ( Y != Global_Player_Vector->at(j)->at(i)->Get_Y() ) )
			{
				inf_rect = Collision_Box.inf( Global_Player_Vector->at(j)->at(i)->Get_Collision_Box() );
				if ( ( inf_rect.getw() != 0 ) || ( inf_rect.geth() != 0 ) ) //we'r collisioning
				{
					if (Handle_Collisions) //Handle Mode ON
					{
						if ( inf_rect.getw() <= inf_rect.geth() )
						{
							if ( inf_rect.getx() <= (Global_Player_Vector->at(j)->at(i)->Get_X() + (Global_Player_Vector->at(j)->at(i)->Get_Sprite_Width()/2) ) )
							{
								Collision_Box.setx( Global_Player_Vector->at(j)->at(i)->Get_X() - Sprite_Width );
							} 
							else 
							{
								Collision_Box.setx( Global_Player_Vector->at(j)->at(i)->Get_X() + Global_Player_Vector->at(j)->at(i)->Get_Sprite_Width() );
							}
							
						} 
						else
						{
							if ( inf_rect.gety() <= (Global_Player_Vector->at(j)->at(i)->Get_Y() + (Global_Player_Vector->at(j)->at(i)->Get_Sprite_Height()/2) ) )
							{
								Collision_Box.sety( Global_Player_Vector->at(j)->at(i)->Get_Y() - Sprite_Height );
							} 
							else 
							{
								Collision_Box.sety( Global_Player_Vector->at(j)->at(i)->Get_Y() + Global_Player_Vector->at(j)->at(i)->Get_Sprite_Height() );
							}
						}
					} else { //Handle Mode OFF
						return false; //presence not allowed no need to work more
					}
				}
			}
		}
	}
	
//Handle collisions with Monsters
	//Loop for all monsters's vector
	for (unsigned int j=0; j < Global_Monster_Vector->size(); j++)
	{
		//loop for the current monster's vector
		for(unsigned int i=0; i < Global_Monster_Vector->at(j)->size(); i++)
		{
			//In order to the character to not check collision's with himself
			if ( ( X != Global_Monster_Vector->at(j)->at(i)->Get_X() ) || ( Y != Global_Monster_Vector->at(j)->at(i)->Get_Y() ) )
			{
				inf_rect = Collision_Box.inf( Global_Monster_Vector->at(j)->at(i)->Get_Collision_Box() );
				if ( ( inf_rect.getw() != 0 ) || ( inf_rect.geth() != 0 ) ) //we'r collisioning
				{
					if (Handle_Collisions) //Handle Mode ON
					{
						if ( inf_rect.getw() <= inf_rect.geth() )
						{
							if ( inf_rect.getx() <= (Global_Monster_Vector->at(j)->at(i)->Get_X() + (Global_Monster_Vector->at(j)->at(i)->Get_Sprite_Width()/2) ) )
							{
								Collision_Box.setx( Global_Monster_Vector->at(j)->at(i)->Get_X() - Sprite_Width );
							} 
							else 
							{
								Collision_Box.setx( Global_Monster_Vector->at(j)->at(i)->Get_X() + Global_Monster_Vector->at(j)->at(i)->Get_Sprite_Width() );
							}
							
						} 
						else
						{
							if ( inf_rect.gety() <= (Global_Monster_Vector->at(j)->at(i)->Get_Y() + (Global_Monster_Vector->at(j)->at(i)->Get_Sprite_Height()/2) ) )
							{
								Collision_Box.sety( Global_Monster_Vector->at(j)->at(i)->Get_Y() - Sprite_Height );
							} 
							else 
							{
								Collision_Box.sety( Global_Monster_Vector->at(j)->at(i)->Get_Y() + Global_Monster_Vector->at(j)->at(i)->Get_Sprite_Height() );
							}
						}
						/*if ( inf_rect.getw() <= inf_rect.geth() )
						{
							if ( (Collision_Box.getx() - X > 0 ) || (Collision_Box.gety() - Y > 0 ) )//we r moving right or down
							{
								Collision_Box.setx( Collision_Box.getx() - inf_rect.getw() ) ;
							} 
							else if ( (Collision_Box.getx() - X < 0 ) || (Collision_Box.gety() - Y < 0 ) ) //we r moving up or left
							{
								Collision_Box.setx( Collision_Box.getx() + inf_rect.getw() ) ;
							}
						} 
						else if ( inf_rect.getw() > inf_rect.geth() )
						{
							if ( (Collision_Box.getx() - X > 0 ) || (Collision_Box.gety() - Y > 0 ) )//we r moving right or down
							{
								Collision_Box.sety( Collision_Box.gety() - inf_rect.geth() );
							}
							else if ( (Collision_Box.getx() - X < 0 ) || (Collision_Box.gety() - Y < 0 ) ) //we r moving up or left
							{
								Collision_Box.sety( Collision_Box.gety() + inf_rect.geth() );
							}
						} */
						/*else  // =
						{
							if (Collision_Box.getx() - X > 0 ) //we r moving right
							{
								Collision_Box.setx( Collision_Box.getx() - inf_rect.getw() ) ;
							} 
							else if (Collision_Box.getx() - X < 0 )
							{
								Collision_Box.setx( Collision_Box.getx() + inf_rect.getw() ) ;
							}
							if (Collision_Box.gety() - Y > 0 ) //we r moving down
							{
								Collision_Box.sety( Collision_Box.gety() - inf_rect.geth() );
							}
							else if (Collision_Box.gety() - Y < 0 )
							{
								Collision_Box.sety( Collision_Box.gety() + inf_rect.geth() );
							}
						}*/
					} else { //Handle Mode OFF
						return false; //presence not allowed no need to work more
					}
				}
			}
		}
	}

	return true; //no error occured & presence allowed
} catch (...) { //error occured
	P0_Logger << nl << "Error when handling collisions ?!" << std::endl;   
	return false;
}
}

//Show Character on the screen
bool Character_Base::Show(const Rect& Camera, VideoSurface& Screen)
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
