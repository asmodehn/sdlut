#ifndef Character_Base_HH
#define Character_Base_HH

//#include "Base.hh"
#include "BattleField.hh"

//Character Class
class Character_Base
{
private:
	//Check if the ground allow the character presence
	std::vector<int>* Check_background_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector);
	
	//Check if the environment allow the character presence
	std::vector<int>* Check_environment_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector);
	
protected:
	//The X and Y offsets of the character
	int X, Y;
	
	//The velocity of the character
	int xVel, yVel;

	//Sprite Characteristics
	int Sprite_Width, Sprite_Height;

	//Characteristics of the character
	int BASE_LIFE, Current_Life;
	int BASE_ARMOR, Current_Armor;

	//Tile & Clip
	RGBSurface Characters_Tile;
	Rect Characters_SpriteRect;

	//The collision boxes of the Monster
	Rect Collision_Box;

	//Bool that will indicate if the character is alive or dead
	bool Alive_Status;

	//The zone where the character is alloed to go (default: whole level)
	Rect Allowed_Area;

	//Battlefield rules (pure virtuals)
	virtual int Get_BG_vs_CH_Rules(int bgType) = 0;
	virtual int Get_Env_vs_CH_Rules(int envType) = 0;

	
public:
	/****Accessor****/
	inline void Set_X(int new_X)
    {
        X = new_X;
    }
	inline int Get_X() const
    {
        return X;
    }

	inline void Set_Y(int new_Y)
    {
        Y = new_Y;
    }
	inline int Get_Y() const
    {
        return Y;
    }
	
	inline void Set_xVel(int new_xVel)
    {
        xVel = new_xVel;
    }
	inline int Get_xVel() const
    {
        return xVel;
    }

	inline void Set_yVel(int new_yVel)
    {
        yVel = new_yVel;
    }
    inline int Get_yVel() const
    {
        return yVel;
    }

	inline void Set_Collision_Box(Rect new_Collision_Box)
    {
        Collision_Box = new_Collision_Box;
    }
	inline Rect Get_Collision_Box() const
    {
        return Collision_Box;
    }

	inline void Set_Alive_Status(bool new_Alive_Status)
    {
        Alive_Status = new_Alive_Status;
    }
	inline bool Get_Alive_Status() const
    {
        return Alive_Status;
	}
	inline void Set_Current_Life(int new_Current_Life)
	{
		Current_Life = new_Current_Life;
	}
	inline int Get_Current_Life()
	{
		return Current_Life;
	}
	inline void Set_Current_Armor(int new_Current_Armor)
	{
		Current_Armor = new_Current_Armor;
	}
	inline int Get_Current_Armor()
	{
		return Current_Armor;
	}

	//Init
	Character_Base();
	virtual ~Character_Base();

	//Check if the battlefield allow the character presence
	bool Check_battlefield_allow_character(Rect Collision_Box, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector);

	//Check collision with everything possible
	bool Check_Collisions(std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector);

	//Move character (pure virtual)
	virtual bool move(unsigned long deltaticks, std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector) = 0;


	//Show Character on the screen
	bool Show(Rect Camera, VideoSurface& Screen);

};

#endif
