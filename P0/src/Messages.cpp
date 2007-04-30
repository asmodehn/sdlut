#include "Messages.hh"

RGBSurface* Messages::Status_Msg = NULL;
bool Messages::has_status_msg_changed = false;

Messages::Messages()
{
	//msg resetter
	Reset_Status_Msg_Timer = new Timer<Messages>();
}

Messages::~Messages()
{
	//reset the pointer (no need to delete coz no new)
	Status_Msg = NULL;

	//the msg resetter timer
	Reset_Status_Msg_Timer->abort();
	delete Reset_Status_Msg_Timer, Reset_Status_Msg_Timer = NULL;
}

//Reset Status Msg after a predefined time (callback)
unsigned int Messages::Reset_Status_Msg(unsigned int interval, void *args)
{
	//reset the message
	Status_Msg = NULL;

	//end of timer
	return 0; 
}

//Display the status msg on the status bar
bool Messages::Show_Status_Msg(VideoSurface& Screen)
{
try {
	//Clean the status Bar
	Screen.fill( Color(0x00, 0x00, 0x00), Rect(0, CURRENT_SCREEN_HEIGHT - STATUS_BAR_H, CURRENT_SCREEN_WIDTH, STATUS_BAR_H) );
	
	if (Status_Msg != NULL) //when there is no msg to display like at the begining
		Screen.blit( *Status_Msg, Point::Point(5, CURRENT_SCREEN_HEIGHT - 30) );

	if ( has_status_msg_changed )
	{
		has_status_msg_changed = false; //the changed msg has been take care of
		Reset_Status_Msg_Timer->abort();
		Reset_Status_Msg_Timer->setCallback(this,&Messages::Reset_Status_Msg, (void*)NULL);
		Reset_Status_Msg_Timer->launch( RESET_STATUS_MSG_INTERVAL );
	}


	return true; //no error
} catch (...) {
	return false; //error occured
}
}
