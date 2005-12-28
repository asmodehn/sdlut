#include "SDLEvent.hh"
#include "SDLEventManager.hh" //to access the general handler
#include "SDLKeyboard.hh" //to access the keyboard handler
#include "SDLMouse.hh"//to access the mouse handler
#include "SDLJoystick.hh"//to access the joystick handler
namespace SDL
{

bool Event::callHandler(GeneralHandler * ghndlr, KeyboardHandler * khndlr, MouseHandler*  mhndlr, JoystickHandler*  jhndlr  )
{

    bool ev_handled = false;
		switch(_event->type) {
			case SDL_ACTIVEEVENT:
				ev_handled = ghndlr->handleActiveEvent(_event->active.gain == 1, _event->active.state);
				break;
			case SDL_KEYDOWN:
				ev_handled = khndlr->handleKeyPressEvent(_event->key.keysym);
				break;
			case SDL_KEYUP:
				ev_handled = khndlr->handleKeyReleaseEvent(_event->key.keysym);
				break;
			case SDL_MOUSEMOTION:
				ev_handled = mhndlr->handleMouseMotionEvent(_event->motion.state, _event->motion.x, _event->motion.y, _event->motion.xrel, _event->motion.yrel);
				break;
			case SDL_MOUSEBUTTONDOWN:
				ev_handled = mhndlr->handleMouseButtonPressEvent(_event->button.button, _event->button.x, _event->button.y);
				break;
			case SDL_MOUSEBUTTONUP:
				ev_handled = mhndlr->handleMouseButtonReleaseEvent(_event->button.button, _event->button.x, _event->button.y);
				break;
			case SDL_JOYAXISMOTION:
				ev_handled = jhndlr->handleJoyAxisEvent(_event->jaxis.which, _event->jaxis.axis, _event->jaxis.value);
				break;
			case SDL_JOYBALLMOTION:
				ev_handled = jhndlr->handleJoyBallEvent(_event->jball.which, _event->jball.ball, _event->jball.xrel, _event->jball.yrel);
				break;
			case SDL_JOYHATMOTION:
				ev_handled = jhndlr->handleJoyHatEvent(_event->jhat.which, _event->jhat.hat, _event->jhat.value);
				break;
			case SDL_JOYBUTTONDOWN:
				ev_handled = jhndlr->handleJoyButtonPressEvent(_event->jbutton.which, _event->jbutton.button);
				break;
			case SDL_JOYBUTTONUP:
				ev_handled = jhndlr->handleJoyButtonReleaseEvent(_event->jbutton.which, _event->jbutton.button);
				break;
            case SDL_USEREVENT:
				ev_handled = ghndlr->handleUserEvent(_event->user.type, _event->user.code,_event->user.data1, _event->user.data2);
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

}
