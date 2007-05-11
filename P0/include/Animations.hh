#ifndef Animations_HH
#define Animations_HH

#include "Config.hh"

class Character_Animation
{
private:
	std::vector<Rect> *Animation_Tile_Rect;
	long Animation_Frames_Interval;
	int Animation_Frame_Number;
	int Animation_KeyFrame;
	int Animation_Sprite_Width;
	int Animation_Sprite_Height;
	RGBSurface* Animation_Tileset;

	//Definition
	Character_Animation();
	void Clean_Animation();

public:
	//Accessor
	inline std::vector<Rect>* Get_Animation_Tile_Rect() const
	{
		return Animation_Tile_Rect;
	}
	inline long Get_Animation_Frames_Interval() const
	{
		return Animation_Frames_Interval;
	}
	inline int Get_Animation_KeyFrame() const
	{
		return Animation_KeyFrame;
	}
	inline int Get_Animation_Frame_Number() const
	{
		return Animation_Frame_Number;
	}
	inline int Get_Animation_Sprite_Width() const
	{
		return Animation_Sprite_Width;
	}
	inline int Get_Animation_Sprite_Height() const
	{
		return Animation_Sprite_Height;
	}
	inline RGBSurface* Get_Animation_Tileset() const
	{
		return Animation_Tileset;
	}

	//Public Definition
	Character_Animation(const char *Animation_Name, const string &Data_Root_Directory, const string &Description_File);
	~Character_Animation();

};

class Building_Permanent_Animation
{
};

class Building_Animation
{
};

#endif
