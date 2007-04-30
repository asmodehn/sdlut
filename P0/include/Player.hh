#ifndef Player_HH
#define Player_HH

#include "Player_Base.hh"
#include "Messages.hh"

//Player Base Class
class Player : public Player_Base
{
    private:
		//Attack msgs
		RGBSurface *attack_melee_msg_hit;
		RGBSurface *attack_melee_msg_miss;
		RGBSurface *attack_distant_msg_hit;
		RGBSurface *attack_distant_msg_miss;

		//The Camera that follow the character
		Rect Camera;

	public:
		/***Accessor***/
		inline void Set_Camera(Rect new_Camera)
        {
            Camera = new_Camera;
        }
        inline Rect Get_Camera() const
        {
            return Camera;
        }

		//Definition
		Player();
		~Player();
		
		//Camera which follow the Character
		bool Following_Camera();

		//Manage Attack Msg regarding the attack style
		bool Set_Attack_Msg();

		//Move the Character and check collisions with everything (based on input)
		bool Move(std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector);
};

#endif
