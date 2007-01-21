#ifndef Monster_Base_HH
#define Monster_Base_HH

#include "Character_Base.hh"

//The Monster
class Monster_Base : public Character_Base
{
    protected:
		//Monster Tile Clip
		Rect _monster[1];

		//Monster type
		Monsters_Type Monster_ID;

		/****Methods****/

		//Check if the background allow the monster presence
		//virtual std::vector<int> check_background_allow_monster(Rect Collision_Box, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);
		//Check if the environment allow the monster presence
		//virtual std::vector<int> check_environment_allow_monster(Rect Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector);
		
		//Battlefield rules
		virtual int Get_BG_vs_CH_Rules(int bgType);
		/* virtual */ int Get_Env_vs_CH_Rules(int envType);

	public:
		inline void Set_Monster_ID(Monsters_Type new_Monster_ID)
        {
            Monster_ID = new_Monster_ID;
        }
		inline Monsters_Type Get_Monster_ID() const
        {
            return Monster_ID;
		}

		/****Methods****/

		//Default construtor
		Monster_Base();

		//Constructor that initialize the variables
		Monster_Base(int x, int y);

		//Copy construtor
		Monster_Base(const Monster_Base& ToCopy);

		//Move the Monster and check collision with everything
		bool move(std::vector< std::vector<Character_Base*> *>* Global_Player_Vector, std::vector<BattleField_Sprite*>* Environment_Sprite_Vector, std::vector<BattleField_Sprite*> *BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector);
	    
		//Check if the battlefield allow the monster presence
		//virtual bool check_battlefield_allow_monster(Rect Collision_Box, std::vector<BattleField_Sprite*> Environment_Sprite_Vector, std::vector<BattleField_Sprite*> BackGround_Sprite_Vector);

		//Check if the battlefield cutting allow monster presence
		bool check_cutting_allow_monster(int x, int y, std::vector<BattleField_Zone*>* BattleField_Cutting_Vector);

		//Shows the Monster movement on the screen
		//bool move_animation(Rect Camera, VideoSurface& Screen);
};

#endif

