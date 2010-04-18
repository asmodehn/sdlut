// Include all necessary headers.
#include <iostream>
#include <sstream>         // Used for int to string conversion
#include <guichan.hpp>
#include <guichan/sdlut.hpp>
#include "SDL.hh"

namespace globals
{
gcn::Gui* gui;
}
#include "action.hpp"

using namespace globals;

gcn::SDLutInput* mySDLutInput;             // Input driver
gcn::SDLutGraphics* graphics;       // Graphics driver
gcn::SDLutImageLoader* imageLoader; // For loading images

Logger logger("Example"); //prefix

//Defining UserInput
class KeyboardInput : public input::Keyboard
{
public:

    bool handleKeyEvent (const Sym &s, bool pressed)
    {
        bool res = false;
        switch ( s.getKey() )
        {
        case Key_Escape: //Quit
            if (!pressed)
            {
                logger << nl << "Quit requested !" << std::endl;
                App::getInstance().requestTermination();
                res=true;
            }
            break;

        case Key_F5: //iconify
            if (pressed)
                App::getInstance().getDisplay().getWindow().iconify();
            res = true;
            break;

        case Key_F6: //FullScreen
            if (pressed)
            {
                App::getInstance().getDisplay().getScreenRequest().requestSize(640, 480);
				App::getInstance().getDisplay().getScreenRequest().requestBPP(App::getInstance().getDisplay().getScreenRequest().getRequestedBPP());
                App::getInstance().getDisplay().getScreenRequest().requestFullscreen(!App::getInstance().getDisplay().getScreenRequest().isFullscreen());
            }
            res = true;
            break;

        default:
            res = false;
        }

        /*
         * Now that we are done polling and using SDLut events we pass
         * the leftovers to the SDLutInput object to later be handled by
         * the Gui. (This example doesn't require us to do this coz there
         * is nothing to handle key input but will do it anyway to show
         * how to set up an SDLut application with Guichan.)
        */
        if (!res)
        {
            mySDLutInput->pushInput(s, pressed);
            res = true;
        }

        return res;
    }
};

//Defining Mouse Input
class MouseInput : public input::Mouse
{
public:

    bool handleMouseButtonEvent (Button button, unsigned int x, unsigned int y, bool pressed)
    {
        bool res = false;

        if (!res)
        {
            mySDLutInput->pushInput(button, x, y, pressed);
            res = true;
        }

        return res;
    }

    bool handleMouseMotionEvent (bool button_pressed, unsigned int x, unsigned int y, signed int xrel, signed int yrel)
    {
        bool res = false;

        if (!res)
        {
            mySDLutInput->pushInput(x, y, xrel, yrel, button_pressed);
            res = true;
        }

        return res;
    }

};

class RenderEngine
{

public:

    RenderEngine() {}

    virtual ~RenderEngine() {}

    bool init(int width, int height)
    {

        return true;
    }

    bool resize(int width, int height)
    {
        gui->getTop()->setDimension(gcn::Rectangle(0, 0, width, height));
        return true;
    }

    bool prerender( unsigned long framerate, unsigned long deltaticks)
    {
        //Check Gui Logic
        gui->logic();

        return true;
    }

    bool render(video::ScreenBuffer& screen) const
    {
        // Set the target for the graphics object to be the screen.
        // In other words, we will draw to the screen.
        graphics->setTarget(&screen);

        //Draw The Gui
        gui->draw();

        return true;
    }
};

KeyboardInput* myKeyboardInput = NULL;
MouseInput* myMouseInput = NULL;
RenderEngine myEngine;

void init(bool ogl = false)
{
    logger.enableFileLog("Example.Log");

    App::getInstance().setName("Example");

    if (! App::getInstance().initVideo(false, true, false) )
        throw std::logic_error( "Init Video Failed: " + GetError() );

    App::getInstance().getDisplay().getScreenRequest().requestOpenGL(ogl);
	App::getInstance().getDisplay().getScreenRequest().requestSize(640, 480);
	App::getInstance().getDisplay().getScreenRequest().requestBPP(32);
}

void implement()
{
//GuiChan SDLuT Stuff
    imageLoader = new gcn::SDLutImageLoader();

    graphics = new gcn::SDLutGraphics();

//Gui Initialization
    gui = new gcn::Gui();
    gcn::Image::setImageLoader(imageLoader);
    gui->setGraphics(graphics); /*SDLuTGraphics*/

    mySDLutInput = new gcn::SDLutInput();
    gui->setInput(mySDLutInput);

    action::init();

//SDLuT Stuff
    myKeyboardInput = new KeyboardInput();
    App::getInstance().getDisplay().getEventManager().setKeyboard(myKeyboardInput);

    myMouseInput = new MouseInput();
    App::getInstance().getDisplay().getEventManager().setMouse(myMouseInput);

    App::getInstance().getDisplay().resetInitCallback(myEngine,&RenderEngine::init);
    App::getInstance().getDisplay().resetResizeCallback(myEngine,&RenderEngine::resize);
    App::getInstance().getDisplay().resetNewFrameCallback(myEngine,&RenderEngine::prerender);
    App::getInstance().getDisplay().resetRenderCallback(myEngine,&RenderEngine::render);

}

void clean()
{
    action::halt();
    delete gui, gui = NULL;

    delete mySDLutInput, mySDLutInput = NULL;
    delete graphics, graphics = NULL;
    delete imageLoader, imageLoader = NULL;

    delete myKeyboardInput, myKeyboardInput = NULL;
    delete myMouseInput, myMouseInput = NULL;
}

int main(int argc, char **argv)
{
    try
    {
#ifdef WK_OPENGL_FOUND
        bool ogl = true;
        if (argc > 1 && std::string(argv[1]) == "nogl" ) ogl = false;
#else
        bool ogl = false;
#endif
        init(ogl);
        implement();


        if (App::getInstance().getDisplay().show())
        {
            App::getInstance().getDisplay().mainLoop();
        }

        clean();
    }
    catch (gcn::Exception e)
    {
        logger << nl << e.getMessage() << std::endl;
        system::Delay(2000);
        return 1;
    }
    catch (std::exception exc)
    {
        logger << nl << exc.what() << std::endl;
        system::Delay(2000);
        return 1;
    }
    catch (...)
    {
        logger << nl << "Unknown exception" << std::endl;
        system::Delay(2000);
        return 1;
    }

    return 0;
}
