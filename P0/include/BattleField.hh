#ifndef BattleField_HH
#define BattleField_HH

//#include "BattleField_Sprite.hh"
#include "Base.hh"

//Battlefield Sprites will be referenced inside a vector which will be used to generate the battlefield (background or environment)
class BattleField_Sprite
{
	private:
		int X,Y;
		int BattleField_Type;
		Rect BattleField_Clip;
		
	public:
		BattleField_Sprite();
		BattleField_Sprite(int x, int y, int battlefield_type, Rect battlefield_clip);
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

		void Set_BattleField_Type(int new_BattleField_Type)
        {
            BattleField_Type = new_BattleField_Type;
        }
        int Get_BattleField_Type() const
        {
            return BattleField_Type;
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

//BackGround class which is designed to manage everything relative to the background layer of the battlefield
class BackGround
{
	private:
		//Default sprite clip
		Rect BackGround_Clip;
		//Tilesets surface
		RGBSurface BackGround_Tileset_Empty, BackGround_Tileset_Grass, BackGround_Tileset_Sands, BackGround_Tileset_Rivers;

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

//Environment class which is designed to manage everything relative to the environment layer of the battlefield
class Environment
{
	private:
		//Default sprite clip
		Rect Environment_Clip;
		//Tilesets surface
		RGBSurface Environment_Tileset_Trees;

		//The vector that will contains the BackGround sprites corresponding to the BackGround map
		std::vector<BattleField_Sprite*> myEnvironment_Sprite_Vector;

	public:
		Environment();
		~Environment();


		/****Methods****/

		//Construct the BackGround vector
		std::vector<BattleField_Sprite*> Environment_Vector();

		//Generate the background of the screen
		bool Render(std::vector<BattleField_Sprite*> Environment_Sprite_Vector, Rect Camera, VideoSurface & Screen);


};

#endif
