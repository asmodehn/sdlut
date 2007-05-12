#ifndef Animation_Center_HH
#define Animation_Center_HH

#include "Animations.hh"

//Where all animation for the character are defined
class Character_Animations_Center
{
private:
	//Animations
	Character_Animation* Attack_Animation;
	Character_Animation* Death_Animation;
	Character_Animation* Run_Animation;
	Character_Animation* Walk_Animation;
	Character_Animation* Hit_Animation;
	Character_Animation* Stop_Animation;
	Character_Animation* Pause_Animation;

	//Default constructor
	Character_Animations_Center();
	//clean up
	void Clean_Character_Animations_Center();

	
protected:

public:
	//Accessor
	inline Character_Animation* Get_Attack_Animation() const
	{
		return Attack_Animation;
	}
	inline Character_Animation* Get_Death_Animation() const
	{
		return Death_Animation;
	}
	inline Character_Animation* Get_Run_Animation() const
	{
		return Run_Animation;
	}
	inline Character_Animation* Get_Walk_Animation() const
	{
		return Walk_Animation;
	}
	inline Character_Animation* Get_Hit_Animation() const
	{
		return Hit_Animation;
	}
	inline Character_Animation* Get_Stop_Animation() const
	{
		return Stop_Animation;
	}
	inline Character_Animation* Get_Pause_Animation() const
	{
		return Pause_Animation;
	}

	//Definition
	Character_Animations_Center(const string &Data_Root_Directory, const string &Animation_Center_Filename);
	~Character_Animations_Center();

};

class Building_Permanent_Animation_Center
{
};

class Building_Animations_Center
{
};

#endif
