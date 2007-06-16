#ifndef Player_HH
#define Player_HH

#include "Player_Base.hh"
#include "Messages.hh"

//Player Base Class
class Player : public Player_Base
{
    private:
		//Attack msgs
		std::auto_ptr<RGBSurface> attack_unarmed_msg_hit;
		std::auto_ptr<RGBSurface> attack_unarmed_msg_miss;
		std::auto_ptr<RGBSurface> attack_melee_msg_hit;
		std::auto_ptr<RGBSurface> attack_melee_msg_miss;
		std::auto_ptr<RGBSurface> attack_distant_msg_hit;
		std::auto_ptr<RGBSurface> attack_distant_msg_miss;

		//for movement based on time not on framerate
		long DeltaTicks;

		//The Camera that follow the character
		Rect Camera;

		//Everything needed to fully clean the player in case of exception or at destruction
		void Clean_Player();

	public:
		/***Accessor***/
		inline void Set_Camera(Rect new_Camera)
        {
            Camera = new_Camera;
        }
        inline Rect& Get_Camera()
        {
            return Camera;
        }
		inline void Set_DeltaTicks(long new_DeltaTicks)
        {
            DeltaTicks = new_DeltaTicks;
        }
        inline long& Get_DeltaTicks()
        {
            return DeltaTicks;
        }

		//Definition
		Player();
		~Player();
		
		//Camera which follow the Character
		bool Following_Camera();

		//Manage Attack Msg regarding the attack style
		bool Set_Attack_Msg();

		//Move the Character and check collisions with everything (based on input)
		void Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector);
		
		//Reset everything to normal mode when the attack is finished (Same method as in Character_Base::Attack_Reset() except that it play attack msg)
		void Attack_Reset();
};

#endif
