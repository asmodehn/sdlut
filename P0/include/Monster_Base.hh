#ifndef Monster_Base_HH
#define Monster_Base_HH

#include "Base.hh"
#include "BattleField.hh"

//The Monster
class Monster_Base
{
    protected:
		//The X and Y offsets of the Monster
		int x, y;

		//Monster Tile
		RGBSurface _monsters_list;

		//Monster Tile Clip
		Rect _monster[1];

		//The velocity of the Monster
		int xVel, yVel;

		//Monster type
		Monsters_Type Monster_ID;

		//The collision boxes of the Monster
		Rect collision_box;

		//Bool that will indicate if the monster is alive or dead
		bool Alive_Status;


		/****Methods****/

		//Check if the background allow the monster presence
		virtual std::vector<int> check_background_allow_monster(Rect Collision_Box, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);
		//Check if the environment allow the monster presence
		virtual std::vector<int> check_environment_allow_monster(Rect Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector);
		
	public:
		/****Accessor****/

		void Set_X(int new_X)
        {
            x = new_X;
        }
		int Get_X() const
        {
            return x;
        }

		void Set_Y(int new_Y)
        {
            y = new_Y;
        }
		int Get_Y() const
        {
            return y;
        }

		void Set_Collision_Box(Rect new_Collision_Box)
        {
            collision_box = new_Collision_Box;
        }
		Rect Get_Collision_Box() const
        {
            return collision_box;
        }

		void Set_Alive_Status(bool new_Alive_Status)
        {
            Alive_Status = new_Alive_Status;
        }
		bool Get_Alive_Status() const
        {
            return Alive_Status;
		}

		void Set_Monster_ID(Monsters_Type new_Monster_ID)
        {
            Monster_ID = new_Monster_ID;
        }
		Monsters_Type Get_Monster_ID() const
        {
            return Monster_ID;
		}

		/****Methods****/

		//Default construtor
		Monster_Base();

		//Constructor that initialize the variables
		Monster_Base(int X, int Y);

		//Copy construtor
		Monster_Base(const Monster_Base& ToCopy);

		//Destructor
		~Monster_Base();

		//Move the Monster and check collision with the collision box of the character in parameter, the background and other monsters
		bool move(Rect CharacterCollisionbox, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector, std::vector< std::vector<Monster_Base*> *> Global_Monster_Vector);
	    
		//Check if the battlefield allow the monster presence
		virtual bool check_battlefield_allow_monster(Rect Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);

		//Check if the battlefield cutting allow monster presence
		bool check_cutting_allow_monster(int x, int y, std::vector<BattleField_Zone*> BattleField_Cutting_Vector);

		//Shows the Monster movement on the screen
		bool move_animation(Rect Camera, VideoSurface& Screen);
};

#endif

