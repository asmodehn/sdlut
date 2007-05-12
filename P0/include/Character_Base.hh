#ifndef Character_Base_HH
#define Character_Base_HH

//#include "Base.hh"
#include "BattleField.hh"
#include "Animations_Center.hh"

//Character Class
class Character_Base
{
private:
	
protected:

/****Characteristics****/

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

	//Characters type
	Character_Types Characters_ID;

	//Bool that will indicate if the character is alive or dead
	bool Alive_Status;

/****Movements****/

	//Moving status define if the player is moving or just changing direction or staying at the same place
	bool Moving_Status;
	//moving direction
	int Move_Direction;
	//The zone where the character is alloew to go (default: whole level)
	Rect Allowed_Area;
	//The collision boxes of the character
	Rect Collision_Box;

/****Attack****/

	//The attack collision box of the player
	Rect attack_CB;

	//Attack Styles
	bool Unarmed_Style_Available, Melee_Style_Available, Distant_Style_Available, Throwing_Style_Available, Magic_Style_Available;

	//Attack variables
	bool attack_status; //Attack key pressed yes or no 
	int attack_style; //Manage the style of attack (0: unarmed, 1: melee attack, 2: distant attack, 3&+: TODO(future) )
	int attack_successfull; //get the monster ID that has been hitted to print the good attack msg
		//initial info of the attack (-1 means no attack)
	int attack_initial_x;
	int attack_initial_y;
	int attack_direction;

/****Animations****/
	//Clip (never deleted coz are only there to link with the real animation tile rect)
	Rect Current_Tile_Rect;
	
	//Tileset (never deleted coz are only there to link with the real animation tileset)
	RGBSurface* Characters_Current_Tileset;

	RGBSurface* Characters_Current_Unarmed_Tileset;
	RGBSurface* Characters_Current_Melee_Tileset;
	RGBSurface* Characters_Current_Distant_Tileset;
	//change that^

	//The center of animations
	Character_Animations_Center *Default_Animations_Center;

	//current animation current frame
	int frame;

	//Collision Box Modifier between sprite dims & "real" dims
	int CB_X_Modifier;
	int CB_Y_Modifier;
	int CB_Width;
	int CB_Height;


/****Methods***/
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
	//Define if the player has push the attack Key
	inline void Set_Attack_Status(bool new_attack_status)
    {
        attack_status=new_attack_status;
    }
	inline bool Get_Attack_Status() const
    {
        return attack_status;
    }
	inline void Set_Attack_Style(int new_attack_style)
    {
        attack_style = new_attack_style;
    }
    inline int Get_Attack_Style() const
    {
        return attack_style;
    }
	inline void Set_Attack_CB(Rect new_Attack_CB)
	{
		attack_CB = new_Attack_CB;
	}
	inline Rect Get_Attack_CB() const
	{
		return attack_CB;
	}

	inline void Set_Attack_Successfull(int new_Attack_Successfull)
    {
        attack_successfull = new_Attack_Successfull;
    }
    inline int Get_Attack_Successfull() const
    {
        return attack_successfull;
    }

	inline void Set_Attack_Initial_X(int new_attack_initial_x)
    {
        attack_initial_x = new_attack_initial_x;
    }
    inline int Get_Attack_Initial_X() const
    {
        return attack_initial_x;
    }
	inline void Set_Attack_Initial_Y(int new_attack_initial_y)
    {
        attack_initial_y = new_attack_initial_y;
    }
    inline int Get_Attack_Initial_Y() const
    {
        return attack_initial_y;
    }
	inline void Set_Attack_Direction(int new_attack_direction)
    {
        attack_direction = new_attack_direction;
    }
    inline int Get_Attack_Direction() const
    {
        return attack_direction;
    }
	
	inline void Set_Moving_Status(bool new_moving_status)
    {
        Moving_Status = new_moving_status;
    }
    inline bool Get_Moving_Status() const
    {
        return Moving_Status;
    }
	inline void Set_Characters_ID(Character_Types new_Characters_ID)
    {
        Characters_ID = new_Characters_ID;
    }
	inline Character_Types Get_Characters_ID() const
    {
        return Characters_ID;
	}
	inline Character_Animations_Center *Get_Default_Animations_Center() const
    {
        return Default_Animations_Center;
	}	

	//Init
	Character_Base();
	virtual ~Character_Base();

	/****Methods****/
//Movement
	//Move character (pure virtual)
	virtual bool Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector) = 0;
	//move the character_base's collision box to a place its allowed to be when moving
	bool Manage_Collisions( std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector, bool Handle_Collisions = 0);
	//check the direction where the character is turn to
	bool Assign_Direction_Sprite();
	//define character sprite which appear on the screen during walk
	bool Set_Walk_Animation_Sprite();
	//define character sprite which appear on the screen during run
	bool Set_Run_Animation_Sprite();
//Attack
	//Manage the character attack stuffs
	void Attack();
	//Check if collision between the attack and one of the monsters on the battlefield regarding the number of movements that the attack collision is currently doing and character infos
	int Attack_Check_Status(int ch2attack_distance, int inflicted_damage, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector);
	//Set Character Sprite Which change when attack occured(callback)
	bool Set_Attack_Animation_Sprite(std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector);
	//Manage when a character decided to change his attack style: check if style present, update characteristics, etc
	bool Change_Attack_Style();
//Characteristics
	//Calculate the current life depending on damage, malus, etc and damage made by the opponent
	bool Calculate_Real_Life(int received_damage = 0);
//Render
	//Show Character on the screen
	bool Show(const Rect& Camera, VideoSurface& Screen);

};

#endif
