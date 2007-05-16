#include "Character_Base.hh" //to be ale to use the character_base class

#ifndef Animation_Center_HH
#define Animation_Center_HH

#include "Animations.hh"


class Character_Base; //false def: to be able to instantiate

//Where all animation for the character are defined
class Character_Animations_Center
{
private:
	//current animation current frame
	int Frame;
	//Character Instance (never deleted coz only a link)
	Character_Base* Character_Instance;

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

	//Animation's Timers
	Timer<Character_Animations_Center>* Death_Animation_Timer;
	Timer<Character_Animations_Center>* Attack_Animation_Timer;
	Timer<Character_Animations_Center>* Hit_Animation_Timer;

	//Animation's Callbacks
	unsigned int Death_Animation_Callback(unsigned int interval, void* args);
	unsigned int Attack_Animation_Callback(unsigned int interval, void* args);
	unsigned int Hit_Animation_Callback(unsigned int interval, void* args);
	
protected:

public:
	//Accessor
	inline int Get_Frame() const
	{
		return Frame;
	}

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

	//Animations for characters
		//Stop Animation
	void Stop_Animation_Play( Character_Base* Character_Instance );
		//Death Animation
	void Death_Animation_Play(Character_Base* Character_Instance);
		//Attack Animation 
	void Attack_Animation_Play(Character_Base* Character_Instance, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector);
		//Hit Animation for characters
	void Hit_Animation_Play(Character_Base* Character_Instance);
};

class Building_Permanent_Animation_Center
{
};

class Building_Animations_Center
{
};

#endif
