#include "NPCs.hh"

/*****NPC_Merchant #1*****/
//Constructor
NPC_Merchant::NPC_Merchant()
{
try{
//characteristics parsing (xml parsing)
	Parse_Description_File("Data/Characters/NPC_Merchant.xml");

} catch (std::exception &exc)
{
	Clean_NPC_Merchant(); //clean
	throw std::logic_error(exc.what());
}
catch (...)
{
	P0_Logger << nl << "Error In NPC_Merchant Constructor " << std::endl;
	Clean_NPC_Merchant(); //clean
	throw std::logic_error("Unhandled Exception");
}
}

//Destructor
NPC_Merchant::~NPC_Merchant()
{
	Clean_NPC_Merchant();
}

void NPC_Merchant::Clean_NPC_Merchant()
{
	if (Unarmed_Animations_Center != NULL)
		delete Unarmed_Animations_Center, Unarmed_Animations_Center = NULL;
	if (Melee_Animations_Center != NULL)
		delete Melee_Animations_Center, Melee_Animations_Center = NULL;
	if (Distant_Animations_Center != NULL)
		delete Distant_Animations_Center, Distant_Animations_Center = NULL;
}
