/*
Made by XorfacX
*/

/*
 * For comments regarding functions please see the header file.
 */

#include "guichan/sdlut/sdlutinput.hpp"

#include "guichan/exception.hpp"

namespace gcn
{
    SDLutInput::SDLutInput()
    {
        mMouseInWindow = true;
        mMouseDown = false;
    }

    bool SDLutInput::isKeyQueueEmpty()
    {
        return mKeyInputQueue.empty();
    }

    KeyInput SDLutInput::dequeueKeyInput()
    {
        KeyInput keyInput;

        if (mKeyInputQueue.empty())
        {
            throw GCN_EXCEPTION("The queue is empty.");
        }

        keyInput = mKeyInputQueue.front();
        mKeyInputQueue.pop();

        return keyInput;
    }

    bool SDLutInput::isMouseQueueEmpty()
    {
        return mMouseInputQueue.empty();
    }

    MouseInput SDLutInput::dequeueMouseInput()
    {
        MouseInput mouseInput;

        if (mMouseInputQueue.empty())
        {
            throw GCN_EXCEPTION("The queue is empty.");
        }

        mouseInput = mMouseInputQueue.front();
        mMouseInputQueue.pop();

        return mouseInput;
    }

    void SDLutInput::pushInput(SDLut::Event sdlut_event)
    {
        KeyInput keyInput;
        MouseInput mouseInput;

		SDLut::Keyboard::Sym* psdlut_sym = NULL;
		short state = 0;
		SDLut::Mouse::Button button;
		SDLut::Point mouse_position;
		bool motion_gain = false, motion_ActiveState = false, motion_InputFocusState = false, motion_MouseFocusState = false;
		

		if ( sdlut_event.getType() == SDLut::Event::str2Type( "KeyDown") )
		{
			sdlut_event.Set_KeyboardInfosFromEvent(*psdlut_sym, state);
			SDLut::Keyboard::Sym sdlut_sym = *psdlut_sym;

			keyInput.setKey(Key(convertKeyCharacter(sdlut_sym, false)));

			keyInput.setType(KeyInput::PRESSED);

			keyInput.setShiftPressed( ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("LShift") ) || ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("RShift") ) );

			keyInput.setControlPressed( ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("LCtrl") ) || ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("RCtrl") ) );

			keyInput.setAltPressed( ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("LAlt") ) || ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("RAlt") ) );

			keyInput.setMetaPressed( ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("Lmeta") ) || ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("RMeta") ) );

			keyInput.setNumericPad( ( sdlut_sym.getKey() >= SDLut::Keyboard::str2Key( "KKP0") ) && ( sdlut_sym.getKey() <= SDLut::Keyboard::str2Key( "KKPEQUALS") ) );
			
			mKeyInputQueue.push(keyInput);

		}
		else if ( sdlut_event.getType() == SDLut::Event::str2Type( "KeyUp") )
		{
			sdlut_event.Set_KeyboardInfosFromEvent(*psdlut_sym, state);
			RAGE::SDL::Keyboard::Sym sdlut_sym = *psdlut_sym;

			keyInput.setKey(Key(convertKeyCharacter(sdlut_sym, true )));
		
			keyInput.setType(KeyInput::RELEASED);

			keyInput.setShiftPressed( ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("LShift") ) || ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("RShift") ) );

			keyInput.setControlPressed( ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("LCtrl") ) || ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("RCtrl") ) );

			keyInput.setAltPressed( ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("LAlt") ) || ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("RAlt") ) );

			keyInput.setMetaPressed( ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("Lmeta") ) || ( sdlut_sym.getMod() == SDLut::Keyboard::str2Modifier("RMeta") ) );

			keyInput.setNumericPad( ( sdlut_sym.getKey() >= SDLut::Keyboard::str2Key( "KKP0") ) && ( sdlut_sym.getKey() <= SDLut::Keyboard::str2Key( "KKPEQUALS") ) );
			
			mKeyInputQueue.push(keyInput);

		}
		else if ( sdlut_event.getType() == SDLut::Event::str2Type( "MouseButtonDown") )
		{
			sdlut_event.Set_MouseButtonInfosFromEvent(button, mouse_position, state);

			mMouseDown = true;
			mouseInput.setX(mouse_position.getx());
			mouseInput.setY(mouse_position.gety());
			mouseInput.setButton(convertMouseButton(button));

			if ( button == SDLut::Mouse::str2Button( "WheelDown") )
			{
				mouseInput.setType(MouseInput::WHEEL_MOVED_DOWN);
			}
			else if ( button == SDLut::Mouse::str2Button( "WheelUp") )
			{
				mouseInput.setType(MouseInput::WHEEL_MOVED_UP);
			}
			else
			{
				mouseInput.setType(MouseInput::PRESSED);
			}
			mouseInput.setTimeStamp(SDLut::GetTicks());

			mMouseInputQueue.push(mouseInput);
		}
		else if ( sdlut_event.getType() == SDLut::Event::str2Type( "MouseButtonUp") )
		{
			sdlut_event.Set_MouseButtonInfosFromEvent(button, mouse_position, state);

			mMouseDown = false;
			mouseInput.setX(mouse_position.getx());
			mouseInput.setY(mouse_position.gety());
			mouseInput.setButton(convertMouseButton(button));
			mouseInput.setType(MouseInput::RELEASED);
			mouseInput.setTimeStamp(SDLut::GetTicks());

			mMouseInputQueue.push(mouseInput);
		}
		else if ( sdlut_event.getType() == SDLut::Event::str2Type( "MouseMotion") )
		{
			sdlut_event.Set_MouseMotionInfosFromEvent(mouse_position, state);

			mouseInput.setX(mouse_position.getx());
			mouseInput.setY(mouse_position.gety());
			mouseInput.setButton(MouseInput::EMPTY);
			mouseInput.setType(MouseInput::MOVED);
			mouseInput.setTimeStamp(SDLut::GetTicks());

			mMouseInputQueue.push(mouseInput);
		}
		else if ( sdlut_event.getType() == SDLut::Event::str2Type( "Active") )
		{
			sdlut_event.Set_ActiveInfosFromEvent(motion_ActiveState, motion_InputFocusState, motion_MouseFocusState, motion_gain);
			//
			// This occurs when the mouse leaves the window and the Gui-chan
			// application loses its mousefocus.
			//
			if ( motion_MouseFocusState && !motion_gain )
			{
				mMouseInWindow = false;

				if (!mMouseDown)
				{
					mouseInput.setX(-1);
					mouseInput.setY(-1);
					mouseInput.setButton(MouseInput::EMPTY);
					mouseInput.setType(MouseInput::MOVED);

					mMouseInputQueue.push(mouseInput);
				}
			}

			if ( motion_MouseFocusState && motion_gain )
			{
				mMouseInWindow = true;
			}
		}
		else { } //no other type in sdlut
    }

	void SDLutInput::pushInput(const SDLut::Keyboard::Sym& s, bool& pressed)
	{
		KeyInput keyInput;
        
		keyInput.setKey(Key(convertKeyCharacter(s, false)));

		if (pressed)
			keyInput.setType(KeyInput::PRESSED);
		else
			keyInput.setType(KeyInput::RELEASED);

		keyInput.setShiftPressed( ( s.getMod() == SDLut::Keyboard::str2Modifier("LShift") ) || ( s.getMod() == SDLut::Keyboard::str2Modifier("RShift") ) );

		keyInput.setControlPressed( ( s.getMod() == SDLut::Keyboard::str2Modifier("LCtrl") ) || ( s.getMod() == SDLut::Keyboard::str2Modifier("RCtrl") ) );

		keyInput.setAltPressed( ( s.getMod() == SDLut::Keyboard::str2Modifier("LAlt") ) || ( s.getMod() == SDLut::Keyboard::str2Modifier("RAlt") ) );

		keyInput.setMetaPressed( ( s.getMod() == SDLut::Keyboard::str2Modifier("Lmeta") ) || ( s.getMod() == SDLut::Keyboard::str2Modifier("RMeta") ) );

		keyInput.setNumericPad( ( s.getKey() >= SDLut::Keyboard::str2Key( "KKP0") ) && ( s.getKey() <= SDLut::Keyboard::str2Key( "KKPEQUALS") ) );
		
		mKeyInputQueue.push(keyInput);

	}

	void SDLutInput::pushInput(const SDLut::Mouse::Button& button, const unsigned int& x, const unsigned int& y, const bool& pressed)
	{
        MouseInput mouseInput;

		if ( pressed )
		{
			mMouseDown = true;
			mouseInput.setX(x);
			mouseInput.setY(y);
			mouseInput.setButton(convertMouseButton(button));

			if ( button == SDLut::Mouse::str2Button( "WheelDown") )
			{
				mouseInput.setType(MouseInput::WHEEL_MOVED_DOWN);
			}
			else if ( button == SDLut::Mouse::str2Button( "WheelUp") )
			{
				mouseInput.setType(MouseInput::WHEEL_MOVED_UP);
			}
			else
			{
				mouseInput.setType(MouseInput::PRESSED);
			}
			mouseInput.setTimeStamp(SDLut::GetTicks());

			mMouseInputQueue.push(mouseInput);
		}
		else 
		{
			mMouseDown = false;
			mouseInput.setX(x);
			mouseInput.setY(y);
			mouseInput.setButton(convertMouseButton(button));
			mouseInput.setType(MouseInput::RELEASED);
			mouseInput.setTimeStamp(SDLut::GetTicks());

			mMouseInputQueue.push(mouseInput);
		}
	}

	void SDLutInput::pushInput(const unsigned int& x, const unsigned int& y, const signed int& xrel, const signed int& yrel, const bool& button_pressed)
	{
        MouseInput mouseInput;

		mouseInput.setX(x);
		mouseInput.setY(y);
		mouseInput.setButton(MouseInput::EMPTY);
		mouseInput.setType(MouseInput::MOVED);
		mouseInput.setTimeStamp(SDLut::GetTicks());

		mMouseInputQueue.push(mouseInput);
	}

	int SDLutInput::convertMouseButton(SDLut::Mouse::Button sdlut_button)
    {
		if ( sdlut_button == SDLut::Mouse::str2Button( "Left") )
			return MouseInput::LEFT;
		else if ( sdlut_button == SDLut::Mouse::str2Button( "Right") )
			return MouseInput::RIGHT;
		else if ( sdlut_button == SDLut::Mouse::str2Button( "Middle") )
			return MouseInput::MIDDLE;
		else // We have an unknown mouse button type which is ignored (Wheel is passed as gcn::MouseType).
			 return sdlut_button;
    }

    int SDLutInput::convertKeyCharacter(SDLut::Keyboard::Sym sdlut_sym, bool KeyIsUp)
    {
		int value = 0;
		if ( sdlut_sym.getUnicode() < 255 )
			value = (int)sdlut_sym.getUnicode();

		if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KTAB") ) 
			value = Key::TAB;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KLALT") ) 
			value = Key::LEFT_ALT;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KRALT") ) 
			value = Key::RIGHT_ALT;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KLSHIFT") ) 
			value = Key::LEFT_SHIFT;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KRSHIFT") ) 
			value = Key::RIGHT_SHIFT;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KLCTRL") ) 
			value = Key::LEFT_CONTROL;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KRCTRL") ) 
			value = Key::RIGHT_CONTROL;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KBACKSPACE") ) 
			value = Key::BACKSPACE;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KPAUSE") )
			value = Key::PAUSE;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KSPACE") ) 
		{
			// Special characters like ~ (tilde) ends up
			// with the keysym.sym SDLK_SPACE which
			// without this check would be lost. The check
			// is only valid on key down events in SDL.
			if (KeyIsUp|| sdlut_sym.getUnicode() == ' ')
			{
				value = Key::SPACE;
			}
		}
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KESCAPE") ) 
			value = Key::ESCAPE;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KDELETE") ) 
			value = Key::DELETE;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KINSERT") ) 
			value = Key::INSERT;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KHOME") )
			value = Key::HOME;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KEND") ) 
			value = Key::END;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KPAGEUP") ) 
			value = Key::PAGE_UP;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KPRINTSCREEN") )
			value = Key::PRINT_SCREEN;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KPAGEDOWN") ) 
			value = Key::PAGE_DOWN;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF1") ) 
			value = Key::F1;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF2") ) 
			value = Key::F2;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF3") ) 
			value = Key::F3;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF4") ) 
			value = Key::F4;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF5") ) 
			value = Key::F5;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF6") ) 
			value = Key::F6;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF7") ) 
			value = Key::F7;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF8") ) 
			value = Key::F8;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF9") ) 
			value = Key::F9;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF10") ) 
			value = Key::F10;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF11") ) 
			value = Key::F11;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF12") ) 
			value = Key::F12;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF13") ) 
			value = Key::F13;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF14") ) 
			value = Key::F14;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KF15") ) 
			value = Key::F15;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KNUMLOCK") ) 
			value = Key::NUM_LOCK;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KCAPSLOCK") )
			value = Key::CAPS_LOCK;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KSCROLLOCK") ) 
			value = Key::SCROLL_LOCK;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KLMETA") )
			value = Key::LEFT_META;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KRMETA") ) 
			value = Key::RIGHT_META;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KLSUPER") ) 
			value = Key::LEFT_SUPER;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KLRUPER") ) 
			value = Key::RIGHT_SUPER;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KMODE") ) 
			value = Key::ALT_GR;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KUP") ) 
			value = Key::UP;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KDOWN") ) 
			value = Key::DOWN;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KLEFT") ) 
			value = Key::LEFT;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KRIGHT") ) 
			value = Key::RIGHT;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KRETURN") ) 
			value = Key::ENTER;
		else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KKPENTER") ) 
			value = Key::ENTER;
		else { }
		
		
		if ( !( sdlut_sym.getMod() & SDLut::Keyboard::str2Modifier("Num") ) )
		{
			if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KKP0") )
				value = Key::INSERT;
			else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KKP1") )
				value = Key::END;
            else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KKP2") )
                value = Key::DOWN;
			else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KKP3") )
				value = Key::PAGE_DOWN;
			else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KKP4") )
				value = Key::LEFT;
			else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KKP5") )
				value = 0;
			else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KKP6") )
				value = Key::RIGHT;
			else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KKP7") )
				value = Key::HOME;
			else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KKP8") )
				value = Key::UP;
			else if ( sdlut_sym.getKey() == SDLut::Keyboard::str2Key("KKP9") )
				value = Key::PAGE_UP;
			else {}
		}
        
        return value;
    }
}
