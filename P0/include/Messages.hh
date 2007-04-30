#ifndef Messages_HH
#define Messages_HH

#include "Base.hh"

class Messages
{
	friend class Player;

private:
	static RGBSurface *Status_Msg; //Will contains the msg displayed in the status bar
	static bool has_status_msg_changed; //tell to this class that his status msg has been changed by a friend class

	Timer<Messages>* Reset_Status_Msg_Timer; //msg resetter timer

	//Reset Status Msg after a predefined time (callback)
	unsigned int Reset_Status_Msg(unsigned int interval, void* args);

public:
	Messages();
	~Messages();

	//Display the status msg on the status bar
	bool Show_Status_Msg(VideoSurface& Screen);

};

#endif
