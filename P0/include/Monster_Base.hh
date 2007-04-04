#ifndef Monster_Base_HH
#define Monster_Base_HH

#include "Character_Base.hh"

//The Monster
class Monster_Base : public Character_Base
{
    protected:
		//Monster Tile Clip
		Rect _monster_clip;

		//Monster type
		Monsters_Type Monster_ID;

		//Life bar infos
		RGBSurface *Life_Bar_Tile;
		Rect empty_life_bar_rect;
		Rect real_life_bar_rect;

		/****Methods****/

		//Battlefield rules
		virtual int Get_BG_vs_CH_Rules(const int& bgType);
		/* virtual */ int Get_Env_vs_CH_Rules(const int& envType);

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
		Monster_Base(int& x, int& y);

		//Copy construtor
		Monster_Base(const Monster_Base& ToCopy);

		//Destructor
		virtual ~Monster_Base();

		//Move the Monster and check collision with everything
		bool Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector);
	    
		//Check if the battlefield cutting allow monster presence
		bool Check_Cutting_Allow_Monster(std::vector<BattleField_Zone*>* &BattleField_Cutting_Vector);

		//Calculate the current life depending on damage, malus, etc and damage made by the opponent
		bool Calculate_Real_Life(int received_damage = 0);

		//Shows the life bar of the monster depending of it's current life
		bool Show_Life_Bar(const Rect& Camera, VideoSurface& Screen);
};

#endif

