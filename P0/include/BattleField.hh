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
		Rect BattleField_Clip;
		
	public:
		BattleField_Sprite();
		BattleField_Sprite(int x, int y, int ground_type, Rect battlefield_clip);
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

		void Set_BattleField_Clip(Rect new_BattleField_Clip)
        {
            BattleField_Clip = new_BattleField_Clip;
        }
        Rect Get_BattleField_Clip() const
        {
            return BattleField_Clip;
        }
};

//BattleField class which is designed to manage everything relative to the batllefield
class BattleField
{
	private:
		//Default sprite clip
		Rect BattleField_Clip;
		//Tilesets surface
		RGBSurface BattleField_Tileset_Empty, BattleField_Tileset_Grass, BattleField_Tileset_Sands, BattleField_Tileset_Rivers, BattleField_Tileset_Trees;

		//The vector that will contains the battlefield sprites corresponding to the battlefield map
		std::vector<BattleField_Sprite*> myBattleField_Sprite_Vector;

	public:
		BattleField();
		~BattleField();


		/****Methods****/

		//Construct the battlefield vector
		std::vector<BattleField_Sprite*> BattleField_Vector();

		//Generate the background of the screen
		bool Render(std::vector<BattleField_Sprite*> BattleField_Sprite_Vector, Rect Camera, VideoSurface & Screen);


};

#endif
