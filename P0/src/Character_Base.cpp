#include "Character_Base.hh"

//Check if the bg allow the character presence
std::vector<int> Character_Base::Check_background_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
	std::vector<int> res; //vector of collision results
	Rect env_rect;

	//loop on all the vector
	for(unsigned int i=0; i < BackGround_Sprite_Vector.size(); i++)
	{
		env_rect.setx(BackGround_Sprite_Vector[i]->Get_X());
		env_rect.sety(BackGround_Sprite_Vector[i]->Get_Y());
		env_rect.setw(BATF_SPRITE_W);
		env_rect.seth(BATF_SPRITE_H);

		//When collision...
		if ( check_collision( Collision_Box, env_rect ) )
		{
			//... fill the vector in function of the destination background rules
			res.push_back( Get_BG_vs_CH_Rules( BackGround_Sprite_Vector[i]->Get_BattleField_Type() ) );
		}
	}

	return res;
}

//Check if the env allow the character presence
std::vector<int> Character_Base::Check_environment_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector)
{
	std::vector<int> res; //vector of collision results
	Rect env_rect;

	//loop on all the vector
	for(unsigned int i=0; i < Environment_Sprite_Vector.size(); i++)
	{
		env_rect.setx(Environment_Sprite_Vector[i]->Get_X());
		env_rect.sety(Environment_Sprite_Vector[i]->Get_Y());
		env_rect.setw(BATF_SPRITE_W);
		env_rect.seth(BATF_SPRITE_H);

		//When collision...
		if ( check_collision( Collision_Box, env_rect ) )
		{
			//... fill the vector in function of the destination background rules
			res.push_back( Get_Env_vs_CH_Rules( Environment_Sprite_Vector[i]->Get_BattleField_Type() ) );
		}
	}

	return res;
}

//Check if the battlefield allow the character presence
bool Character_Base::Check_battlefield_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector)
{
	bool res = true;

	std::vector<int> env_vs_ch_collisions = Check_environment_allow_character(Collision_Box, Environment_Sprite_Vector);
	std::vector<int> bg_vs_ch_collisions = Check_background_allow_character(Collision_Box, BackGround_Sprite_Vector);

	for (unsigned int i = 0; i < env_vs_ch_collisions.size(); i++)
	{
		if ( env_vs_ch_collisions[i] == -1 ) //environment is not present
		{
			if ( bg_vs_ch_collisions[i] == 0 )
			{
				res = false; //collision with bg
				return res; //no need to work more
			}

		} else if ( env_vs_ch_collisions[i] == 0 ) 
		{
			res = false; //collision with env
			return res; //no need to work more
		} else {
			res = true; //no collision
		}
	}
	
	//Never happend (just 4 warning)
	return res;
}
