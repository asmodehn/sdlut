#include "Character_Base.hh"

//Constructor
Character_Base::Character_Base()
{
try {
/****Characteristics****/
	X = 0, Y =0;
	Ch_Vel = CH_VEL; //default velocity
	xVel = 0, yVel = 0;

	Sprite_Width = 0, Sprite_Height = 0;

	BASE_LIFE = 0, Real_Life = BASE_LIFE;
	BASE_ARMOR = 0, Real_Armor = BASE_ARMOR;
	BASE_INFLICTED_DAMAGE = 0, Real_Inflicted_Damage = BASE_INFLICTED_DAMAGE;
	BASE_RANGE = 0, Real_Range = BASE_RANGE;

	Characters_ID = Humanoid; //default

/****Movements****/
	Move_Direction = CH_RIGHT; //initial direction: right

	//Default Area: the whole level
	Allowed_Area.setx(0);
	Allowed_Area.sety(0);
	Allowed_Area.setw(LEVEL_WIDTH);
	Allowed_Area.seth(LEVEL_HEIGHT);

/****Attack****/
	//Attack variable
	attack_successfull = 0; //Tells if a monster has been hit, by default no
	attack_initial_x = -1;
	attack_initial_y = -1;
	attack_direction = -1;

	//Attack Styles (default: unarmed only)
	Unarmed_Style_Available = true, Melee_Style_Available = false, Distant_Style_Available = false, Throwing_Style_Available = false, Magic_Style_Available = false;

/****Animations****/
	Current_Tileset = NULL;
	//Animations Centers
	Current_Animations_Center = NULL;
	//TODO: the 3 animations center below must be the link to the different animations center
	Unarmed_Animations_Center = NULL;
	Melee_Animations_Center = NULL;
	Distant_Animations_Center = NULL;	

	//CB modifier between sprite dimensions and "real" dimensions
	CB_X_Modifier = 0, CB_Y_Modifier = 0, CB_Width = 0, CB_Height = 0;

/****Default Flags****/
	Moving_Status = -1; //stopped
	Alive_Status = 1; //alive
	attack_status = false; //no attack, false = 0
	attack_style = 0; //unarmed
	Hitted_Status = 0; //not hitted

} catch (std::exception &exc) {
	throw std::logic_error(exc.what());
} catch (...) {
	throw std::logic_error("Unhandled Error In Character Base Constructor");
}
}

//Destructor
Character_Base::~Character_Base()
{
}

//Move character using the AI or a predefined movement
void Character_Base::Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
try {
	//character can move if: he is alived && he has not been hitted && he is stopped or paused
	if ( (Get_Alive_Status() == 1) && (Get_Hitted_Status() == 0) && (Get_Moving_Status() <= -1) )
	{
		//move: 10 chances over 1200 (that should correspond to 1 chance over 2 every 1s @ 60fps)
		if (rand()%1200 < 10) 
		//if (rand()%10 < 10)
		{
P0_Logger << nl << "Character " << this << " Finding Path" << std::endl; 

			//
			//todo get the sight range from character's xml desc file
			//
			int Sight_Range = 6*BATF_SPRITE_W;

			//the destination
			Point Destination;
			bool Dest_Founded = false;
			//we check for a destination only 5 times max
			for (unsigned int i = 0; i<5; i++)
			{
				//we get a possible destination then store it to the collision box in order to check w Manage_Collisions() if the destination is reachable at this time
				Destination = AI::Choose_Destination( Point(Get_X(), Get_Y()), Sight_Range, Point(Sprite_Width, Sprite_Height) );
				Collision_Box.setx(Destination.getx() + CB_X_Modifier );
				Collision_Box.sety(Destination.gety() + CB_Y_Modifier );

				//destination same as current position
				if ( Destination == Point(Get_X(), Get_Y()) )
					continue;

				if( Manage_Collisions(Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector, false) )
				{//Destination ok: indicate the dest has been founded than leave loop
					
					Dest_Founded = true;
					break;
				}
				//Dest not found loop
			}

			//reset CB
			Collision_Box.setx(Get_X() + CB_X_Modifier);
			Collision_Box.sety(Get_Y() + CB_Y_Modifier);

			if (!Dest_Founded)
				return; //we have not found a destination in time, we leave

			if ( ( abs( Destination.getx() - Get_X()) > Sprite_Width ) || ( abs( Destination.gety() - Get_Y()) > Sprite_Height ) )
			{
				P0_Logger << nl << "Path Must have at leat 2 steps" << std::endl; 
			}

			//we have found a dest, it's time to found a path to it. NB: we used the sprite dims as the grid size (todo: perhaps use a static method or implement the pathfinder in the constructor to gain time ?)
			PathFinder myPathFinder = PathFinder( Point(Sprite_Width, Sprite_Height) );
			Path = myPathFinder.Get_Path( Point(Get_X(), Get_Y()), Destination, this, Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector );

			//now that we have the path we must inform that we want to move
			Set_Moving_Status(2);

P0_Logger << nl << "Character Path Found: " << &Path << " w Size: " << Path.size() << std::endl; 
P0_Logger << nl << "Origin: (" << Get_X() << ", " << Get_Y() << "); Final Destination: (" << Destination.getx() << ", " << Destination.gety() << ")" << std::endl; 

		}
	}
	//character: want to move or his animation have just finished or have an non empty path (-> has not finished his movement) ) and he is alived and he has not been hitted
	else if  ( ( ( Get_Moving_Status() == 2 ) || ( Get_Moving_Status() == 0 ) ) && (Get_Alive_Status() == 1) && (Get_Hitted_Status() == 0) )
	{

P0_Logger << nl << "Character Moving Animation For Path: " << &Path << " @ Step " << Path.size() << std::endl;  

		list<Point>::iterator i = Path.begin();

		//We follow the path until we reach the destination
		if ( ( i != Path.end() ) && ( Path.size() > 0) )
		{
			assert( Path.size() > 0 && "Path size <= 0 !!!" );	

			//Update velocity
			xVel = i->getx() - Get_X();
			if ( xVel < 0 )
				xVel = -1;// * Ch_Vel;
			else if ( xVel > 0 )
				xVel = 1;//Ch_Vel;
			else //=
				xVel = 0;

			yVel = i->gety() - Get_Y();
			if ( yVel < 0 )
				yVel = -1;// * Ch_Vel;
			else if ( yVel > 0 )
				yVel = 1;//Ch_Vel;
			else //=
				yVel = 0;

			//Find Direction
			if( Find_Direction_From_Velocities() == false )
			{ 
				P0_Logger << nl << "Check character direction Failed " << std::endl;    
			}				

P0_Logger << nl << "Going From (" << Get_X() << ", " << Get_Y() << ") To (" << i->getx() << ", " << i->gety() << ") using the direction: " << Get_Move_Direction() <<std::endl;  

			//Launch Move Animation (todo: manage walk/run !)
			assert( this != NULL && "The Character Instance is NULL ???!!!");
			Current_Animations_Center->Walk_Animation_Play(const_cast<Character_Base*>(this), Point(i->getx(), i->gety()), Global_Player_Vector, Environment_Sprite_Vector, BackGround_Sprite_Vector, Global_Monster_Vector);

P0_Logger << nl << "Character Moving Animation Launched For Path: " << &Path << " @ Step " << Path.size() << std::endl;  

			//Erase the place we've just reached
			if ( Get_Moving_Status() >= 0 ) //coz the Walk_Animation_Play() could have stopped the character & erase the Path in case he is blocked
				Path.pop_front(); 
	
		} else {

P0_Logger << nl << "Character Moving Animation For Path: " << &Path << " Finished @ (" << Get_X() << ", " << Get_Y() << ")\n" << std::endl;  

			//We've reach destination (todo: launch a timer to disable move during 3s (usefull?))
			Current_Animations_Center->Stop_Animation_Play(const_cast<Character_Base*>(this));
		}
	}
	//character: want to move and he his alived but he has been hitted
	else if  ( ( Get_Moving_Status() >= 0 ) && (Get_Alive_Status() == 1) && (Get_Hitted_Status() > 0) )
	{
		Current_Animations_Center->Stop_Animation_Play(const_cast<Character_Base*>(this));
	}

} catch (std::exception &exc) {
	//reset CB
	Collision_Box.setx( Get_X() + CB_X_Modifier );
	Collision_Box.sety( Get_Y() + CB_Y_Modifier );
	Set_Moving_Status(-1); //stop the ch
	throw std::logic_error( "From Character_Base::Move(), " + (string)exc.what() );
} catch (...) {
	//reset CB
	Collision_Box.setx( Get_X() + CB_X_Modifier );
	Collision_Box.sety( Get_Y() + CB_Y_Modifier );
	Set_Moving_Status(-1); //stop the ch
	throw std::logic_error("Unhandled Error In Character_Base::Move()");  
}
}

//Handle collisions between the ch's collision box & the battlefield & other characters
//Handle_Collisions Mode OFF: return true if the CB is allowed to be here
//Handle_Collisions Mode ON: Check if CB is allowed to be here, if no, moved it to the best place near it's current position regarding of interactions rules. return false in case of error.
bool Character_Base::Manage_Collisions(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector, bool Handle_Collisions )
{
try {
//Handle collisions with Allowed area
	if (Handle_Collisions) //Handle Mode ON
	{
		Collision_Box.setx( max<int>( Collision_Box.getx(), Allowed_Area.getx() ) );
		Collision_Box.setx( min<int>( Collision_Box.getx(), Allowed_Area.getx() + Allowed_Area.getw() - Collision_Box.getw() ) );
		Collision_Box.sety( max<int>( Collision_Box.gety(), Allowed_Area.gety() ) );
		Collision_Box.sety( min<int>( Collision_Box.gety(), Allowed_Area.gety() + Allowed_Area.geth() - Collision_Box.geth() ) );
	} else { //Handle Mode OFF
		//outside the allowed area
		if ( ( Collision_Box.getx() < Allowed_Area.getx() ) || ( (signed)(Collision_Box.getx() + Collision_Box.getw()) > (signed)(Allowed_Area.getx() + Allowed_Area.getw()) ) || ( Collision_Box.gety() < Allowed_Area.gety() ) || ( (signed)(Collision_Box.gety() + Collision_Box.geth()) > (signed)(Allowed_Area.gety() + Allowed_Area.geth()) ) )
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
									Collision_Box.setx( BackGround_Sprite_Vector->at(it)->Get_X() - CB_Width );
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
									Collision_Box.sety( BackGround_Sprite_Vector->at(it)->Get_Y() - CB_Height );
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
							Collision_Box.setx( Environment_Sprite_Vector->at(i)->Get_X() - CB_Width );
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
							Collision_Box.sety( Environment_Sprite_Vector->at(i)->Get_Y() - CB_Height );
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
							if ( inf_rect.getx() <= (signed)(Global_Player_Vector->at(j)->at(i)->Get_Collision_Box().getx() + (Global_Player_Vector->at(j)->at(i)->Get_Collision_Box().getw()/2) ) )
							{
								Collision_Box.setx( Global_Player_Vector->at(j)->at(i)->Get_Collision_Box().getx() - CB_Width );
							} 
							else 
							{
								Collision_Box.setx( Global_Player_Vector->at(j)->at(i)->Get_Collision_Box().getx() + Global_Player_Vector->at(j)->at(i)->Get_Collision_Box().getw() );
							}
						} 
						else
						{
							if ( inf_rect.gety() <= (signed)(Global_Player_Vector->at(j)->at(i)->Get_Collision_Box().gety() + (Global_Player_Vector->at(j)->at(i)->Get_Collision_Box().geth()/2) ) )
							{
								Collision_Box.sety( Global_Player_Vector->at(j)->at(i)->Get_Collision_Box().gety() - CB_Height );
							} 
							else 
							{
								Collision_Box.sety( Global_Player_Vector->at(j)->at(i)->Get_Collision_Box().gety() + Global_Player_Vector->at(j)->at(i)->Get_Collision_Box().geth() );
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
							if ( inf_rect.getx() <= (signed)(Global_Monster_Vector->at(j)->at(i)->Get_Collision_Box().getx() + (Global_Monster_Vector->at(j)->at(i)->Get_Collision_Box().getw()/2) ) )
							{
								Collision_Box.setx( Global_Monster_Vector->at(j)->at(i)->Get_Collision_Box().getx() - CB_Width );
							} 
							else 
							{
								Collision_Box.setx( Global_Monster_Vector->at(j)->at(i)->Get_Collision_Box().getx() + Global_Monster_Vector->at(j)->at(i)->Get_Collision_Box().getw() );
							}
						} 
						else
						{
							if ( inf_rect.gety() <= (signed)(Global_Monster_Vector->at(j)->at(i)->Get_Collision_Box().gety() + (Global_Monster_Vector->at(j)->at(i)->Get_Collision_Box().geth()/2) ) )
							{
								Collision_Box.sety( Global_Monster_Vector->at(j)->at(i)->Get_Collision_Box().gety() - CB_Height );
							} 
							else 
							{
								Collision_Box.sety( Global_Monster_Vector->at(j)->at(i)->Get_Collision_Box().gety() + Global_Monster_Vector->at(j)->at(i)->Get_Collision_Box().geth() );
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
bool Character_Base::Find_Direction_From_Velocities()
{
try {
	if (!Get_Attack_Status()) //no attack is occuring (todo: find if this test is usefull & necessary^^)
	{
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
	}
	return true; //no error
} catch (...) {
  return false; //error occured
}
}

//Set values defining attack for all attack styles
void Character_Base::Attack()
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


	//attack is occuring
	Set_Attack_Status(true);
	//get the attack direction
	attack_direction = Move_Direction;
	//By default consider that no attack was successfull
	attack_successfull = 0;

	//temp stuff to make code below more readable
	int _x = Collision_Box.getx(), _y = Collision_Box.gety(), _w = Collision_Box.getw(), _h = Collision_Box.geth();

	//Unarmed Style
	if (attack_style == 0)
	{
		//Characters_Current_Tileset = Current_Animations_Center->Get_Attack_Animation()->Get_Animation_Tileset();

		//range: Only hit at contact (TODO future: find a more realistic hit with the sword)
		BASE_RANGE = 1;
		Real_Range = BASE_RANGE;
		//
		//TODO move that^ to xml
		//

		//Move the attack box at border of the character sprite in the good direction
		if( attack_direction == CH_RIGHT )
		{
			attack_initial_x = _x + _w;
			attack_initial_y = _y;
			attack_CB.setw( _w/8 );
			attack_CB.seth( _h );
		}
		else if( attack_direction == CH_RIGHT_DOWN )
		{
			attack_initial_x = _x+(5*_w/8);
			attack_initial_y = _y+(5*_h/8);
			attack_CB.setw( 5*_w/8 );
			attack_CB.seth( 5*_h/8 );
		}
		else if( attack_direction == CH_DOWN )
		{
			attack_initial_x = _x;
			attack_initial_y = _y+_h;
			attack_CB.setw( _w );
			attack_CB.seth( _h/8 );
		}
		else if( attack_direction == CH_LEFT_DOWN )
		{
			attack_initial_x = _x-PC_WIDTH/8;
			attack_initial_y = _y+(5*_h/8);
			attack_CB.setw( 5*_w/8 );
			attack_CB.seth( 5*_h/8 );
		}
		else if( attack_direction == CH_LEFT )
		{
			attack_initial_x = _x-_w/8;
			attack_initial_y = _y;
			attack_CB.setw( _w/8 );
			attack_CB.seth( _h );
		}
		else if( attack_direction == CH_LEFT_UP )
		{			
			attack_initial_x = _x-_w/8;
			attack_initial_y = _y-_h/8;
			attack_CB.setw( 5*_w/8 );
			attack_CB.seth( 5*_h/8 );
		}
		else if( attack_direction == CH_UP )
		{
			attack_initial_x = _x;
			attack_initial_y = _y-_h/8;
			attack_CB.setw( _w );
			attack_CB.seth( _h/8 );
		}
		else if( attack_direction == CH_RIGHT_UP )
		{
			attack_initial_x = _x+(5*_w/8);
			attack_initial_y = _y-_h/8;
			attack_CB.setw( 5*_w/8 );
			attack_CB.seth( 5*_h/8 );
		}
		
		//Set Attack BOX
		attack_CB.setx( attack_initial_x );
		attack_CB.sety( attack_initial_y );
	}
	// Melee Style
	else if (attack_style == 1)
	{
		//Characters_Current_Tileset = Current_Animations_Center->Get_Attack_Animation()->Get_Animation_Tileset();
		
		//range: Only hit at contact (TODO future: find a more realistic hit with the sword)
		BASE_RANGE = 1;
		Real_Range = BASE_RANGE;
		//
		//TODO move that^ to xml
		//

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
	// Distant Style
	else if (attack_style == 2)
	{
		//Characters_Current_Tileset = Current_Animations_Center->Get_Attack_Animation()->Get_Animation_Tileset();

			
		//range: 6 square (until new map format -> 12 !!)
		BASE_RANGE = BATF_SPRITE_W*6;
		Real_Range = BASE_RANGE;
		//
		//TODO move that^ to xml
		//

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

	
} catch (std::exception &exc) {
	Set_Attack_Status(false);
	throw std::logic_error("Error In Character_Base::Attack() : " + (string)exc.what() );
} catch (...) {
	Set_Attack_Status(false);
	throw std::logic_error("Unhandled Error In Character_Base::Attack()");
}
}

//Check if collision between the attack and one of the monsters on the battlefield regarding the number of movements that the attack collision is currently doing (callback method)
int Character_Base::Attack_Check_Status(int ch2attack_distance, int inflicted_damage, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
try {
	//Check attack direction
	if( attack_direction == CH_RIGHT )
	{
		attack_CB.setx ( attack_CB.getx() + ch2attack_distance );
	}
	else if( attack_direction == CH_RIGHT_DOWN )
	{
		attack_CB.setx ( (int)(attack_CB.getx() + ceil(ch2attack_distance/sqrt(2.f))) );
		attack_CB.sety ( (int)(attack_CB.gety() + ceil(ch2attack_distance/sqrt(2.f))) );
	}
	else if( attack_direction == CH_DOWN )
	{
		attack_CB.sety( attack_CB.gety() + ch2attack_distance );
	}
	else if( attack_direction == CH_LEFT_DOWN )
	{
		attack_CB.setx( (int)(attack_CB.getx() - ceil(ch2attack_distance/sqrt(2.f))) );
		attack_CB.sety( (int)(attack_CB.gety() + ceil(ch2attack_distance/sqrt(2.f))) );
	}
	else if( attack_direction == CH_LEFT )
	{
		attack_CB.setx( attack_CB.getx() - ch2attack_distance );
	}
	else if( attack_direction == CH_LEFT_UP )
	{
		attack_CB.setx( (int)(attack_CB.getx() - ceil(ch2attack_distance/sqrt(2.f))) );
		attack_CB.sety( (int)(attack_CB.gety() - ceil(ch2attack_distance/sqrt(2.f))) );
	}
	else if( attack_direction == CH_UP )
	{
		attack_CB.sety( attack_CB.gety() - ch2attack_distance );
	}
	else if( attack_direction == CH_RIGHT_UP )
	{
		attack_CB.setx( (int)(attack_CB.getx() + ceil(ch2attack_distance/sqrt(2.f))) );
		attack_CB.sety( (int)(attack_CB.gety() - ceil(ch2attack_distance/sqrt(2.f))) );
	}
	
	//
	//todo: make this work for monsters
	//

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
					//Stop the monster
					Current_Monster->Get_Current_Animations_Center()->Stop_Animation_Play(Current_Monster);
					//Set the Hitted_Status to 2 for the character
					Current_Monster->Set_Hitted_Status( 2 );
					//Leave the check returning the ID (which will be saved inside the attack_sucessful) in order to hit only one monster at a time.
					return Current_Monster->Get_Characters_ID();
				}
			}
		}
	}
	//miss
	return 0;

} catch (std::exception &exc) {
	throw std::logic_error("From Character_Base::Attack_Check_Status(), " + (string)exc.what() );
} catch (...) {
	throw std::logic_error("Unhandled Error In Character_Base::Attack_Check_Status()");
}
}

//Set Character Sprite Which change when attack occured (callback)
void Character_Base::Attack_Set_Animation_Sprite(std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector)
{
try {
	//reset the frame status at end of animation depending of the attack style
	if ( Get_Attack_Style() == 0 ) // Unarmed Style
	{
		//
		//todo: for unarmed: play good sound
		//
		//play foot Fx	
		//App::getInstance().getMixer().playChannel(SwordFx_Chan);

		Current_Animations_Center->Attack_Animation_Play(const_cast<Character_Base*>(this), Global_Monster_Vector);
	}
	if ( Get_Attack_Style() == 1 ) // Melee Style
	{
		//play sword Fx
		if ( (ENABLE_SFXS_SOUNDS) && (ENABLE_ALL_SOUNDS) )
			App::getInstance().getMixer().playChannel(*SwordFx.get(), SFXS_VOLUME);

		Current_Animations_Center->Attack_Animation_Play(const_cast<Character_Base*>(this), Global_Monster_Vector);
		
	}
	else if ( Get_Attack_Style() == 2 ) // Distant Style
	{
		//play bow Fx
		if ( (ENABLE_SFXS_SOUNDS) && (ENABLE_ALL_SOUNDS) )
			App::getInstance().getMixer().playChannel(*BowFx.get(), SFXS_VOLUME);

		Current_Animations_Center->Attack_Animation_Play(const_cast<Character_Base*>(this), Global_Monster_Vector);

	}

	//P0_Logger << nl << "Attack_Set_Animation_Sprite called FRAME:" << frame << std::endl;

} catch (std::exception &exc) {
	throw std::logic_error("From Character_Base::Attack_Set_Animation_Sprite(), " + (string)exc.what() );
} catch (...) {
	throw std::logic_error("Unhandled Error In Character_Base::Attack_Set_Animation_Sprite()");
}
}

//Reset everything to normal mode when the attack is finished
void Character_Base::Attack_Reset()
{
try {
	//unarmed
	if ( attack_style == 0 )
	{
		//if the attack was successfull
		if (attack_successfull != 0 )
		{
			//
			//todo: play good fx
			//
			//play hit Fx	
			//App::getInstance().getMixer().playChannel(HitFx_Chan);
		}
		else 
		{
			//
			//todo play good fx
			//
			//play miss Fx	
			//App::getInstance().getMixer().playChannel(MissFx_Chan);
		} 
		
			//reset attack
		Set_Attack_Initial_X(-1);
		Set_Attack_Initial_Y(-1);
		Set_Attack_Direction(-1);
	}
	//melee attack 
	else if ( attack_style == 1 )
	{
		//if the attack was successfull
		if (attack_successfull != 0 )
		{
			//play hit Fx	
			if ( (ENABLE_SFXS_SOUNDS) && (ENABLE_ALL_SOUNDS) )
				App::getInstance().getMixer().playChannel(*HitFx.get(), SFXS_VOLUME);
		}
		else 
		{
			//play miss Fx	
			if ( (ENABLE_SFXS_SOUNDS) && (ENABLE_ALL_SOUNDS) )
				App::getInstance().getMixer().playChannel(*MissFx.get(), SFXS_VOLUME);
		} 
		
			//reset attack
		Set_Attack_Initial_X(-1);
		Set_Attack_Initial_Y(-1);
		Set_Attack_Direction(-1);
	}
	//distant attack 
	else if ( attack_style == 2 )
	{
		//nothing to do for now
	}

	Set_Attack_Status(false); //end of attack for the character (arrow is independent)

} catch (std::exception &exc) {
	throw std::logic_error( "From Character_Base::Attack_Reset(), " + (string)exc.what() );
} catch (...) {
	throw std::logic_error("Unhandled Error In Character_Base::Attack_Reset()");  
}
}

//Manage when a character decided to change his attack style: check if style present, update characteristics, etc
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

//Calculate the current life of the monster depending on damage, malus, etc
bool Character_Base::Calculate_Real_Life(int received_damage)
{
	int real_received_damage = (received_damage - Get_Real_Armor()); //TODO(future): Set the real damage formula base on mo's condition

	real_received_damage = max(0, real_received_damage); //in case damage dont exceed armor value then set it to 0: no damage

	Set_Real_Life( Get_Real_Life() - real_received_damage) ;
	
	//Monster as no life => dying animation should start
	if ( Get_Real_Life() <= 0 )
		Set_Alive_Status(0);

	return true; //everything went fine
}

//Show Character on the screen
bool Character_Base::Show(const Rect& Camera, VideoSurface& Screen)
{
try {

	if (Get_Alive_Status() == 0 ) //dying: launch the animation
	{
		Current_Animations_Center->Death_Animation_Play(const_cast<Character_Base*>(this));
	}

	if ( (Get_Hitted_Status() == 2 ) && Get_Alive_Status() == 1 )//hitted & alive: launch the animation
	{
		Current_Animations_Center->Hit_Animation_Play(const_cast<Character_Base*>(this));
	}

	if (  !(Get_Alive_Status() == -2) ) //every case except when character is "fully" dead: -2
	{
		//Defaults
		if (Current_Tileset == NULL)
		{
			Current_Animations_Center->Stop_Animation_Play(const_cast<Character_Base*>(this));
		}


		//Check if the character sprite is present on the screen minus the status bar
		//NOTE : PC_WIDTH/PC_HEIGHT are present because the camera is centered on the middle of the player and so we need to draw the screen a little more than the camera dim
		if ( ( (Camera.getx()-PC_WIDTH) <= X) && (X < (signed)(Camera.getx() + Camera.getw()) ) && ( (Camera.gety()-PC_HEIGHT) <= Y) && (Y < (signed)(Camera.gety() + Camera.geth() - STATUS_BAR_H) ) )
		{
			//It's present than draw it
			Screen.blit(*Current_Tileset, Point::Point(X - Camera.getx(), Y - Camera.gety()), Current_Tile_Rect);
		}
	}

	return true; //no error
} catch (...) {
  		return false; //error occured
}
}
