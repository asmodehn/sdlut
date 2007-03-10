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

		inline void Set_BattleField_Type(int new_BattleField_Type)
        {
            BattleField_Type = new_BattleField_Type;
        }
        inline int Get_BattleField_Type() const
        {
            return BattleField_Type;
        }

		inline void Set_BattleField_Clip(Rect new_BattleField_Clip)
        {
            BattleField_Clip = new_BattleField_Clip;
        }
        inline Rect Get_BattleField_Clip() const
        {
            return BattleField_Clip;
        }
};
//Battlefield zone is a class that defined an area with the allowed monster to be born
class BattleField_Zone
{
	private:
		Rect Area;
		std::vector<int>* Allowed_Monsters;

	public:
		~BattleField_Zone();
		BattleField_Zone();
		BattleField_Zone(int x, int y, int w, int h, int num, ...);

		/****Accessor****/

		inline void Set_Area(Rect new_Area)
        {
            Area = new_Area;
        }
        inline Rect Get_Area() const
        {
            return Area;
        }
		
		inline void Set_Allowed_Monsters(std::vector<int>* new_Allowed_Monsters)
        {
            Allowed_Monsters = new_Allowed_Monsters;
        }
        inline std::vector<int>* Get_Allowed_Monsters() const
        {
            return Allowed_Monsters;
        }


		/****Methods****/

		//Fill the Allowed_Monsters_Generation vector directly
		static std::vector<BattleField_Zone*>* Fill_Vector();

};

//BackGround class which is designed to manage everything relative to the background layer of the battlefield
class BackGround // : public BattleField_Sprite
{
	private:
		//Default sprite clip
		Rect BackGround_Clip;
		//Tilesets surface
		RGBSurface BackGround_Tileset_Grass, BackGround_Tileset_Sands, BackGround_Tileset_Rivers;
		RGBSurface BackGround_Tileset_Lakes, BackGround_Tileset_Bridges;

		//The vector that will contains the BackGround sprites corresponding to the BackGround map
		std::vector<BattleField_Sprite*>* myBackGround_Sprite_Vector;

	public:
		BackGround();
		~BackGround();

		/****Methods****/

		//Construct the BackGround vector
		std::vector<BattleField_Sprite*>* BackGround_Vector();

		//Generate the background of the screen
		bool Render(Rect Camera, VideoSurface & Screen);
};

//Environment class which is designed to manage everything relative to the environment layer of the battlefield
class Environment // : public BattleField_Sprite
{
	private:
		//Default sprite clip
		Rect Environment_Clip;
		//Tilesets surface
		RGBSurface Environment_Tileset_Trees, Environment_Tileset_Rocks, Environment_Tileset_Walls, Environment_Tileset_Houses;

		//The vector that will contains the BackGround sprites corresponding to the BackGround map
		std::vector<BattleField_Sprite*>* myEnvironment_Sprite_Vector;

	public:
		Environment();
		~Environment();

		/****Methods****/

		//Construct the BackGround vector
		std::vector<BattleField_Sprite*>* Environment_Vector();

		//Generate the background of the screen
		bool Render(Rect Camera, VideoSurface & Screen);
};

#endif
