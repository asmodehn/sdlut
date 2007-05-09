#ifndef Character_Base_HH
#define Character_Base_HH

//#include "Base.hh"
#include "BattleField.hh"
#include "Animations.hh"

//Character Class
class Character_Base
{
private:
	
protected:
	//The X and Y offsets of the character
	int X, Y;
	
	//The velocity of the character
	int Ch_Vel, xVel, yVel;

	//Sprite Characteristics
	int Sprite_Width, Sprite_Height;
	string Sprite_Filename; //designed to disapear

	//Characteristics of the character
	int BASE_LIFE, Real_Life;
	int BASE_ARMOR, Real_Armor;
	int BASE_INFLICTED_DAMAGE, Real_Inflicted_Damage;
	int BASE_RANGE, Real_Range;

	//Attack Styles
	bool Melee_Style_Available, Distant_Style_Available, Throwing_Style_Available, Magic_Style_Available;

	//Clip (never deleted coz are only there to link with the real animation tile rect)
	Rect Current_Tile_Rect;
	
	//Tileset (never deleted coz are only there to link with the real animation tileset)
	RGBSurface* Characters_Current_Tileset;
	RGBSurface* Characters_Current_Unarmed_Tileset;
	RGBSurface* Characters_Current_Melee_Tileset;
	RGBSurface* Characters_Current_Distant_Tileset;

	//Animations (designed to be deleted where it's used not in character_base's destructor)
	Character_Animation *Attack_Animation, *Death_Animation, *Run_Animation, *Walk_Animation, *Hit_Animation, *Stop_Animation, *Pause_Animation;

	//The collision boxes of the character
	Rect Collision_Box;
	int CB_X_Modifier;
	int CB_Y_Modifier;
	int CB_Width;
	int CB_Height;

	//Bool that will indicate if the character is alive or dead
	bool Alive_Status;

	//The zone where the character is alloed to go (default: whole level)
	Rect Allowed_Area;

	//moving direction
	int Move_Status;

	//Parse the xml file (called by the constructor)
	void Parse_Description_File(const string &Description_Filename);

	//Battlefield rules (pure virtuals)
	virtual int Get_BG_vs_CH_Rules(const int& bgType) = 0;
	virtual int Get_Env_vs_CH_Rules(const int& envType) = 0;
	
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

	inline void Set_Sprite_Width(int new_Sprite_Width)
    {
        Sprite_Width = new_Sprite_Width;
    }
    inline int Get_Sprite_Width() const
    {
        return Sprite_Width;
    }
	inline void Set_Sprite_Height(int new_Sprite_Height)
    {
        Sprite_Height = new_Sprite_Height;
    }
    inline int Get_Sprite_Height() const
    {
        return Sprite_Height;
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
	inline void Set_Real_Life(int new_Real_Life)
	{
		Real_Life = new_Real_Life;
	}
	inline int Get_Real_Life()
	{
		return Real_Life;
	}
	inline void Set_Real_Armor(int new_Real_Armor)
	{
		Real_Armor = new_Real_Armor;
	}
	inline int Get_Real_Armor()
	{
		return Real_Armor;
	}
	inline void Set_Real_Inflicted_Damage(int new_Real_Inflicted_Damage)
	{
		Real_Inflicted_Damage = new_Real_Inflicted_Damage;
	}
	inline int Get_Real_Inflicted_Damage()
	{
		return Real_Inflicted_Damage;
	}
	inline void Set_Real_Range(int new_Real_Range)
	{
		Real_Range = new_Real_Range;
	}
	inline int Get_Real_Range()
	{
		return Real_Range;
	}
	inline void Set_Allowed_Area(Rect new_Allowed_Area)
	{
		Allowed_Area = new_Allowed_Area;
	}
	inline Rect Get_Allowed_Area()
	{
		return Allowed_Area;
	}


	//Init
	Character_Base();
	virtual ~Character_Base();

	//move the character_base's collision box to a place its allowed to be when moving
	bool Manage_Collisions( std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector, bool Handle_Collisions = 0);
	
	//Move character (pure virtual)
	virtual bool Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector) = 0;

	//Show Character on the screen
	bool Show(const Rect& Camera, VideoSurface& Screen);

};

#endif
