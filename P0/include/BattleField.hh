#ifndef BattleField_HH
#define BattleField_HH

#include "Base.hh"

//Battlefield Sprites will be referenced inside a vector which will be used to generate the battlefield
class BattleField_Sprite
{
	private:
		int X,Y;
		int Terrain_Type;
		Rect BG_Clip;
		
	public:
		BattleField_Sprite();
		BattleField_Sprite(int x, int y, int terrain_type, Rect bg_clip);
		~BattleField_Sprite();
		
		/****Methods****/


};

//BattleField class which is designed to manage everything relative to the batllefield
class BattleField
{
	private:
		int Current_Terrain_Type;

		RGBSurface Background;
		Rect BattleField_Clip;
		Rect BattleField_Grass_Clip;

		//
		std::vector<BattleField_Sprite*> BattleField_Sprite_Vector;

	public:
		BattleField();
		~BattleField();
		
		/****Methods****/
		std::vector<BattleField_Sprite*> BattleField::BattleField_Vector();
		bool BattleField::BattleField_Camera_Vector(Rect Camera);
		bool Render(VideoSurface & Screen);


};

#endif BattleField_HH
