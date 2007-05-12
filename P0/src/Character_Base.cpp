#include "Character_Base.hh"

//Constructor
Character_Base::Character_Base()
{
/****Characteristics****/
	X = 0, Y =0;
	Ch_Vel = CH_VEL; //default velocity
	xVel = 0, yVel = 0;

	Sprite_Width = 0, Sprite_Height = 0;
	Sprite_Filename = "";

	BASE_LIFE = 0, Real_Life = BASE_LIFE;
	BASE_ARMOR = 0, Real_Armor = BASE_ARMOR;
	BASE_INFLICTED_DAMAGE = 0, Real_Inflicted_Damage = BASE_INFLICTED_DAMAGE;
	BASE_RANGE = 0, Real_Range = BASE_RANGE;

	Characters_ID = Humanoid; //default

	Alive_Status = true;

/****Movements****/
	//Initial moving status
	Moving_Status = false;
	Move_Direction = CH_RIGHT;

	//Default Area: the whole level
	Allowed_Area.setx(0);
	Allowed_Area.sety(0);
	Allowed_Area.setw(LEVEL_WIDTH);
	Allowed_Area.seth(LEVEL_HEIGHT);

/****Attack****/
	//Attack variable
	attack_status = false; //false = 0
	attack_style = 0; //default: unarmed
	attack_successfull = 0; //Tells if a monster has been hit, by default no
	attack_initial_x = -1;
	attack_initial_y = -1;
	attack_direction = -1;

	//Attack Styles (default: unarmed only)
	Unarmed_Style_Available = true, Melee_Style_Available = false, Distant_Style_Available = false, Throwing_Style_Available = false, Magic_Style_Available = false;

/****Animations****/
	//Tilesets
	Characters_Current_Tileset = NULL;
	Characters_Current_Unarmed_Tileset = NULL;
	Characters_Current_Melee_Tileset = NULL;
	Characters_Current_Distant_Tileset = NULL;
	//TODO: the 3 tileset below must be the link to the different animations center not a tileset

	Default_Animations_Center = NULL;

	//initial frame
    frame = 0;

	//CB modifier between sprite dimensions and "real" dimensions
	CB_X_Modifier = 0, CB_Y_Modifier = 0, CB_Width = 0, CB_Height = 0;
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

//check the move direction and assign the good sprite
bool Character_Base::Assign_Direction_Sprite()
{
try {
	if (!Get_Attack_Status()) //no attack is occuring
	{
		int old_Move_Status = Move_Direction;

		//check velocities
		if ( (Get_xVel() > 0) && (Get_yVel() == 0) ) //CH is moving right
		{
			Move_Direction = CH_RIGHT;
		}
		else if ( (Get_xVel() > 0) && (Get_yVel() > 0) )  //right down
		{
			Move_Direction = CH_RIGHT_DOWN;
		}
		else if ( (Get_xVel() == 0) && (Get_yVel() > 0) )  //down
		{
			Move_Direction = CH_DOWN;
		}
		else if ( (Get_xVel() < 0) && (Get_yVel() > 0) ) //left down
		{
			Move_Direction = CH_LEFT_DOWN;
		}
		else if ( (Get_xVel() < 0) && (Get_yVel() == 0) ) //left
		{
			Move_Direction = CH_LEFT;
		}
		else if ( (Get_xVel() < 0) && (Get_yVel() < 0) ) //left up
		{
			Move_Direction = CH_LEFT_UP;
		}
		else if ( (Get_xVel() == 0) && (Get_yVel() < 0) ) //up
		{
			Move_Direction = CH_UP;
		}
		else if ( (Get_xVel() > 0) && (Get_yVel() < 0) ) //right up
		{
			Move_Direction = CH_RIGHT_UP;
		}
		
		//Good sprite for the direction
		//Current_Tile_Rect = Attack_Tile_Rect->at(Move_Direction*PLAYER_SWORD_ATTACK_ANIMATION_FRAME + 0);
		Current_Tile_Rect = Default_Animations_Center->Get_Stop_Animation()->Get_Animation_Tile_Rect()->at(Move_Direction);

		//Check if we are changing direction
		if ( old_Move_Status != Move_Direction )
		{ //change but dont move
			//xVel = 0;
			//yVel = 0;
			Moving_Status = false;
		} else {
			Moving_Status = true; //we're moving
		}
	}
	return true; //no error
} catch (...) {
  return false; //error occured
}
}

//define character sprite which appear on the screen during moves
bool Character_Base::Set_Walk_Animation_Sprite()
{
	//P0_Logger << nl << "Set_Walk_Animation_Sprite called" << std::endl;

	//end of the timer for the moment (until walk animation developped (future dev))
	return false; //no animation
}

//define character sprite which appear on the screen during run
bool Character_Base::Set_Run_Animation_Sprite()
{
	//P0_Logger << nl << "Set_Run_Animation_Sprite called" << std::endl;

	//end of the timer for the moment (until run animation developped (future dev))
	return false; //no animation
}

//Set values defining attack for all attack styles
bool Character_Base::Attack()
{
try
{
	//attack is occuring
	attack_status = true;
	//get the attack direction
	attack_direction = Move_Direction;
	//By default consider that no attack was successfull
	attack_successfull = 0;

	if (attack_style == 0) //unarmed
	{
	//
	//todo: for unarmed: sound + move attack_cb & attack initials
	//
	}
	if (attack_style == 1) //melee
	{
		//play sword Fx	
		App::getInstance().getMixer().playChannel(SwordFx_Chan);

		//Move the attack box at border of the character sprite in the good direction
		if( attack_direction == CH_RIGHT )
		{
			attack_initial_x = X+PC_WIDTH;
			attack_initial_y = Y;
			attack_CB.setw( PC_WIDTH/8 );
			attack_CB.seth( PC_HEIGHT );
		}
		else if( attack_direction == CH_RIGHT_DOWN )
		{
			attack_initial_x = X+(5*PC_WIDTH/8);
			attack_initial_y = Y+(5*PC_HEIGHT/8);
			attack_CB.setw( 5*PC_WIDTH/8 );
			attack_CB.seth( 5*PC_HEIGHT/8 );
		}
		else if( attack_direction == CH_DOWN )
		{
			attack_initial_x = X;
			attack_initial_y = Y+PC_HEIGHT;
			attack_CB.setw( PC_WIDTH );
			attack_CB.seth( PC_HEIGHT/8 );
		}
		else if( attack_direction == CH_LEFT_DOWN )
		{
			attack_initial_x = X-PC_WIDTH/8;
			attack_initial_y = Y+(5*PC_HEIGHT/8);
			attack_CB.setw( 5*PC_WIDTH/8 );
			attack_CB.seth( 5*PC_HEIGHT/8 );
		}
		else if( attack_direction == CH_LEFT )
		{
			attack_initial_x = X-PC_WIDTH/8;
			attack_initial_y = Y;
			attack_CB.setw( PC_WIDTH/8 );
			attack_CB.seth( PC_HEIGHT );
		}
		else if( attack_direction == CH_LEFT_UP )
		{			
			attack_initial_x = X-PC_WIDTH/8;
			attack_initial_y = Y-PC_HEIGHT/8;
			attack_CB.setw( 5*PC_WIDTH/8 );
			attack_CB.seth( 5*PC_HEIGHT/8 );
		}
		else if( attack_direction == CH_UP )
		{
			attack_initial_x = X;
			attack_initial_y = Y-PC_HEIGHT/8;
			attack_CB.setw( PC_WIDTH );
			attack_CB.seth( PC_HEIGHT/8 );
		}
		else if( attack_direction == CH_RIGHT_UP )
		{
			attack_initial_x = X+(5*PC_WIDTH/8);
			attack_initial_y = Y-PC_HEIGHT/8;
			attack_CB.setw( 5*PC_WIDTH/8 );
			attack_CB.seth( 5*PC_HEIGHT/8 );
		}
		
		//Set Attack BOX
		attack_CB.setx( attack_initial_x );
		attack_CB.sety( attack_initial_y );

	}
	else if (attack_style == 2) //distant
	{
		//play bow Fx	
		App::getInstance().getMixer().playChannel(BowFx_Chan);

		//Move the attack box at the middle of the character sprite in the good direction
		if( attack_direction == CH_RIGHT )
		{
			attack_initial_x = X+PC_WIDTH;
			attack_initial_y = Y+(PC_HEIGHT/2);
		}
		else if( attack_direction == CH_RIGHT_DOWN )
		{
			attack_initial_x = (int)( X+ceil(PC_WIDTH/sqrt(2.f)) ) ;
			attack_initial_y = (int)( Y+ceil(PC_HEIGHT/sqrt(2.f)) ) ;
		}
		else if( attack_direction == CH_DOWN )
		{
			attack_initial_x = X+(PC_WIDTH/2);
			attack_initial_y = Y+PC_HEIGHT;
		}
		else if( attack_direction == CH_LEFT_DOWN )
		{
			attack_initial_x = (int)( X+PC_WIDTH-ceil(PC_WIDTH/sqrt(2.f)) );
			attack_initial_y = (int)( Y+ceil(PC_HEIGHT/sqrt(2.f)) );
		}
		else if( attack_direction == CH_LEFT )
		{
			attack_initial_x = X;
			attack_initial_y = Y+(PC_HEIGHT/2);
		}
		else if( attack_direction == CH_LEFT_UP )
		{
			attack_initial_x = (int)( X+PC_WIDTH-ceil(PC_WIDTH/sqrt(2.f)) );
			attack_initial_y = (int)( Y+PC_HEIGHT-ceil(PC_HEIGHT/sqrt(2.f)) );
		}
		else if( attack_direction == CH_UP )
		{
			attack_initial_x = X+(PC_WIDTH/2);
			attack_initial_y = Y ;
		}
		else if( attack_direction == CH_RIGHT_UP )
		{
			attack_initial_x = (int)( X+ceil(PC_WIDTH/sqrt(2.f)) );
			attack_initial_y = (int)( Y+PC_HEIGHT-ceil(PC_HEIGHT/sqrt(2.f)) );
		}
		
		//Set Attack BOX
		attack_CB.setx( attack_initial_x );
		attack_CB.sety( attack_initial_y );
				//the arrow only hit with it tip
		attack_CB.setw(1);
		attack_CB.seth(1);

		//
		//
		// ARROW DISABLED FOR NOW: ONLY UNARMED STYLE AVAILABLE
		//
		//
		////Good Arrow sprite
		//	Current_Arrow_SpriteRect = Arrow_SpriteRect->at(attack_direction*PLAYER_ARROW_ATTACK_ANIMATION_FRAME);
		//
		////initial arrow position
		//	Set_Arrow_Sprite_Coordinate();
	}

	//no error
	return true;
}
catch (...) {
  return false; //error occured
}
}

//Check if collision between the attack and one of the monsters on the battlefield regarding the number of movements that the attack collision is currently doing (callback method)
int Character_Base::Attack_Check_Status(int attack_distance, int inflicted_damage, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
	//Check attack direction
	if( attack_direction == CH_RIGHT )
	{
		attack_CB.setx ( attack_CB.getx() + attack_distance );
	}
	else if( attack_direction == CH_RIGHT_DOWN )
	{
		attack_CB.setx ( (int)(attack_CB.getx() + ceil(attack_distance/sqrt(2.f))) );
		attack_CB.sety ( (int)(attack_CB.gety() + ceil(attack_distance/sqrt(2.f))) );
	}
	else if( attack_direction == CH_DOWN )
	{
		attack_CB.sety( attack_CB.gety() + attack_distance );
	}
	else if( attack_direction == CH_LEFT_DOWN )
	{
		attack_CB.setx( (int)(attack_CB.getx() - ceil(attack_distance/sqrt(2.f))) );
		attack_CB.sety( (int)(attack_CB.gety() + ceil(attack_distance/sqrt(2.f))) );
	}
	else if( attack_direction == CH_LEFT )
	{
		attack_CB.setx( attack_CB.getx() - attack_distance );
	}
	else if( attack_direction == CH_LEFT_UP )
	{
		attack_CB.setx( (int)(attack_CB.getx() - ceil(attack_distance/sqrt(2.f))) );
		attack_CB.sety( (int)(attack_CB.gety() - ceil(attack_distance/sqrt(2.f))) );
	}
	else if( attack_direction == CH_UP )
	{
		attack_CB.sety( attack_CB.gety() - attack_distance );
	}
	else if( attack_direction == CH_RIGHT_UP )
	{
		attack_CB.setx( (int)(attack_CB.getx() + ceil(attack_distance/sqrt(2.f))) );
		attack_CB.sety( (int)(attack_CB.gety() - ceil(attack_distance/sqrt(2.f))) );
	}
	
	//Collision with Monsters
	//Loop for all monster's vector
	for (unsigned int j=0; j < Global_Monster_Vector->size(); j++)
	{
		//loop for the current monster's vector
		for(unsigned int i=0; i < Global_Monster_Vector->at(j)->size(); i++)
		{
			//Get the current monster
			Character_Base* Current_Monster = Global_Monster_Vector->at(j)->at(i);

			//In order to not check himself
			if ( ( X != Current_Monster->Get_X() ) || Y != Current_Monster->Get_Y() )
			{
				if (check_collision( attack_CB, Current_Monster->Get_Collision_Box() ))
				{
					//One monster has been hit so send damage value to the monster
					Current_Monster->Calculate_Real_Life( inflicted_damage );
					//Than leave the check returning the ID (which will be saved inside the attack_sucessful) in order to hit only one monster at a time.
					return Current_Monster->Get_Characters_ID();
				}
			}
		}
	}
	//miss
	return 0;
}

//Set Character Sprite Which change when attack occured (callback)
bool Character_Base::Set_Attack_Animation_Sprite(std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
	//increase frame each time the timer is run (from 0 to the number of frame for the animation)
	frame++;

	//reset the frame status at end of animation depending of the attack style
	if ( Get_Attack_Style() == 0 ) // Unarmed Style
	{
		if (frame >= Default_Animations_Center->Get_Attack_Animation()->Get_Animation_Frame_Number() )
			frame =0; //reset frame anim
		//assign the good sprite rect to the character sprite rect depending on the frame and the direction
		Current_Tile_Rect = Default_Animations_Center->Get_Attack_Animation()->Get_Animation_Tile_Rect()->at(attack_direction * Default_Animations_Center->Get_Attack_Animation()->Get_Animation_Frame_Number() + frame );
		
		if ( frame == Default_Animations_Center->Get_Attack_Animation()->Get_Animation_KeyFrame() )
		{
			attack_successfull = Attack_Check_Status(Real_Range, Real_Inflicted_Damage, Global_Monster_Vector) ;
		}

	}
	if ( Get_Attack_Style() == 1 ) // Melee Style
	{
		if (frame >= PLAYER_SWORD_ATTACK_ANIMATION_FRAME )
			frame = 0; //reset frame anim

		//assign the good sprite rect to the character sprite rect depending on the frame and the direction
		
		Current_Tile_Rect = Default_Animations_Center->Get_Attack_Animation()->Get_Animation_Tile_Rect()->at(attack_direction * Default_Animations_Center->Get_Attack_Animation()->Get_Animation_Frame_Number() + frame );
		//to change  for the melee animation center ^
		//Current_Tile_Rect = Attack_Tile_Rect->at(attack_direction*PLAYER_SWORD_ATTACK_ANIMATION_FRAME + frame);
		
		//at the second frame of the anim we check if attack hit a monster
		if ( frame == 1 )
		{
			attack_successfull = Attack_Check_Status(Real_Range, Real_Inflicted_Damage, Global_Monster_Vector) ;
		}
	}
	else if ( Get_Attack_Style() == 2 ) // Distant Style
	{
		if (frame >= PLAYER_BOW_ATTACK_ANIMATION_FRAME )
			frame = 0; //reset frame anim
		
		//
		//TODO(future): define the good character sprite (future devs: depending of the frame and the direction)
		//
		//frame = 0;
	}


	//P0_Logger << nl << "Set_Attack_Animation_Sprite called FRAME:" << frame << std::endl;

	if ( frame == 0 )
		return false; //end of anim

	//anim is still looping
	return true;

}

//Manage attack between distant & melee style if these style are or non present
bool Character_Base::Change_Attack_Style()
{
	//
	//only unarmed for now !!!
	//
	Set_Attack_Style(0);
	return true;

	////Change weapon style by looping between the available styles (2 for the moment)
	//Set_Attack_Style( Get_Attack_Style() + 1 );
	//if (Get_Attack_Style() > 2) { Set_Attack_Style(1); } //loop between style

	//return true;
}

//Character Graphic Style Initialiation regarding the attack style
bool Character_Base::Manage_Attack_Style()
{
try
{
	//
	//TODO(future): Set weapons max hit range & damage and calculate character range and damage from them
	//TODO(future): put these value's definitions inside the constructor (when monster/npc will be allowed to attack)
	//TODO(future): use formula for character_real_damage depending on character condition (disease, etc)
	//
	//int character_max_damage = Real_Inflicted_Damage;
	//int character_real_damage = character_max_damage;
	//int character_current_damage = character_real_damage;

	//int character_max_range = 0;

	//Unarmed Style
	if (attack_style == 0)
	{
		Characters_Current_Tileset = Default_Animations_Center->Get_Attack_Animation()->Get_Animation_Tileset();

		//range: Only hit at contact (TODO future: find a more realistic hit with the sword)
		BASE_RANGE = 1;
		Real_Range = BASE_RANGE;
		//
		//TODO move that to xml
		//
		//P0_Logger << nl << "Graphic Style Updated To Unarmed Style : OK " << std::endl;
	}
	// Melee Style
	else if (attack_style == 1)
	{
		Characters_Current_Tileset = Default_Animations_Center->Get_Attack_Animation()->Get_Animation_Tileset();
		//Characters_Current_Tileset = Players_Tile_Melee;
		
		//range: Only hit at contact (TODO future: find a more realistic hit with the sword)
		BASE_RANGE = 1;
		Real_Range = BASE_RANGE;

		//P0_Logger << nl << "Graphic Style Updated To Melee Style : OK " << std::endl;
	}
	// Distant Style
	else if (attack_style == 2)
	{
		Characters_Current_Tileset = Default_Animations_Center->Get_Attack_Animation()->Get_Animation_Tileset();
		//Characters_Current_Tileset = Players_Tile_Distant;
			
		//range: 6 square
		BASE_RANGE = BATF_SPRITE_W*6;
		Real_Range = BASE_RANGE;

		//P0_Logger << nl << "Graphic Style Updated To Distant Style : OK " << std::endl;
	}
	return true;
}
catch (...) {
  return false; //error occured
}
}

//Calculate the current life of the monster depending on damage, malus, etc
bool Character_Base::Calculate_Real_Life(int received_damage)
{
	int real_received_damage = (received_damage - Get_Real_Armor()); //TODO(future): Set the real damage formula base on mo's condition

	if ( (real_received_damage) < 0) //in case damage dont exceed armor value then set it to 0: no damage
		real_received_damage = 0;

	Set_Real_Life( Get_Real_Life() - real_received_damage) ;
	
	//Monster as no life => dead
	if ( Get_Real_Life() <= 0 )
		Set_Alive_Status(false);

	return true; //everything went fine
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
		Screen.blit(*Characters_Current_Tileset, Point::Point(X - Camera.getx(), Y - Camera.gety()), Current_Tile_Rect);
	}
	return true; //no error
} catch (...) {
  		return false; //error occured
}
}
