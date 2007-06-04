#ifndef Character_Base_HH
#define Character_Base_HH

//#include "Base.hh"
#include "BattleField.hh"
#include "Animations_Center.hh"
#include "AI.hh"
#include "PathFinder.hh"

//Character Class
class Character_Base
{
	friend class Character_Animations_Center;
	friend class PathFinder;

private:
	
protected:

/****Characteristics****/

	//The X and Y offsets of the character
	int X, Y;
	
	//The velocity of the character
	int Ch_Vel, xVel, yVel;

	//Sprite Characteristics
	int Sprite_Width, Sprite_Height;

	//Characteristics of the character
	int BASE_LIFE, Real_Life;
	int BASE_ARMOR, Real_Armor;
	int BASE_INFLICTED_DAMAGE, Real_Inflicted_Damage;
	int BASE_RANGE, Real_Range;

	//Characters type
	Character_Types Characters_ID;

/****Movements****/

	//moving direction
	int Move_Direction;
	//The zone where the character is alloew to go (default: whole level)
	Rect Allowed_Area;
	//The collision boxes of the character
	Rect Collision_Box;
	//the path the character is following
	list<Point> Path;

/****Attack****/

	//The attack collision box of the player
	Rect attack_CB;

	//Attack Styles
	bool Unarmed_Style_Available, Melee_Style_Available, Distant_Style_Available, Throwing_Style_Available, Magic_Style_Available;

	//Attack variables
	int attack_successfull; //get the monster ID that has been hitted to print the good attack msg
		//initial info of the attack (-1 means no attack)
	int attack_initial_x;
	int attack_initial_y;
	int attack_direction;

/****Animations****/
	//Clip
	Rect Current_Tile_Rect;
	//Tileset (never deleted coz only a link)
	RGBSurface* Current_Tileset;
	
	//The center of animations
	Character_Animations_Center *Current_Animations_Center;
	Character_Animations_Center *Unarmed_Animations_Center;
	Character_Animations_Center *Melee_Animations_Center;
	Character_Animations_Center *Distant_Animations_Center;

	//Collision Box Modifier between sprite dims & "real" dims
	int CB_X_Modifier;
	int CB_Y_Modifier;
	int CB_Width;
	int CB_Height;

/****Flags****/
	//Moving status define if the player is 2:moving, 1:moving animation in progress, 0:animation finished, -1: stopped, -2: paused
	int Moving_Status;
	//indicate if the character is 1:alive, 0:dying, -1:dying animation in progress, -2:dead
	int Alive_Status;
	//Attack key pressed yes or no 
	bool attack_status;
	//Manage the style of attack (0: unarmed, 1: melee attack, 2: distant attack, 3&+: TODO(future) )
	int attack_style;
	//indicate if the character has been 2:hitted; 1:hitted animation in progress; 0:not hitted
	int Hitted_Status;

/****Methods***/
	//Battlefield rules (pure virtuals)
	virtual int Get_BG_vs_CH_Rules(const int& bgType) = 0;
	virtual int Get_Env_vs_CH_Rules(const int& envType) = 0;
	
	//Reset everything to normal mode when the attack is finished
	virtual void Attack_Reset();

	//Calculate the current life depending on damage, malus, etc and damage made by the opponent
	bool Calculate_Real_Life(int received_damage = 0);
	
public:
	/****Accessor****/
	inline void Set_X(int new_X)
    {
        X = new_X;
    }
	inline int& Get_X()
    {
        return X;
    }

	inline void Set_Y(int new_Y)
    {
        Y = new_Y;
    }
	inline int& Get_Y()
    {
        return Y;
    }
	
	inline void Set_xVel(int new_xVel)
    {
        xVel = new_xVel;
    }
	inline int& Get_xVel()
    {
        return xVel;
    }

	inline void Set_yVel(int new_yVel)
    {
        yVel = new_yVel;
    }
    inline int& Get_yVel()
    {
        return yVel;
    }

	inline void Set_Sprite_Width(int new_Sprite_Width)
    {
        Sprite_Width = new_Sprite_Width;
    }
    inline int& Get_Sprite_Width()
    {
        return Sprite_Width;
    }
	inline void Set_Sprite_Height(int new_Sprite_Height)
    {
        Sprite_Height = new_Sprite_Height;
    }
    inline int& Get_Sprite_Height() 
    {
        return Sprite_Height;
    }
	

	inline void Set_Collision_Box(Rect new_Collision_Box)
    {
        Collision_Box = new_Collision_Box;
    }
	inline Rect& Get_Collision_Box()
    {
        return Collision_Box;
    }

	inline void Set_Alive_Status(int new_Alive_Status)
    {
        Alive_Status = new_Alive_Status;
    }
	inline int& Get_Alive_Status()
    {
        return Alive_Status;
	}
	inline void Set_Real_Life(int new_Real_Life)
	{
		Real_Life = new_Real_Life;
	}
	inline int& Get_Real_Life()
	{
		return Real_Life;
	}
	inline void Set_Real_Armor(int new_Real_Armor)
	{
		Real_Armor = new_Real_Armor;
	}
	inline int& Get_Real_Armor()
	{
		return Real_Armor;
	}
	inline void Set_Real_Inflicted_Damage(int new_Real_Inflicted_Damage)
	{
		Real_Inflicted_Damage = new_Real_Inflicted_Damage;
	}
	inline int& Get_Real_Inflicted_Damage()
	{
		return Real_Inflicted_Damage;
	}
	inline void Set_Real_Range(int new_Real_Range)
	{
		Real_Range = new_Real_Range;
	}
	inline int& Get_Real_Range()
	{
		return Real_Range;
	}
	inline void Set_Allowed_Area(Rect new_Allowed_Area)
	{
		Allowed_Area = new_Allowed_Area;
	}
	inline Rect& Get_Allowed_Area()
	{
		return Allowed_Area;
	}
	//Define if the player has push the attack Key
	inline void Set_Attack_Status(bool new_attack_status)
    {
		//cout << "Attack status set to: " << new_attack_status << endl;
        attack_status=new_attack_status;
    }
	inline bool& Get_Attack_Status()
    {
        return attack_status;
    }
	inline void Set_Attack_Style(int new_attack_style)
    {
        attack_style = new_attack_style;
    }
    inline int& Get_Attack_Style()
    {
        return attack_style;
    }
	inline void Set_Attack_CB(Rect new_Attack_CB)
	{
		attack_CB = new_Attack_CB;
	}
	inline Rect& Get_Attack_CB()
	{
		return attack_CB;
	}

	inline void Set_Attack_Successfull(int new_Attack_Successfull)
    {
        attack_successfull = new_Attack_Successfull;
    }
    inline int& Get_Attack_Successfull()
    {
        return attack_successfull;
    }

	inline void Set_Attack_Initial_X(int new_attack_initial_x)
    {
        attack_initial_x = new_attack_initial_x;
    }
    inline int& Get_Attack_Initial_X()
    {
        return attack_initial_x;
    }
	inline void Set_Attack_Initial_Y(int new_attack_initial_y)
    {
        attack_initial_y = new_attack_initial_y;
    }
    inline int& Get_Attack_Initial_Y()
    {
        return attack_initial_y;
    }
	inline void Set_Attack_Direction(int new_attack_direction)
    {
        attack_direction = new_attack_direction;
    }
    inline int& Get_Attack_Direction()
    {
        return attack_direction;
    }

	inline int& Get_Move_Direction()
    {
        return Move_Direction;
    }	
	inline void Set_Moving_Status(int new_moving_status)
    {
        Moving_Status = new_moving_status;
    }
    inline int& Get_Moving_Status()
    {
        return Moving_Status;
    }
	inline void Set_Characters_ID(Character_Types new_Characters_ID)
    {
        Characters_ID = new_Characters_ID;
    }
	inline Character_Types& Get_Characters_ID()
    {
        return Characters_ID;
	}
	inline void Set_Hitted_Status(int newHitted_Status)
    {
        Hitted_Status = newHitted_Status;
    }
    inline int& Get_Hitted_Status()
    {
        return Hitted_Status;
    }

	inline Character_Animations_Center*& Get_Current_Animations_Center()
    {
        return Current_Animations_Center;
	}

	inline RGBSurface*& Get_Current_Tileset()
	{
		return Current_Tileset;
	}
	inline void Set_Current_Tileset(RGBSurface* newTileset)
	{
		Current_Tileset = newTileset;
	}

	inline Rect& Get_Current_Tile_Rect()
	{
		return Current_Tile_Rect;
	}
	inline void Set_Current_Tile_Rect(Rect newTile_Rect)
	{
		Current_Tile_Rect = newTile_Rect;
	}

	inline list<Point>& Get_Path()
	{
		return Path;
	}
	inline void Set_Path(list<Point> newPath)
	{
		Path = newPath;
	}
	inline void Clear_Path()
	{
		Path.clear();
	}

	//Init
	Character_Base();
	virtual ~Character_Base();

	/****Methods****/
//Movement
	//Move character (should be reimplemented by the player in order to not use AI)
	virtual void Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector);
	//Handle collisions between the ch's collision box & the battlefield & other characters
	//Handle_Collisions Mode OFF: tell if the CB is allowed to be here
	//Handle_Collisions Mode ON: Check if CB is allowed to be here, if not moved it to the best place near it's current position regarding of interactions rules
	bool Manage_Collisions( std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector, bool Handle_Collisions = 0);
	//check the direction where the character is turn to
	bool Find_Direction_From_Velocities();
	//define character sprite which appear on the screen during walk
	bool Set_Walk_Animation_Sprite();
	//define character sprite which appear on the screen during run
	bool Set_Run_Animation_Sprite();
//Attack
	//Manage the character attack stuffs
	void Attack();
	//Set Character Sprite Which change when attack occured(callback)
	//
	//todo: perhaps move this method in private & called it directly from the attack() method
	//
	void Attack_Set_Animation_Sprite(std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector);
	//Check if collision between the attack and one of the monsters on the battlefield regarding the number of movements that the attack collision is currently doing and character infos
	//
	//TODO change below to private whe the arrow management wont be managed by daemon else, stay public
	//
	int Attack_Check_Status(int ch2attack_distance, int inflicted_damage, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector);
	//Manage when a character decided to change his attack style: check if style present, update characteristics, etc
	bool Change_Attack_Style();

//Render
	//Show Character on the screen
	bool Show(const Rect& Camera, VideoSurface& Screen);

};

#endif
