#include "SDLEvent.hh"
#include "SDLEventManager.hh" //to access the general handler
#include "SDLKeyboard.hh" //to access the keyboard handler
#include "SDLMouse.hh"//to access the mouse handler
#include "SDLApp.hh"//to access the joystick handler
#include "SDLConfig.hh"


namespace RAGE{
    namespace SDL {

	    std::map<short,Event::Type> Event::EventTypesdl2rage;
	    std::map<std::string,Event::Type> Event::EventTypestr2rage;

	    //based on the fact that Rage's enum map to in [0..number-1]. This way the vector is easily built
	    std::vector<short> Event::InitEventMapping()
	    {
		    std::vector<short> result;
		    std::map<Event::Type,SDL_EventType> EventTyperage2sdlmap;

		//using a max here to support partial mapping list...
		    int maxvecindex =0;
		
#define ASSOCIATE( key, sdlkey, strkey ) EventTyperage2sdlmap[key] = sdlkey; EventTypesdl2rage[sdlkey] = key; EventTypestr2rage[strkey] = key; maxvecindex = (maxvecindex>key)? maxvecindex : key;
#include "SDLEventMapping.inl"
#undef ASSOCIATE

{
	result.resize(maxvecindex+1, SDLK_UNKNOWN);

	std::map<Event::Type, SDL_EventType>::iterator it = EventTyperage2sdlmap.begin();
	std::map<Event::Type, SDL_EventType>::iterator itEnd = EventTyperage2sdlmap.end();
	for (; it != itEnd; ++it)
	{
		assert((*it).first >= 0 && (*it).first < result.size());
		result[(*it).first] = (*it).second;
	}
}
	    }

	    std::vector<short> Event::EventTyperage2sdl = InitEventMapping();
	    
	    
	    short Event::Type2sdl(Event::Type b)
{
	return EventTyperage2sdl[b];
}
	    Event::Type Event::sdl2Type(short sdlb)
{
	return EventTypesdl2rage[sdlb];
}
		Event::Type Event::str2Type(std::string strt)
{
	return EventTypestr2rage[strt];
}

Event::Event(Event::Type type) : _event()
{
    //syntax to put in the constructor call to get rid of the warning ?
	_event->type=type;
}


Event::~Event()
{
}

bool Event::push()
{
	return SDL_PushEvent(_event) == 0;
}

int Event::push(int number)
{
	int cur = 0;
	SDL_Event * eventTab = new SDL_Event[number];
	while ( cur < number )
	{
		eventTab[cur] = *_event;
        //maybe some arithmetic on pointer can improve that ? ( all pointers to the same event instead of copy the event everywhere ? )
	}
	return SDL_PeepEvents(eventTab, number, SDL_ADDEVENT, _event->type);
}


// VECTOR CANT OPERATE ON OBJECTS WITH NON STATIC REFERENCE MEMBER I BELIEVE
//NEED TO DO THT SOMEHOW DIFFERENT
////Peek number of currently pending event of the same type. (not removed from the queue)
//std::vector<CriticalEvent> CriticalEvent::peek(int number)
//{
//    int cur = 0;
//    std::vector<CriticalEvent> res;
//    SDL_Event eventTab[number];
//	number= SDL_PeepEvents(eventTab, number, SDL_PEEKEVENT, _event.type);
//    res.reserve(number);
//    while ( cur < number )
//    {
//        CriticalEvent cev(eventTab[cur]);
//         res.push_back(cev);
//    };
//    return res;
//}
//
////Get number of currently pending event of the same type. (removed from the queue)
//std::vector<CriticalEvent> CriticalEvent::get(int number)
//{
//    int cur = 0;
//    std::vector<CriticalEvent> res;
//    SDL_Event eventTab[number];
//	number= SDL_PeepEvents(eventTab, number, SDL_GETEVENT, _event.type);
//    res.reserve(number);
//    while ( cur < number )
//    {
//         res.push_back(CriticalEvent(eventTab[cur]));
//    };
//    return res;
//}



Event::Type Event::getType()
{
	return sdl2Type(_event->type);
}

bool Event::callHandler(GeneralHandler * ghndlr, Keyboard * khndlr, Mouse*  mhndlr )
{

    bool ev_handled = false;
		switch(_event->type) {
			case SDL_ACTIVEEVENT:
				ev_handled = ghndlr->handleActiveEvent(_event->active.gain == 1, (_event->active.state & SDL_APPACTIVE) == SDL_APPACTIVE, (_event->active.state & SDL_APPINPUTFOCUS) == SDL_APPINPUTFOCUS, (_event->active.state & SDL_APPMOUSEFOCUS) == SDL_APPMOUSEFOCUS );
				break;
			case SDL_KEYDOWN:
				ev_handled = khndlr == NULL ? false : khndlr->handleKeyPressEvent(static_cast<Keyboard::Sym>(_event->key.keysym));
				break;
			case SDL_KEYUP:
				ev_handled = khndlr == NULL ? false : khndlr->handleKeyReleaseEvent(static_cast<Keyboard::Sym>(_event->key.keysym));
				break;
			case SDL_MOUSEMOTION:
				ev_handled = mhndlr->handleMouseMotionEvent( (_event->motion.state == SDL_PRESSED) , _event->motion.x, _event->motion.y, _event->motion.xrel, _event->motion.yrel);
				break;
			case SDL_MOUSEBUTTONDOWN:
				ev_handled = mhndlr->handleMouseButtonPressEvent(Mouse::sdl2Button(_event->button.button), _event->button.x, _event->button.y);
				break;
			case SDL_MOUSEBUTTONUP:
				ev_handled = mhndlr->handleMouseButtonReleaseEvent(Mouse::sdl2Button(_event->button.button), _event->button.x, _event->button.y);
				break;
			case SDL_JOYAXISMOTION:
                assert(App::getInstance().getJoystickPool()); //just to make sure but if we get an event, that means joystick has been initialized and therefore we should be able to get the pool
				ev_handled = App::getInstance().getJoystickPool()->handleJoyAxisEvent(_event->jaxis.which, _event->jaxis.axis, _event->jaxis.value);
				break;
			case SDL_JOYBALLMOTION:
			assert(App::getInstance().getJoystickPool()); //just to make sure but if we get an event, that means joystick has been initialized and therefore we should be able to get the jpool
				ev_handled = App::getInstance().getJoystickPool()->handleJoyBallEvent(_event->jball.which, _event->jball.ball, _event->jball.xrel, _event->jball.yrel);
				break;
			case SDL_JOYHATMOTION:
			assert(App::getInstance().getJoystickPool()); //just to make sure but if we get an event, that means joystick has been initialized and therefore we should be able to get the jpool
			ev_handled = App::getInstance().getJoystickPool()->handleJoyHatEvent(_event->jhat.which, Joystick::sdl2JoyHat(_event->jhat.hat), _event->jhat.value);
				break;
			case SDL_JOYBUTTONDOWN:
			assert(App::getInstance().getJoystickPool()); //just to make sure but if we get an event, that means joystick has been initialized and therefore we should be able to get the jpool
				ev_handled = App::getInstance().getJoystickPool()->handleJoyButtonPressEvent(_event->jbutton.which, _event->jbutton.button);
				break;
			case SDL_JOYBUTTONUP:
			assert(App::getInstance().getJoystickPool()); //just to make sure but if we get an event, that means joystick has been initialized and therefore we should be able to get the jpool
				ev_handled = App::getInstance().getJoystickPool()->handleJoyButtonReleaseEvent(_event->jbutton.which, _event->jbutton.button);
				break;

            case SDL_USEREVENT:
		    ev_handled = ghndlr->handleUserEvent(sdl2Type(_event->user.type), _event->user.code,_event->user.data1, _event->user.data2);
				break;
            case SDL_QUIT:
				ev_handled = ghndlr->handleQuitEvent();
				break;
			case SDL_SYSWMEVENT:
				ev_handled = ghndlr->handleSysWMEvent();
				break;
			case SDL_VIDEORESIZE:
				ev_handled = ghndlr->handleResizeEvent(_event->resize.w, _event->resize.h);
				break;
            case SDL_VIDEOEXPOSE:
				ev_handled = ghndlr->handleExposeEvent();
				break;
		}
        return ev_handled;
}

Logger & operator << (Logger & log, const  Event::Type & type)
{ 
	switch (type)
	{
		case Event::Active : log << "Active"; break;
		case Event::KeyDown : log << "KeyDown"; break;
		case Event::KeyUp : log << "KeyUp"; break;
		case Event::MouseMotion : log << "MouseMotion"; break;
		case Event::MouseButtonDown: log << "MouseButtonDown"; break;
		case Event::MouseButtonUp : log << "MouseButtonUp"; break;
		case Event::JoyAxis : log << "JoyAxis"; break;
		case Event::JoyBall : log << "JoyBall"; break;
		case Event::JoyHat : log << "JoyHat"; break;
		case Event::JoyButtonDown : log << "JoyButtonDown"; break;
		case Event::JoyButtonUp : log << "JoyButtonUp"; break;
		case Event::User : log << "User"; break;
		case Event::Quit : log << "Quit"; break;
		case Event::SysWM : log << "SysWM"; break;
		case Event::Resize : log << "Resize"; break;
		case Event::Expose : log << "Expose"; break;
	}
	return log;
}


}
}
