/*
Made by XorfacX
*/

#ifndef GCN_SDLutINPUT_HPP
#define GCN_SDLutINPUT_HPP

#include <queue>

#include "sdlutdepends.hpp"

#include "guichan/input.hpp"
#include "guichan/keyinput.hpp"
#include "guichan/mouseinput.hpp"
#include "guichan/platform.hpp"

namespace gcn
{
class Key;

/**
 * SDLut implementation of Input.
 */
class GCN_EXTENSION_DECLSPEC SDLutInput : public Input
{
public:

    /**
     * Constructor.
     */
    SDLutInput();

    /**
     * Pushes an Event. It should be called at least once per frame to
     * update input with user input.
     *
     * @param sdlut_event an event from SDLut.
     */
	virtual void pushInput(system::Event sdlut_event);

    /**
     * Pushes a KeyInput. It should be called at least once per frame to
     * update input with user input.
     *
     * @param s, a sdlut KeySym.
     * @param pressed, tell if key is pressed.
     */
	void pushInput(const input::Keyboard::Sym& s, bool& pressed);

    /**
     * Pushes a MouseInput. It should be called at least once per frame to
     * update input with mouse input.
     *
     * @param button, a sdlut Mouse::Button.
     * @x & y, coordinate of the button.
     * @pressed, tell if button is pressed.
     */
	void pushInput(const input::Mouse::Button& button, const unsigned int& x, const unsigned int& y, const bool& pressed);

    /**
     * Pushes a MouseInput. It should be called at least once per frame to
     * update input with mouse motion.
     *
     * @x & y, coordinate of the button.
     * @xrel & yrel, relative motions in the X & Y directions.
     * @button_pressed, tell if button is pressed during motion.
     */
    void pushInput(const unsigned int& x, const unsigned int& y, const signed int& xrel, const signed int& yrel, const bool& button_pressed);


    /**
    * Polls all input. It exists for input driver compatibility. If you
    * only use SDLut and plan sticking with SDLut you can safely ignore this
    * function as it in the SDLut case does nothing.
    */
    virtual void _pollInput() { }


    // Inherited from Input

    virtual bool isKeyQueueEmpty();

    virtual KeyInput dequeueKeyInput();

    virtual bool isMouseQueueEmpty();

    virtual MouseInput dequeueMouseInput();

protected:
    /**
     * Converts a mouse button from SDLut to a Guichan mouse button
     * representation.
     *
     * @param button an SDLut mouse button.
     * @return a Guichan mouse button.
     */
    int convertMouseButton(input::Mouse::Button sdlut_button);

    /**
     * Converts an SDLut key to a key value.
     *
     * @param s, a sdlut KeySym.
     * @param KeyIsUp, tell if key is released.
     * @return a key value.
     * @see Key
     */
    int convertKeyCharacter(input::Keyboard::Sym sdlut_sym, bool KeyIsUp);

    std::queue<KeyInput> mKeyInputQueue;
    std::queue<MouseInput> mMouseInputQueue;

    bool mMouseDown;
    bool mMouseInWindow;
};
}

#endif // end GCN_SDLutINPUT_HPP
