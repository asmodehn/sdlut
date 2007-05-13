#ifndef Monster_Base_HH
#define Monster_Base_HH

#include "Character_Base.hh"

//The Monster
class Monster_Base : public Character_Base
{
    protected:
		//Monster Tile Clip
		Rect _monster_clip;

		//Life bar infos
		RGBSurface *Life_Bar_Tile;
		Rect empty_life_bar_rect;
		Rect real_life_bar_rect;

		/****Methods****/

		//Battlefield rules
		virtual int Get_BG_vs_CH_Rules(const int& bgType);
		/* virtual */ int Get_Env_vs_CH_Rules(const int& envType);

	public:
		/****Methods****/

		//Default construtor
		Monster_Base();

		//Constructor that initialize the variables
		//Monster_Base(int& x, int& y);

		//Copy construtor
		Monster_Base(const Monster_Base& ToCopy);

		//Destructor
		virtual ~Monster_Base();

		//Intialize Monster: get all data from external files, assign surface, boxs, ...
		static void Initialize(const string &Description_Filename,
						int &Ch_Vel, int &BASE_LIFE, int &BASE_ARMOR, int &BASE_INFLICTED_DAMAGE, int &Sprite_Width, int &Sprite_Height, Character_Types &Characters_ID,
						Rect &Allowed_Area,
						int &CB_X_Modifier, int &CB_Y_Modifier, int &CB_Width, int &CB_Height,
						Character_Animations_Center* &Default_Animations_Center,
						RGBSurface* &Life_Bar_Tile, Rect &empty_life_bar_rect, Rect &real_life_bar_rect
						);

		//Move the Monster and check collision with everything
		bool Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector);
	    
		//Check if the battlefield cutting allow monster presence
		bool Check_Cutting_Allow_Monster(std::vector<BattleField_Zone*>* &BattleField_Cutting_Vector);

		//Shows the life bar of the monster depending of it's current life
		bool Show_Life_Bar(const Rect& Camera, VideoSurface& Screen);
};

#endif

