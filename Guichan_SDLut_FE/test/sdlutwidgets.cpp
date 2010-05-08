// Include all necessary headers.
#include <iostream>
#include <guichan.hpp>
#include <guichan/sdlut.hpp>
#include "SDL.hh"

namespace globals
{
gcn::Gui* gui;
}
#include "widgets.hpp"

using namespace globals;

gcn::SDLutInput* mySDLutInput;             // Input driver
gcn::SDLutGraphics* graphics;       // Graphics driver
gcn::SDLutImageLoader* imageLoader; // For loading images
gcn::Font* myfont;

Logger logger("Example"); //prefix

//Defining UserInput
class KeyboardInput : public input::TextInput
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
                App::getInstance().getDisplay().requestSize(640, 480);
                App::getInstance().getDisplay().requestBPP(App::getInstance().getDisplay().getRequestedBPP());
                App::getInstance().getDisplay().requestFullscreen(!App::getInstance().getDisplay().getScreenBuffer().getScreenInfo().isFullscreen());
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

void init(bool ogl = true)
{
    logger.enableFileLog("Example.Log");

    App::getInstance().setName("Example");

    if (! App::getInstance().initVideo(false, true, false) )
        throw std::logic_error( "Init Video Failed: " + GetError() );

    if (! App::getInstance().initText())
        throw std::logic_error( "TTF Init Failed: " + GetError() );

    App::getInstance().getDisplay().requestOpenGL(ogl);
    App::getInstance().getDisplay().requestSize(640, 480);
    App::getInstance().getDisplay().requestBPP(32);
}

void implement(std::string fontfile = "" )
{

//GuiChan SDLuT Stuff
    imageLoader = new gcn::SDLutImageLoader();

    graphics = new gcn::SDLutGraphics();

//Gui Initialization
    gui = new gcn::Gui();
    gcn::Image::setImageLoader(imageLoader);
    gui->setGraphics(graphics);

    mySDLutInput = new gcn::SDLutInput();
    gui->setInput(mySDLutInput);

    widgets::init();

    if (fontfile != "")
    {
        myfont = new gcn::SDLutFont(fontfile, 13, font::Font::Solid );
        delete widgets::font, widgets::font = NULL;
        // The global font is static and must be set.
        gcn::Widget::setGlobalFont(myfont);
    }

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
    delete globals::gui, globals::gui = NULL;
    delete myfont, myfont = NULL;

    widgets::halt();
    if (widgets::image != NULL)
        delete widgets::image, widgets::image = NULL;

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
        std::string fontfile = "";



        if (argc > 1)
        {
            if ( std::string(argv[1]) == "nogl" )
            {
                init(false);
                if (argc > 2)
                {
                    fontfile = std::string(argv[2]);
                }
            }
            else
            {
                init();
                fontfile = std::string(argv[1]);
            }
        }

        implement(fontfile);

        if (App::getInstance().getDisplay().show())
        {
            App::getInstance().getDisplay().mainLoop(100,100);
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
