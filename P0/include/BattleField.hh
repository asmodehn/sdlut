#ifndef BattleField_HH
#define BattleField_HH

//#include "BattleField_Sprite.hh"
#include "Base.hh"

//Battlefield Sprites will be referenced inside a vector which will be used to generate the battlefield (background or environement)
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

//BackGround class which is designed to manage everything relative to the batllefield
class BackGround
{
	private:
		//Default sprite clip
		Rect BackGround_Clip;
		//Tilesets surface
		RGBSurface BackGround_Tileset_Empty, BackGround_Tileset_Grass, BackGround_Tileset_Sands, BackGround_Tileset_Rivers, BackGround_Tileset_Trees;

		//The vector that will contains the BackGround sprites corresponding to the BackGround map
		std::vector<BattleField_Sprite*> myBackGround_Sprite_Vector;

	public:
		BackGround();
		~BackGround();


		/****Methods****/

		//Construct the BackGround vector
		std::vector<BattleField_Sprite*> BackGround_Vector();

		//Generate the background of the screen
		bool Render(std::vector<BattleField_Sprite*> BackGround_Sprite_Vector, Rect Camera, VideoSurface & Screen);


};

#endif
