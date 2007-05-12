#include "Animations_Center.hh"

Character_Animations_Center::Character_Animations_Center()
{
	Attack_Animation = NULL;
	Death_Animation = NULL;
	Run_Animation = NULL;
	Walk_Animation = NULL;
	Hit_Animation = NULL;
	Stop_Animation = NULL;
	Pause_Animation = NULL;
}

//Constructor
Character_Animations_Center::Character_Animations_Center(const string &Data_Root_Directory, const string &Animation_Center_Filename)
{
try {
	Attack_Animation = NULL;
	Death_Animation = NULL;
	Run_Animation = NULL;
	Walk_Animation = NULL;
	Hit_Animation = NULL;
	Stop_Animation = NULL;
	Pause_Animation = NULL;

	//1st validate !
	XML_Manager::Validate_File(Animation_Center_Filename);

	string Default_Attack_Style = XML_Manager::Get_Option_String(Animation_Center_Filename, "Style");
	string Default_Attack_Type = XML_Manager::Get_Option_String(Animation_Center_Filename, "Type");

//Animation Always present !
	Stop_Animation = new Character_Animation("Stop_Animation_Filename", Data_Root_Directory, Animation_Center_Filename);

//Animations that must be defined but can be the stop animation
	if ( XML_Manager::Check_Node_Exists(Animation_Center_Filename, "Walk_Animation_Filename") ) //if animation defined
	{
		Walk_Animation = new Character_Animation("Walk_Animation_Filename", Data_Root_Directory, Animation_Center_Filename);
	} else {
		*&Walk_Animation = *&Stop_Animation;
	}

	if ( XML_Manager::Check_Node_Exists(Animation_Center_Filename, "Run_Animation_Filename") ) //if animation defined
	{
		Run_Animation = new Character_Animation("Run_Animation_Filename", Data_Root_Directory, Animation_Center_Filename);
	} else {
		*&Run_Animation = *&Stop_Animation;
	}

	if ( XML_Manager::Check_Node_Exists(Animation_Center_Filename, "Attack_Animation_Filename") ) //if animation defined
	{
		Attack_Animation = new Character_Animation("Attack_Animation_Filename", Data_Root_Directory, Animation_Center_Filename);
	} else {
		*&Attack_Animation = *&Stop_Animation;
	}

	if ( XML_Manager::Check_Node_Exists(Animation_Center_Filename, "Hit_Animation_Filename") ) //if animation defined
	{
		Hit_Animation = new Character_Animation("Hit_Animation_Filename", Data_Root_Directory, Animation_Center_Filename);
	} else {
		*&Hit_Animation = *&Stop_Animation;
	}

//animations that can be null
	if ( XML_Manager::Check_Node_Exists(Animation_Center_Filename, "Pause_Animation_Filename") ) //if animation defined
		Pause_Animation = new Character_Animation("Pause_Animation_Filename", Data_Root_Directory, Animation_Center_Filename);

	if ( XML_Manager::Check_Node_Exists(Animation_Center_Filename, "Death_Animation_Filename") ) //if animation defined
		Death_Animation = new Character_Animation("Death_Animation_Filename", Data_Root_Directory, Animation_Center_Filename);

	//if ( XML_Manager::Check_Node_Exists(Animation_Center_Filename, "Talk_Animation_Filename") ) //if animation defined
	//	Talk_Animation = Character_Animation("Talk_Animation_Filename", Data_Root_Directory, Animation_Center_Filename);

} catch (std::exception &exc) {
	Clean_Character_Animations_Center();
	throw std::logic_error(exc.what());
} catch (...) {
	Clean_Character_Animations_Center();
	throw std::logic_error("Unhandled Error In Character_Animations_Center Constructor");
}
}

//Destructor
Character_Animations_Center::~Character_Animations_Center()
{
	Clean_Character_Animations_Center();
}

//clean up
void Character_Animations_Center::Clean_Character_Animations_Center()
{
try{
//Not always independent animations
	if (Walk_Animation != Stop_Animation)
		delete Walk_Animation, Walk_Animation = NULL;
	if (Run_Animation != Stop_Animation)
		delete Run_Animation, Run_Animation = NULL;
	if (Attack_Animation != Stop_Animation)
		delete Attack_Animation, Attack_Animation = NULL;
	if (Hit_Animation != Stop_Animation)
		delete Hit_Animation, Hit_Animation = NULL;
//Independent animation
	delete Stop_Animation, Stop_Animation = NULL;
//Independent animations that can be NULL
	delete Death_Animation, Death_Animation = NULL;
	delete Pause_Animation, Pause_Animation = NULL;
} catch (...) {
	P0_Logger << nl << " Clean_Character_Animations_Center() Failed !!" << std::endl;
}
}
