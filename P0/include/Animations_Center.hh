#ifndef Animation_Center_HH
#define Animation_Center_HH

#include "Animations.hh"
#include "BattleField.hh"

class Character_Base; //fwd def: to be able to instantiate

//Where all animation for the character are defined
class Character_Animations_Center
{
private:
	//current animation current frame
	int Frame;
	//Character Instance (never deleted coz only a link)
	Character_Base* Character_Instance;

	//Indicate if the animation manager is the owner of the animations and so if he must delete it when he is destructed
	bool Animations_Owner;

	//Animations
	Character_Animation* Attack_Animation;
	Character_Animation* Death_Animation;
	Character_Animation* Run_Animation;
	Character_Animation* Walk_Animation;
	Character_Animation* Hit_Animation;
	Character_Animation* Stop_Animation;
	Character_Animation* Pause_Animation;

	//Structure to pass infos to the timer
	struct Timer_Arg{
		Character_Base* Ch_Instance;
		Point Destination;
		std::vector<BattleField_Sprite*>* Environment_Sprite_Vector;
		std::vector<BattleField_Sprite*>* BackGround_Sprite_Vector;
		std::vector< std::vector<Character_Base*> *>* Global_Player_Vector;
		std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector;
	};
	Timer_Arg sTimer_Arg;

	//Default constructor
	Character_Animations_Center();
	//clean up
	void Clean_Character_Animations_Center();

	//Animation's Timers
	Timer<Character_Animations_Center>* Walk_Animation_Timer;
	Timer<Character_Animations_Center>* Death_Animation_Timer;
	Timer<Character_Animations_Center>* Attack_Animation_Timer;
	Timer<Character_Animations_Center>* Hit_Animation_Timer;

	//Animation's Callbacks
	unsigned int Walk_Animation_Callback(unsigned int interval, void* args);
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
	Character_Animations_Center(
		Character_Animation* &Stop_Animation,
		Character_Animation* &Walk_Animation,
		Character_Animation* &Run_Animation,
		Character_Animation* &Attack_Animation,		
		Character_Animation* &Hit_Animation,
		Character_Animation* &Pause_Animation,
		Character_Animation* &Death_Animation,
		//,Character_Animation* &Talk_Animation,
		bool Animations_Owner = false
		);
	~Character_Animations_Center();

	//Animations for characters
		//Stop Animation
	void Stop_Animation_Play( Character_Base* &Character_Instance );
		//Walk Animation
	void Walk_Animation_Play( Character_Base* &Character_Instance, const Point& Destination, std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector );
		//Death Animation
	void Death_Animation_Play(Character_Base* &Character_Instance);
		//Attack Animation 
	void Attack_Animation_Play(Character_Base* &Character_Instance, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector);
		//Hit Animation for characters
	void Hit_Animation_Play(Character_Base* &Character_Instance);
};

class Building_Permanent_Animation_Center
{
};

class Building_Animations_Center
{
};

#endif
