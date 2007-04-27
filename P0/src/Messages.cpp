#include "Messages.hh"

Messages::Messages()
{
	status_msg = NULL;
}

Messages::~Messages()
{
	//reset the pointer (no need to delete coz no new)
	status_msg = NULL;
}

//Reset Status Msg after a predefined time (callback)
unsigned int Messages::Reset_Status_Msg(unsigned int interval, void *args)
{
	//reset the message
	status_msg = NULL;

	//end of timer
	return 0; 
}
