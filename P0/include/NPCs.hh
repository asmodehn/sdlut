#ifndef NPCs_HH
#define NPCs_HH

#include "Player_Base.hh"

//Merchant NPC
class NPC_Merchant : public Player_Base
{
	private:
		void Clean_NPC_Merchant();

	public:
		//Declaration
		NPC_Merchant();
		~NPC_Merchant();


};

#endif
