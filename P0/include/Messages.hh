#ifndef Messages_HH
#define Messages_HH

#include "Base.hh"

class Messages
{
	friend class Player;

private:
	RGBSurface *status_msg; //Will contains the msg displayed in the status bar

	//Reset Status Msg after a predefined time (callback)
	unsigned int Reset_Status_Msg(unsigned int interval, void* args);

public:
	Messages();
	~Messages();

};

#endif
