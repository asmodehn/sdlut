#ifndef Character_Base_HH
#define Character_Base_HH

#include "Base.hh"
#include "BattleField.hh"

//Character Class
class Character_Base
{
private:
	//Check if the ground allow the character presence
	std::vector<int> Check_background_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);
	
	//Check if the environment allow the character presence
	std::vector<int> Check_environment_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector);
	
protected:
	//The X and Y offsets of the character
	int X, Y;
	
	//The velocity of the character
	int xVel, yVel;

	//Tile & Clip
	RGBSurface Characters_Tile;
	Rect Characters_SpriteRect;

	//Battlefield rules (pure virtuals)
	virtual int Get_BG_vs_CH_Rules(int bgType) = 0;
	virtual int Get_Env_vs_CH_Rules(int envType) = 0;

	
public:
	/****Accessor****/
	void Set_X(int new_X)
    {
        X = new_X;
    }
	int Get_X() const
    {
        return X;
    }

	void Set_Y(int new_Y)
    {
        Y = new_Y;
    }
	int Get_Y() const
    {
        return Y;
    }
	
	void Set_xVel(int new_xVel)
    {
        xVel = new_xVel;
    }
	int Get_xVel() const
    {
        return xVel;
    }

	void Set_yVel(int new_yVel)
    {
        yVel = new_yVel;
    }
    int Get_yVel() const
    {
        return yVel;
    }


	//Check if the battlefield allow the character presence
	bool Check_battlefield_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);
};

#endif
