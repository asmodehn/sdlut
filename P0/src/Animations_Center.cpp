#include "Animations_Center.hh"

Character_Animations_Center::Character_Animations_Center()
{
	Frame = 0;
	Character_Instance = NULL;

	Death_Animation_Timer = NULL;
	Attack_Animation_Timer = NULL;
	Hit_Animation_Timer = NULL;

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
////To be able to delete anything at any time
	Character_Instance = NULL;

	Death_Animation_Timer = NULL;
	Attack_Animation_Timer = NULL;
	Hit_Animation_Timer = NULL;

	Attack_Animation = NULL;
	Death_Animation = NULL;
	Run_Animation = NULL;
	Walk_Animation = NULL;
	Hit_Animation = NULL;
	Stop_Animation = NULL;
	Pause_Animation = NULL;
	Death_Animation_Timer = NULL;
////

	Frame = 0;
	//Timers
	Death_Animation_Timer = new Timer<Character_Animations_Center>();
	Attack_Animation_Timer = new Timer<Character_Animations_Center>();
	Hit_Animation_Timer = new Timer<Character_Animations_Center>();

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
//Timers
	Death_Animation_Timer->abort();
	delete Death_Animation_Timer, Death_Animation_Timer = NULL;
	Attack_Animation_Timer->abort();
	delete Attack_Animation_Timer, Attack_Animation_Timer = NULL;
	Hit_Animation_Timer->abort();
	delete Hit_Animation_Timer, Hit_Animation_Timer = NULL;

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

//Set the direction sprite regarding of the direction
void Character_Animations_Center::Stop_Animation_Play( Character_Base* Character_Instance )
{
	//store the instance
	this->Character_Instance = Character_Instance;

	//reset tileset if necessary
	if ( Character_Instance->Get_Current_Tileset() != Stop_Animation->Get_Animation_Tileset() )
		Character_Instance->Set_Current_Tileset( Stop_Animation->Get_Animation_Tileset() );

	//reset tile rect
	Character_Instance->Set_Current_Tile_Rect( Stop_Animation->Get_Animation_Tile_Rect()->at(Character_Instance->Get_Move_Direction()) );
}

//Death Animation for characters
void Character_Animations_Center::Death_Animation_Play( Character_Base* Character_Instance )
{
	//Reset frame
	Frame = 0;
	//store the instance
	this->Character_Instance = Character_Instance;
	//set the tileset
	Character_Instance->Set_Current_Tileset( Death_Animation->Get_Animation_Tileset() );
	//Anim occuring
	Character_Instance->Set_Alive_Status(-1);
	//set & launch dying animation with the direction in argument
	Death_Animation_Timer->setCallback(this,&Character_Animations_Center::Death_Animation_Callback, (void*)Character_Instance);
	Death_Animation_Timer->launch( 1 );
}

//Death Animation for characters (callback method)
unsigned int Character_Animations_Center::Death_Animation_Callback(unsigned int interval, void* args)
{
try {
	if (Frame >= Death_Animation->Get_Animation_Frame_Number() )
	{
		Frame = 0; //reset frame anim
		((Character_Base*)args)->Set_Alive_Status( -2 ); //anim ended: true death
		Stop_Animation_Play( ((Character_Base*)args) ); //reset tileset + tile_rect
		return 0; //end timer
	}

	((Character_Base*)args)->Set_Current_Tile_Rect( Death_Animation->Get_Animation_Tile_Rect()->at( ((Character_Base*)args)->Get_Move_Direction() * Death_Animation->Get_Animation_Frame_Number() + Frame ) );
	
	Frame++;
	return Death_Animation->Get_Animation_Frames_Interval();

} catch (std::exception &exc) {
	Frame = 0;
	((Character_Base*)args)->Set_Alive_Status( -2 );
	Stop_Animation_Play( (Character_Base*)args );
	P0_Logger << nl << " From Character_Animations_Center::Death_Animation_Callback(), " << exc.what() << std::endl;
#ifdef _DEBUG
	throw std::logic_error("DEBUG_MODE -> Stop In Character_Animations_Center::Death_Animation_Callback");
#else
	return 0;//end of timer
#endif
} catch (...) {
	Frame = 0;
	((Character_Base*)args)->Set_Alive_Status( -2 );
	Stop_Animation_Play( (Character_Base*)args );
	P0_Logger << nl << "Unhandled Error In Character_Animations_Center::Death_Animation_Callback()" << std::endl; 
#ifdef _DEBUG
	throw std::logic_error("DEBUG_MODE -> Stop In Character_Animations_Center::Death_Animation_Callback");
#else
	return 0;//end of timer
#endif
}
}

//Attack Animation for characters
void Character_Animations_Center::Attack_Animation_Play(Character_Base* Character_Instance, std::vector< std::vector<Character_Base*> *>* Global_Monster_Vector)
{
	//Reset frame
	Frame = 0;
	//store the instance
	this->Character_Instance = Character_Instance;
	//set the tileset
	Character_Instance->Set_Current_Tileset( Attack_Animation->Get_Animation_Tileset() );
	//set & launch attack animation with the direction in argument
	Attack_Animation_Timer->setCallback(this,&Character_Animations_Center::Attack_Animation_Callback, (void*)Global_Monster_Vector);
	//
	//todo: use the arg which must contain the character instance and the global monster_vector ?!!
	//		coz when monster will be able to attack they need to know which instance is attacking
	//
	Attack_Animation_Timer->launch( 1 );
}

//Attack Animation for characters (callback method)
unsigned int Character_Animations_Center::Attack_Animation_Callback(unsigned int interval, void* args)
{
try {
	//This is here to allow the last frame to play as long as the previous frames
	if (!Character_Instance->Get_Attack_Status()) //attack already been finished
	{
		Stop_Animation_Play( Character_Instance ); //reset tileset + tile_rect
		return 0; //end of timer
	}

	//
	//todo: use the arg which must contain the character instance and the global monster_vector ?!!
	//		coz when monster will be able to attack they need to know which instance is attacking
	//
	if (Frame >= Attack_Animation->Get_Animation_Frame_Number() )
	{
		Frame = 0; //reset frame anim
		Character_Instance->Attack_Reset();//Reset Attack		
		return Attack_Animation->Get_Animation_Frames_Interval() - 10; //-10ms else it less realist
	}

	//assign the good sprite rect to the character sprite rect depending on the frame and the direction
	Character_Instance->Set_Current_Tile_Rect( Attack_Animation->Get_Animation_Tile_Rect()->at( Character_Instance->Get_Attack_Direction() * Attack_Animation->Get_Animation_Frame_Number() + Frame ) );
	
	if ( Frame == Attack_Animation->Get_Animation_KeyFrame() )
	{
		Character_Instance->Set_Attack_Successfull( Character_Instance->Attack_Check_Status(Character_Instance->Real_Range, Character_Instance->Real_Inflicted_Damage, (std::vector< std::vector<Character_Base*> *>*&)args) ) ;
	}

	//loop
	Frame++;
	return Attack_Animation->Get_Animation_Frames_Interval();


} catch (std::exception &exc) {
	//force reset
	if ( ( Character_Instance->Get_Attack_Style() == 0 ) || ( Character_Instance->Get_Attack_Style() == 1 ) )
	{
		Character_Instance->Set_Attack_Initial_X(-1);
		Character_Instance->Set_Attack_Initial_Y(-1);
		Character_Instance->Set_Attack_Direction(-1);
	}
	Character_Instance->Set_Attack_Status(false); //end of attack

	Stop_Animation_Play( Character_Instance );
	Frame = 0;
	P0_Logger << nl << " From Character_Animations_Center::Attack_Animation_Callback(), " << exc.what() << std::endl;
	return 0;//end of timer
} catch (...) {
	//force reset
	if ( ( Character_Instance->Get_Attack_Style() == 0 ) || ( Character_Instance->Get_Attack_Style() == 1 ) )
	{
		Character_Instance->Set_Attack_Initial_X(-1);
		Character_Instance->Set_Attack_Initial_Y(-1);
		Character_Instance->Set_Attack_Direction(-1);
	}
	Character_Instance->Set_Attack_Status(false); //end of attack

	Stop_Animation_Play( Character_Instance );
	Frame = 0;
	P0_Logger << nl << "Unhandled Error In Character_Animations_Center::Attack_Animation_Callback()" << std::endl;
	return 0;//end of timer
}
}

//Hit Animation for characters
void Character_Animations_Center::Hit_Animation_Play(Character_Base* Character_Instance)
{
	//Reset frame
	Frame = 0;
	//store the instance
	this->Character_Instance = Character_Instance;
	//set the tileset
	Character_Instance->Set_Current_Tileset( Hit_Animation->Get_Animation_Tileset() );
	
	//
	//todo: stop move timer; launch attitude vs player_base or monster_base timer
	//
	Character_Instance->Set_Hitted_Status( 1 ); //anim occuring

	//set & launch the animation with the direction in argument
	Hit_Animation_Timer->setCallback(this,&Character_Animations_Center::Hit_Animation_Callback, (void*)Character_Instance);
	//
	//todo: use the arg which must contain the character instance and the global monster_vector ?!!
	//		coz when monster will be able to attack they need to know which instance is attacking
	//
	Hit_Animation_Timer->launch( 1 );
}

//Hit Animation for characters (callback method)
unsigned int Character_Animations_Center::Hit_Animation_Callback(unsigned int interval, void* args)
{
try {
	//This is here to allow the last frame to play as long as the previous frames
	if ( ((Character_Base*)args)->Get_Hitted_Status() == 0 ) //anim already been finished
	{
		Stop_Animation_Play( ((Character_Base*)args) ); //reset tileset + tile_rect
		return 0; //end of timer
	}

	if (Frame >= Hit_Animation->Get_Animation_Frame_Number() )
	{
		Frame = 0; //reset frame anim
		((Character_Base*)args)->Set_Hitted_Status( 0 );		
		return Hit_Animation->Get_Animation_Frames_Interval() - 10; //-10ms else it less realist
	}

	//assign the good sprite rect to the character sprite rect depending on the frame and the direction
	((Character_Base*)args)->Set_Current_Tile_Rect( Hit_Animation->Get_Animation_Tile_Rect()->at( ((Character_Base*)args)->Get_Move_Direction() * Hit_Animation->Get_Animation_Frame_Number() + Frame ) );
	

	//loop
	Frame++;
	return Hit_Animation->Get_Animation_Frames_Interval();


} catch (std::exception &exc) {
	//reset
	((Character_Base*)args)->Set_Hitted_Status( 0 );
	Stop_Animation_Play( ((Character_Base*)args) );
	Frame = 0;
	P0_Logger << nl << " From Character_Animations_Center::Hit_Animation_Callback(), " << exc.what() << std::endl;
	return 0;//end of timer
} catch (...) {
	//reset
	((Character_Base*)args)->Set_Hitted_Status( 0 );
	Stop_Animation_Play( ((Character_Base*)args) );
	Frame = 0;
	P0_Logger << nl << "Unhandled Error In Character_Animations_Center::Hit_Animation_Callback()" << std::endl;
	return 0;//end of timer
}
}
