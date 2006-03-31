#ifndef BattleField_HH
#define BattleField_HH

//#include "BattleField_Sprite.hh"
#include "Base.hh"

//Battlefield Sprites will be referenced inside a vector which will be used to generate the battlefield
class BattleField_Sprite
{
	private:
		int X,Y;
		int Ground_Type;
		Rect BG_Clip;
		
	public:
		BattleField_Sprite();
		BattleField_Sprite(int x, int y, int ground_type, Rect bg_clip);
		~BattleField_Sprite();

		/****Wrapper****/
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

		void Set_Ground_Type(int new_Ground_Type)
        {
            Ground_Type = new_Ground_Type;
        }
        int Get_Ground_Type() const
        {
            return Ground_Type;
        }

		void Set_BG_Clip(int new_BG_Clip)
        {
            BG_Clip = new_BG_Clip;
        }
        Rect Get_BG_Clip() const
        {
            return BG_Clip;
        }
};

//BattleField class which is designed to manage everything relative to the batllefield
class BattleField
{
	private:
		RGBSurface Background;
		Rect BattleField_Clip;
		Rect BattleField_Empty_Clip, BattleField_Grass_Clip, BattleField_Sand_Clip, BattleField_River_Clip;

		//The vector that will contains the battlefield sprites corresponding to the battlefield map
		std::vector<BattleField_Sprite*> myBattleField_Sprite_Vector;

	public:
		BattleField();
		~BattleField();

		/****Methods****/
		std::vector<BattleField_Sprite*> BattleField_Vector();
		//std::vector<BattleField_Sprite*> BattleField::BattleField_Camera_Vector(std::vector<BattleField_Sprite*> BattleField_Sprite_Vector, Rect Camera);
		bool Render(std::vector<BattleField_Sprite*> BattleField_Sprite_Vector, Rect Camera, VideoSurface & Screen);


};

#endif
