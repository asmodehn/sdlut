#include "SDLCriticalEvent.hh"
#include "SDLEventManager.hh" //to access the general handler
#include "SDLKeyboard.hh" //to access the keyboard handler
#include "SDLMouse.hh"//to access the mouse handler

namespace SDL {



CriticalEvent::CriticalEvent(EventType type) : _event()
{
    //syntax to put in the constructor call to get rid of the warning ?
    _event.type=type;
}

bool CriticalEvent::push()
{
	return SDL_PushEvent(&_event) == 0;
}

int CriticalEvent::push(int number)
{
    int cur = 0;
    SDL_Event eventTab[number];
    while ( cur < number )
    {
        eventTab[cur] = _event;
        //maybe some arithmetic on pointer can improve that ?
    }
	return SDL_PeepEvents(eventTab, number, SDL_ADDEVENT, _event.type);
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



EventType CriticalEvent::getType()
{
    return static_cast<EventType>(_event.type);
}



bool CriticalEvent::callHandler(GeneralHandler & ghndlr, KeyboardHandler & khndlr, MouseHandler&  mhndlr )
{

    bool ev_handled = false;
		switch(_event.type) {
			case SDL_ACTIVEEVENT:
				ev_handled = ghndlr.handleActiveEvent(_event.active.gain == 1, _event.active.state);
				break;
			case SDL_KEYDOWN:
				ev_handled = khndlr.handleKeyPressEvent(_event.key.keysym);
				break;
			case SDL_KEYUP:
				ev_handled = khndlr.handleKeyReleaseEvent(_event.key.keysym);
				break;
			case SDL_MOUSEMOTION:
				ev_handled = mhndlr.handleMouseMotionEvent(_event.motion.state, _event.motion.x, _event.motion.y, _event.motion.xrel, _event.motion.yrel);
				break;
			case SDL_MOUSEBUTTONDOWN:
				ev_handled = mhndlr.handleMouseButtonPressEvent(_event.button.button, _event.button.x, _event.button.y);
				break;
			case SDL_MOUSEBUTTONUP:
				ev_handled = mhndlr.handleMouseButtonReleaseEvent(_event.button.button, _event.button.x, _event.button.y);
				break;
//			case SDL_JOYAXISMOTION:
//				ev_handled = jhndlr.handleJoyAxisEvent(_event.jaxis.which, _event.jaxis.axis, _event.jaxis.value);
//				break;
//			case SDL_JOYBALLMOTION:
//				ev_handled = jhndlr.handleJoyBallEvent(_event.jball.which, _event.jball.ball, _event.jball.xrel, _event.jball.yrel);
//				break;
//			case SDL_JOYHATMOTION:
//				ev_handled = jhndlr.handleJoyHatEvent(_event.jhat.which, _event.jhat.hat, _event.jhat.value);
//				break;
//			case SDL_JOYBUTTONDOWN:
//				ev_handled = jhndlr.handleJoyButtonPressEvent(_event.jbutton.which, _event.jbutton.button);
//				break;
//			case SDL_JOYBUTTONUP:
//				ev_handled = jhndlr.handleJoyButtonReleaseEvent(_event.jbutton.which, _event.jbutton.button);
//				break;
            case SDL_USEREVENT:
				ev_handled = ghndlr.handleUserEvent(_event.user.type, _event.user.code,_event.user.data1, _event.user.data2);
				break;
		}
        return ev_handled;
}



}

