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

	Animations_Owner = false;
}

//Constructor
Character_Animations_Center::Character_Animations_Center(
		Character_Animation* &Stop_Animation,
		Character_Animation* &Walk_Animation,
		Character_Animation* &Run_Animation,
		Character_Animation* &Attack_Animation,		
		Character_Animation* &Hit_Animation,
		Character_Animation* &Pause_Animation,
		Character_Animation* &Death_Animation,
		//,Character_Animation* &Talk_Animation,
		bool Animations_Owner /*= false*/)
{
try {
////To be able to delete anything at any time
	Character_Instance = NULL;

	Walk_Animation_Timer = NULL;
	Death_Animation_Timer = NULL;
	Attack_Animation_Timer = NULL;
	Hit_Animation_Timer = NULL;
////

	this->Stop_Animation = Stop_Animation;
	this->Walk_Animation = Walk_Animation;
	this->Run_Animation = Run_Animation;
	this->Attack_Animation = Attack_Animation;
	this->Hit_Animation = Hit_Animation;
	this->Pause_Animation = Pause_Animation;
	this->Death_Animation = Death_Animation;
	//this->Talk_Animation = Talk_Animation;

	this->Animations_Owner = Animations_Owner;

	Frame = 0;
	//Timers
	Walk_Animation_Timer = new Timer<Character_Animations_Center>();
	Death_Animation_Timer = new Timer<Character_Animations_Center>();
	Attack_Animation_Timer = new Timer<Character_Animations_Center>();
	Hit_Animation_Timer = new Timer<Character_Animations_Center>();
	
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
	Walk_Animation_Timer->abort();
	delete Walk_Animation_Timer, Walk_Animation_Timer = NULL;
	Death_Animation_Timer->abort();
	delete Death_Animation_Timer, Death_Animation_Timer = NULL;
	Attack_Animation_Timer->abort();
	delete Attack_Animation_Timer, Attack_Animation_Timer = NULL;
	Hit_Animation_Timer->abort();
	delete Hit_Animation_Timer, Hit_Animation_Timer = NULL;

	if (Animations_Owner) //if he is the owner, he must clean the animations
	{
	//Not always independent animations
		if ( (Walk_Animation != Stop_Animation) && (Walk_Animation != NULL) )
			delete Walk_Animation, Walk_Animation = NULL;
		if ( (Run_Animation != Stop_Animation) && (Run_Animation != NULL) )
			delete Run_Animation, Run_Animation = NULL;
		if ( (Attack_Animation != Stop_Animation) && (Attack_Animation != NULL) )
			delete Attack_Animation, Attack_Animation = NULL;
		if ( (Hit_Animation != Stop_Animation) && (Hit_Animation != NULL) )
			delete Hit_Animation, Hit_Animation = NULL;
	//Independent animation
		if (Stop_Animation != NULL)
			delete Stop_Animation, Stop_Animation = NULL;
	//Independent animations that can be NULL
		if (Death_Animation != NULL)
			delete Death_Animation, Death_Animation = NULL;
		if (Pause_Animation != NULL)
			delete Pause_Animation, Pause_Animation = NULL;
	}

} catch (...) {
	P0_Logger << nl << " Clean_Character_Animations_Center() Failed !!" << std::endl;
}
}

//Set the direction sprite regarding of the direction
void Character_Animations_Center::Stop_Animation_Play( Character_Base* Character_Instance )
{
P0_Logger << nl << "Character: " << Character_Instance << " Stopped @ (" << Character_Instance->Get_X() << ", " << Character_Instance->Get_Y() << ")" << std::endl;  	

	//Stop Walk Animation
	Walk_Animation_Timer->abort();

	//reset tileset if necessary
	if ( Character_Instance->Get_Current_Tileset() != Stop_Animation->Get_Animation_Tileset() )
		Character_Instance->Set_Current_Tileset( Stop_Animation->Get_Animation_Tileset() );

	//reset tile rect
	Character_Instance->Set_Current_Tile_Rect( Stop_Animation->Get_Animation_Tile_Rect()->at(Character_Instance->Get_Move_Direction()) );
	Character_Instance->Set_Moving_Status(-1); //stopped

	//Clear Path
	Character_Instance->Clear_Path();
}

//Walk Animation for characters
void Character_Animations_Center::Walk_Animation_Play( Character_Base* Character_Instance, const Point& Destination, std::vector< std::vector<Character_Base*> *>* &Global_Player_Vector, std::vector<BattleField_Sprite*>* &Environment_Sprite_Vector, std::vector<BattleField_Sprite*>* &BackGround_Sprite_Vector, std::vector< std::vector<Character_Base*> *>* &Global_Monster_Vector )
{
	//abort timer if existant
	Walk_Animation_Timer->abort();

	//Reset frame
	Frame = 0;

	assert( Character_Instance != NULL && "The Character Instance is NULL ???!!!");

	//Fill the structure
	sTimer_Arg.Ch_Instance = Character_Instance;
	sTimer_Arg.Destination = Destination;
	sTimer_Arg.Environment_Sprite_Vector = Environment_Sprite_Vector;
	sTimer_Arg.BackGround_Sprite_Vector = BackGround_Sprite_Vector;
	sTimer_Arg.Global_Player_Vector = Global_Player_Vector;
	sTimer_Arg.Global_Monster_Vector = Global_Monster_Vector;

	assert( &sTimer_Arg != NULL && "The Structure pointer is NULL ???!!!");
	assert( sTimer_Arg.Ch_Instance != NULL && "The Character Instance inside the structure is NULL ???!!!");

	//set the tileset
	Character_Instance->Set_Current_Tileset( Walk_Animation->Get_Animation_Tileset() );

	//Anim occuring
	Character_Instance->Set_Moving_Status(1);

	//set & launch walk animation with the struct in argument
	Walk_Animation_Timer->setCallback(this,&Character_Animations_Center::Walk_Animation_Callback, (void*)&sTimer_Arg);
	Walk_Animation_Timer->launch( 1 );
}

//Walk Animation for characters (callback method)
unsigned int Character_Animations_Center::Walk_Animation_Callback(unsigned int interval, void* args)
{
try {
	//in order to not cast each time we want to use the arg
	assert( args != NULL && "The Structure pointer is NULL ???!!!");
	Timer_Arg* myTimer_Arg = static_cast<Timer_Arg*>(args);
	assert( myTimer_Arg->Ch_Instance != NULL && "The Character Instance inside the structure is NULL ???!!!");

	if (Frame >= Walk_Animation->Get_Animation_Frame_Number() )
	{
		Frame = 0; //reset frame anim
		myTimer_Arg->Ch_Instance->Set_Moving_Status(0); //anim finished
		return 0; //max<long>(Walk_Animation->Get_Animation_Frames_Interval() - 10, 1); //interval-10ms else it's less realist (but always > to 1 !)
	}

	//set the tilerect depending on the frame
	myTimer_Arg->Ch_Instance->Set_Current_Tile_Rect( Walk_Animation->Get_Animation_Tile_Rect()->at( myTimer_Arg->Ch_Instance->Get_Move_Direction() * Walk_Animation->Get_Animation_Frame_Number() + Frame ) );


	if (Frame == (Walk_Animation->Get_Animation_Frame_Number() - 1) ) //last frame b4 end of anim
	{
		//final position: we need to do this coz the normal frame process below round the position & we must be sure that we reach the global position on the grid when the animation finished
		myTimer_Arg->Ch_Instance->Get_Collision_Box().setx( myTimer_Arg->Destination.getx() + myTimer_Arg->Ch_Instance->CB_X_Modifier );
		myTimer_Arg->Ch_Instance->Get_Collision_Box().sety( myTimer_Arg->Destination.gety() + myTimer_Arg->Ch_Instance->CB_Y_Modifier );
P0_Logger << nl << "Character Final Frame " << Frame << " Moving CB @ (" << myTimer_Arg->Ch_Instance->Get_Collision_Box().getx() << ", " << myTimer_Arg->Ch_Instance->Get_Collision_Box().gety() << ")" << std::endl;  	
	}
	else //normal frame
	{
		assert(Walk_Animation->Get_Animation_Frame_Number()>0 && "Walk Animation Must at least have one frame !!");
		//Update the CB to intermediate position: velocity*grid_size/nb_of_frame_of_animation
		myTimer_Arg->Ch_Instance->Get_Collision_Box().setx( myTimer_Arg->Ch_Instance->Get_X() + myTimer_Arg->Ch_Instance->CB_X_Modifier + myTimer_Arg->Ch_Instance->Get_xVel()*myTimer_Arg->Ch_Instance->Get_Sprite_Width()/Walk_Animation->Get_Animation_Frame_Number() );
		myTimer_Arg->Ch_Instance->Get_Collision_Box().sety( myTimer_Arg->Ch_Instance->Get_Y() + myTimer_Arg->Ch_Instance->CB_Y_Modifier + myTimer_Arg->Ch_Instance->Get_yVel()*myTimer_Arg->Ch_Instance->Get_Sprite_Height()/Walk_Animation->Get_Animation_Frame_Number() );
P0_Logger << nl << "Character Normal Frame " << Frame << " Moving CB @ (" << myTimer_Arg->Ch_Instance->Get_Collision_Box().getx() << ", " << myTimer_Arg->Ch_Instance->Get_Collision_Box().gety() << ")" << std::endl;  	
	}
	
	//Check if intermediate position is available
	if ( myTimer_Arg->Ch_Instance->Manage_Collisions(myTimer_Arg->Global_Player_Vector, myTimer_Arg->Environment_Sprite_Vector, myTimer_Arg->BackGround_Sprite_Vector, myTimer_Arg->Global_Monster_Vector, false) )
	{
		//Update position
		myTimer_Arg->Ch_Instance->Set_X( myTimer_Arg->Ch_Instance->Get_Collision_Box().getx() - myTimer_Arg->Ch_Instance->CB_X_Modifier );
		myTimer_Arg->Ch_Instance->Set_Y( myTimer_Arg->Ch_Instance->Get_Collision_Box().gety() - myTimer_Arg->Ch_Instance->CB_Y_Modifier );

		P0_Logger << nl << "Character Frame " << Frame << " Moving Character to his CB place @ (" << myTimer_Arg->Ch_Instance->Get_X() << ", " << myTimer_Arg->Ch_Instance->Get_Y() << ")" << std::endl;  	
	}
	else
	{

P0_Logger << nl << "Character Stopped bcz blocked" << std::endl;  
		//todo: what do we do when the intermediate is not available ??!! now we stop brutally and reset anim
		myTimer_Arg->Ch_Instance->Get_Collision_Box().setx( myTimer_Arg->Ch_Instance->Get_X() + myTimer_Arg->Ch_Instance->CB_X_Modifier );
		myTimer_Arg->Ch_Instance->Get_Collision_Box().sety( myTimer_Arg->Ch_Instance->Get_Y() + myTimer_Arg->Ch_Instance->CB_Y_Modifier );
		Stop_Animation_Play(myTimer_Arg->Ch_Instance); //stop ch
		return 0;//stop timer
	}
	
	//loop
	Frame++;
	return max<long>(Walk_Animation->Get_Animation_Frames_Interval(), 1);//must be > 1!

} catch (std::exception &exc) {
	Stop_Animation_Play( static_cast<Timer_Arg*>(args)->Ch_Instance );
	P0_Logger << nl << " From Character_Animations_Center::Walk_Animation_Callback(), " << exc.what() << std::endl;
#ifdef _DEBUG
	throw std::logic_error("DEBUG_MODE -> Stop In Character_Animations_Center::Walk_Animation_Callback");
#else
	return 0;//end of timer
#endif
} catch (...) {
	Stop_Animation_Play( static_cast<Timer_Arg*>(args)->Ch_Instance );
	P0_Logger << nl << "Unhandled Error In Character_Animations_Center::Walk_Animation_Callback()" << std::endl; 
#ifdef _DEBUG
	throw std::logic_error("DEBUG_MODE -> Stop In Character_Animations_Center::Walk_Animation_Callback");
#else
	return 0;//end of timer
#endif
}
}

//Death Animation for characters
void Character_Animations_Center::Death_Animation_Play( Character_Base* Character_Instance )
{
	//abort timer if existant
	Death_Animation_Timer->abort();

	//Reset frame
	Frame = 0;

	//set the tileset
	Character_Instance->Set_Current_Tileset( Death_Animation->Get_Animation_Tileset() );

	//Anim occuring
	Character_Instance->Set_Alive_Status(-1);

	//set & launch dying animation with the ch instance in arg
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
		//Stop_Animation_Play( ((Character_Base*)args) ); //reset tileset + tile_rect
		return 0; //end timer
	}

	((Character_Base*)args)->Set_Current_Tile_Rect( Death_Animation->Get_Animation_Tile_Rect()->at( ((Character_Base*)args)->Get_Move_Direction() * Death_Animation->Get_Animation_Frame_Number() + Frame ) );
	
	Frame++;
	return max<long>(Death_Animation->Get_Animation_Frames_Interval(), 1);//must be > 1!

} catch (std::exception &exc) {
	Frame = 0;
	((Character_Base*)args)->Set_Alive_Status( -2 );
	//Stop_Animation_Play( (Character_Base*)args );
	P0_Logger << nl << " From Character_Animations_Center::Death_Animation_Callback(), " << exc.what() << std::endl;
#ifdef _DEBUG
	throw std::logic_error("DEBUG_MODE -> Stop In Character_Animations_Center::Death_Animation_Callback");
#else
	return 0;//end of timer
#endif
} catch (...) {
	Frame = 0;
	((Character_Base*)args)->Set_Alive_Status( -2 );
	//Stop_Animation_Play( (Character_Base*)args );
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
	//abort timer if existant
	Attack_Animation_Timer->abort();

	//Reset frame
	Frame = 0;
	//store the instance
	this->Character_Instance = Character_Instance;

	//set the tileset
	Character_Instance->Set_Current_Tileset( Attack_Animation->Get_Animation_Tileset() );

	//set & launch attack animation with the structure in arg
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
	//
	//todo: use the arg which must contain the character instance and the global monster_vector ?!!
	//		coz when monster will be able to attack they need to know which instance is attacking
	//
	if (Frame >= Attack_Animation->Get_Animation_Frame_Number() )
	{
		Frame = 0; //reset frame anim
		Character_Instance->Attack_Reset();//Reset Attack	
		Stop_Animation_Play( Character_Instance ); //reset tileset + tile_rect
		return 0; //end timer
	}

	//assign the good sprite rect to the character sprite rect depending on the frame and the direction
	Character_Instance->Set_Current_Tile_Rect( Attack_Animation->Get_Animation_Tile_Rect()->at( Character_Instance->Get_Attack_Direction() * Attack_Animation->Get_Animation_Frame_Number() + Frame ) );
	
	if ( Frame == Attack_Animation->Get_Animation_KeyFrame() )
	{
		Character_Instance->Set_Attack_Successfull( Character_Instance->Attack_Check_Status(Character_Instance->Real_Range, Character_Instance->Real_Inflicted_Damage, (std::vector< std::vector<Character_Base*> *>*&)args) ) ;
	}

	//loop
	Frame++;
	return max<long>(Attack_Animation->Get_Animation_Frames_Interval(), 1);//must be > 1!


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
	//abort timer if existant
	Hit_Animation_Timer->abort();

	//Reset frame
	Frame = 0;
	//store the instance
	this->Character_Instance = Character_Instance;
	//set the tileset
	Character_Instance->Set_Current_Tileset( Hit_Animation->Get_Animation_Tileset() );
	
	//
	//todo:launch attitude vs player_base or monster_base timer
	//

	//Tell anim occuring
	Character_Instance->Set_Hitted_Status( 1 );

	//set & launch the animation with the ch instance in argument
	Hit_Animation_Timer->setCallback(this,&Character_Animations_Center::Hit_Animation_Callback, (void*)Character_Instance);

	Hit_Animation_Timer->launch( 1 );
}

//Hit Animation for characters (callback method)
unsigned int Character_Animations_Center::Hit_Animation_Callback(unsigned int interval, void* args)
{
try {
	if (Frame >= Hit_Animation->Get_Animation_Frame_Number() )
	{
		Frame = 0; //reset frame anim
		((Character_Base*)args)->Set_Hitted_Status( 0 );
		Stop_Animation_Play( ((Character_Base*)args) ); //reset tileset + tile_rect
		return 0; //end of timer
	}

	//assign the good sprite rect to the character sprite rect depending on the frame and the direction
	((Character_Base*)args)->Set_Current_Tile_Rect( Hit_Animation->Get_Animation_Tile_Rect()->at( ((Character_Base*)args)->Get_Move_Direction() * Hit_Animation->Get_Animation_Frame_Number() + Frame ) );
	
	//loop
	Frame++;
	return max<long>(Hit_Animation->Get_Animation_Frames_Interval(), 1);//must be > 1!


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
