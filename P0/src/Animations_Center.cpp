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

	string Default_Attack_Style = XML_Manager::Get_Option_String(Animation_Center_Filename, "Style");
	string Default_Attack_Type = XML_Manager::Get_Option_String(Animation_Center_Filename, "Type");

	if ( XML_Manager::Check_Node_Exists(Animation_Center_Filename, "Attack_Animation_Filename") ) //if animation defined
		Attack_Animation = new Character_Animation("Attack_Animation_Filename", Data_Root_Directory, Animation_Center_Filename);

	if ( XML_Manager::Check_Node_Exists(Animation_Center_Filename, "Stop_Animation_Filename") ) //if animation defined
		Stop_Animation = new Character_Animation("Stop_Animation_Filename", Data_Root_Directory, Animation_Center_Filename); 

	if ( XML_Manager::Check_Node_Exists(Animation_Center_Filename, "Walk_Animation_Filename") ) //if animation defined
		Walk_Animation = new Character_Animation("Walk_Animation_Filename", Data_Root_Directory, Animation_Center_Filename);

	if ( XML_Manager::Check_Node_Exists(Animation_Center_Filename, "Run_Animation_Filename") ) //if animation defined
		Run_Animation = new Character_Animation("Run_Animation_Filename", Data_Root_Directory, Animation_Center_Filename);

	if ( XML_Manager::Check_Node_Exists(Animation_Center_Filename, "Pause_Animation_Filename") ) //if animation defined
		Pause_Animation = new Character_Animation("Pause_Animation_Filename", Data_Root_Directory, Animation_Center_Filename);

	if ( XML_Manager::Check_Node_Exists(Animation_Center_Filename, "Hit_Animation_Filename") ) //if animation defined
		Hit_Animation = new Character_Animation("Hit_Animation_Filename", Data_Root_Directory, Animation_Center_Filename);

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
	delete Attack_Animation, Attack_Animation = NULL;
	delete Death_Animation, Death_Animation = NULL;
	delete Run_Animation, Run_Animation = NULL;
	delete Walk_Animation, Walk_Animation = NULL;
	delete Hit_Animation, Hit_Animation = NULL;
	delete Stop_Animation, Stop_Animation = NULL;
	delete Pause_Animation, Pause_Animation = NULL;
} catch (...) {
	P0_Logger << nl << " Clean_Character_Animations_Center() Failed !!" << std::endl;
}
}
